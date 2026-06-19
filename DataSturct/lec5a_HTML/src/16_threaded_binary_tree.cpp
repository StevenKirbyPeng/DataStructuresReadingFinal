
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
    const string folder="16_threaded_binary_tree_steps";
    const string title="16 Threaded Binary Tree Step by Step";
    vector<string> caps = {"ordinary binary tree","inorder sequence D B E A F C G","NULL left/right links exist","D successor thread points to B","E successor thread points to A","F predecessor/successor threads","G predecessor thread points to C","Next() follows thread if available","traversal without stack","final threaded tree"};
    int total=(int)caps.size();
    vector<NodeInfo> nodes = {{"A","A",550,130},{"B","B",370,260},{"C","C",730,260},{"D","D",280,390},{"E","E",460,390},{"F","F",640,390},{"G","G",820,390}};
    vector<EdgeInfo> edges = {{"A","B"},{"A","C"},{"B","D"},{"B","E"},{"C","F"},{"C","G"}};
    vector<set<string>> hot(total);
    hot[1].insert("A");
    hot[1].insert("G");
    hot[1].insert("C");
    hot[1].insert("B");
    hot[1].insert("D");
    hot[1].insert("E");
    hot[1].insert("F");
    hot[2].insert("D");
    hot[2].insert("E");
    hot[2].insert("G");
    hot[2].insert("F");
    hot[3].insert("B");
    hot[3].insert("D");
    hot[4].insert("A");
    hot[4].insert("E");
    hot[5].insert("C");
    hot[5].insert("F");
    hot[6].insert("G");
    hot[6].insert("C");
    hot[7].insert("B");
    hot[7].insert("D");
    hot[7].insert("E");
    hot[7].insert("A");
    for(int i=0;i<total;i++){
        string body;
        body+=renderTree(nodes,edges,hot[i]);
        if(i>=3) body += "<path d=\"M280 414 C220 510 370 510 370 284\" class=\"red\"/>\n";
        if(i>=4) body += "<path d=\"M460 414 C510 500 550 300 550 154\" class=\"red\"/>\n";
        if(i>=5) body += "<path d=\"M640 414 C610 500 730 500 730 284\" class=\"red\"/>\n";
        body+=rect(760,560,300,60,"note","Thread = unused NULL link reused as inorder predecessor/successor pointer.");
        saveFrame(folder,i+1,total,title,caps[i],body);
    }
}
