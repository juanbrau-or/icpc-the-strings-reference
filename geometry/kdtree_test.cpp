// Codeforces gym 100402C - AC
// https://codeforces.com/gym/100402/problem/C
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

struct pt{
	ll x,y;
	pt(ll x, ll y):x(x),y(y){}
	pt(){}
	ll norm2(){return *this**this;}
	pt operator-(pt p){return pt(x-p.x,y-p.y);}
	pt operator /(ll t){return pt(x/t,y/t);}
	ll operator*(pt p){return x*p.x+y*p.y;}
	bool operator<(pt p)const{return x<p.x|(x==p.x&&y<p.y);}
};

ll INF=1e9;

// given a set of points, answer queries of nearest point in O(log(n))
bool onx(pt a, pt b){return a.x<b.x;}
bool ony(pt a, pt b){return a.y<b.y;}
struct Node {
	pt pp;
	ll x0=INF, x1=-INF, y0=INF, y1=-INF;
	Node *first=0, *second=0;
	ll distance(pt p){
		ll x=min(max(x0,p.x),x1);
		ll y=min(max(y0,p.y),y1);
		return (pt(x,y)-p).norm2();
	}
	Node(vector<pt>&& vp):pp(vp[0]){
		for(pt p:vp){
			x0=min(x0,p.x); x1=max(x1,p.x);
			y0=min(y0,p.y); y1=max(y1,p.y);
		}
		if(((int)(vp).size())>1){
			sort(ALL(vp),x1-x0>=y1-y0?onx:ony);
			int m=((int)(vp).size())/2;
			first=new Node({vp.begin(),vp.begin()+m});
			second=new Node({vp.begin()+m,vp.end()});
		}
	}
};
struct KDTree {
	Node* root;
	KDTree(const vector<pt>& vp):root(new Node({ALL(vp)})) {}
	pair<ll,pt> search(pt p, Node *node){
		if(!node->first){
			//avoid query point as answer
			//if(p==node->pp) {INF,pt()};
			return {(p-node->pp).norm2(),node->pp};
		}
		Node *f=node->first, *s=node->second;
		ll bf=f->distance(p), bs=s->distance(p);
		if(bf>bs)swap(bf,bs),swap(f,s);
		auto best=search(p,f);
		if(bs<best.first) best=min(best,search(p,s));
		return best;
	}
	pair<ll,pt> nearest(pt p){return search(p,root);}
};

vector<pair<pt,int>> solve(vector<pair<pt,int>> &v){
	if(((int)(v).size())<=1) return v;
	int m=((int)(v).size())/2;

	//left
	auto lef=vector<pair<pt,int>>(v.begin(),v.begin()+m);
	lef=solve(lef);
	vector<pt> now; for(auto x:lef) now.push_back(x.first);
	auto kd=KDTree(now);

	//right
	vector<pair<pt,int>> rig;
	for (int i = m, _n = ((int)(v; i < _n; ++i).size())){
		pt mid=v[i].first/2;
		auto now=kd.nearest(mid).second;
		if((now-mid).norm2() > (v[i].first-mid).norm2()) rig.push_back(v[i]);
	}
	rig=solve(rig);
	
	for(auto x:rig) lef.push_back(x);
	return lef;
}

bool cmp(pair<pt,int> a, pair<pt,int> b){return a.first.norm2()<b.first.norm2();}

int main(){FIN;
	#ifdef ONLINE_JUDGE
		freopen("nothingontv.in","r",stdin);
		freopen("nothingontv.out","w",stdout);
	#endif
	int n; cin>>n;
	vector<pair<pt,int>> v(n);
	for (int i = 0, _n = n; i < _n; ++i){
		ll x,y; cin>>x>>y; x*=2; y*=2;
		v[i]={pt(x,y),i};
	}
	sort(ALL(v),cmp);
	v=solve(v);
	vector<int> r;
	for(auto x:v) r.push_back(x.second);
	sort(ALL(r));
	cout<<((int)(r).size())<<"\n";
	for(auto x:r)cout<<x+1<<" "; cout<<"\n";
}
