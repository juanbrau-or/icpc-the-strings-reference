// SPOJ SUBST1 - TLE
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

pair<int, int> sf[MAXN];
bool sacomp(int lhs, int rhs) {return sf[lhs]<sf[rhs];}
vector<int> constructSA(string& s){ // O(n log^2(n))
	int n=s.size();                 // (sometimes fast enough) -> not in this example :P
	vector<int> sa(n),r(n);
	for (int i = 0, _n = n; i < _n; ++i)r[i]=s[i];
	for(int m=1;m<n;m*=2){
		for (int i = 0, _n = n; i < _n; ++i)sa[i]=i,sf[i]={r[i],i+m<n?r[i+m]:-1};
		stable_sort(sa.begin(),sa.end(),sacomp);
		r[sa[0]]=0;
		for (int i = 1, _n = n; i < _n; ++i)r[sa[i]]=sf[sa[i]]!=sf[sa[i-1]]?i:r[sa[i-1]];
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
