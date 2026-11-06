// Connected, undirected tree. Iterative: safe on long chains.
struct TreeTour{
    vector<int> tin,tout,order,parent,depth;
    TreeTour(const vector<vector<int>>& g,int root=0):
        tin(SZ(g)),tout(SZ(g)),parent(SZ(g),-1),depth(SZ(g)){
        vector<int> it(SZ(g)),st={root};
        while(!st.empty()){
            int u=st.back();
            if(it[u]==0){tin[u]=SZ(order);order.pb(u);}
            if(it[u]==SZ(g[u])){tout[u]=SZ(order);st.pop_back();continue;}
            int v=g[u][it[u]++];if(v==parent[u])continue;
            parent[v]=u;depth[v]=depth[u]+1;st.pb(v);
        }
    }
    bool ancestor(int u,int v)const{
        return tin[u]<=tin[v]&&tin[v]<tout[u];
    }
};
