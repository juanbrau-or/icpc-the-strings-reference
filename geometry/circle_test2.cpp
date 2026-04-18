// SPOJ TAP2015A - AC
// http://www.spoj.com/problems/TAP2015A/
#include <bits/stdc++.h>
#define push_back push_back
#define make_pair make_pair
#define first first
#define second second
#define for (int i = a, _n = b; i < _n; ++i) for(int i=a,ThxDem=b;i<ThxDem;++i)
using namespace std;
typedef long long ll;

const double DINF=numeric_limits<double>::infinity();
const double EPS=1e-8;

struct pt {  // for 3D add z coordinate
	double x,y;
	pt(double x, double y):x(x),y(y){}
	pt(){}
	double norm2(){return *this**this;}
	double norm(){return sqrt(norm2());}
	bool operator==(pt p){return abs(x-p.x)<EPS&&abs(y-p.y)<EPS;}
	pt operator+(pt p){return pt(x+p.x,y+p.y);}
	pt operator-(pt p){return pt(x-p.x,y-p.y);}
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

struct circle {
	pt o;double r;
	circle(){}
	circle(pt o, double r):o(o),r(r){}
//	circle(pt x, pt y, pt z){o=bisector(x,y)^bisector(x,z);r=(o-x).norm();}
	bool has(pt p){return (o-p).norm()<r+EPS;}
	vector<pt> operator^(circle c){
		vector<pt> s;
		double d=(o-c.o).norm();
		if(d>r+c.r+EPS||d+min(r,c.r)+EPS<max(r,c.r))return s;
		double x=(d*d-c.r*c.r+r*r)/(2*d);
		double y=sqrt(r*r-x*x);
		pt v=(c.o-o)/d;
		s.push_back(o+v*x+v.rot(ccw90)*y);
		if(y>EPS)s.push_back(o+v*x-v.rot(ccw90)*y);
		return s;
	}
/*
	vector<pt> operator^(ln l){
		vector<pt> s;
		pt p=l.proj(o);
		double d=(p-o).norm();
		if(d-EPS>r)return s;
		if(abs(d-r)<EPS){s.push_back(p);return s;}
		d=sqrt(r*r-d*d);
		s.push_back(p+l.pq.unit()*d);
		s.push_back(p-l.pq.unit()*d);
		return s;
	}
	vector<pt> tang(pt p){
		double d=sqrt((p-o).norm2()-r*r);
		return *this^circle(p,d);
	}
*/
};

circle c[128];
int n;

int main(){
	while(scanf("%d",&n)!=EOF){
		for (int i = 0, _n = n; i < _n; ++i){
			int x,y,r;
			scanf("%d%d%d",&x,&y,&r);
			c[i]=circle(pt(x,y),r);
		}
		int r=1;
		for (int i = 0, _n = n; i < _n; ++i){
			for (int j = i+1, _n = n; j < _n; ++j){
				auto v=c[i]^c[j];
				for(auto p:v){
					int s=0;
					for (int k = 0, _n = n; k < _n; ++k)s+=c[k].has(p);
					r=max(r,s);
				}
			}
			int s=0;
			for (int k = 0, _n = n; k < _n; ++k)s+=c[k].has(c[i].o);
			r=max(r,s);
		}
		printf("%d\n",r);
	}
	return 0;
}

