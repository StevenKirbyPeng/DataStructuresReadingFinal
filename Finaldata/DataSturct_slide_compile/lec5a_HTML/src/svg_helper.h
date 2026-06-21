#pragma once
#include <bits/stdc++.h>
using namespace std;
static string esc(const string& s){string r;for(char c:s){if(c=='&')r+="&amp;";else if(c=='<')r+="&lt;";else if(c=='>')r+="&gt;";else if(c=='"')r+="&quot;";else r+=c;}return r;}
static void writeFile(const string& p,const string& t){ofstream f(p); if(!f){cerr<<"Cannot open "<<p<<endl; exit(1);} f<<t;}
static string startSVG(int w,int h,string title){string s; s+="<svg xmlns=\"http://www.w3.org/2000/svg\" width=\""+to_string(w)+"\" height=\""+to_string(h)+"\" viewBox=\"0 0 "+to_string(w)+" "+to_string(h)+"\">\n<rect width=\"100%\" height=\"100%\" fill=\"white\"/>\n";
s+="<style>.title{font:700 28px Arial;fill:#111}.sub{font:17px Arial;fill:#333}.small{font:13px Arial;fill:#333}.num{font:18px Arial;text-anchor:middle;dominant-baseline:middle}.box{fill:#E8F4FF;stroke:#333;stroke-width:1.5}.hot{fill:#F8CECC;stroke:#C00000;stroke-width:2}.ok{fill:#D5E8D4;stroke:#2E7D32;stroke-width:2}.note{fill:#FFF2CC;stroke:#555;stroke-width:1.5}.null{fill:#eee;stroke:#777;stroke-width:1}.edge{stroke:#333;stroke-width:2;fill:none}.red{stroke:red;stroke-width:3;fill:none}.green{stroke:#00A651;stroke-width:3;fill:none}.dash{stroke:#777;stroke-width:2;fill:none;stroke-dasharray:6 5}.ptr{stroke:#333;stroke-width:2;fill:none;marker-end:url(#arrow)}.rptr{stroke:red;stroke-width:2.5;fill:none;marker-end:url(#arrowRed)}</style>\n";
s+="<defs><marker id=\"arrow\" markerWidth=\"10\" markerHeight=\"10\" refX=\"8\" refY=\"3\" orient=\"auto\"><path d=\"M0,0 L0,6 L9,3 z\" fill=\"#333\"/></marker><marker id=\"arrowRed\" markerWidth=\"10\" markerHeight=\"10\" refX=\"8\" refY=\"3\" orient=\"auto\"><path d=\"M0,0 L0,6 L9,3 z\" fill=\"red\"/></marker></defs>\n";
s+="<text x=\"30\" y=\"42\" class=\"title\">"+esc(title)+"</text>\n"; return s;}
static string endSVG(){return "</svg>\n";}
static string text(int x,int y,string t,string cls="sub",string anchor="start"){return "<text x=\""+to_string(x)+"\" y=\""+to_string(y)+"\" class=\""+cls+"\" text-anchor=\""+anchor+"\">"+esc(t)+"</text>\n";}
static string rect(int x,int y,int w,int h,string cls,string label=""){string s="<rect x=\""+to_string(x)+"\" y=\""+to_string(y)+"\" width=\""+to_string(w)+"\" height=\""+to_string(h)+"\" rx=\"8\" class=\""+cls+"\"/>\n"; if(label!="")s+="<text x=\""+to_string(x+w/2)+"\" y=\""+to_string(y+h/2)+"\" class=\"num\">"+esc(label)+"</text>\n"; return s;}
static string circle(int x,int y,string label,string cls="box",int r=24){return "<circle cx=\""+to_string(x)+"\" cy=\""+to_string(y)+"\" r=\""+to_string(r)+"\" class=\""+cls+"\"/>\n<text x=\""+to_string(x)+"\" y=\""+to_string(y)+"\" class=\"num\">"+esc(label)+"</text>\n";}
static string line(int x1,int y1,int x2,int y2,string cls="edge"){return "<line x1=\""+to_string(x1)+"\" y1=\""+to_string(y1)+"\" x2=\""+to_string(x2)+"\" y2=\""+to_string(y2)+"\" class=\""+cls+"\"/>\n";}
static string nodeBox(int x,int y,string data,string l="L",string r="R",string cls="box"){string s=rect(x,y,120,48,cls,data); s+="<rect x=\""+to_string(x)+"\" y=\""+to_string(y+48)+"\" width=\"60\" height=\"38\" class=\"null\"/><rect x=\""+to_string(x+60)+"\" y=\""+to_string(y+48)+"\" width=\"60\" height=\"38\" class=\"null\"/>\n"; s+="<text x=\""+to_string(x+30)+"\" y=\""+to_string(y+67)+"\" class=\"small\" text-anchor=\"middle\">"+esc(l)+"</text><text x=\""+to_string(x+90)+"\" y=\""+to_string(y+67)+"\" class=\"small\" text-anchor=\"middle\">"+esc(r)+"</text>\n"; return s;}
static string arrCell(int x,int y,int i,string val,string cls="box"){string s=rect(x,y,52,42,cls,val); s+=text(x+26,y-8,"["+to_string(i)+"]","small","middle"); return s;}

static string drawStepBadge(int step,int total,const string& caption){
    string s;
    s += rect(30,55,180,42,"note","Step "+to_string(step)+" / "+to_string(total));
    s += text(230,83,caption,"sub");
    return s;
}
static string mkdirOutput(const string& dir){
#ifdef _WIN32
    system(("if not exist \""+dir+"\" mkdir \""+dir+"\"").c_str());
#else
    system(("mkdir -p \""+dir+"\"").c_str());
#endif
    return "";
}
static string stepFile(const string& folder,int step){
    ostringstream os; os<<"output/"<<folder<<"/step_"<<setw(2)<<setfill('0')<<step<<".svg"; return os.str();
}
