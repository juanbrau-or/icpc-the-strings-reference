// f[mask] <- sum of original f[sub] for sub subset of mask.
void sos(vector<ll>& f,int n,bool inverse=false){
    assert(SZ(f)==(1<<n));
    fore(b,0,n)fore(s,0,1<<n)if(s&(1<<b))f[s]+=(inverse?-1:1)*f[s^(1<<b)];
}
const ll INF_TSP=LLONG_MAX/4;
// Minimum Hamiltonian cycle from 0. c[u][v]=INF_TSP for absent edges.
// Real costs >= 0, n <= ~20; cost sums must be < INF_TSP.
ll held_karp(const vector<vector<ll>>& c){
    int n=SZ(c);if(n<=1)return 0;
    vector<ll> dp((1<<n)*n,INF_TSP);dp[n]=0;
    fore(s,1,1<<n)if(s&1)fore(u,0,n)if((s>>u&1)&&dp[s*n+u]<INF_TSP)
        fore(v,0,n)if(!(s>>v&1)&&c[u][v]<INF_TSP){
            ll &z=dp[(s|(1<<v))*n+v];z=min(z,dp[s*n+u]+c[u][v]);
        }
    ll ans=INF_TSP;
    fore(u,1,n)ans=min(ans,dp[((1<<n)-1)*n+u]+c[u][0]);
    return ans;
}
