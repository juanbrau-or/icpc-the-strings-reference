struct FenwickOrder{
    int n;vector<ll> ft;
    FenwickOrder(int n):n(n),ft(n+1){}
    void add(int p,ll v){for(++p;p<=n;p+=p&-p)ft[p]+=v;}
    ll prefix(int r)const{ll s=0;for(;r;r-=r&-r)s+=ft[r];return s;}
    ll sum(int l,int r)const{return prefix(r)-prefix(l);}
    int kth(ll k)const{ // 0-based rank; individual frequencies >= 0
        if(k<0||k>=prefix(n))return -1;
        int p=0,step=1;while(step<=n/2)step*=2;
        for(;step;step/=2){
            int q=p+step;if(q<=n&&ft[q]<=k)k-=ft[q],p=q;
        }
        return p;
    }
};
