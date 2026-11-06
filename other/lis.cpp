// Indices of a longest strictly increasing subsequence.
template<class T> vector<int> lis(const vector<T>& a){
    vector<T> tails;vector<int> ids,prev(SZ(a),-1);
    fore(i,0,SZ(a)){
        int k=lower_bound(ALL(tails),a[i])-tails.begin();
        if(k)prev[i]=ids[k-1];
        if(k==SZ(tails))tails.pb(a[i]),ids.pb(i);
        else tails[k]=a[i],ids[k]=i;
    }
    vector<int> ans;
    for(int i=ids.empty()?-1:ids.back();i>=0;i=prev[i])ans.pb(i);
    reverse(ALL(ans));return ans;
}
