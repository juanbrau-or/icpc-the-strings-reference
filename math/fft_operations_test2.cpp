// Stress test for exp/log functions - AC
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

const int MAXN=1<<20;
typedef int tf;
typedef vector<tf> poly;
const tf MOD=998244353,RT=5;
struct CD {
	tf x;
	CD(tf x):x(x){}
	CD(){}
};
int addmod(int a, int b){a+=b;if(a>=MOD)a-=MOD;return a;}
int submod(int a, int b){a-=b;if(a<0)a+=MOD;return a;}
int mulmod(ll a, ll b){return a*b%MOD;}
int fpow(int a, ll b){
	int r=1;
	while(b){if(b&1)r=mulmod(r,a); b>>=1; a=mulmod(a,a);}
	return r;
}
int inv(int a){return fpow(a,MOD-2);}
CD operator*(const CD& a, const CD& b){return CD(mulmod(a.x,b.x));}
CD operator+(const CD& a, const CD& b){return CD(addmod(a.x,b.x));}
CD operator-(const CD& a, const CD& b){return CD(submod(a.x,b.x));}
vector<tf> rts(MAXN+9,-1);
CD root(int n, bool inv){
	tf r=rts[n]<0?rts[n]=fpow(RT,(MOD-1)/n):rts[n];
	return CD(inv?fpow(r,MOD-2):r);
}
CD cp1[MAXN+9],cp2[MAXN+9];
int R[MAXN+9];
void dft(CD* a, int n, bool inv){
	for (int i = 0, _n = n; i < _n; ++i)if(R[i]<i)swap(a[R[i]],a[i]);
	for(int m=2;m<=n;m*=2){
		CD wi=root(m,inv);
		for(int j=0;j<n;j+=m){
			CD w(1);
			for(int k=j,k2=j+m/2;k2<j+m;k++,k2++){
				CD u=a[k];CD v=a[k2]*w;a[k]=u+v;a[k2]=u-v;w=w*wi;
			}
		}
	}
	if(inv){
		CD z(fpow(n,MOD-2));
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
	for (int i = 0, _n = n; i < _n; ++i)res.push_back(cp1[i].x);
	return res;
}

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

// first d terms of log(p)
poly log(poly &p, int d){
	assert(p[0]==1);
	poly cur=takemod(p,d);
	poly a=invert(cur,d), b=derivate(cur);
	auto res=multiply(a,b);
	res=takemod(res,d-1);
	res=integrate(res);
	return res;
}

// first d terms of exp(p)
poly exp(poly &p, int d){
	assert(!p[0]);
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

poly fast(vector<int> &a, int top){
	// the answer is exp(sum (log(1+x^a[i])))
	poly ans={0};
	for (int i = 0, _n = ((int)(a; i < _n; ++i).size())){
		poly p(a[i]+1);
		p[0]=p[a[i]]=1;
		poly now=log(p, top+1);
		ans=add(ans, now);
	}
	
	return exp(ans,top+1);
}

poly brute(vector<int> &a, int top){
	poly dp(top+1);
	dp[0]=1;
	for(auto x:a) for(int i=top;i>=x;i--) dp[i]=addmod(dp[i],dp[i-x]);
	return dp;
}

int main(){FIN;
	for (int it = 1, _n = 101; it < _n; ++it){
		int n=100;
		int mx=100;
		
		auto rnd=bind(uniform_int_distribution<int>(1,mx), mt19937(time(0)));
		
		vector<int> a(n);
		for (int i = 0, _n = n; i < _n; ++i) a[i]=rnd();
		
		auto me=fast(a,mx);
		auto he=brute(a,mx);
		
		assert(me==he);
		cout<<"OK "<<it<<endl;
	}
}
