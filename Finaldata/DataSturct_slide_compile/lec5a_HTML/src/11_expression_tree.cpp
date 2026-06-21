
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
    const string folder="11_expression_tree_steps";
    const string title="11 Expression Tree Step by Step";
    vector<string> caps = {"leaves are operands","operators are internal nodes","divide A by B","multiply by C","multiply by D","add E","infix traversal","prefix traversal","postfix traversal","evaluate bottom up","final expression tree"};
    int total=(int)caps.size();
    vector<NodeInfo> nodes = {{"plus","+",550,110},{"mul1","*",430,220},{"E","E",710,220},{"mul2","*",320,330},{"D","D",500,330},{"div","/",240,440},{"C","C",400,440},{"A","A",180,550},{"B","B",300,550}};
    vector<EdgeInfo> edges = {{"plus","mul1"},{"plus","E"},{"mul1","mul2"},{"mul1","D"},{"mul2","div"},{"mul2","C"},{"div","A"},{"div","B"}};
    vector<set<string>> hot(total);
    hot[0].insert("A");
    hot[0].insert("C");
    hot[0].insert("B");
    hot[0].insert("D");
    hot[0].insert("E");
    hot[1].insert("plus");
    hot[1].insert("div");
    hot[1].insert("mul1");
    hot[1].insert("mul2");
    hot[2].insert("B");
    hot[2].insert("A");
    hot[2].insert("div");
    hot[3].insert("C");
    hot[3].insert("mul2");
    hot[4].insert("D");
    hot[4].insert("mul1");
    hot[5].insert("plus");
    hot[5].insert("E");
    hot[6].insert("plus");
    hot[6].insert("A");
    hot[6].insert("D");
    hot[6].insert("mul2");
    hot[6].insert("mul1");
    hot[6].insert("C");
    hot[6].insert("B");
    hot[6].insert("div");
    hot[6].insert("E");
    hot[7].insert("plus");
    hot[7].insert("A");
    hot[7].insert("D");
    hot[7].insert("mul2");
    hot[7].insert("mul1");
    hot[7].insert("C");
    hot[7].insert("B");
    hot[7].insert("div");
    hot[7].insert("E");
    hot[8].insert("plus");
    hot[8].insert("A");
    hot[8].insert("D");
    hot[8].insert("mul2");
    hot[8].insert("mul1");
    hot[8].insert("C");
    hot[8].insert("B");
    hot[8].insert("div");
    hot[8].insert("E");
    hot[9].insert("plus");
    hot[9].insert("div");
    hot[9].insert("mul1");
    hot[9].insert("mul2");
    for(int i=0;i<total;i++){
        string body;
        body+=renderTree(nodes,edges,hot[i]); body+=rect(700,420,330,50,"note","Infix: A/B*C*D+E"); body+=rect(700,490,330,50,"note","Postfix: A B / C * D * E +");
        saveFrame(folder,i+1,total,title,caps[i],body);
    }
}
