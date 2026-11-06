// Successive shortest augmenting paths. No reachable negative residual cycle.
typedef ll tf;typedef ll tc;
const ll INFCOST=LLONG_MAX/4,INFFLOW=LLONG_MAX/4;
struct MCF{
    struct edge{int to,rev;tf f,cap;tc cost;};
    int n;vector<vector<edge>> g;
    MCF(int n):n(n),g(n){}
    void add_edge(int s,int t,tf cap,tc cost){
        int a=SZ(g[s]),b=SZ(g[t]);
        g[s].pb({t,b+(s==t),0,cap,cost});
        g[t].pb({s,a,0,0,-cost});
    }
    // Returns additional {flow,cost}; limit is additional requested flow.
    pair<tf,tc> get_flow(int s,int t,tf limit=INFFLOW){
        assert(s!=t&&limit>=0);
        vector<tc> pot(n,INFCOST);pot[s]=0;
        // Bellman-Ford makes initial negative edge costs safe.
        fore(it,0,n){
            bool changed=false;
            fore(u,0,n)if(pot[u]<INFCOST)for(auto &e:g[u])
                if(e.f<e.cap&&pot[e.to]>pot[u]+e.cost){
                    pot[e.to]=pot[u]+e.cost;changed=true;
                }
            if(!changed)break;
            if(it==n-1)throw invalid_argument("negative residual cycle");
        }
        for(auto &p:pot)if(p==INFCOST)p=0;
        tf flow=0;tc cost=0;
        while(flow<limit){
            vector<tc> d(n,INFCOST);vector<int> pv(n),pe(n);
            priority_queue<pair<tc,int>,vector<pair<tc,int>>,greater<pair<tc,int>>> q;
            d[s]=0;q.push({0,s});
            while(!q.empty()){
                auto [du,u]=q.top();q.pop();if(du!=d[u])continue;
                fore(i,0,SZ(g[u])){
                    auto &e=g[u][i];if(e.f>=e.cap)continue;
                    tc nd=du+e.cost+pot[u]-pot[e.to];
                    if(nd<d[e.to])d[e.to]=nd,pv[e.to]=u,pe[e.to]=i,q.push({nd,e.to});
                }
            }
            if(d[t]==INFCOST)break;
            fore(u,0,n)if(d[u]<INFCOST)pot[u]+=d[u];
            tf df=limit-flow;
            for(int v=t;v!=s;v=pv[v]){
                auto &e=g[pv[v]][pe[v]];df=min(df,e.cap-e.f);
            }
            for(int v=t;v!=s;v=pv[v]){
                auto &e=g[pv[v]][pe[v]];
                e.f+=df;g[v][e.rev].f-=df;cost+=df*e.cost;
            }
            flow+=df;
        }
        return {flow,cost};
    }
};
