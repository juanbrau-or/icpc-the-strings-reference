vector<int> g[MAXN];int n;
vector<int> tsort(){  // lexicographically smallest topological sort
	vector<int> r;priority_queue<int> q;
	vector<int> d(2*n,0);
	for (int i = 0; i < n; ++i)for (int j = 0; j < g[i].size(); ++j)d[g[i][j]]++;
	for (int i = 0; i < n; ++i)if(!d[i])q.push(-i);
	while(!q.empty()){
		int x=-q.top();q.pop();r.push_back(x);
		for (int i = 0; i < g[x].size(); ++i){
			d[g[x][i]]--;
			if(!d[g[x][i]])q.push(-g[x][i]);
		}
	}
	return r;  // if not DAG it will have less than n elements
}
