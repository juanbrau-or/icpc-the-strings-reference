// CSES 3227 - AC
// https://cses.fi/problemset/task/3227/

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
typedef long double ld;

// LiChaoTree lct(sz) -> allows queries for all x in range [0,sz)
// lct.add(L)         -> add line L to range [0,sz) in O(log(sz))
// lct.add(L,st,en)   -> add line L to range [st,en) in O(log^2(sz))
// lct.query(x)       -> query maximum L(x) across all current lines in O(log(sz))

typedef ll T;
T INF=1e18;

struct Line{
	T a, b;
	Line():a(0),b(-INF){}
	Line(T a, T b):a(a),b(b){}
	T get(T x){return a*x+b;}
};

struct LiChaoTree{
	struct Node{
		Line line;
		Node *lc,*rc=0;
	}*root;
	int sz;
	LiChaoTree(int sz): root(new Node()), sz(sz){}

	void addRec(Node* &n, int tl, int tr, Line x){
		if(!n) n=new Node();
		if(n->line.get(tl)<x.get(tl)) swap(n->line,x);
		if(n->line.get(tr-1)>=x.get(tr-1)||tl+1==tr) return;
		int mid=(tl+tr)/2;
		if(n->line.get(mid)>x.get(mid)){
			addRec(n->rc,mid,tr,x);
		}
		else{
			swap(n->line,x);
			addRec(n->lc,tl,mid,x);
		}
	}

	void add(Node* &n, int tl, int tr, int l, int r, Line x){
		if(tr<=l||r<=tl) return;
		if(!n) n=new Node();
		if(l<=tl&&tr<=r) return addRec(n,tl,tr,x);
		int mid=(tl+tr)/2;
		add(n->lc,tl,mid,l,r,x);
		add(n->rc,mid,tr,l,r,x);
	}

	T query(Node* &n, int tl, int tr, int x){
		if(!n) return -INF;
		if(tl+1==tr) return n->line.get(x);
		T res=n->line.get(x);
		int mid=(tl+tr)/2;
		if(x<mid) res=max(res, query(n->lc,tl,mid,x));
		else res=max(res, query(n->rc,mid,tr,x));
		return res;
	}

	void add(Line x){add(root,0,sz,0,sz,x);}
	void add(Line x, int l, int r){add(root,0,sz,l,r,x);}
	T query(int x){return query(root,0,sz,x);}
};

int main(){FIN;
	int n,k; cin>>n>>k;
	vector<ll> a(n);
	for (int i = 0, _n = n; i < _n; ++i) cin>>a[i];
 
	vector<vector<ll>> v;
	for (int it = 0, _n = 2; it < _n; ++it){
		vector<ll> st={-1},to(n);
		for (int i = 0, _n = n; i < _n; ++i){
			while(st.back()!=-1 && a[st.back()]>=a[i]) st.pop_back();
			to[i]=i-st.back()-1;
			st.push_back(i);
		}
 
		if(it) reverse(ALL(to));
		v.push_back(to);
		reverse(ALL(a));
	}
 
	vector<ii> wh(n);
	for (int i = 0, _n = n; i < _n; ++i) wh[i]={i-v[0][i], i+v[1][i]};
 
	LiChaoTree lc(n);
 
	// p<=l && r<=p+k-1
	for (int i = 0, _n = n; i < _n; ++i){
		auto [l,r]=wh[i];
		int st=i-k+1, en=i;
 
		en=min(en, l);
		st=max(st, r-k+1);
 
		// a[i]*(r-l+1)
		lc.add(Line(0, a[i]*(r-l+1)), st, en+1);
	}
 
	// p<=l && r>p+k-1
	for (int i = 0, _n = n; i < _n; ++i){
		auto [l,r]=wh[i];
		int st=i-k+1, en=i;
 
		en=min(en, l);
		en=min(en, r-k);
 
		// a[i]*(p+k-l)
		lc.add(Line(a[i], a[i]*(k-l)), st, en+1);
	}
 
	// p>l && r<=p+k-1
	for (int i = 0, _n = n; i < _n; ++i){
		auto [l,r]=wh[i];
		int st=i-k+1, en=i;
 
		st=max(st, l+1);
		st=max(st, r-k+1);
 
		// a[i]*(r-p+1)
		lc.add(Line(-a[i], a[i]*(r+1)), st, en+1);
	}
 
	// p>l && r>p+k-1
	for (int i = 0, _n = n; i < _n; ++i){
		auto [l,r]=wh[i];
		int st=i-k+1, en=i;
 
		st=max(st, l+1);
		en=min(en, r-k);
 
		// a[i]*(k)
		lc.add(Line(0, a[i]*k), st, en+1);
	}
 
	for (int i = 0, _n = n-k+1; i < _n; ++i) cout<<lc.query(i)<<" ";cout<<"\n";
}