vector<ll> subset_sums(const vector<ll>& a,int l,int r){
    vector<ll> sums={0};
    fore(i,l,r){int n=SZ(sums);fore(j,0,n)sums.pb(sums[j]+a[i]);}
    return sums;
}
// Counts subsets of indices, including empty, with sum <= bound. n <= ~40.
ll count_subsets_leq(const vector<ll>& a,ll bound){
    int m=SZ(a)/2;auto x=subset_sums(a,0,m),y=subset_sums(a,m,SZ(a));
    sort(ALL(y));ll ans=0;
    for(ll v:x)ans+=upper_bound(ALL(y),bound-v)-y.begin();return ans;
}
