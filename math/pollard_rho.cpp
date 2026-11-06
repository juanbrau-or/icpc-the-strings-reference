// Positive signed 64-bit integers. Exact modular products with __int128.
ll mulmod(ll a,ll b,ll m){return (__int128)a*b%m;}
ll expmod(ll b,ll e,ll m){
    ll r=1;while(e){if(e&1)r=mulmod(r,b,m);b=mulmod(b,b,m);e>>=1;}
    return r;
}
// Deterministic Miller-Rabin bases, also used by KACTL (CC0).
bool rabin(ll n){
    if(n<2)return false;
    for(ll p:{2,3,5,7,11,13,17,19,23,29,31,37})if(n%p==0)return n==p;
    ll d=n-1;int s=0;while(!(d&1))d>>=1,s++;
    for(ll a:{2LL,325LL,9375LL,28178LL,450775LL,9780504LL,1795265022LL}){
        if(a%n==0)continue;
        ll x=expmod(a%n,d,n);if(x==1||x==n-1)continue;
        bool witness=true;
        fore(i,1,s){x=mulmod(x,x,n);if(x==n-1){witness=false;break;}}
        if(witness)return false;
    }
    return true;
}
ll rho(ll n){ // n composite, n > 1
    if(n%2==0)return 2;if(n%3==0)return 3;
    static mt19937_64 rng(712367821);
    while(true){
        ll c=uniform_int_distribution<ll>(1,n-1)(rng);
        ll x=uniform_int_distribution<ll>(0,n-1)(rng),y=x,d=1;
        auto step=[&](ll v){return (ll)(((__int128)mulmod(v,v,n)+c)%n);};
        for(int it=0;d==1&&it<1000000;it++){
            x=step(x);y=step(step(y));d=std::gcd(x>y?x-y:y-x,n);
        }
        if(d>1&&d<n)return d;
    }
}
void fact(ll n,map<ll,int>& f){
    assert(n>=1);if(n==1)return;
    if(rabin(n)){f[n]++;return;}
    ll p=rho(n);fact(p,f);fact(n/p,f);
}
