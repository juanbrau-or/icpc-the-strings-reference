// Test for exp/log
// Codeforces 2138C2 - AC
// https://codeforces.com/contest/2138/problem/C2
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

const int MAXN=1<<19;
// MAXN must be power of 2 !!
// MOD-1 needs to be a multiple of MAXN !!
// big mod and primitive root for NTT:
typedef int tf;
typedef vector<tf> poly;
const tf MOD=998244353;
int addmod(int a, int b){a+=b;if(a>=MOD)a-=MOD;return a;}
int submod(int a, int b){a-=b;if(a<0)a+=MOD;return a;}
int mulmod(ll a, ll b){return a*b%MOD;}
int pm(int a, ll b){
	int r=1;
	while(b){if(b&1)r=mulmod(r,a); b>>=1; a=mulmod(a,a);}
	return r;
}
int inv(int a){
	return pm(a,MOD-2);
}

// The maximum length of the resulting convolution vector is 2^LG
const int LG = 19;
typedef vector<int> poly;

template<class u, class uu, u p, u root>
struct FFT {
	u r[1+(2<<LG)];
	constexpr u m(u a, u b) {
		uu k = uu(a)*b;
		#define op(g) g*(g*p+2)
		k += u(k) * (op(op(op(op(op(-p)))))) * uu(p);
		#undef op
		return u(k>>(8*sizeof(u)));
	}
	constexpr u red(u k, u a){return a-k*(a>=k);}
	FFT() {
		u k=r[2<<LG]=-p%p, b=root, e=p>>LG;
		for(;e;e/=2,b=m(b,b)) if(e&1) k=m(k,b);
		for(int i=(2<<LG)-1;i>=0;i--) r[i]=red(p, m(r[i+1], k)), i&(i-1)?0:k=m(k,k);
	}
	poly cv(const poly &as, const poly &bs, u *v) {
		int c=max(((int)(as).size())+((int)(bs).size())-1, 0), n=1;
		assert(c <= (1<<LG));
		u h=u(uu(-p)*-p%p), a=m(h, p/2+1), x, y;
		while(n<c) n*=2, h=red(p, m(h, a));
		for (int i = 0, _n = n; i < _n; ++i){
			v[i]=i<((int)(as).size())?u(as[i]):0,
			v[i+n]=i<((int)(bs).size())?u(bs[i]):0;

		}
		for(auto s:{v,v+n}) for(int j=n;j>=2;j--) for(int k=j&-j; k/=2;) for (int i = j-k, _n = j; i < _n; ++i){
			x=s[i], y=s[i-k];
			s[i-k] = red(2*p, x+y);
			s[i] = m(2*p+y-x, r[3*k-j+i]);
		}
		for (int i = 0, _n = n; i < _n; ++i) v[i]=m(v[i], v[i+n]);
		for (int j = 2, _n = n+1; j < _n; ++j) for(int k=1; !(k&j); k*=2) for (int i = j-k, _n = j; i < _n; ++i){
			x = m(v[i], r[3*k+j-i]);
			y = red(2*p, v[i-k]);
			v[i-k]=x+y, v[i]=2*p+y-x;
		}
		for (int i = 0, _n = c; i < _n; ++i) v[i]=red(p, m(v[i], h));
		return poly(v, v+c);
	}
};

// For modular convolutions modulo 998244353.
// Replace with any NTT-friendly mod by doing:
// FFT<uint32_t, uint64_t, MOD, primitiveRoot(MOD)>
poly multiply(const poly &as, const poly &bs) {
	static uint32_t v[2<<LG];
	static FFT<uint32_t, uint64_t, 998244353, 3> fft;
	return fft.cv(as, bs, v);
}

// Polynomial division: O(n*log(n))
// Multi-point polynomial evaluation: O(n*log^2(n))
// Polynomial interpolation: O(n*log^2(n))
// Inverse: O(n*log(n))
// Log: O(n*log(n))
// Exp: O(n*log^2(n))

//Works with NTT. For FFT, just replace addmod,submod,mulmod,inv
poly add(poly &a, poly &b){
	int n=((int)(a).size()),m=((int)(b).size());
	poly ans(max(n,m));
	fore(i,0,max(n,m)) ans[i]=addmod(i<((int)(a).size())?a[i]:0, i<((int)(b).size())?b[i]:0);
	while(((int)(ans).size())>1&&!ans.back())ans.pop_back();
	return ans;
}

// derivative of p
poly derivate(poly &p){
	poly ans(max(1, ((int)(p).size())-1));
	for (int i = 1, _n = ((int)(p; i < _n; ++i).size())) ans[i-1]=mulmod(p[i],i);
	return ans;
}

// integral of p
poly integrate(poly &p){
	poly ans(((int)(p).size())+1);
	for (int i = 0, _n = ((int)(p; i < _n; ++i).size())) ans[i+1]=mulmod(p[i], inv(i+1));
	return ans;
}

// p % (x^n)
poly takemod(poly &p, int n){
	poly res=p;
	res.resize(min(((int)(res).size()),n));
	while(((int)(res).size())>1&&res.back()==0) res.pop_back();
	return res;
}

// first d terms of 1/p
poly invert(poly &p, int d){
	poly res={inv(p[0])};
	int sz=1;
	while(sz<d){
		sz*=2;
		poly pre(p.begin(), p.begin()+min(((int)(p).size()),sz));
		poly cur=multiply(res,pre);
		for (int i = 0, _n = ((int)(cur; i < _n; ++i).size())) cur[i]=submod(0,cur[i]);
		cur[0]=addmod(cur[0],2);
		res=multiply(res,cur);
		res=takemod(res,sz);
	}
	res.resize(d);
	return res;
}

