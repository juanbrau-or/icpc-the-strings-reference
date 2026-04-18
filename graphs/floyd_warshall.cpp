// g[i][j]: weight of edge (i, j) or INF if there's no edge
// g[i][i]=0
ll g[MAXN][MAXN];int n;
void floyd(){ // O(n^3) . Replaces g with min distances
	for (int k = 0, _n = n; k < _n; ++k)for (int i = 0, _n = n; i < _n; ++i)if(g[i][k]<INF)for (int j = 0, _n = n; j < _n; ++j)if(g[k][j]<INF)
		g[i][j]=min(g[i][j],g[i][k]+g[k][j]);
}
bool inNegCycle(int v){return g[v][v]<0;}
bool hasNegCycle(int a, int b){ // true iff there's neg cycle in between
	for (int i = 0, _n = n; i < _n; ++i)if(g[a][i]<INF&&g[i][b]<INF&&g[i][i]<0)return true;
	return false;
}
