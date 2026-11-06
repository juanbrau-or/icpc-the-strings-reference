ll modpow(ll a,ll e,ll p){
    assert(p>1&&e>=0);a%=p;if(a<0)a+=p;ll r=1;
    while(e){if(e&1)r=(__int128)r*a%p;a=(__int128)a*a%p;e>>=1;}
    return r;
}
// p MUST be prime, 0 <= N < p.
struct Comb{
    ll p;vector<ll> fac,ifac;
    Comb(int N,ll p):p(p),fac(N+1,1),ifac(N+1,1){
        assert(N>=0&&N<p);
        fore(i,1,N+1)fac[i]=(__int128)fac[i-1]*i%p;
        ifac[N]=modpow(fac[N],p-2,p);
        for(int i=N;i>0;--i)ifac[i-1]=(__int128)ifac[i]*i%p;
    }
    ll C(int n,int k)const{
        if(k<0||k>n||n<0)return 0;assert(n<SZ(fac));
        return (__int128)fac[n]*ifac[k]%p*ifac[n-k]%p;
    }
};
