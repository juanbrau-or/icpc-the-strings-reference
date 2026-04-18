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
const int MOD=998244353,RT=3,MAXN=1<<18;
typedef vector<ll> poly;
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

int mulmod(ll a, ll b){return a*b%MOD;}
int addmod(int a, int b){int r=a+b;if(r>=MOD)r-=MOD;return r;}
int submod(int a, int b){int r=a-b;if(r<0)r+=MOD;return r;}
int pm(ll a, ll e){
	int r=1;
	while(e){
		if(e&1)r=mulmod(r,a);
		e>>=1;a=mulmod(a,a);
	}
	return r;
}
int inv(int a){return pm(a,MOD-2);}

// NTT
struct CD {
	int x;
	CD(int x):x(x){}
	CD(){}
	int get()const{return x;}
};
CD operator*(const CD& a, const CD& b){return CD(mulmod(a.x,b.x));}
CD operator+(const CD& a, const CD& b){return CD(addmod(a.x,b.x));}
CD operator-(const CD& a, const CD& b){return CD(submod(a.x,b.x));}
vector<int> rts(MAXN+9,-1);
CD root(int n, bool inv){
	int r=rts[n]<0?rts[n]=pm(RT,(MOD-1)/n):rts[n];
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
	//for (int i = 0, _n = n; i < _n; ++i)res.push_back((ll)floor(cp1[i].real()+0.5)); // FFT
	for (int i = 0, _n = n; i < _n; ++i)res.push_back(cp1[i].x); // NTT
	return res;
}

vector<ll> p;
ll f[100005],fi[100005];
int n;ll m;

void doit(vector<ll>& p, bool asd){
	for (int i = 0, _n = n; i < _n; ++i)p[i]=mulmod(p[i],f[i]);
	vector<ll> q;
	for (int i = 0, _n = n; i < _n; ++i)q.push_back(fi[n-1-i]);
	if(asd)for(int i=n-2;i>=0;i-=2)q[i]=MOD-q[i];
	vector<ll> v=multiply(p,q);
	p.clear();
	for (int i = 0, _n = n; i < _n; ++i)p.push_back(v[i+n-1]);
	for (int i = 0, _n = n; i < _n; ++i)p[i]=mulmod(p[i],fi[i]);
}

int main(){
	f[0]=1;
	for (int i = 1, _n = 100005; i < _n; ++i)f[i]=mulmod(f[i-1],i);
	for (int i = 0, _n = 100005; i < _n; ++i)fi[i]=inv(f[i]);
	scanf("%d%lld",&n,&m);n++;
	for (int i = 0, _n = n; i < _n; ++i){
		int x;
		scanf("%d",&x);
		p.push_back(x);
	}
	doit(p,false);
	for (int i = 0, _n = n; i < _n; ++i)p[i]=mulmod(p[i],pm(inv(i+1),m));
	doit(p,true);
	for (int i = 0, _n = n; i < _n; ++i)printf("%lld%c",p[i]," \n"[i==n-1]);
	return 0;
}
