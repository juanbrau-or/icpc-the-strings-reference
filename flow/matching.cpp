vector<int> g[MAXN]; // [0,n)->[0,m)
int n,m;
int mat[MAXM];bool vis[MAXN];
int match(int x){
	if(vis[x])return 0;
	vis[x]=true;
	for(int y:g[x])if(mat[y]<0||match(mat[y])){mat[y]=x;return 1;}
	return 0;
}
vector<pair<int,int> > max_matching(){
	vector<pair<int,int> > r;
	memset(mat,-1,sizeof(mat));
	for (int i = 0, _n = n; i < _n; ++i)memset(vis,false,sizeof(vis)),match(i);
	for (int i = 0, _n = m; i < _n; ++i)if(mat[i]>=0)r.push_back({mat[i],i});
	return r;
}
