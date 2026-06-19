
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
    const string folder="07_binary_tree_node_formulas_steps";
    const string title="07 Binary Tree Formulas Step by Step";
    vector<string> caps = {"level 1 has 1 node","level 2 has 2 nodes","level 3 has 4 nodes","level i has at most 2^(i-1)","depth k total is 2^k - 1","minimum depth ceil(log2(n+1))","maximum depth n","leaf relation n0 = n2 + 1"};
    int total=(int)caps.size();
    vector<NodeInfo> nodes = {};
    vector<EdgeInfo> edges = {};
    vector<set<string>> hot(total);
    
    for(int i=0;i<total;i++){
        string body;
        for(int level=1;level<=4;level++){int cnt=1<<(level-1);int y=120+level*80;int start=560-(cnt-1)*40;for(int j=0;j<cnt;j++)body+=circle(start+j*80,y,to_string(j+1),(i==level-1?"hot":"box"),18);body+=text(90,y+5,"Level "+to_string(level)+": max 2^"+to_string(level-1));} vector<string> notes={"1","2","4","2^(i-1)","1+2+...+2^(k-1)=2^k-1","best case is complete-like","worst case is skewed","full binary tree leaves = degree-2 nodes + 1"}; body+=rect(650,170,360,240,"note",notes[i]);
        saveFrame(folder,i+1,total,title,caps[i],body);
    }
}
