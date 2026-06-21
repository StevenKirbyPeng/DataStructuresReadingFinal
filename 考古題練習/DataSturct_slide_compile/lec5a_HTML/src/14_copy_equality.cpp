
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
    const string folder="14_copy_equality_steps";
    const string title="14 Copy and Equality Step by Step";
    vector<string> caps = {"Copy(NULL) returns NULL","copy root A","copy left subtree B","copy D and E","copy right subtree C","equality checks data","equality checks structure","both recursive results must be true"};
    int total=(int)caps.size();
    vector<NodeInfo> nodes = {{"A","A",550,130},{"B","B",370,260},{"C","C",730,260},{"D","D",280,390},{"E","E",460,390},{"F","F",640,390},{"G","G",820,390}};
    vector<EdgeInfo> edges = {{"A","B"},{"A","C"},{"B","D"},{"B","E"},{"C","F"},{"C","G"}};
    vector<set<string>> hot(total);
    hot[1].insert("A");
    hot[2].insert("B");
    hot[3].insert("D");
    hot[3].insert("E");
    hot[4].insert("G");
    hot[4].insert("C");
    hot[4].insert("F");
    hot[5].insert("A");
    hot[6].insert("A");
    hot[6].insert("G");
    hot[6].insert("C");
    hot[6].insert("B");
    hot[6].insert("D");
    hot[6].insert("E");
    hot[6].insert("F");
    for(int i=0;i<total;i++){
        string body;
        body+=renderTree(nodes,edges,hot[i]); body+=line(560,520,720,520,"ptr"); body+=text(600,500,"Copy / Equal recursion"); body+=rect(720,560,320,50,"note","Copy uses preorder creation; Equal uses paired recursion.");
        saveFrame(folder,i+1,total,title,caps[i],body);
    }
}
