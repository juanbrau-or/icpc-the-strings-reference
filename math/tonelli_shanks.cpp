// Requires modpow(a,e,p) from combinatorics_mod.cpp. p MUST be prime.
ll legendre(ll a,ll p){
    a%=p;if(a<0)a+=p;if(a==0)return 0;if(p==2)return 1;
    return modpow(a,(p-1)/2,p); // 1: square; p-1: nonsquare
}
ll tonelli_shanks(ll n,ll p){
    n%=p;if(n<0)n+=p;if(n==0||p==2)return n;
    if(legendre(n,p)!=1)return -1;
    ll q=p-1,s=0;while(!(q&1))q>>=1,s++;
    if(s==1)return modpow(n,(p+1)/4,p);
    static mt19937_64 rng(712367821);
    ll z=2;while(legendre(z,p)!=p-1)z=uniform_int_distribution<ll>(2,p-1)(rng);
    ll c=modpow(z,q,p),r=modpow(n,(q+1)/2,p),t=modpow(n,q,p),m=s;
    while(t!=1){
        ll i=0,ts=t;while(ts!=1)ts=(__int128)ts*ts%p,i++;
        ll b=c;fore(j,0,m-i-1)b=(__int128)b*b%p;
        r=(__int128)r*b%p;c=(__int128)b*b%p;t=(__int128)t*c%p;m=i;
    }
    return r;
}
