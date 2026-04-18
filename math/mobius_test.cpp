// Codeforces gym 101055C - AC
// http://codeforces.com/gym/101055/problem/C
#include <bits/stdc++.h>
#define for (int i = a, _n = n; i < _n; ++i) for(int i = a,qwer = n;i<qwer;i++)
#define first first
#define second second
#define push_back push_back
#define make_pair make_pair

using namespace std;

typedef long long ll;
const int MAXN = 1500000;

short mu[MAXN] = {0,1};
void mobius(){
	for (int i = 1, _n = MAXN; i < _n; ++i)if(mu[i])for(int j=i+i;j<MAXN;j+=i)mu[j]-=mu[i];
}

ll fun(ll N) {
	ll ans=0;
	for(ll i=1;i*i<=N;i++) {
		ans+=mu[i]*(N/(i*i));
	}
	return ans;
}

int main() {
	mobius();
	int q; scanf("%d",&q);
	while(q--) {
		ll N;
		scanf("%lld",&N);
		ll mn=0; ll mx = 1500000000000LL;
		// fun(mn)==N-1 fun(mn+1)==N
		while(mx-mn>1) {
			ll md = (mx+mn)/2;
			if(fun(md)>=N) mx = md;
			else {
				mn=md;
			}
		}
		printf("%lld\n",mx);
	}
	return 0;
}
