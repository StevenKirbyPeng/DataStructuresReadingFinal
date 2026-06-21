
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
    const string folder="03_kary_memory_waste_steps";
    const string title="03 k-ary Memory Waste Step by Step";
    vector<string> caps = {"one node reserves k fields","example k = 5","only two child fields used","remaining fields are NULL","total child fields = n*k","real edges = n - 1","waste = n(k-1)+1","why LCRS saves space"};
    int total=(int)caps.size();
    vector<NodeInfo> nodes = {};
    vector<EdgeInfo> edges = {};
    vector<set<string>> hot(total);
    
    for(int i=0;i<total;i++){
        string body;
        body+=text(70,130,"A fixed k-ary node layout reserves every child slot."); for(int c=0;c<5;c++){ string cls=(c<=i-2?"ok":(i>=3&&c>=2?"hot":"box")); body+=rect(130+c*165,190,150,70,cls,c<2?"used child":"NULL"); } body+=rect(90,360,880,70,"note", i<4?"Unused pointer fields waste memory.":"Formula: nk total fields - (n-1) used fields = n(k-1)+1 empty fields.");
        saveFrame(folder,i+1,total,title,caps[i],body);
    }
}