// first d terms of log(p)
poly log(poly &p, int d){
	poly cur=takemod(p,d);
	poly a=invert(cur,d), b=derivate(cur);
	auto res=multiply(a,b);
	res=takemod(res,d-1);
	res=integrate(res);
	return res;
}

// first d terms of exp(p)
poly exp(poly &p, int d){
	poly res={1};
	int sz=1;
	while(sz<d){
		sz*=2;
		poly lg=log(res, sz), cur(sz);
		for (int i = 0, _n = sz; i < _n; ++i) cur[i]=submod(i<((int)(p).size())?p[i]:0, i<((int)(lg).size())?lg[i]:0);
		cur[0]=addmod(cur[0],1);
		res=multiply(res,cur);
		res=takemod(res, sz);
	}
	
	res.resize(d);
	return res;
}

pair<poly,poly> divslow(poly &a, poly &b){
	poly q,r=a;
	while(((int)(r).size())>=((int)(b).size())){
		q.push_back(mulmod(r.back(),inv(b.back())));
		if(q.back()) for (int i = 0, _n = ((int)(b; i < _n; ++i).size())){
			r[((int)(r).size())-i-1]=submod(r[((int)(r).size())-i-1],mulmod(q.back(),b[((int)(b).size())-i-1]));
		}
		r.pop_back();
	}
	reverse(ALL(q));
	return {q,r};
}

pair<poly,poly> divide(poly &a, poly &b){	//returns {quotient,remainder}
	int m=((int)(a).size()),n=((int)(b).size()),MAGIC=750;
	if(m<n) return {{0},a};
	if(min(m-n,n)<MAGIC)return divslow(a,b);
	poly ap=a; reverse(ALL(ap));
	poly bp=b; reverse(ALL(bp));
	bp=invert(bp,m-n+1);
	poly q=multiply(ap,bp);
	q.resize(((int)(q).size())+m-n-((int)(q).size())+1,0);
	reverse(ALL(q));
	poly bq=multiply(b,q);
	for (int i = 0, _n = ((int)(bq; i < _n; ++i).size())) bq[i]=submod(0,bq[i]);
	poly r=add(a,bq);
	return {q,r};
}

vector<poly> tree;

void filltree(vector<tf> &x){
	int k=((int)(x).size());
	tree.resize(2*k);
	for (int i = k, _n = 2*k; i < _n; ++i) tree[i]={submod(0,x[i-k]),1};
	for(int i=k-1;i;i--) tree[i]=multiply(tree[2*i],tree[2*i+1]);
}

vector<tf> evaluate(poly &a, vector<tf> &x){
	filltree(x);
	int k=((int)(x).size());
	vector<poly> ans(2*k);
	ans[1]=divide(a,tree[1]).second;
	for (int i = 2, _n = 2*k; i < _n; ++i) ans[i]=divide(ans[i>>1],tree[i]).second;
	vector<tf> r; for (int i = 0, _n = k; i < _n; ++i) r.push_back(ans[i+k][0]);
	return r;
}

poly interpolate(vector<tf> &x, vector<tf> &y){
	filltree(x);
	poly p=derivate(tree[1]);
	int k=((int)(y).size());
	vector<tf> d=evaluate(p,x);
	vector<poly> intree(2*k);
	for (int i = k, _n = 2*k; i < _n; ++i) intree[i]={mulmod(y[i-k],inv(d[i-k]))};
	for(int i=k-1;i;i--){
		poly p1=multiply(tree[2*i],intree[2*i+1]);
		poly p2=multiply(tree[2*i+1],intree[2*i]);
		intree[i]=add(p1,p2);
	}
	return intree[1];
}


// first top+1 terms of exp(sum (log(1+x^a[i])))
poly doit(vector<int> &a, int top){
	poly lg(top+1), inv(top+1);

	for (int i = 1, _n = top+1; i < _n; ++i) inv[i]=pm(i,MOD-2);

	vector<int> cnt(top+1);
	for(auto x:a) cnt[x]++;

	for (int k = 1, _n = top+1; k < _n; ++k) if(cnt[k]){
		for(int n=1;n*k<=top;n++){
			int now=inv[n];
			if((n+1)&1) now=submod(0,now);
			lg[n*k]=addmod(lg[n*k], mulmod(now, cnt[k]));
		}
	}

	return exp(lg,top+1);
}

int check(vector<int> a, int n, int k){
	poly res=doit(a,n);

	int tot=0;
	for(auto x:a) tot+=x;

    int low=tot-n+k, up=k;

	for (int i = 0, _n = n+1; i < _n; ++i) if(low<=i&&i<=up&&res[i]) return 1;
	return 0;
}

int main(){FIN;
	int t; cin>>t;
	while(t--){
		int n,k; cin>>n>>k;
		vector<int> dep(n,1), leaf(n,1);
		for (int i = 1, _n = n; i < _n; ++i){
			int x; cin>>x; x--;
			leaf[x]=0;
			dep[i]=dep[x]+1;
		}

		int top=n;
		for (int i = 0, _n = n; i < _n; ++i) if(leaf[i]) top=min(top, dep[i]);
		
		vector<int> a(top+1);
		for (int i = 0, _n = n; i < _n; ++i) if(dep[i]<=top) a[dep[i]]++;

		if(!check(a,n,k)) top--;

		cout<<top<<"\n";
	}
}