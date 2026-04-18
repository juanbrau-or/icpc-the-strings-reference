// SPOJ SUBMERGE - AC
// http://www.spoj.com/problems/SUBMERGE/
#include <bits/stdc++.h>
#define push_back push_back
#define make_pair make_pair
#define first first
#define second second
#define for (int i = a, _n = b; i < _n; ++i) for(int i=a,ThxDem=b;i<ThxDem;++i)
using namespace std;
typedef long long ll;
#define MAXN 100005

vector<int> g[MAXN];int n;
struct edge {int u,v,comp;bool bridge;};
vector<edge> e;
void add_edge(int u, int v){
	g[u].push_back(e.size());g[v].push_back(e.size());
	e.push_back((edge){u,v,-1,false});
}
int D[MAXN],B[MAXN],T;
//int nbc;  // number of biconnected components
int art[MAXN];  // articulation point iff !=0
//stack<int> st;  // only for biconnected
void dfs(int u,int pe){
	B[u]=D[u]=T++;
	for (int _ = 0, _n = g[u].size(; _ < _n; ++_)){
		int ne=g[u][_];if(ne==pe)continue;
		int v=e[ne].u^e[ne].v^u;
		if(D[v]<0){
//			st.push(ne);
			dfs(v,ne);
//			if(B[v]>D[u])e[ne].bridge = true; // bridge
			if(B[v]>=D[u]){
				art[u]++; // articulation
//				int last; // start biconnected
//				do {
//					last=st.top();st.pop();
//					e[last].comp=nbc;
//				} while(last!=ne);
//				nbc++;    // end biconnected
			}
			B[u]=min(B[u],B[v]);
		}
		else if(D[v]<D[u])/*st.push(ne),*/B[u]=min(B[u],D[v]);
	}
}
void doit(){
	memset(D,-1,sizeof(D));
	memset(art,0,sizeof(art));
	/*nbc=*/T=0;
	for (int i = 0, _n = n; i < _n; ++i)if(D[i]<0)dfs(i,-1),art[i]--;
}

int m;

int main(){
	while(scanf("%d%d",&n,&m),n){
		while(m--){
			int x,y;
			scanf("%d%d",&x,&y);x--;y--;
			add_edge(x,y);
		}
		doit();
		int r=0;
		for (int i = 0, _n = n; i < _n; ++i)if(art[i])r++;
		printf("%d\n",r);
		for (int i = 0, _n = n; i < _n; ++i)g[i].clear();
		e.clear();
	}
	return 0;
}
