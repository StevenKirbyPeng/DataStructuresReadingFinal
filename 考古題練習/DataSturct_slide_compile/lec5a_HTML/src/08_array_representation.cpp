
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
    const string folder="08_array_representation_steps";
    const string title="08 Array Representation Step by Step";
    vector<string> caps = {"reserve index 0 empty","put root at index 1","left child goes 2i","right child goes 2i+1","B children at 4 and 5","C children at 6 and 7","D children at 8 and 9","parent index is floor(i/2)","works best for complete tree","final array mapping"};
    int total=(int)caps.size();
    vector<NodeInfo> nodes = {{"A","A",550,130},{"B","B",370,260},{"C","C",730,260},{"D","D",280,390},{"E","E",460,390},{"F","F",640,390},{"G","G",820,390}};
    vector<EdgeInfo> edges = {{"A","B"},{"A","C"},{"B","D"},{"B","E"},{"C","F"},{"C","G"}};
    vector<set<string>> hot(total);
    hot[0].insert("A");
    hot[1].insert("A");
    hot[2].insert("B");
    hot[2].insert("A");
    hot[2].insert("A-B");
    hot[3].insert("A");
    hot[3].insert("C");
    hot[3].insert("A-C");
    hot[4].insert("B");
    hot[4].insert("D");
    hot[4].insert("E");
    hot[5].insert("G");
    hot[5].insert("C");
    hot[5].insert("F");
    hot[6].insert("D");
    hot[7].insert("E");
    hot[8].insert("A");
    hot[8].insert("G");
    hot[8].insert("C");
    hot[8].insert("B");
    hot[8].insert("D");
    hot[8].insert("E");
    hot[8].insert("F");
    for(int i=0;i<total;i++){
        string body;
        body+=renderTree(nodes,edges,hot[i]); vector<string> vals={"-","A","B","C","D","E","F","G","H","I"}; int hi=min(i,9); body+=renderArray(vals,hi); body+=rect(760,560,300,55,"note","parent=i/2; left=2i; right=2i+1");
        saveFrame(folder,i+1,total,title,caps[i],body);
    }
}
