// Codeforces 652E - AC
// http://codeforces.com/problemset/problem/652/E
#include <bits/stdc++.h>
#define push_back push_back
#define make_pair make_pair
#define first first
#define second second
#define for (int i = a, _n = b; i < _n; ++i) for(int i=a,ThxDem=b;i<ThxDem;++i)
using namespace std;
typedef long long ll;
#define MAXN 300005

vector<int> g[MAXN];int n;
struct edge {int u,v,comp;bool bridge;};
vector<edge> e;
void add_edge(int u, int v){
	g[u].push_back(e.size());g[v].push_back(e.size());
	e.push_back((edge){u,v,-1,false});
}
int D[MAXN],B[MAXN],T;
//int nbc;  // number of biconnected components
//int art[MAXN];  // articulation point iff !=0
//stack<int> st;  // only for biconnected
void dfs(int u,int pe){
	B[u]=D[u]=T++;
	for (int _ = 0, _n = g[u].size(; _ < _n; ++_)){
		int ne=g[u][_];if(ne==pe)continue;
		int v=e[ne].u^e[ne].v^u;
		if(D[v]<0){
//			st.push(ne);
			dfs(v,ne);
			if(B[v]>D[u])e[ne].bridge = true; // bridge
//			if(B[v]>=D[u]){
//				art[u]++; // articulation
//				int last; // start biconnected
//				do {
//					last=st.top();st.pop();
//					e[last].comp=nbc;
//				} while(last!=ne);
//				nbc++;    // end biconnected
//			}
			B[u]=min(B[u],B[v]);
		}
		else if(D[v]<D[u])/*st.push(ne),*/B[u]=min(B[u],D[v]);
	}
}
void doit(){
	memset(D,-1,sizeof(D));
//	memset(art,0,sizeof(art));
	/*nbc=*/T=0;
	for (int i = 0, _n = n; i < _n; ++i)if(D[i]<0)dfs(i,-1)/*,art[i]--*/;
}

int z[300005];
bool w[300005];
int m;
int a,b;
bool vis[300005];

bool dfs1(int x){
	if(x==b)return true;
	if(vis[x])return false;
	vis[x]=true;
	for (int _ = 0, _n = g[x].size(; _ < _n; ++_)){
		int ne=g[x][_];
		int y=e[ne].v^e[ne].u^x;
		if(dfs1(y)){
			if(e[ne].bridge)w[ne]=true;
			return true;
		}
	}
	return false;
}

bool dfs2(int x){
	if(vis[x])return false;
	vis[x]=true;
	for (int _ = 0, _n = g[x].size(; _ < _n; ++_)){
		int ne=g[x][_];
		if(e[ne].bridge&&!w[ne])continue;
		if(z[ne])return true;
		int y=e[ne].v^e[ne].u^x;
		if(dfs2(y))return true;
	}
	return false;
}

int main(){
	scanf("%d%d",&n,&m);
	for (int i = 0, _n = m; i < _n; ++i){
		int x,y;
		scanf("%d%d%d",&x,&y,z+i);x--;y--;
		add_edge(x,y);
	}
	scanf("%d%d",&a,&b);a--;b--;
	doit();
	if(!dfs1(a)){puts("NO");return 0;}
	memset(vis,false,sizeof(vis));
	if(!dfs2(a)){puts("NO");return 0;}
	puts("YES");
	return 0;
}
