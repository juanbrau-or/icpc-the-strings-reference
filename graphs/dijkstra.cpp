vector<pair<int,int> > g[MAXN];  // u->[(v,cost)]
ll dist[MAXN];
void dijkstra(int x){
	memset(dist,-1,sizeof(dist));
	priority_queue<pair<ll,int> > q;
	dist[x]=0;q.push({0,x});
	while(!q.empty()){
		x=q.top().second;ll c=-q.top().first;q.pop();
		if(dist[x]!=c)continue;
		for (int i = 0, _n = g[x].size(; i < _n; ++i)){
			int y=g[x][i].first; ll c=g[x][i].second;
			if(dist[y]<0||dist[x]+c<dist[y])
				dist[y]=dist[x]+c,q.push({-dist[y],y});
		}
	}
}
