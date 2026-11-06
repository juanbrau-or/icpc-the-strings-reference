// g[u] = {(v, weight)}; every weight MUST be 0 or 1.
vector<int> bfs01(const vector<vector<pair<int,int>>>& g,int s){
    vector<int> d(SZ(g),INT_MAX);deque<pair<int,int>> q;
    d[s]=0;q.push_front({0,s});
    while(!q.empty()){
        auto [du,u]=q.front();q.pop_front();if(du!=d[u])continue;
        for(auto [v,w]:g[u]){
            assert(w==0||w==1);if(d[v]<=du+w)continue;
            d[v]=du+w;
            if(w)q.pb({d[v],v});else q.push_front({d[v],v});
        }
    }
    return d;
}
