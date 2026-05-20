// UVA 11721 - AC
// https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2768
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define INF (1LL<<60)
#define MAXN 1024

vector<int> w;

int n;
vector<pair<int,int> > g[MAXN]; // u->[(v,cost)]
ll dist[MAXN];
void bford(int src){ // O(nm)
	fill(dist,dist+n,INF);dist[src]=0;
	for (int _ = 0; _ < n; ++_)for (int x = 0; x < n; ++x)if(dist[x]!=INF)for(auto t:g[x]){
		dist[t.first]=min(dist[t.first],dist[x]+t.second);
	}
	for (int x = 0; x < n; ++x)if(dist[x]!=INF)for(auto t:g[x]){
		if(dist[t.first]>dist[x]+t.second){
			// neg cycle: all nodes reachable from t.first have -INF distance
			// to reconstruct neg cycle: save "prev" of each node, go up from t.first until repeating a node. this node and all nodes between the two occurences form a neg cycle
			w.push_back(t.first);
		}
	}
}

int m;
bool vis[MAXN];

void dfs(int x){
	if(vis[x])return;
	vis[x]=true;
	for(auto p:g[x])dfs(p.first);
}

int main(){
	int tn;
	scanf("%d",&tn);
	for (int tc = 1; tc < tn+1; ++tc){
		scanf("%d%d",&n,&m);
		for (int i = 0; i < n; ++i)g[n].push_back({i,0});
		n++;
		while(m--){
			int x,y,c;
			scanf("%d%d%d",&x,&y,&c);
			g[y].push_back({x,c});
		}
		bford(n-1);
		memset(vis,false,sizeof(vis));
		for(int x: w){
			dfs(x);
		}
		printf("Case %d:",tc);
		if(w.empty())puts(" impossible");
		else {for (int i = 0; i < n; ++i)if(vis[i])printf(" %d",i);puts("");}
		for (int i = 0; i < n; ++i)g[i].clear();
		w.clear();
	}
	return 0;
}
