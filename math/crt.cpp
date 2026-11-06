// Generalized CRT: conditions {a,b,m} mean a*x == b (mod m), m > 0.
// Requires extendedEuclid and inv(a,m); combined period must fit in ll.
#define mod(a,m) (((a)%(m)+(m))%(m))
pair<ll,ll> sol(tuple<ll,ll,ll> c){
    auto [a,b,m]=c;assert(m>0);
    ll d=gcd(a,m);if(b%d)return {-1,-1};
    a/=d;b/=d;m/=d;if(m==1)return {0,1};
    a=(ll)mod((__int128)a,m);
    return {(ll)mod((__int128)b*inv(a,m),m),m};
}
pair<ll,ll> crt(vector<tuple<ll,ll,ll>> cond){
    ll x=0,M=1;
    for(auto c:cond){
        auto [y,N]=sol(c);if(N<0)return {-1,-1};
        ll d=gcd(M,N);if((y-x)%d)return {-1,-1};
        ll n=N/d,k=0;
        if(n>1)k=(ll)mod((__int128)((y-x)/d)*inv((M/d)%n,n),n);
        ll period=M*n; // assumption: period fits in signed 64 bits
        x=(ll)mod((__int128)M*k+x,period);M=period;
    }
    return {x,M};
}
