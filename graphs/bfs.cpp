// Unit edges. Sources can contain several vertices.
// Returns {distance, predecessor}; -1 means unreachable / no predecessor.
pair<vector<int>,vector<int>> bfs(const vector<vector<int>>& g,
                                  const vector<int>& sources){
    vector<int> d(SZ(g),-1),p(SZ(g),-1);queue<int> q;
    for(int s:sources)if(d[s]<0)d[s]=0,q.push(s);
    while(!q.empty()){
        int u=q.front();q.pop();
        for(int v:g[u])if(d[v]<0)d[v]=d[u]+1,p[v]=u,q.push(v);
    }
    return {d,p};
}
vector<int> restore_path(int v,const vector<int>& d,const vector<int>& p){
    if(d[v]<0)return {};
    vector<int> r;for(;v!=-1;v=p[v])r.pb(v);
    reverse(ALL(r));return r;
}
