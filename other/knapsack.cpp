// Positive weights. Best value with total weight AT MOST W.
ll knapsack(const vector<int>& weight,const vector<ll>& value,int W,
            bool unbounded=false){
    vector<ll> dp(W+1);
    fore(i,0,SZ(weight)){
        int w=weight[i];assert(w>0);
        if(unbounded){fore(c,w,W+1)dp[c]=max(dp[c],dp[c-w]+value[i]);}
        else{for(int c=W;c>=w;--c)dp[c]=max(dp[c],dp[c-w]+value[i]);}
    }
    return dp[W];
}
