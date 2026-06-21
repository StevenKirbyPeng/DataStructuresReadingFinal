#pragma once
#include <bits/stdc++.h>
using namespace std;
static string esc(const string& s){ string r; for(char c:s){ if(c=='&') r+="&amp;"; else if(c=='<') r+="&lt;"; else if(c=='>') r+="&gt;"; else if(c=='"') r+="&quot;"; else r+=c;} return r; }
static void ensureDir(const string& d){ filesystem::create_directories(d); }
static void writeText(const string& path,const string& txt){ ofstream f(path, ios::binary); if(!f){ cerr<<"Cannot write "<<path<<"\n"; exit(1);} f<<txt; }
struct Node{string id,label; double x,y; bool hi=false, done=false;};
struct Edge{string a,b,label; bool directed=false, hi=false, done=false;};
static string line(double x1,double y1,double x2,double y2,const string& color="#666",int w=2,bool arrow=false){
 string s="<line x1='"+to_string(x1)+"' y1='"+to_string(y1)+"' x2='"+to_string(x2)+"' y2='"+to_string(y2)+"' stroke='"+color+"' stroke-width='"+to_string(w)+"'"; if(arrow) s+=" marker-end='url(#arrow)'"; return s+="/>\n";
}
static string txt(double x,double y,const string& t,int size=16,const string& color="#222", const string& anchor="middle"){ return "<text x='"+to_string(x)+"' y='"+to_string(y)+"' text-anchor='"+anchor+"' font-size='"+to_string(size)+"' fill='"+color+"' font-family='Microsoft JhengHei, Arial'>"+esc(t)+"</text>\n"; }
static string rect(double x,double y,double w,double h,const string& fill="#fff", const string& stroke="#555", int sw=2, double rx=10){ return "<rect x='"+to_string(x)+"' y='"+to_string(y)+"' width='"+to_string(w)+"' height='"+to_string(h)+"' rx='"+to_string(rx)+"' fill='"+fill+"' stroke='"+stroke+"' stroke-width='"+to_string(sw)+"'/>\n"; }
static string circle(double x,double y,double r,const string& fill="#FFF2CC", const string& stroke="#555", int sw=2){ return "<circle cx='"+to_string(x)+"' cy='"+to_string(y)+"' r='"+to_string(r)+"' fill='"+fill+"' stroke='"+stroke+"' stroke-width='"+to_string(sw)+"'/>\n"; }
static string svgStart(const string& title,const string& subtitle,int step,int total){
 string s="<svg xmlns='http://www.w3.org/2000/svg' width='1100' height='720' viewBox='0 0 1100 720'>\n";
 s += "<defs><marker id='arrow' markerWidth='10' markerHeight='10' refX='9' refY='3' orient='auto' markerUnits='strokeWidth'><path d='M0,0 L0,6 L9,3 z' fill='#555'/></marker></defs>\n";
 s += "<rect width='1100' height='720' fill='#fbfbff'/>\n";
 s += txt(550,38,title,26,"#1f3763");
 s += txt(550,68,"Step "+to_string(step)+" / "+to_string(total)+"："+subtitle,18,"#444");
 return s;
}
static string svgEnd(){ return "</svg>\n"; }
static void drawGraph(string& s, vector<Node> nodes, vector<Edge> edges){
 map<string,Node> mp; for(auto &n:nodes) mp[n.id]=n;
 for(auto &e:edges){ auto u=mp[e.a], v=mp[e.b]; string col=e.hi?"#d62828":(e.done?"#2a9d8f":"#777"); int w=e.hi?5:(e.done?4:2); s+=line(u.x,u.y,v.x,v.y,col,w,e.directed); if(!e.label.empty()) s+=txt((u.x+v.x)/2,(u.y+v.y)/2-8,e.label,15,col); }
 for(auto &n:nodes){ string fill=n.hi?"#FFD6A5":(n.done?"#CDEAC0":"#E8F1FF"); string st=n.hi?"#d62828":"#355070"; s+=circle(n.x,n.y,34,fill,st,n.hi?4:2); s+=txt(n.x,n.y+5,n.label,16,"#111"); }
}
static void saveFrame(const string& dir,int idx,const string& title,const string& subtitle,const string& body){ stringstream ss; ss<<dir<<"/step_"<<setw(2)<<setfill('0')<<idx<<".svg"; writeText(ss.str(), body); }
static string noteBox(double x,double y,const string& title,const vector<string>& lines){ string s=rect(x,y,360,110,"#ffffff","#9aa",2,12)+txt(x+180,y+28,title,18,"#1f3763"); double yy=y+56; for(auto &l:lines){ s+=txt(x+18,yy,"• "+l,15,"#333","start"); yy+=22;} return s; }
