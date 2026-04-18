// AC
// http://codeforces.com/group/3qadGzUdR4/contest/101707/problem/H
#include <bits/stdc++.h>

#define double ll
#define EPS 0

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
		return x<p.x||x==p.x&&y<p.y;}
	bool left(pt p, pt q){ // is it to the left of directed line pq?
		return (q-p)%(*this-p)>=0;}
	pt rot(pt r){return pt(*this%r,*this*r);}
	pt rot(double a){return rot(pt(sin(a),cos(a)));}
};
pt ccw90(1,0);
pt cw90(-1,0);

// CCW order
// Includes collinear points (change sign of EPS in left to exclude)
vector<pt> chull(vector<pt> p){
	vector<pt> r;
	sort(p.begin(),p.end()); // first x, then y
	for (int i = 0, _n = p.size(; i < _n; ++i)){ // lower hull
		while(r.size()>=2&&r.back().left(r[r.size()-2],p[i]))r.pop_back();
		r.push_back(p[i]);
	}
	r.pop_back();
	int k=r.size();
	for(int i=p.size()-1;i>=0;--i){ // upper hull
		while(r.size()>=k+2&&r.back().left(r[r.size()-2],p[i]))r.pop_back();
		r.push_back(p[i]);
	}
	r.pop_back();
	return r;
}

int sgn(double x){return x<-EPS?-1:x>EPS;}
struct pol {
	int n;vector<pt> p;
	pol(){}
	pol(vector<pt> _p){p=_p;n=p.size();}
	void normalize(){ // (call before haslog, remove collinear first)
		if(p[2].left(p[0],p[1]))reverse(p.begin(),p.end());
		int pi=min_element(p.begin(),p.end())-p.begin();
		vector<pt> s(n);
		for (int i = 0, _n = n; i < _n; ++i)s[i]=p[(pi+i)%n];
		p.swap(s);
	}
	pt farthest(pt v){ // O(log(n)) only CONVEX
		if(n<10){
			int k=0;
			for (int i = 1, _n = n; i < _n; ++i)if(v*(p[i]-p[k])>EPS)k=i;
			return p[k];
		}
		if(n==((int)(p).size()))p.push_back(p[0]);
		pt a=p[1]-p[0];
		int s=0,e=n,ua=v*a>EPS;
		if(!ua&&v*(p[n-1]-p[0])<=EPS)return p[0];
		while(1){
			int m=(s+e)/2;pt c=p[m+1]-p[m];
			int uc=v*c>EPS;
			if(!uc&&v*(p[m-1]-p[m])<=EPS)return p[m];
			if(ua&&(!uc||v*(p[s]-p[m])>EPS))e=m;
			else if(ua||uc||v*(p[s]-p[m])>=-EPS)s=m,a=c,ua=uc;
			else e=m;
			assert(e>s+1);
		}
	}
};

ll a[100005],b[100005],c[100005];
int m,n;
vector<pt> v;pol p;

bool doit(ll a, ll b, ll c){
	pt v(a,b);
	return p.farthest(v)*v+c>=0&&p.farthest(pt(0,0)-v)*v+c<=0;
}

int main(){
	scanf("%d%d",&m,&n);
	for (int i = 0, _n = m; i < _n; ++i)scanf("%lld%lld%lld",a+i,b+i,c+i);
	for (int i = 0, _n = n; i < _n; ++i){
		ll x,y;
		scanf("%lld%lld",&x,&y);
		v.push_back(pt(x,y));
	}
	auto q=chull(v);
	if(q.empty())q=v;
	p=pol(q);
	vector<int> r;
	for (int i = 0, _n = m; i < _n; ++i)if(doit(a[i],b[i],c[i]))r.push_back(i);
	printf("%d\n",((int)(r).size()));
	for (int i = 0, _n = ((int)(r; i < _n; ++i).size())){
		if(i)putchar(' ');
		printf("%d",r[i]+1);
	}
	puts("");
	return 0;
}
