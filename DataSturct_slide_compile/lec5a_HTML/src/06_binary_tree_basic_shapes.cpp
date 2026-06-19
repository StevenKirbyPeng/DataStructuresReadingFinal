
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
    const string folder="06_binary_tree_basic_shapes_steps";
    const string title="06 Binary Tree Shapes Step by Step";
    vector<string> caps = {"binary tree distinguishes left and right","skewed tree step 1","skewed tree step 2","complete tree fills levels left to right","complete tree next inserted position","full tree every node has 0 or 2 children","compare three shapes","common exam distinction","final view"};
    int total=(int)caps.size();
    vector<NodeInfo> nodes = {};
    vector<EdgeInfo> edges = {};
    vector<set<string>> hot(total);
    
    for(int i=0;i<total;i++){
        string body;
        vector<pair<int,int>> sk={{120,160},{120,250},{120,340},{120,430}}; for(int j=0;j<4;j++){body+=circle(sk[j].first,sk[j].second,string(1,char('A'+j)), (i==j+1?"hot":"box")); if(j)body+=line(sk[j-1].first,sk[j-1].second+24,sk[j].first,sk[j].second-24);} body+=text(70,520,"Skewed"); vector<pair<int,int>> co={{540,160},{440,260},{640,260},{390,360},{490,360},{590,360}}; for(int j=0;j<6;j++){body+=circle(co[j].first,co[j].second,to_string(j+1),(i==4&&j==5?"hot":"ok"));} for(auto e:vector<pair<int,int>>{{0,1},{0,2},{1,3},{1,4},{2,5}})body+=line(co[e.first].first,co[e.first].second+24,co[e.second].first,co[e.second].second-24); body+=text(460,520,"Complete"); vector<pair<int,int>> fu={{910,160},{820,260},{1000,260},{770,360},{870,360},{950,360},{1050,360}}; for(int j=0;j<7;j++)body+=circle(fu[j].first,fu[j].second,to_string(j+1),(i==5?"hot":"box")); for(auto e:vector<pair<int,int>>{{0,1},{0,2},{1,3},{1,4},{2,5},{2,6}})body+=line(fu[e.first].first,fu[e.first].second+24,fu[e.second].first,fu[e.second].second-24); body+=text(860,520,"Full"); body+=rect(70,600,900,50,"note","Skewed: one chain; Complete: filled left-to-right; Full: each internal node has exactly two children.");
        saveFrame(folder,i+1,total,title,caps[i],body);
    }
}
