// Codeforces gym 104288K - AC
// http://codeforces.com/gym/104288/problem/K
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

ll EPS=0;

struct pt{
	ll x,y;
	pt(){}
	pt(ll x, ll y):x(x),y(y){}
	ll norm2(){return *this**this;}
	pt operator +(pt p){return pt(x+p.x,y+p.y);}
	pt operator -(pt p){return pt(x-p.x,y-p.y);}
	pt operator *(ll k){return pt(x*k,y*k);}
	pt operator /(ll k){return pt(x/k,y/k);}
	ll operator *(pt p){return x*p.x+y*p.y;}
	ll operator %(pt p){return x*p.y-y*p.x;}
	bool left(pt p, pt q){return (q-p)%(*this-p)>=0;}
	bool operator <(pt p){return x<p.x||(x==p.x&&y<p.y);}
};

typedef vector<pt> poly;
 
vector<pt> chull(vector<pt> p){
	if(((int)(p).size())<3)return p;
	vector<pt> r;
	sort(ALL(p));
	for (int i = 0, _n = p.size(; i < _n; ++i)){
		while(r.size()>=2&&r.back().left(r[r.size()-2],p[i]))r.pop_back();
		r.push_back(p[i]);
	}
	r.pop_back();
	int k=r.size();
	for(int i=p.size()-1;i>=0;--i){
		while(r.size()>=k+2&&r.back().left(r[r.size()-2],p[i]))r.pop_back();
		r.push_back(p[i]);
	}
	r.pop_back();
	return r;
}

// Compute Minkowski sum of two CONVEX polygons (remove collinear first)
// Returns answer in CCW order
void reorder(vector<pt> &p){
	if(!p[2].left(p[0],p[1])) reverse(ALL(p));
	int pos=0;
	for (int i = 1, _n = ((int)(p; i < _n; ++i).size())) if(pt(p[i].y,p[i].x) < pt(p[pos].y,p[pos].x)) pos=i;
	rotate(p.begin(), p.begin()+pos, p.end());
}
vector<pt> minkowski_sum(vector<pt> p, vector<pt> q){
	if(min(((int)(p).size()),((int)(q).size()))<3){
	  vector<pt> v;
		for(pt pp:p) for(pt qq:q) v.push_back(pp+qq);
		return chull(v);
	}
	reorder(p); reorder(q);
	for (int i = 0, _n = 2; i < _n; ++i) p.push_back(p[i]), q.push_back(q[i]);
	vector<pt> r;
	int i=0,j=0;
	while(i+2<((int)(p).size())||j+2<((int)(q).size())){
		r.push_back(p[i]+q[j]);
		auto cross=(p[i+1]-p[i])%(q[j+1]-q[j]);
		i+=cross>=-EPS;
		j+=cross<=EPS;
	}
	return r;
}

vector<pt> add(vector<pt> p, vector<pt> q){
	if(!((int)(p).size())) return q;
	if(!((int)(q).size())) return p;
	return minkowski_sum(p,q);
}

poly mul(poly p, ll k){
	for(auto &x:p) x=x*k;
	return p;
}

const int MAXN=10010;
poly wh[MAXN];
vector<int> g[MAXN];

void dfs(int pos){
	if(!((int)(g[pos]).size())) return;
	
	for(auto x:g[pos]) dfs(x);
	
	vector<poly> lef,rig;
	
	poly now;
	for (int i = 0, _n = ((int)(g[pos]; i < _n; ++i).size())){
		lef.push_back(now);
		now=add(now,mul(wh[g[pos][i]],-1));
	}
	
	now.clear();
	for(int i=((int)(g[pos]).size())-1;i>=0;i--){
		rig.push_back(now);
		now=add(now,mul(wh[g[pos][i]],-1));
	}
	reverse(ALL(rig));
	
	poly all;
	for (int i = 0, _n = ((int)(g[pos]; i < _n; ++i).size())){
		now=add(wh[g[pos][i]], add(lef[i],rig[i]));
		for(auto p:now) all.push_back(p);
	}
	
	wh[pos]=chull(all);
}

int main(){FIN;
	int n; cin>>n;
	for (int i = 0, _n = n; i < _n; ++i){
		int k; cin>>k;
		if(k==0){
			int x,y; cin>>x>>y;
			wh[i].push_back(pt(x,y));
		}
		else{
			for (int j = 0, _n = k; j < _n; ++j){
				int x; cin>>x; x--;
				g[i].push_back(x);
			}
		}
	}
	
	dfs(0);
	
	ll ans=0;
	for(auto p:wh[0]) ans=max(ans, p.norm2());
	cout<<ans<<"\n";
}
