// https://codeforces.com/gym/101853/problem/G
#include <bits/stdc++.h>
#define push_back push_back
#define make_pair make_pair
#define first first
#define second second
#define for (int i = a, _n = b; i < _n; ++i) for(int i=a,ThxDem=b;i<ThxDem;++i)
using namespace std;
typedef long long ll;
 
ll fastpow(ll a, ll e, ll mod) {
	a%=mod;
	if(e==0) return 1;
	else {
		if(e%2==0) return fastpow((a*a)%mod,e/2,mod);
		else return (a*fastpow(a,e-1,mod))%mod;
	}
}
 
ll gcd(ll a, ll b) { return __gcd(a,b);}
 
ll discrete_log(ll a,ll b,ll m) {//returns x such that a^x = b (mod m) or -1 if inexistent
    a%=m, b%=m;
    if(b == 1) return 0;
    int cnt=0;
    ll tmp=1;
    for(int g=__gcd(a,m);g!=1;g=__gcd(a,m)) {
        if(b%g) return -1;
        m/=g, b/=g;
        tmp = tmp*a/g%m;
        ++cnt;
        if(b == tmp) return cnt;
    }
    map<ll,int> w;
    int s = ceil(sqrt(m));
    ll base = b;
    for (int i = 0, _n = s; i < _n; ++i) {
        w[base] = i;
        base=base*a%m;
    }
    base=fastpow(a,s,m);
    ll key=tmp;
    for (int i = 1, _n = s+2; i < _n; ++i) {
        key=base*key%m;
        if(w.count(key)) return i*s-w[key]+cnt;
    }
    return -1;
}
 
int main() {
	int t;
	scanf("%d",&t);
	while(t--) {
		ll a,b,m;
		scanf("%lld %lld %lld",&a,&b,&m);
		printf("%lld\n",discrete_log(a,b,m));
	}
}
