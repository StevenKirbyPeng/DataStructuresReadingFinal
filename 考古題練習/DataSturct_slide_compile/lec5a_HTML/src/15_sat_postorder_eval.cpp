
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
    const string folder="15_sat_postorder_eval_steps";
    const string title="15 SAT Postorder Evaluation Step by Step";
    vector<string> caps = {"assign truth values to leaves","evaluate NOT x2","evaluate x1 AND NOT x2","evaluate NOT x1","combine with x3","evaluate NOT x3","evaluate right OR","evaluate root OR","postorder means children first","operator result bubbles upward","final Boolean value","SAT tree complete"};
    int total=(int)caps.size();
    vector<NodeInfo> nodes = {{"or1","OR",550,90},{"and1","AND",380,200},{"or2","OR",730,200},{"x1","x1",290,320},{"not1","NOT",470,320},{"and2","AND",650,320},{"not3","NOT",850,320},{"x2","x2",470,440},{"not2","NOT",600,440},{"x3","x3",720,440},{"x1b","x1",600,560},{"x3b","x3",850,440}};
    vector<EdgeInfo> edges = {{"or1","and1"},{"or1","or2"},{"and1","x1"},{"and1","not1"},{"not1","x2"},{"or2","and2"},{"or2","not3"},{"and2","not2"},{"and2","x3"},{"not2","x1b"},{"not3","x3b"}};
    vector<set<string>> hot(total);
    hot[0].insert("x2");
    hot[0].insert("x3");
    hot[0].insert("x1b");
    hot[0].insert("x3b");
    hot[0].insert("x1");
    hot[1].insert("x2");
    hot[1].insert("not1");
    hot[2].insert("not1");
    hot[2].insert("and1");
    hot[2].insert("x1");
    hot[3].insert("x1b");
    hot[3].insert("not2");
    hot[4].insert("x3");
    hot[4].insert("and2");
    hot[4].insert("not2");
    hot[5].insert("x3b");
    hot[5].insert("not3");
    hot[6].insert("or2");
    hot[6].insert("and2");
    hot[6].insert("not3");
    hot[7].insert("and1");
    hot[7].insert("or1");
    hot[7].insert("or2");
    hot[8].insert("x2");
    hot[8].insert("not1");
    hot[8].insert("and1");
    hot[8].insert("x1");
    hot[9].insert("or1");
    hot[9].insert("or2");
    hot[9].insert("and2");
    hot[10].insert("or1");
    for(int i=0;i<total;i++){
        string body;
        body+=renderTree(nodes,edges,hot[i]); body+=rect(60,610,960,45,"note","Evaluation order is postorder: evaluate children before applying AND / OR / NOT.");
        saveFrame(folder,i+1,total,title,caps[i],body);
    }
}
