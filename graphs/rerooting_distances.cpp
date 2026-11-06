// Requires TreeTour. ans[u] = sum of unweighted distances from u.
vector<ll> distance_sums(const vector<vector<int>>& g,int root=0){
    int n=SZ(g);TreeTour t(g,root);vector<ll> sz(n,1),ans(n);
    for(int u:t.order)ans[root]+=t.depth[u];
    for(int i=n-1;i>0;--i){int u=t.order[i];sz[t.parent[u]]+=sz[u];}
    for(int u:t.order)if(u!=root)ans[u]=ans[t.parent[u]]+n-2*sz[u];
    return ans;
}
