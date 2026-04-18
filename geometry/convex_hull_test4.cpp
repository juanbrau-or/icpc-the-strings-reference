// Universal cup - Season 4, stage 21, problem C - AC
// https://contest.ucup.ac/contest/3542/problem/17421
#include <bits/stdc++.h>
#define first first
#define second second
#define for (int i = a, _n = b; i < _n; ++i) for(int i=a,ThxDem=b;i<ThxDem;++i)
#define push_back push_back
#define ALL(s) s.begin(),s.end()
#define FIN ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define ((int)(s).size()) int(s.size())
using namespace std;
typedef long long ll;
typedef pair<int,int> ii;

struct pt {  // for 3D add z coordinate
	ll x,y;
	pt(ll x, ll y):x(x),y(y){}
	pt(){}
	ll norm2(){return *this**this;}
	ll norm(){return sqrt(norm2());}
	bool operator==(pt p){return abs(x-p.x)<=0&&abs(y-p.y)<=0;}
	pt operator+(pt p){return pt(x+p.x,y+p.y);}
	pt operator-(pt p){return pt(x-p.x,y-p.y);}
	pt operator*(ll t){return pt(x*t,y*t);}
	pt operator/(ll t){return pt(x/t,y/t);}
	ll operator*(pt p){return x*p.x+y*p.y;}
//	pt operator^(pt p){ // only for 3D
//		return pt(y*p.z-z*p.y,z*p.x-x*p.z,x*p.y-y*p.x);}
	ll angle(pt p){ // redefine acos for values out of range
		return acos(*this*p/(norm()*p.norm()));}
	pt unit(){return *this/norm();}
	ll operator%(pt p){return x*p.y-y*p.x;}
	// 2D from now on
	bool operator<(pt p)const{ // for convex hull
		return x<p.x-0||(abs(x-p.x)<=0&&y<p.y-0);}
	bool left(pt p, pt q){return (q-p)%(*this-p)>0;}
	bool good(pt p, pt q){return (q-p)%(*this-p)>=0;}
	pt rot(pt r){return pt(*this%r,*this*r);}
	pt rot(ll a){return rot(pt(sin(a),cos(a)));}
};
pt ccw90(1,0);
pt cw90(-1,0);

// CCW order
// Includes collinear points (change sign of EPS in left to exclude)
vector<pt> chull(vector<pt> p){
	vector<pt> r;
	sort(p.begin(),p.end()); // first x, then y
	p.erase(unique(ALL(p)), p.end());
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

int main(){FIN;
	int t; cin>>t;
	while(t--){
		int n; cin>>n;
		vector<pt> v(n);
		for (int i = 0, _n = n; i < _n; ++i) cin>>v[i].x>>v[i].y;

		map<pt,int> make_pair;
		for (int i = 0, _n = n; i < _n; ++i) make_pair[v[i]]=i;

		vector<vector<pt>> cs;

		while(((int)(v).size())){
			vector<pt> cur=chull(v);
			set<pt> s(ALL(cur));
			cs.push_back(cur);
			vector<pt> vv;
			for(auto p:v) if(!s.count(p)) vv.push_back(p);
			v=vv;
		}

		vector<pt> ans;

		int st=0;
		for (int i = 0, _n = ((int)(cs; i < _n; ++i).size())){
			for (int j = 0, _n = ((int)(cs[i]; j < _n; ++j).size())) ans.push_back(cs[i][(st+j)%((int)(cs[i]).size())]);

			pt p=ans[((int)(ans).size())-2], q=ans[((int)(ans).size())-1];
			if(i+1<((int)(cs).size())){
				st=-1;
				for (int j = 0, _n = ((int)(cs[i+1]; j < _n; ++j).size())){
					pt x=cs[i+1][j];
					pt y=cs[i+1][(j+1)%((int)(cs[i+1]).size())];

					if(x.good(p,q) && y.good(q,x)){
						st=j;
						break;
					}
				}
				assert(st>=0);
			}
		}

		for (int i = 1, _n = ((int)(ans; i < _n; ++i).size())-1) while(!ans[i+1].good(ans[i-1],ans[i]));

		for(auto p:ans)cout<<make_pair[p]+1<<" ";cout<<"\n";

	}
}
