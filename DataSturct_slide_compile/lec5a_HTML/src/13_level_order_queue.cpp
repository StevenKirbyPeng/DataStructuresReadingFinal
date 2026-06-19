
#include "svg_helper.h"

struct NodeInfo{string id,label;int x,y;};
struct EdgeInfo{string a,b;};

static string renderTree(const vector<NodeInfo>& nodes,const vector<EdgeInfo>& edges,const set<string>& hot,const set<string>& ok=set<string>()){
    string s; map<string,pair<int,int>> p; map<string,string> lab; for(auto &n:nodes){p[n.id]={n.x,n.y}; lab[n.id]=n.label;}
    for(auto &e:edges){ string cls=(hot.count(e.a+"-"+e.b)||hot.count(e.b+"-"+e.a))?"red":"edge"; s+=line(p[e.a].first,p[e.a].second+24,p[e.b].first,p[e.b].second-24,cls);}
    for(auto &n:nodes){ string cls=hot.count(n.id)?"hot":(ok.count(n.id)?"ok":"box"); s+=circle(n.x,n.y,n.label,cls);}
    return s;
}

static string renderArray(const vector<string>& vals,int hotIndex){
    string s; for(int i=0;i<(int)vals.size();++i){ s+=arrCell(110+i*64,560,i,vals[i], i==hotIndex?"hot":(i==0?"null":"box")); } return s;
}

static void saveFrame(const string& folder,int step,int total,const string& title,const string& caption,const string& body){
    mkdirOutput("output/"+folder);
    string s=startSVG(1120,700,title); s+=drawStepBadge(step,total,caption); s+=body; s+=endSVG(); writeFile(stepFile(folder,step),s);
}

int main(){
    const string folder="13_level_order_queue_steps";
    const string title="13 Level Order Queue Step by Step";
    vector<string> caps = {"enqueue root A","dequeue A visit, enqueue B C","dequeue B, enqueue D E","dequeue C, enqueue F G","dequeue D","dequeue E","dequeue F","dequeue G","level order complete"};
    int total=(int)caps.size();
    vector<NodeInfo> nodes = {{"A","A",550,130},{"B","B",370,260},{"C","C",730,260},{"D","D",280,390},{"E","E",460,390},{"F","F",640,390},{"G","G",820,390}};
    vector<EdgeInfo> edges = {{"A","B"},{"A","C"},{"B","D"},{"B","E"},{"C","F"},{"C","G"}};
    vector<set<string>> hot(total);
    hot[0].insert("A");
    hot[1].insert("B");
    hot[1].insert("A");
    hot[1].insert("C");
    hot[2].insert("B");
    hot[2].insert("D");
    hot[2].insert("E");
    hot[3].insert("G");
    hot[3].insert("C");
    hot[3].insert("F");
    hot[4].insert("D");
    hot[5].insert("E");
    hot[6].insert("F");
    hot[7].insert("G");
    for(int i=0;i<total;i++){
        string body;
        body+=renderTree(nodes,edges,hot[i]); vector<string> qv={"A","B","C","D","E","F","G"}; for(int k=0;k<7;k++)body+=rect(165+k*105,560,90,45,(k==i?"hot":"box"),qv[k]); body+=text(170,640,"Queue visits nodes by level, from left to right.");
        saveFrame(folder,i+1,total,title,caps[i],body);
    }
}
