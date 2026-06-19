
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
    const string folder="12_iterative_inorder_stack_steps";
    const string title="12 Iterative Inorder with Stack";
    vector<string> caps = {"current = A push A","move left push B","move left push D","D has no left, pop visit D","pop visit B","move right push E","pop visit E","pop visit A","move right push C","push F then visit F","visit C and G","inorder complete"};
    int total=(int)caps.size();
    vector<NodeInfo> nodes = {{"A","A",550,130},{"B","B",370,260},{"C","C",730,260},{"D","D",280,390},{"E","E",460,390},{"F","F",640,390},{"G","G",820,390}};
    vector<EdgeInfo> edges = {{"A","B"},{"A","C"},{"B","D"},{"B","E"},{"C","F"},{"C","G"}};
    vector<set<string>> hot(total);
    hot[0].insert("A");
    hot[1].insert("B");
    hot[1].insert("A");
    hot[2].insert("B");
    hot[2].insert("A");
    hot[2].insert("D");
    hot[3].insert("D");
    hot[4].insert("B");
    hot[5].insert("E");
    hot[6].insert("E");
    hot[7].insert("A");
    hot[8].insert("C");
    hot[9].insert("F");
    hot[10].insert("G");
    hot[10].insert("C");
    for(int i=0;i<total;i++){
        string body;
        body+=renderTree(nodes,edges,hot[i]); vector<string> st={"A","B","D"}; for(int k=0;k<3;k++){body+=rect(820,420-k*55,150,42,(i==k?"hot":"box"), k<(int)st.size()?st[k]:"");} body+=text(835,470,"Stack top changes by push/pop"); body+=rect(70,610,900,45,"note","Algorithm: push left chain, pop and visit, then move to right subtree.");
        saveFrame(folder,i+1,total,title,caps[i],body);
    }
}
