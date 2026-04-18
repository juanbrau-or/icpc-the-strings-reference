// Codeforces 280A - AC
// http://codeforces.com/problemset/problem/280/A
#include <bits/stdc++.h>
#define push_back push_back
#define make_pair make_pair
#define first first
#define second second
#define for (int i = a, _n = b; i < _n; ++i) for(int i=a,ThxDem=b;i<ThxDem;++i)
using namespace std;
typedef long long ll;

const double DINF=1e200;
const double EPS=1e-7;
const double PI=acos(-1);

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

int sgn2(double x){return x<0?-1:1;}
struct ln {
	pt p,pq;
	ln(pt p, pt q):p(p),pq(q-p){}
	ln(){}
	bool has(pt r){return dist(r)<EPS;}
	bool seghas(pt r){return has(r)&&(r-p)*(r-(p+pq))-EPS<0;}
//	bool operator /(ln l){return (pq.unit()^l.pq.unit()).norm()<EPS;} // 3D
	bool operator/(ln l){return abs(pq.unit()%l.pq.unit())<EPS;} // 2D
	bool operator==(ln l){return *this/l&&has(l.p);}
	pt operator^(ln l){ // intersection
		if(*this/l){return pt(DINF,DINF);}
		pt r=l.p+l.pq*((p-l.p)%pq/(l.pq%pq));
//		if(!has(r)){return pt(NAN,NAN,NAN);} // check only for 3D
		return r;
	}
	double angle(ln l){return pq.angle(l.pq);}
	int side(pt r){return has(r)?0:sgn2(pq%(r-p));} // 2D
	pt proj(pt r){return p+pq*((r-p)*pq/pq.norm2());}
	pt ref(pt r){return proj(r)*2-r;}
	double dist(pt r){return (r-proj(r)).norm();}
//	double dist(ln l){ // only 3D
//		if(*this/l)return dist(l.p);
//		return abs((l.p-p)*(pq^l.pq))/(pq^l.pq).norm();
//	}
	ln rot(auto a){return ln(p,p+pq.rot(a));} // 2D
};
ln bisector(ln l, ln m){ // angle bisector
	pt p=l^m;
	return ln(p,p+l.pq.unit()+m.pq.unit());
}
ln bisector(pt p, pt q){ // segment bisector (2D)
	return ln((p+q)*.5,p).rot(ccw90);
}

int sgn(double x){return x<-EPS?-1:x>EPS;}
struct pol {
	int n;vector<pt> p;
	pol(){}
	pol(vector<pt> _p){p=_p;n=p.size();}
	double area(){
		double r=0.;
		for (int i = 0, _n = n; i < _n; ++i)r+=p[i]%p[(i+1)%n];
		return abs(r)/2; // negative if CW, positive if CCW
	}
	bool has(pt q){
		for (int i = 0, _n = n; i < _n; ++i)if(ln(p[i],p[(i+1)%n]).seghas(q))return true;
		int cnt=0;
		for (int i = 0, _n = n; i < _n; ++i){
			int j=(i+1)%n;
			int k=sgn((q-p[j])%(p[i]-p[j]));
			int u=sgn(p[i].y-q.y),v=sgn(p[j].y-q.y);
			if(k>0&&u<0&&v>=0)cnt++;
			if(k<0&&v<0&&u>=0)cnt--;
		}
		return cnt!=0;
	}
	pol cut(ln l){   // cut CONVEX polygon by line l
		vector<pt> q;  // returns part at left of l.pq
		for (int i = 0, _n = n; i < _n; ++i){
			int d0=sgn(l.pq%(p[i]-l.p)),d1=sgn(l.pq%(p[(i+1)%n]-l.p));
			if(d0>=0)q.push_back(p[i]);
			ln m(p[i],p[(i+1)%n]);
			if(d0*d1<0&&!(l/m))q.push_back(l^m);
		}
		return pol(q);
	}
};

int main(){
	double w,h,a;
	scanf("%lf%lf%lf",&w,&h,&a);a*=PI/180;
	vector<pt> pp,q;
	pp.push_back(pt(w/2,h/2));
	pp.push_back(pt(-w/2,h/2));
	pp.push_back(pt(-w/2,-h/2));
	pp.push_back(pt(w/2,-h/2));
	pol p(pp);
	for (int i = 0, _n = 4; i < _n; ++i)q.push_back(pp[i].rot(a));
	for (int i = 0, _n = 4; i < _n; ++i)p=p.cut(ln(q[i],q[(i+1)%4]));
	printf("%.12lf\n",p.area());
	return 0;
}

