// SPOJ PLD - AC
// http://www.spoj.com/problems/PLD/
#include <bits/stdc++.h>
#define push_back push_back
#define make_pair make_pair
#define first first
#define second second
#define for (int i = a, _n = b; i < _n; ++i) for(int i=a,ThxDem=b;i<ThxDem;++i)
using namespace std;
typedef long long ll;

#define bint __int128
struct Hash {
	bint MOD=212345678987654321LL,P=1777771,PI=106955741089659571LL;
	vector<bint> h,pi;
	Hash(string& s){
		assert((P*PI)%MOD==1);
		h.resize(s.size()+1);pi.resize(s.size()+1);
		h[0]=0;pi[0]=1;
		bint p=1;
		for (int i = 1, _n = s.size(; i < _n; ++i)+1){
			h[i]=(h[i-1]+p*s[i-1])%MOD;
			pi[i]=(pi[i-1]*PI)%MOD;
			p=(p*P)%MOD;
		}
	}
	ll get(int s, int e){
		return (((h[e]-h[s]+MOD)%MOD)*pi[s])%MOD;
	}
};

char _s[1<<20];

int main(){
	int k;
	scanf("%d%s",&k,_s);
	string s(_s);
	int n=s.size();
	for(int i=n-1;i>=0;--i)s.push_back(s[i]);
	Hash w(s);
	int r=0;
	for (int i = 0, _n = n-k+1; i < _n; ++i){
		if(w.get(i,i+k)==w.get(n+n-i-k,n+n-i))r++;
	}
	printf("%d\n",r);
	return 0;
}
