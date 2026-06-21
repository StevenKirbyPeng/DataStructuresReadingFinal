
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
    const string folder="17_thread_insert_right_steps";
    const string title="17 Threaded Tree InsertRight Step by Step";
    vector<string> caps = {"case A: s right is a thread","create new node r","r inherits s old right thread","s.rightChild becomes r","s.rightThread becomes false","case B: s has right subtree","old right subtree moves under r","find inorder successor t","t.leftThread points to r","InsertRight complete"};
    int total=(int)caps.size();
    vector<NodeInfo> nodes = {};
    vector<EdgeInfo> edges = {};
    vector<set<string>> hot(total);
    
    for(int i=0;i<total;i++){
        string body;
        body+=circle(240,170,"s","ok"); if(i>=1)body+=circle(360,260,"r","hot"); if(i>=3)body+=line(240,194,360,236,"red"); body+=rect(80,390,430,80,"note","Case A: if s has right thread, insert r directly and copy the old thread."); body+=circle(700,170,"s","ok"); body+=circle(860,350,"old","box"); body+=line(700,194,860,326,"edge"); if(i>=5)body+=circle(790,260,"r","hot"); if(i>=6){body+=line(700,194,790,236,"red"); body+=line(790,284,860,326,"red");} if(i>=8){body+=circle(620,330,"t","box"); body+=line(620,306,790,260,"rptr");} body+=rect(575,430,460,90,"note","Case B: r becomes s right child; old right subtree becomes r right child; successor thread is repaired.");
        saveFrame(folder,i+1,total,title,caps[i],body);
    }
}
