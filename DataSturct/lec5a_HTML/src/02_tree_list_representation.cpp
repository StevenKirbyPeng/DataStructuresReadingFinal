
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
    const string folder="02_tree_list_representation_steps";
    const string title="02 Tree List Representation Step by Step";
    vector<string> caps = {"read A as root","open child list of A","read subtree B","read subtree E under B","read K and L under E","read C and G","read D subtree","finish parenthesized representation"};
    int total=(int)caps.size();
    vector<NodeInfo> nodes = {{"A","A",550,120},{"B","B",340,230},{"C","C",550,230},{"D","D",760,230},{"E","E",250,340},{"F","F",430,340},{"G","G",550,340},{"H","H",690,340},{"I","I",830,340},{"K","K",200,460},{"L","L",310,460},{"M","M",690,460}};
    vector<EdgeInfo> edges = {{"A","B"},{"A","C"},{"A","D"},{"B","E"},{"B","F"},{"C","G"},{"D","H"},{"D","I"},{"E","K"},{"E","L"},{"H","M"}};
    vector<set<string>> hot(total);
    hot[0].insert("A");
    hot[1].insert("B");
    hot[1].insert("A");
    hot[1].insert("D");
    hot[1].insert("C");
    hot[2].insert("B");
    hot[2].insert("E");
    hot[2].insert("F");
    hot[3].insert("L");
    hot[3].insert("K");
    hot[3].insert("E");
    hot[4].insert("L");
    hot[4].insert("K");
    hot[5].insert("G");
    hot[5].insert("C");
    hot[6].insert("D");
    hot[6].insert("I");
    hot[6].insert("M");
    hot[6].insert("H");
    for(int i=0;i<total;i++){
        string body;
        body+=rect(60,115,960,50,"note","( A ( B ( E ( K, L ), F ), C ( G ), D ( H ( M ), I ) ) )"); body+=renderTree(nodes,edges,hot[i]);
        saveFrame(folder,i+1,total,title,caps[i],body);
    }
}
