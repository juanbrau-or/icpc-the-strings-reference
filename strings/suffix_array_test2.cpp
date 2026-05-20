// SPOJ SUBST1 - AC
// http://www.spoj.com/problems/SUBST1/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define MAXN (1<<20)

#define RB(x) (x<n?r[x]:0)
void csort(vector<int>& sa, vector<int>& r, int k){
	int n=sa.size(),top=max(255,n+1);
	vector<int> f(top,0),t(n);
	for (int i = 0; i < n; ++i)f[RB(i+k)]++;
	int sum=0;
	for (int i = 0; i < top; ++i)f[i]=(sum+=f[i])-f[i];
	for (int i = 0; i < n; ++i)t[f[RB(sa[i]+k)]++]=sa[i];
	sa=t;
}
vector<int> constructSA(string& s){ // O(n logn)
	int n=s.size(),rank;
	vector<int> sa(n),r(n),t(n);
	for (int i = 0; i < n; ++i)sa[i]=i,r[i]=s[i];
	for(int k=1;k<n;k*=2){
		csort(sa,r,k);csort(sa,r,0);
		t[sa[0]]=rank=1;
		for (int i = 1; i < n; ++i){
			if(r[sa[i]]!=r[sa[i-1]]||RB(sa[i]+k)!=RB(sa[i-1]+k))rank++;
			t[sa[i]]=rank;
		}
		r=t;
		if(r[sa[n-1]]==n)break;
	}
	return sa;
}
vector<int> computeLCP(string& s, vector<int>& sa){
	int n=s.size(),L=0;
	vector<int> lcp(n),plcp(n),phi(n);
	phi[sa[0]]=-1;
	for (int i = 1; i < n; ++i)phi[sa[i]]=sa[i-1];
	for (int i = 0; i < n; ++i){
		if(phi[i]<0){plcp[i]=0;continue;}
		while(s[i+L]==s[phi[i]+L])L++;
		plcp[i]=L;
		L=max(L-1,0);
	}
	for (int i = 0; i < n; ++i)lcp[i]=plcp[sa[i]];
	return lcp; // lcp[i]=LCP(sa[i-1],sa[i])
}

int main(){
	int tn; cin>>tn;
	while(tn--){
		string s; cin>>s;
		vector<int> sa=constructSA(s);
		vector<int> lcp=computeLCP(s,sa);
		ll r=1LL*s.size()*(s.size()+1)/2;
		for (int i = 1; i < s.size(); ++i)
			r-=lcp[i];
		cout<<r<<"\n";
	}
	return 0;
}
