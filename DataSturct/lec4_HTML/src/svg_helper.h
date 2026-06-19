
#pragma once
#include <bits/stdc++.h>
using namespace std;
static string esc(const string& s){ string r; for(char c:s){ if(c=='&')r+="&amp;"; else if(c=='<')r+="&lt;"; else if(c=='>')r+="&gt;"; else if(c=='\"')r+="&quot;"; else r+=c;} return r; }
static void ensureDir(const string& d){ std::filesystem::create_directories(d); }
static void writeFile(const string& path,const string& text){ ofstream f(path); if(!f){ cerr<<"Cannot open "<<path<<"\n"; exit(1);} f<<text; }
static string startSVG(int w,int h,const string& title,const string& subtitle){
 string s; s+="<svg xmlns=\"http://www.w3.org/2000/svg\" width=\""+to_string(w)+"\" height=\""+to_string(h)+"\" viewBox=\"0 0 "+to_string(w)+" "+to_string(h)+"\">\n";
 s+="<rect width=\"100%\" height=\"100%\" fill=\"#f7fbff\"/>\n";
 s+="<style>.title{font:700 26px Arial;fill:#111}.sub{font:16px Arial;fill:#222}.small{font:13px Arial;fill:#333}.tiny{font:11px Arial;fill:#333}.box{fill:#e8f4ff;stroke:#6aa1d8;stroke-width:1.4}.hot{fill:#ffe6e6;stroke:#d93025;stroke-width:2.5}.ok{fill:#e6f4ea;stroke:#188038;stroke-width:2}.note{fill:#fff7d6;stroke:#d9a300;stroke-width:1.5}.gray{fill:#eeeeee;stroke:#888}.node{fill:#dbeafe;stroke:#2b73bd;stroke-width:2}.data{fill:#fef3c7;stroke:#b7791f;stroke-width:1.5}.link{fill:#ecfdf5;stroke:#047857;stroke-width:1.5}.ptr{stroke:#4b5563;stroke-width:2.2;fill:none;marker-end:url(#arr)}.redptr{stroke:#dc2626;stroke-width:3;fill:none;marker-end:url(#arrRed)}.dash{stroke:#777;stroke-width:2;fill:none;stroke-dasharray:6 5;marker-end:url(#arr)}</style>\n";
 s+="<defs><marker id=\"arr\" markerWidth=\"10\" markerHeight=\"10\" refX=\"8\" refY=\"3\" orient=\"auto\"><path d=\"M0,0 L0,6 L9,3 z\" fill=\"#4b5563\"/></marker><marker id=\"arrRed\" markerWidth=\"10\" markerHeight=\"10\" refX=\"8\" refY=\"3\" orient=\"auto\"><path d=\"M0,0 L0,6 L9,3 z\" fill=\"#dc2626\"/></marker></defs>\n";
 s+="<rect x=\"28\" y=\"22\" width=\"1220\" height=\"72\" rx=\"14\" fill=\"#e8f2ff\" stroke=\"#4f8bd6\" stroke-width=\"2\"/>\n";
 s+="<text x=\"54\" y=\"58\" class=\"title\">"+esc(title)+"</text>\n<text x=\"54\" y=\"82\" class=\"sub\">"+esc(subtitle)+"</text>\n"; return s; }
static string endSVG(){return "</svg>\n";}
static string T(int x,int y,const string&t,const string&cls="sub"){return "<text x=\""+to_string(x)+"\" y=\""+to_string(y)+"\" class=\""+cls+"\">"+esc(t)+"</text>\n";}
static string R(int x,int y,int w,int h,const string&cls,const string&label=""){ string s="<rect x=\""+to_string(x)+"\" y=\""+to_string(y)+"\" width=\""+to_string(w)+"\" height=\""+to_string(h)+"\" rx=\"8\" class=\""+cls+"\"/>\n"; if(label.size()) s+="<text x=\""+to_string(x+w/2)+"\" y=\""+to_string(y+h/2+6)+"\" font-family=\"Arial\" font-size=\"18\" text-anchor=\"middle\">"+esc(label)+"</text>\n"; return s; }
static string L(int x1,int y1,int x2,int y2,const string&cls="ptr"){return "<line x1=\""+to_string(x1)+"\" y1=\""+to_string(y1)+"\" x2=\""+to_string(x2)+"\" y2=\""+to_string(y2)+"\" class=\""+cls+"\"/>\n";}
static string cell(int x,int y,const string&v,bool hot=false){return R(x,y,70,48,hot?"hot":"box",v);} 
static string listNode(int x,int y,const string&v,bool hot=false){ string s=R(x,y,78,52,hot?"hot":"data",v); s+=R(x+78,y,38,52,"link","*"); return s;}
static string dllNode(int x,int y,const string&v,bool hot=false){ string s=R(x,y,34,52,"link","p"); s+=R(x+34,y,78,52,hot?"hot":"data",v); s+=R(x+112,y,34,52,"link","n"); return s;}
static string sidePanel(int step,const vector<string>& bullets){ string s=R(790,130,420,160,"box",""); s+=T(815,162,"Step state table","title"); s+=T(815,195,"Current step = "+to_string(step),"sub"); s+=T(815,225,"Red = this step's active pointer/data change","small"); s+=T(815,252,"Blue/gray = existing structure or waiting nodes","small"); s+=R(790,315,420,190,"note",""); s+=T(815,348,"Animation focus","title"); int y=382; for(auto &b:bullets){s+=T(815,y,"- "+b,"small"); y+=24;} return s;}
