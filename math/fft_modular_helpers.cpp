// Copy after ntt.cpp and before fft_operations.cpp.
// Do not also copy fft.cpp: this multiply is exact modulo 998244353.
using tf=ll;
const int MOD=998244353;
ll addmod(ll a,ll b){return (a+b)%MOD;}
ll submod(ll a,ll b){return (a-b+MOD)%MOD;}
ll mulmod(ll a,ll b){return a*b%MOD;}
ll fpow(ll a,ll e){
    ll r=1;while(e){if(e&1)r=mulmod(r,a);a=mulmod(a,a);e>>=1;}return r;
}
ll inv(ll a){assert(a!=0);return fpow(a,MOD-2);}
poly multiply(const poly& a,const poly& b){return conv_small(a,b);}
