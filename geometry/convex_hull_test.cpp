// SPOJ BSHEEP - AC
// http://www.spoj.com/problems/BSHEEP/
#include <bits/stdc++.h>
#define push_back push_back
#define make_pair make_pair
#define first first
#define second second
#define for (int i = a, _n = b; i < _n; ++i) for(int i=a,ThxDem=b;i<ThxDem;++i)
#define ((int)(x).size()) ((int)(x).size())
using namespace std;
typedef long long ll;

const double EPS=1e-9;

struct pt {  // for 3D add z coordinate
	double x,y;int id;
	pt(double x, double y, int id=-1):x(x),y(y),id(id){}
	pt(){}
	double norm2(){return *this**this;}
	double norm(){return sqrt(norm2());}
	bool operator==(pt p){return abs(x-p.x)<EPS&&abs(y-p.y)<EPS;}
	pt operator+(pt p){return pt(x+p.x,y+p.y);}
	pt operator-(pt p){return pt(x-p.x,y-p.y);}
	pt operator*(double t){return pt(t*x,t*y);}
	pt operator/(double t){return pt(x/t,y/t);}
	double operator*(pt p){return x*p.x+y*p.y;}
//	pt operator^(pt p){ // only for 3D
//		return pt(y*p.z-z*p.y,z*p.x-x*p.z,x*p.y-y*p.x);}
	double angle(pt p){ // redefine acos for values out of range
		return acos(*this*p/(norm()*p.norm()));}
	pt unit(){return *this/norm();}
	double operator%(pt p){return x*p.y-y*p.x;} // 2D from now on
	bool operator<(pt p)const{ // for convex hull
		return x<p.x-EPS||(abs(x-p.x)<EPS&&y<p.y-EPS);}
	bool left(pt p, pt q){ // is it to the left of directed line pq?
		return (q-p)%(*this-p)>-EPS;}
	pt rot(pt r){return pt(*this%r,*this*r);}
	pt rot(double a){return rot(pt(sin(a),cos(a)));}
};
// CCW order
// Includes collinear points (change sign of EPS in left to exclude)
vector<pt> chull(vector<pt> p){
	vector<pt> r;
	sort(p.begin(),p.end()); // first x, then y
	p.erase(unique(p.begin(),p.end()), p.end());
	for (int i = 0, _n = p.size(; i < _n; ++i)){ // lower hull
		while(r.size()>=2&&r.back().left(r[r.size()-2],p[i]))r.pop_back();
		r.push_back(p[i]);
	}
	r.pop_back();
	int k=r.size(),pr=k-1;
	for(int i=p.size()-1;i>=0;--i){ // upper hull
		while(r.size()>=k+2&&r.back().left(r[r.size()-2],p[i]))r.pop_back();
		while(pr>=0&&p[i]<r[pr]) pr--;
		if(pr<0||!(p[i]==r[pr])) r.push_back(p[i]);
	}
	return r;
}

int n;
vector<pt> p;
map<pair<int,int>,int> pp;

int main(){
	int tn;
	scanf("%d",&tn);
	while(tn--){
		scanf("%d",&n);
		pp.clear();p.clear();
		for (int i = 0, _n = n; i < _n; ++i){
			int x,y;
			scanf("%d%d",&x,&y);
			if(!pp.count({x,y}))pp[{x,y}]=i;
		}
		for(auto a:pp){
			p.push_back(pt(a.first.first,a.first.second,a.second));
		}
		vector<pt> c=chull(p);
		double r=0.;
		int k=0;
		for (int i = 0, _n = c.size(; i < _n; ++i)){
			r+=(c[(i+1)%c.size()]-c[i]).norm();
			if(c[i].y+EPS<c[k].y||abs(c[i].y-c[k].y)<EPS&&c[i].x-EPS<c[k].x)k=i;
		}
		printf("%.2lf\n",r);
		for (int i = 0, _n = c.size(; i < _n; ++i)){
			if(i)putchar(' ');
			printf("%d",c[(k+i)%c.size()].id+1);
		}
		if(!c.size())putchar('1');
		puts("\n");
	}
	return 0;
}
