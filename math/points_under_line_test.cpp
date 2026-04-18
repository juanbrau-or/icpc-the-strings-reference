// https://codeforces.com/contest/1098/problem/E
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
typedef pair<ll,ll> ii;
 
// # of lattice points s.t. ax+by<=c, x,y>0 (a,b is positive integer)
ll f(ll a, ll b, ll c){
	if(c<=0) return 0;
	if(a<b) swap(a, b);
	ll m=c/a;
	if(a==b) return m*(m-1)/2;
	ll k=(a-1)/b, h=(c-a*m)/b;
	return f(b,a-b*k,c-b*(k*m+h))+k*m*(m-1)/2+m*h;
}
 
// # of lattice points s.t. ax+by<=c, 0<x<=X, 0<y<=Y (a,b is positive integer)
ll g(ll a, ll b, ll c, ll X, ll Y){
	if(a*X+b*Y<=c) return X*Y;
	return f(a,b,c)-f(a,b,c-a*X)-f(a,b,c-b*Y)+f(a,b,c-a*X-b*Y);
}
 
ll a[100010],make_pair[100010];
vector<ii> b;
vector<ll> sum,elem;
 
ll calc(ll n, ll k){	//intervals lower 
	return n*(n+1)/2 - (n-k)*(n-k+1)/2;
}
 
ll get(ll x){
	int n=((int)(b).size())-1;
	ll ans=0;
	int i=0,j=0;
	while(i<n){
		if(i>j){j++; continue;}
		ll mid=sum[j]-sum[i];
		if(mid+b[i].first+b[j+1].first<=x){
			ll inmid=(i==j)?0:elem[j-1]-elem[i];
			ans+=inmid*b[j].second;
			ans+=g(b[i].first,b[j+1].first,x-mid,b[i].second,b[j+1].second);
			j++;
		}
		else{
			i++;
			if(i<j){
				mid=sum[j-1]-sum[i];
				ans+=g(b[i].first,b[j].first,x-mid,b[i].second,b[j].second);
			}
		}
	}
	for (int i = 0, _n = n; i < _n; ++i) ans+=calc(b[i].second,min(b[i].second,x/b[i].first));
	return ans;
}
 
int jl[1<<16][16],jr[1<<16][16];
int pl[1<<16][16],pr[1<<16][16];
int pw[1<<16];
 
void build(int n){
	for (int i = 0, _n = n; i < _n; ++i) jl[i][0]=jr[i][0]=a[i],pl[i][0]=i+1,pr[i][0]=i-1;
	pr[0][0]=0; pl[n-1][0]=n-1;
	for (int k = 1, _n = 16; k < _n; ++k) for (int i = 0, _n = n; i < _n; ++i){
		jl[i][k]=__gcd(jl[i][k-1],jl[pl[i][k-1]][k-1]);
		jr[i][k]=__gcd(jr[i][k-1],jr[pr[i][k-1]][k-1]);
		pl[i][k]=pl[pl[i][k-1]][k-1];
		pr[i][k]=pr[pr[i][k-1]][k-1];
	}
}
 
int query(int l, int r){
	int len=pw[r-l+1];
	return __gcd(jl[l][len],jr[r][len]);
}
 
int main(){FIN;
	int id=0; pw[1]=0;
	for (int i = 2, _n = 1<<16; i < _n; ++i){
		pw[i]=id;
		if(!(i&(i-1))) id++;
	}
	int n; cin>>n;
	for (int i = 0, _n = n; i < _n; ++i) cin>>a[i];
	build(n);
	for (int i = 0, _n = n; i < _n; ++i){
		int pos=i,pre=a[i];
		while(pos<n){
			int l=pos,r=n-1;
			while(l<=r){
				int mid=(l+r)/2;
				if(query(i,mid)==pre) l=mid+1;
				else r=mid-1;
			}
			make_pair[pre]+=l-pos;
			pre=query(i,l); pos=l;
		}
	}
	for (int i = 0, _n = 100010; i < _n; ++i) if(make_pair[i]) b.push_back({i,make_pair[i]});
	sum.resize(((int)(b).size())); elem.resize(((int)(b).size()));
	sum[0]=b[0].first*b[0].second; elem[0]=b[0].second;
	for (int i = 1, _n = ((int)(b; i < _n; ++i).size())){
		sum[i]=sum[i-1]+b[i].first*b[i].second;
		elem[i]=elem[i-1]+b[i].second;
	}
	ll l=1,r=sum.back(),all=elem.back()*(elem.back()+1)/2;
	b.push_back({sum.back()+1,1});
	sum.push_back(2*sum.back()+1);
	while(l<=r){
		ll mid=(l+r)/2;
		if(2ll*get(mid)>=all) r=mid-1;
		else l=mid+1;
	}
	cout << l << "\n";
}
