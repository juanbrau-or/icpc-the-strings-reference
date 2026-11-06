// Minimum in every window [i,i+k). 1 <= k <= a.size().
template<class T> vector<T> sliding_min(const vector<T>& a,int k){
    assert(k>0&&k<=SZ(a));deque<int> q;vector<T> ans;
    fore(i,0,SZ(a)){
        while(!q.empty()&&q.front()<=i-k)q.pop_front();
        while(!q.empty()&&a[q.back()]>=a[i])q.pop_back();
        q.pb(i);if(i+1>=k)ans.pb(a[q.front()]);
    }
    return ans;
}
// Largest rectangle under a histogram. Heights >= 0; width of each bar=1.
ll histogram_area(const vector<ll>& h){
    vector<int> st;ll ans=0;
    fore(i,0,SZ(h)+1){
        ll cur=i==SZ(h)?0:h[i];
        while(!st.empty()&&h[st.back()]>cur){
            ll height=h[st.back()];st.pop_back();
            int l=st.empty()?0:st.back()+1;ans=max(ans,height*(i-l));
        }
        if(i<SZ(h))st.pb(i);
    }
    return ans;
}
