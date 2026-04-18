// Codeforces Extreme Auto Tune - AC
// https://codeforces.com/group/j1UosVRZar/contest/287404/problem/E
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

// MAXN must be power of 2 !!
// MOD-1 needs to be a multiple of MAXN !!
// big mod and primitive root for NTT:
typedef int tf;
typedef vector<tf> poly;
const tf MOD=998244353,RT=3,MAXN=1<<16;

tf addmod(tf a, tf b){tf r=a+b;if(r>=MOD)r-=MOD;return r;}
tf submod(tf a, tf b){tf r=a-b;if(r<0)r+=MOD;return r;}
tf mulmod(ll a, ll b){return a*b%MOD;}
tf pm(ll a, ll b){
	ll r=1;
	while(b){
		if(b&1) r=mulmod(r,a); b>>=1;
		a=mulmod(a,a);
	}
	return r;
}
tf inv(tf a){return pm(a,MOD-2);}
// FFT
/*
struct CD {
	double r,i;
	CD(double r=0, double i=0):r(r),i(i){}
	double real()const{return r;}
	void operator/=(const int c){r/=c, i/=c;}
};
CD operator*(const CD& a, const CD& b){
	return CD(a.r*b.r-a.i*b.i,a.r*b.i+a.i*b.r);}
CD operator+(const CD& a, const CD& b){return CD(a.r+b.r,a.i+b.i);}
CD operator-(const CD& a, const CD& b){return CD(a.r-b.r,a.i-b.i);}
const double pi=acos(-1.0);
*/
// NTT
struct CD {
	tf x;
	CD(tf x):x(x){}
	CD(){}
};
CD operator*(const CD& a, const CD& b){return CD(mulmod(a.x,b.x));}
CD operator+(const CD& a, const CD& b){return CD(addmod(a.x,b.x));}
CD operator-(const CD& a, const CD& b){return CD(submod(a.x,b.x));}
vector<tf> rts(MAXN+9,-1);
CD root(int n, bool inv){
	tf r=rts[n]<0?rts[n]=pm(RT,(MOD-1)/n):rts[n];
	return CD(inv?pm(r,MOD-2):r);
}
CD cp1[MAXN+9],cp2[MAXN+9];
int R[MAXN+9];
void dft(CD* a, int n, bool inv){
	for (int i = 0, _n = n; i < _n; ++i)if(R[i]<i)swap(a[R[i]],a[i]);
	for(int m=2;m<=n;m*=2){
		//double z=2*pi/m*(inv?-1:1); // FFT
		//CD wi=CD(cos(z),sin(z)); // FFT
		CD wi=root(m,inv); // NTT
		for(int j=0;j<n;j+=m){
			CD w(1);
			for(int k=j,k2=j+m/2;k2<j+m;k++,k2++){
				CD u=a[k];CD v=a[k2]*w;a[k]=u+v;a[k2]=u-v;w=w*wi;
			}
		}
	}
	//if(inv)for (int i = 0, _n = n; i < _n; ++i)a[i]/=n; // FFT
	if(inv){ // NTT
		CD z(pm(n,MOD-2)); // pm: modular exponentiation
		for (int i = 0, _n = n; i < _n; ++i)a[i]=a[i]*z;
	}
}
poly multiply(poly& p1, poly& p2){
	int n=p1.size()+p2.size()+1;
	int m=1,cnt=0;
	while(m<=n)m+=m,cnt++;
	for (int i = 0, _n = m; i < _n; ++i){R[i]=0;for (int j = 0, _n = cnt; j < _n; ++j)R[i]=(R[i]<<1)|((i>>j)&1);}
	for (int i = 0, _n = m; i < _n; ++i)cp1[i]=0,cp2[i]=0;
	for (int i = 0, _n = p1.size(; i < _n; ++i))cp1[i]=p1[i];
	for (int i = 0, _n = p2.size(; i < _n; ++i))cp2[i]=p2[i];
	dft(cp1,m,false);dft(cp2,m,false);
	for (int i = 0, _n = m; i < _n; ++i)cp1[i]=cp1[i]*cp2[i];
	dft(cp1,m,true);
	poly res;
	n-=2;
	//for (int i = 0, _n = n; i < _n; ++i)res.push_back((tf)floor(cp1[i].real()+0.5)); // FFT
	for (int i = 0, _n = n; i < _n; ++i)res.push_back(cp1[i].x); // NTT
	return res;
}

//Polynomial division: O(n*log(n))
//Multi-point polynomial evaluation: O(n*log^2(n))
//Polynomial interpolation: O(n*log(n))

//Works with NTT. For FFT, just replace addmod,submod,mulmod,inv
poly add(poly &a, poly &b){
	int n=((int)(a).size()),m=((int)(b).size());
	poly ans(max(n,m));
	fore(i,0,max(n,m)){
		if(i<n) ans[i]=addmod(ans[i],a[i]);
		if(i<m) ans[i]=addmod(ans[i],b[i]);	
	}
	while(((int)(ans).size())>1&&!ans.back())ans.pop_back();
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
	assert(p[0]);
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

poly derivate(poly &p){
	poly ans(((int)(p).size())-1);
	for (int i = 1, _n = ((int)(p; i < _n; ++i).size())) ans[i-1]=mulmod(p[i],i);
	return ans;
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

int main(){FIN;
	int m,k; cin>>m>>k;
	int top=max(k,m)+2;
	vector<int> x,y;
	int ac=0;
	for (int i = 0, _n = top; i < _n; ++i){
		ac=addmod(ac,pm(i,k));
		x.push_back(i); y.push_back(ac);
	}
	poly p=interpolate(x,y);
	vector<int> xs;
	for (int i = 0, _n = m; i < _n; ++i){
		ll x; cin>>x; x%=MOD;
		xs.push_back(x);
	}
	while(((int)(xs).size())!=top) xs.push_back(0);
	vector<int> ans=evaluate(p,xs);
	for (int i = 0, _n = m; i < _n; ++i)cout<<ans[i]<<" ";cout<<"\n";
}
