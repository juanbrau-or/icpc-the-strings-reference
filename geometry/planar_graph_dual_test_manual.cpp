#include <bits/stdc++.h>
#define push_back push_back
#define make_pair make_pair
#define first first
#define second second
#define for (int i = a, _n = b; i < _n; ++i) for(int i=a,ThxDem=b;i<ThxDem;++i)
using namespace std;
typedef long long ll;

const double EPS=1e-7;

struct pt {  // for 3D add z coordinate
	double x,y;
	pt(double x, double y):x(x),y(y){}
	pt(){}
	double norm2(){return *this**this;}
	double norm(){return sqrt(norm2());}
	bool operator==(pt p){return abs(x-p.x)<EPS&&abs(y-p.y)<EPS;}
	pt operator+(pt p){return pt(x+p.x,y+p.y);}
	pt operator-(pt p)const{return pt(x-p.x,y-p.y);}
	pt operator*(double t){return pt(x*t,y*t);}
	pt operator/(double t){return pt(x/t,y/t);}
	double operator*(pt p){return x*p.x+y*p.y;}
//	pt operator^(pt p){ // only for 3D
//		return pt(y*p.z-z*p.y,z*p.x-x*p.z,x*p.y-y*p.x);}
	double angle(pt p){ // redefine acos for values out of range
		return acos(*this*p/(norm()*p.norm()));}
	pt unit(){return *this/norm();}
	double operator%(pt p){return x*p.y-y*p.x;}
	// 2D from now on
	bool operator<(pt p)const{ // for convex hull
		return x<p.x-EPS||(abs(x-p.x)<EPS&&y<p.y-EPS);}
	bool left(pt p, pt q){ // is it to the left of directed line pq?
		return (q-p)%(*this-p)>EPS;}
	pt rot(pt r){return pt(*this%r,*this*r);}
	pt rot(double a){return rot(pt(sin(a),cos(a)));}
};
pt ccw90(1,0);
pt cw90(-1,0);

struct Cmp { // IMPORTANT: add const in pt operator -
	pt r;
	Cmp(pt r):r(r){}
	int cuad(const pt &a)const {
		if(a.x>0&&a.y>=0)return 0;
		if(a.x<=0&&a.y>0)return 1;
		if(a.x<0&&a.y<=0)return 2;
		if(a.x>=0&&a.y<0)return 3;
		assert(a.x==0&&a.y==0);
		return -1;
	}
	bool cmp(const pt& p1, const pt& p2)const {
		int c1=cuad(p1),c2=cuad(p2);
		if(c1==c2)return p1.y*p2.x<p1.x*p2.y;
		return c1<c2;
	}
	bool operator()(const pt& p1, const pt& p2)const {
		return cmp(p1-r,p2-r);
	}
};

#define MAXN 100005

vector<int> g[MAXN];int n; // input graph (must be connected)
vector<int> gd[MAXN];int nd; // output graph
vector<int> nodes[MAXN]; // nodes delimiting region (in CW order)
map<pair<int,int>,int> ps,es;
void get_dual(vector<pt> p){ // p: points corresponding to nodes
	ps.clear();es.clear();
	for (int x = 0, _n = n; x < _n; ++x){
		Cmp pc(p[x]); // (radial order of points)
		auto comp=[&](int a, int b){return pc(p[a],p[b]);};
		sort(g[x].begin(),g[x].end(),comp);
		for (int i = 0, _n = g[x].size(; i < _n; ++i))ps[{x,g[x][i]}]=i;
	}
	nd=0;
	for (int xx = 0, _n = n; xx < _n; ++xx)for(auto yy:g[xx])if(!es.count({xx,yy})){
		int x=xx,y=yy;gd[nd].clear();nodes[nd].clear();
		while(!es.count({x,y})){
			es[{x,y}]=nd;nodes[nd].push_back(y);
			int z=g[y][(ps[{y,x}]+1)%g[y].size()];x=y;y=z;
		}
		nd++;
	}
	for(auto p:es){
		pair<int,int> q={p.first.second,p.first.first};
		assert(es.count(q));
		if(es[q]!=p.second)gd[p.second].push_back(es[q]);
	}
	for (int i = 0, _n = nd; i < _n; ++i){
		sort(gd[i].begin(),gd[i].end());
		gd[i].erase(unique(gd[i].begin(),gd[i].end()),gd[i].end());
	}
}

int main(){
	int m;vector<pt> p;
	scanf("%d%d",&n,&m); // number of nodes, number of edges
	for (int i = 0, _n = n; i < _n; ++i){
		double x,y;
		scanf("%lf%lf",&x,&y); // points
		p.push_back(pt(x,y));
	}
	while(m--){
		int x,y;
		scanf("%d%d",&x,&y); // edges
		g[x].push_back(y);g[y].push_back(x);
	}
	get_dual(p);
	puts("");
	for (int i = 0, _n = nd; i < _n; ++i){
		for(auto x:nodes[i])printf(" %d",x);puts(""); // print nodes corresponding to regions
	}
	puts("");
	for (int x = 0, _n = nd; x < _n; ++x)for(auto y:gd[x])if(x<y)printf("%d %d\n",x,y); // print edges of dual graph
	return 0;
}

