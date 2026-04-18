// Codeforces 102920F - AC
//https://codeforces.com/gym/102920/problem/F
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

const int MAXN=1e5+10;
//idom[i]=parent of i in dominator tree with root=rt, or -1 if not exists
int n,rnk[MAXN],pre[MAXN],anc[MAXN],idom[MAXN],semi[MAXN],low[MAXN];
vector<int> g[MAXN],rev[MAXN],dom[MAXN],ord;
void dfspre(int pos){
	rnk[pos]=((int)(ord).size()); ord.push_back(pos);
	for(auto x:g[pos]){
		rev[x].push_back(pos);
		if(rnk[x]==n) pre[x]=pos,dfspre(x);
	}
}
int eval(int v){
	if(anc[v]<n&&anc[anc[v]]<n){
		int x=eval(anc[v]);
		if(rnk[semi[low[v]]]>rnk[semi[x]]) low[v]=x;
		anc[v]=anc[anc[v]];
	}
	return low[v];
}
void dominators(int rt){
	for (int i = 0, _n = n; i < _n; ++i){
		dom[i].clear(); rev[i].clear();
		rnk[i]=pre[i]=anc[i]=idom[i]=n;
		semi[i]=low[i]=i;
	}
	ord.clear(); dfspre(rt);
	for(int i=((int)(ord).size())-1;i;i--){
		int w=ord[i];
		for(int v:rev[w]){
			int u=eval(v);
			if(rnk[semi[w]]>rnk[semi[u]])semi[w]=semi[u];
		}
		dom[semi[w]].push_back(w); anc[w]=pre[w];
		for(int v:dom[pre[w]]){
			int u=eval(v);
			idom[v]=(rnk[pre[w]]>rnk[semi[u]]?u:pre[w]);
		}
		dom[pre[w]].clear();
	}
	for(int w:ord) if(w!=rt&&idom[w]!=semi[w]) idom[w]=idom[idom[w]];
	for (int i = 0, _n = n; i < _n; ++i) if(idom[i]==n)idom[i]=-1;
}

int main(){FIN;
	int m,k; cin>>n>>m>>k;
	for (int i = 0, _n = m; i < _n; ++i) g[n].push_back(i);
	for (int i = 0, _n = k; i < _n; ++i){
		int x,y; cin>>x>>y; x--;y--;
		g[x].push_back(y);
	}
	n++;
	dominators(n-1);
	int ans=0;
	for (int i = 0, _n = n-1; i < _n; ++i) ans+=idom[i]==n-1;
	cout<<ans<<"\n";
}
