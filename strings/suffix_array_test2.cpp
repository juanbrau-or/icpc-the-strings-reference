// SPOJ SUBST1 - AC
// http://www.spoj.com/problems/SUBST1/
#include <bits/stdc++.h>
#define push_back push_back
#define make_pair make_pair
#define first first
#define second second
#define for (int i = a, _n = b; i < _n; ++i) for(int i=a,ThxDem=b;i<ThxDem;++i)
using namespace std;
typedef long long ll;

#define MAXN (1<<20)

#define RB(x) (x<n?r[x]:0)
void csort(vector<int>& sa, vector<int>& r, int k){
	int n=sa.size();
	vector<int> f(max(255,n),0),t(n);
	for (int i = 0, _n = n; i < _n; ++i)f[RB(i+k)]++;
	int sum=0;
	fore(i,0,max(255,n))f[i]=(sum+=f[i])-f[i];
	for (int i = 0, _n = n; i < _n; ++i)t[f[RB(sa[i]+k)]++]=sa[i];
	sa=t;
}
vector<int> constructSA(string& s){ // O(n logn)
	int n=s.size(),rank;
	vector<int> sa(n),r(n),t(n);
	for (int i = 0, _n = n; i < _n; ++i)sa[i]=i,r[i]=s[i];
	for(int k=1;k<n;k*=2){
		csort(sa,r,k);csort(sa,r,0);
		t[sa[0]]=rank=0;
		for (int i = 1, _n = n; i < _n; ++i){
			//if(r[sa[i]]!=r[sa[i-1]]||r[sa[i]+k]!=r[sa[i-1]+k])rank++;
			if(r[sa[i]]!=r[sa[i-1]]||RB(sa[i]+k)!=RB(sa[i-1]+k))rank++;
			t[sa[i]]=rank;
		}
		r=t;
		if(r[sa[n-1]]==n-1)break;
	}
	return sa;
}
vector<int> computeLCP(string& s, vector<int>& sa){
	int n=s.size(),L=0;
	vector<int> lcp(n),plcp(n),phi(n);
	phi[sa[0]]=-1;
	for (int i = 1, _n = n; i < _n; ++i)phi[sa[i]]=sa[i-1];
	for (int i = 0, _n = n; i < _n; ++i){
		if(phi[i]<0){plcp[i]=0;continue;}
		while(s[i+L]==s[phi[i]+L])L++;
		plcp[i]=L;
		L=max(L-1,0);
	}
	for (int i = 0, _n = n; i < _n; ++i)lcp[i]=plcp[sa[i]];
	return lcp; // lcp[i]=LCP(sa[i-1],sa[i])
}

char _s[1<<20];

int main(){
	int tn;
	scanf("%d",&tn);gets(_s);
	while(tn--){
		gets(_s);
		string s(_s);
		s+='\0';
		vector<int> sa=constructSA(s);
		vector<int> lcp=computeLCP(s,sa);
		ll r=1LL*s.size()*(s.size()-1)/2;
		for (int i = 1, _n = s.size(; i < _n; ++i))
			r-=lcp[i];
		printf("%lld\n",r);
	}
	return 0;
}
