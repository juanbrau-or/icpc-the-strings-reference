// Exactly one successor per vertex. 0 <= k < 2^63.
struct FunctionalGraph{
    static const int LOG=63;
    vector<array<int,LOG>> up;
    vector<int> comp,entry,dist,pos,len;
    FunctionalGraph(const vector<int>& nxt):up(SZ(nxt)),
        comp(SZ(nxt),-1),entry(SZ(nxt)),dist(SZ(nxt)),pos(SZ(nxt),-1){
        int n=SZ(nxt);vector<int> deg(n),removed;queue<int> q;
        fore(u,0,n){up[u][0]=nxt[u];deg[nxt[u]]++;}
        fore(j,1,LOG)fore(u,0,n)up[u][j]=up[up[u][j-1]][j-1];
        fore(u,0,n)if(!deg[u])q.push(u);
        while(!q.empty()){
            int u=q.front();q.pop();removed.pb(u);
            if(!--deg[nxt[u]])q.push(nxt[u]);
        }
        fore(u,0,n)if(deg[u]&&comp[u]<0){
            int v=u,id=SZ(len),k=0;
            do{comp[v]=id;entry[v]=v;pos[v]=k++;v=nxt[v];}while(v!=u);
            len.pb(k);
        }
        reverse(ALL(removed));
        for(int u:removed){
            int v=nxt[u];comp[u]=comp[v];entry[u]=entry[v];dist[u]=dist[v]+1;
        }
    }
    int jump(int u,ll k)const{
        assert(k>=0);fore(j,0,LOG)if((k>>j)&1LL)u=up[u][j];return u;
    }
    ll steps(int u,int v)const{
        if(comp[u]!=comp[v])return -1;
        if(dist[v]){
            int d=dist[u]-dist[v];return d>=0&&jump(u,d)==v?d:-1;
        }
        int l=len[comp[u]];
        return (ll)dist[u]+(pos[v]-pos[entry[u]]+l)%l;
    }
};
