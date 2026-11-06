//returns x such that a^x = b (mod m) or -1 if inexistent
ll discrete_log(ll a,ll b,ll m) {
    assert(m>0);if(m==1)return 0;
    a%=m;b%=m;if(a<0)a+=m;if(b<0)b+=m;
    if(b == 1) return 0;
    int cnt=0;
    ll tmp=1;
    for(int g=std::gcd(a,m);g!=1;g=std::gcd(a,m)) {
        if(b%g) return -1;
        m/=g, b/=g;
        tmp = (ll)((__int128)tmp*(a/g)%m);
        ++cnt;
        if(b == tmp) return cnt;
    }
    map<ll,int> w;
    int s = ceil(sqrt(m));
    ll base = b;
    fore(i,0,s) {
        w[base] = i;
        base=(__int128)base*a%m;
    }
    base=modpow(a,s,m);
    ll key=tmp;
    fore(i,1,s+2) {
        key=(__int128)base*key%m;
        if(w.count(key)) return i*s-w[key]+cnt;
    }
    return -1;
}
