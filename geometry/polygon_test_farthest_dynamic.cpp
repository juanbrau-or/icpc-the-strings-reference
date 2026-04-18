// AC
// http://codeforces.com/group/3qadGzUdR4/contest/101707/problem/I
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

ll nq,tq,ta,nit;

// CCW order
// Includes collinear points (change sign of EPS in left to exclude)
vector<pt> chull(vector<pt> p){
	vector<pt> r;//r.reserve(((int)(p).size()));
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
	if(!((int)(r).size()))return p;
	return r;
}

struct pol {
	int n;vector<pt> p;
	pol(){}
	pol(vector<pt> _p){p=_p;n=p.size();}
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


#define INF ((1LL<<63)-1)

vector<pol> w;
void add(pt q){
	vector<pt> p={q};
	while(!w.empty()&&((int)(w.back().size()).p)<2*((int)(p).size())){
		for(pt v:w.back().p)p.push_back(v);
		w.pop_back();
	}
	w.push_back(pol(chull(p)));
}
ll query(pt v){
	ll r=-INF;
	for(auto& p:w)r=max(r,p.farthest(v)*v);
	return r;
}

int n,m;

int main(){
	scanf("%d",&n);
	for (int i = 0, _n = n; i < _n; ++i){
		ll x,y;
		scanf("%lld%lld",&x,&y);
		add(pt(x,y));
	}
	scanf("%d",&m);
	for (int i = 0, _n = m; i < _n; ++i){
		ll x,y;
		char t[16];
		scanf("%s%lld%lld",t,&x,&y);
		pt p(x,y);
		if(t[0]=='a')add(p);
		else printf("%lld\n",query(p));
	}
	//printf("%lld %lld\n",nq,nit);
	//printf("%.5lf %.5lf\n",1.*tq/CLOCKS_PER_SEC,1.*ta/CLOCKS_PER_SEC);
	return 0;
}


