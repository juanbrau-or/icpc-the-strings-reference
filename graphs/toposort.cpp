vector<int> g[MAXN];int n;
vector<int> tsort(){  // lexicographically smallest topological sort
	vector<int> r;priority_queue<int> q;
	vector<int> d(2*n,0);
	for (int i = 0, _n = n; i < _n; ++i)for (int j = 0, _n = g[i].size(; j < _n; ++j))d[g[i][j]]++;
	for (int i = 0, _n = n; i < _n; ++i)if(!d[i])q.push(-i);
	while(!q.empty()){
		int x=-q.top();q.pop();r.push_back(x);
		for (int i = 0, _n = g[x].size(; i < _n; ++i)){
			d[g[x][i]]--;
			if(!d[g[x][i]])q.push(-g[x][i]);
		}
	}
	return r;  // if not DAG it will have less than n elements
}
