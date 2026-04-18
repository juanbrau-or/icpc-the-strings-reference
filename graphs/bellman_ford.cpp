int n;
vector<pair<int,int> > g[MAXN]; // u->[(v,cost)]
ll dist[MAXN];
void bford(int src){ // O(nm)
	fill(dist,dist+n,INF);dist[src]=0;
	for (int _ = 0, _n = n; _ < _n; ++_)for (int x = 0, _n = n; x < _n; ++x)if(dist[x]!=INF)for(auto t:g[x]){
		dist[t.first]=min(dist[t.first],dist[x]+t.second);
	}
	for (int x = 0, _n = n; x < _n; ++x)if(dist[x]!=INF)for(auto t:g[x]){
		if(dist[t.first]>dist[x]+t.second){
			// neg cycle: all nodes reachable from t.first have -INF distance
			// to reconstruct neg cycle: save "prev" of each node, go up from t.first until repeating a node. this node and all nodes between the two occurences form a neg cycle
		}
	}
}
