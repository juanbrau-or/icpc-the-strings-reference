// dp[g][r] = min_{g-1 <= l < r}(dp[g-1][l]+cost(l,r)).
// cost(l,r): cost of nonempty segment [l,r), O(1).
// Requires nondecreasing argmin l as r grows (for every row).
const ll INF_DP=LLONG_MAX/4;
template<class Cost> ll partition_dp(int n,int groups,Cost cost){
    if(groups>n||groups<0)return INF_DP;
    vector<ll> prev(n+1,INF_DP),cur(n+1,INF_DP);prev[0]=0;
    fore(g,1,groups+1){
        fill(ALL(cur),INF_DP);
        function<void(int,int,int,int)> solve=[&](int l,int r,int optL,int optR){
            if(l>r)return;
            int m=(l+r)/2,best=optL;ll val=INF_DP;
            fore(j,optL,min(m-1,optR)+1)if(prev[j]<INF_DP){
                ll v=prev[j]+cost(j,m);if(v<val)val=v,best=j;
            }
            cur[m]=val;
            solve(l,m-1,optL,best);solve(m+1,r,best,optR);
        };
        solve(g,n,g-1,n-1);swap(prev,cur);
    }
    return prev[n];
}
