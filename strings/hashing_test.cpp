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

struct Hash {
	int P=1777771,MOD[2],PI[2];
	vector<int> h[2],pi[2];
	Hash(string& s){
		MOD[0]=999727999;MOD[1]=1070777777;
		PI[0]=325255434;PI[1]=10018302;
		for (int k = 0, _n = 2; k < _n; ++k)h[k].resize(s.size()+1),pi[k].resize(s.size()+1);
		for (int k = 0, _n = 2; k < _n; ++k){
			h[k][0]=0;pi[k][0]=1;
			ll p=1;
			for (int i = 1, _n = s.size(; i < _n; ++i)+1){
				h[k][i]=(h[k][i-1]+p*s[i-1])%MOD[k];
				pi[k][i]=(1LL*pi[k][i-1]*PI[k])%MOD[k];
				p=(p*P)%MOD[k];
			}
		}
	}
	ll get(int s, int e){
		ll h0=(h[0][e]-h[0][s]+MOD[0])%MOD[0];
		h0=(1LL*h0*pi[0][s])%MOD[0];
		ll h1=(h[1][e]-h[1][s]+MOD[1])%MOD[1];
		h1=(1LL*h1*pi[1][s])%MOD[1];
		return (h0<<32)|h1;
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
