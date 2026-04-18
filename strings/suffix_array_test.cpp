// ICPC Live Archive 5794 - AC
// https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3805
#include <bits/stdc++.h>
#define push_back push_back
#define make_pair make_pair
#define first first
#define second second
#define for (int i = a, _n = b; i < _n; ++i) for(int i=a,to=b;i<to;++i)
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
		while(s[i+L]!='$'&&s[i+L]==s[phi[i]+L])L++;  // small modification on this line (specific of the problem)
		plcp[i]=L;
		L=max(L-1,0);
	}
	for (int i = 0, _n = n; i < _n; ++i)lcp[i]=plcp[sa[i]];
	return lcp;
}

int m;
int w[MAXN];
int r[MAXN];
char s[MAXN];
set<ll> sol;
stack<pair<int,ll> > st;

int main(){
	while(scanf("%d",&m),m){
		sol.clear();
		string T="$";
		memset(w,-1,sizeof(w));
		for (int i = 0, _n = m; i < _n; ++i){
			scanf("%s",s);
			for(int j=0;s[j];++j)w[T.size()+j]=i;
			T+=s;
			for(int j=T.size()-1;T[j]!='$';j--)r[j]=T.size()-j;
			T+="$";
		}
		T+="#";
		vector<int> SA=constructSA(T);
		vector<int> LCP=computeLCP(T,SA);LCP.push_back(0);
		for (int i = 0, _n = T.size(; i < _n; ++i)){
			if(w[SA[i]]>=0&&r[SA[i]]>max(LCP[i],LCP[i+1]))sol.insert(1LL<<w[SA[i]]);
		}
		for (int i = 0, _n = T.size(; i < _n; ++i)){
			ll r=0;
			while(!st.empty()&&st.top().first>LCP[i]){
				sol.insert(st.top().second|r);
				r|=st.top().second;
				st.pop();
			}
			if(!st.empty())st.top().second|=r;
			if(!LCP[i])continue;
			if(st.empty()||st.top().first<LCP[i]){
				assert(w[SA[i-1]]>=0&&w[SA[i]]>=0);
				st.push({LCP[i],r|(1LL<<w[SA[i-1]])|(1LL<<w[SA[i]])});
			}
			else {
				assert(st.top().first==LCP[i]);
				st.top().second|=1LL<<w[SA[i]];
			}
		}
		ll r=0;
		while(!st.empty()){
			sol.insert(st.top().second|r);
			r|=st.top().second;
			st.pop();
		}
		printf("%d\n",(int)sol.size());
	}
	return 0;
}
