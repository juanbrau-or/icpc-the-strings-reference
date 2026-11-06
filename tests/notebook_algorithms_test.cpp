// Regression/stress checks include the ACTUAL notebook snippets.
// Standard headers keep this test runner usable with Apple Clang too.
#include <algorithm>
#include <array>
#include <cassert>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <deque>
#include <functional>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>
using namespace std;
using ll=long long;
#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)
#define SZ(x) ((int)(x).size())
#define ALL(x) (x).begin(),(x).end()
namespace seq{
#include "../other/binary_search.cpp"
#include "../other/coordinate_compression.cpp"
#include "../other/prefix_sums_2d.cpp"
#include "../other/lis.cpp"
#include "../other/knapsack.cpp"
#include "../other/subset_dp.cpp"
#include "../other/meet_in_middle.cpp"
#include "../other/digit_dp.cpp"
#include "../other/monotonic_queue.cpp"
#include "../other/divide_and_conquer_dp.cpp"
}
namespace graph{
#include "../graphs/bfs.cpp"
#include "../graphs/zero_one_bfs.cpp"
#include "../graphs/tree_tour.cpp"
#include "../graphs/rerooting_distances.cpp"
#include "../graphs/functional_graph.cpp"
}
namespace freq{
#include "../data_structures/fenwick_order.cpp"
#include "../data_structures/disjoint_intervals.cpp"
#include "../data_structures/li_chao_tree.cpp"
}
namespace num{
#include "../math/combinatorics_mod.cpp"
#include "../math/xor_basis.cpp"
#include "../math/pollard_rho.cpp"
#include "../math/tonelli_shanks.cpp"
#include "../math/discrete_log.cpp"
#include "../math/diophantine.cpp"
#include "../math/inversemod.cpp"
#include "../math/divisors.cpp"
#include "../math/floor_division.cpp"
#include "../math/points_under_line.cpp"
#include "../math/prime_count.cpp"
const int MOD=1000000007,LOG=63;
#include "../math/linear_rec.cpp"
ll fast_pow(ll a,ll e){return modpow(a,e,MOD);}
#include "../math/berlekamp_massey.cpp"
#include "../math/crt.cpp"
#undef mod
}
namespace fftcheck{
const int MAXN=512;
#include "../math/fft.cpp"
}
namespace nttcheck{
#include "../math/ntt.cpp"
}
namespace fhtcheck{
const int MAXN=512;
#include "../math/fht.cpp"
}
namespace karacheck{
#include "../math/karatsuba.cpp"
#undef add
}
namespace series{
using nttcheck::poly;using nttcheck::conv_small;
#include "../math/fft_modular_helpers.cpp"
#include "../math/fft_operations.cpp"
}
namespace hldcheck{
const int MAXN=64,INF=1000000000;
#include "../data_structures/segment_tree.cpp"
#include "../graphs/hld.cpp"
#undef oper
#undef NEUT
}
namespace persistent{
const int INF=1000000000;
#include "../data_structures/segment_tree_persistent.cpp"
#undef oper
#undef NEUT
}
namespace lazycheck{
#include "../data_structures/segment_tree_lazy.cpp"
}
namespace cuts{
const int MAXN=64;
#include "../graphs/articulation_bridges_biconnected.cpp"
}
namespace sat{
const int MAXN=64;
#include "../graphs/tarjan_2sat.cpp"
}
namespace sa{
#include "../strings/suffix_array.cpp"
#include "../strings/lcp.cpp"
#undef RB
}
namespace saslow{
const int MAXN=512;
#include "../strings/suffix_array_slow.cpp"
}
namespace str{
const int MAXN=512,INF=1000000000;
#include "../strings/kmp.cpp"
#include "../strings/z_function.cpp"
#include "../strings/manacher.cpp"
#include "../strings/minimal_rotation.cpp"
#include "../strings/suffix_automaton.cpp"
#include "../strings/palindromic_tree.cpp"
#include "../strings/aho_corasick.cpp"
#include "../strings/suffix_tree.cpp"
}
namespace hashing{
#include "../strings/hashing.cpp"
}
namespace hash128{
#include "../strings/hashing_128.cpp"
#undef bint
}
namespace flow{
const ll INF=LLONG_MAX/4;
#include "../flow/dinic.cpp"
#include "../flow/min_cost_max_flow.cpp"
}
namespace assignment{
#include "../flow/hungarian.cpp"
}
namespace hk{
const int MAXN=64;
#include "../flow/hopcroft_karp.cpp"
}
namespace geo{
const double EPS=1e-9,DINF=numeric_limits<double>::infinity(),INF=1e100;
#include "../geometry/point.cpp"
#include "../geometry/line.cpp"
#include "../geometry/radial_order.cpp"
#include "../geometry/circle.cpp"
#include "../geometry/convex_hull.cpp"
#include "../geometry/polygon.cpp"
#include "../geometry/halfplanes.cpp"
#include "../geometry/minkowski_sum.cpp"
#include "../geometry/kdtree.cpp"
#include "../geometry/delaunay.cpp"
}
mt19937 rng(20261105);
int rnd(int a,int b){return uniform_int_distribution<int>(a,b)(rng);}
ll checked=0;
#define CHECK(x) do{++checked;if(!(x)){cerr<<"FAIL line "<<__LINE__<<": "<<#x<<'\n';abort();}}while(0)
vector<ll> convolution(const vector<ll>& a,const vector<ll>& b,ll mod=0){
    if(a.empty()||b.empty())return {};
    vector<ll> c(SZ(a)+SZ(b)-1);
    fore(i,0,SZ(a))fore(j,0,SZ(b)){c[i+j]+=a[i]*b[j];if(mod)c[i+j]%=mod;}
    return c;
}
void sequences(){
    fore(it,0,200){
        int n=rnd(0,12);vector<ll> a(n);for(ll &x:a)x=rnd(-5,8);
        seq::Compression<ll> c(a);for(ll x:a)CHECK(c.value(c.rank(x))==x);
        auto ids=seq::lis(a);int best=0;
        fore(s,0,1<<n){ll last=LLONG_MIN;int len=0;bool ok=true;
            fore(i,0,n)if(s>>i&1){if(a[i]<=last)ok=false;last=a[i];len++;}
            if(ok)best=max(best,len);
        }
        CHECK(SZ(ids)==best);fore(i,1,SZ(ids))CHECK(ids[i]>ids[i-1]&&a[ids[i]]>a[ids[i-1]]);
        ll B=rnd(-10,20),count=0;
        fore(s,0,1<<n){ll sum=0;fore(i,0,n)if(s>>i&1)sum+=a[i];count+=sum<=B;}
        CHECK(seq::count_subsets_leq(a,B)==count);
        if(n){int k=rnd(1,n);auto mins=seq::sliding_min(a,k);
            fore(i,0,n-k+1)CHECK(mins[i]==*min_element(a.begin()+i,a.begin()+i+k));}
        vector<ll> heights(n);for(ll &x:heights)x=rnd(0,9);ll area=0;
        fore(l,0,n){ll h=LLONG_MAX;fore(r,l,n){h=min(h,heights[r]);area=max(area,h*(r-l+1));}}
        CHECK(seq::histogram_area(heights)==area);
        int bits=rnd(0,7);vector<ll> f(1<<bits);for(ll &x:f)x=rnd(-5,8);auto old=f;
        seq::sos(f,bits);fore(s,0,1<<bits){ll sum=0;fore(t,0,1<<bits)if((s&t)==t)sum+=old[t];CHECK(f[s]==sum);}
        seq::sos(f,bits,true);CHECK(f==old);
        ll target=rnd(-5,25);CHECK(seq::first_true(-5,26,[&](ll x){return x>=target;})==target);
        CHECK(seq::first_true(0,10,[](ll){return false;})==10);
        vector<int> w(n);vector<ll> v(n);fore(i,0,n)w[i]=rnd(1,6),v[i]=rnd(-3,9);
        int W=rnd(0,20);ll val=0;
        fore(s,0,1<<n){int wt=0;ll vl=0;fore(i,0,n)if(s>>i&1)wt+=w[i],vl+=v[i];if(wt<=W)val=max(val,vl);}
        CHECK(seq::knapsack(w,v,W)==val);
        vector<ll> dp(W+1);fore(b,1,W+1)fore(i,0,n)if(w[i]<=b)dp[b]=max(dp[b],dp[b-w[i]]+v[i]);
        CHECK(seq::knapsack(w,v,W,true)==dp[W]);
    }
    fore(N,0,2500){int brute=0;fore(x,0,N+1){string s=to_string(x);bool ok=true;fore(i,1,SZ(s))if(s[i]==s[i-1])ok=false;brute+=ok;}CHECK(seq::count_no_adjacent(N)==brute);}
    CHECK(seq::count_no_adjacent(-1)==0);
    fore(it,0,60){
        int n=rnd(1,15),k=rnd(1,n);vector<ll> p(n+1);
        fore(i,0,n)p[i+1]=p[i]+rnd(0,8);
        auto cost=[&](int l,int r){return (p[r]-p[l])*(p[r]-p[l]);};
        vector<ll> dp(n+1,seq::INF_DP);dp[0]=0;
        fore(g,0,k){vector<ll> ndp(n+1,seq::INF_DP);fore(r,1,n+1)fore(l,0,r)if(dp[l]<seq::INF_DP)ndp[r]=min(ndp[r],dp[l]+cost(l,r));dp=ndp;}
        CHECK(seq::partition_dp(n,k,cost)==dp[n]);
        int rows=rnd(1,7),cols=rnd(1,7);vector<vector<ll>> a(rows,vector<ll>(cols));
        for(auto &r:a)for(auto &x:r)x=rnd(-5,9);seq::Prefix2D pref(a);
        fore(x0,0,rows+1)fore(x1,x0,rows+1)fore(y0,0,cols+1)fore(y1,y0,cols+1){
            ll sum=0;fore(x,x0,x1)fore(y,y0,y1)sum+=a[x][y];CHECK(pref.query(x0,x1,y0,y1)==sum);
        }
        int cities=rnd(2,7);vector<vector<ll>> c(cities,vector<ll>(cities));
        for(auto &r:c)for(auto &x:r)x=rnd(0,20);
        vector<int> perm(cities-1);iota(ALL(perm),1);ll opt=LLONG_MAX;
        do{ll sum=0;int prev=0;for(int u:perm)sum+=c[prev][u],prev=u;sum+=c[prev][0];opt=min(opt,sum);}while(next_permutation(ALL(perm)));
        CHECK(seq::held_karp(c)==opt);
    }
}
void graphs(){
    fore(it,0,150){
        int n=rnd(1,20);vector<vector<int>> g(n);
        fore(u,1,n){int p=rnd(0,u-1);g[u].pb(p);g[p].pb(u);}
        graph::TreeTour tour(g);auto sums=graph::distance_sums(g,rnd(0,n-1));
        fore(u,0,n){auto [d,p]=graph::bfs(g,{u});CHECK(accumulate(ALL(d),0LL)==sums[u]);
            fore(v,0,n){auto path=graph::restore_path(v,d,p);CHECK(SZ(path)==d[v]+1);CHECK(path.front()==u&&path.back()==v);
                bool anc=false;for(int x=v;x>=0;x=tour.parent[x])if(x==u)anc=true;CHECK(tour.ancestor(u,v)==anc);}}
        vector<vector<pair<int,int>>> edges(n);vector<vector<int>> d(n,vector<int>(n,10000));
        fore(u,0,n){d[u][u]=0;fore(v,0,n)if(rnd(0,4)==0){int w=rnd(0,1);edges[u].pb({v,w});d[u][v]=min(d[u][v],w);}}
        fore(k,0,n)fore(u,0,n)fore(v,0,n)d[u][v]=min(d[u][v],d[u][k]+d[k][v]);
        fore(u,0,n){auto got=graph::bfs01(edges,u);fore(v,0,n)CHECK(got[v]==(d[u][v]==10000?INT_MAX:d[u][v]));}
        vector<int> nxt(n);for(int &v:nxt)v=rnd(0,n-1);graph::FunctionalGraph f(nxt);
        fore(u,0,n){vector<int> steps(n,-1);int x=u,k=0;while(steps[x]<0)steps[x]=k++,x=nxt[x];
            fore(v,0,n)CHECK(f.steps(u,v)==steps[v]);x=u;fore(k,0,150){CHECK(f.jump(u,k)==x);x=nxt[x];}
            int entry=f.entry[u],len=f.len[f.comp[u]];CHECK(f.jump(entry,LLONG_MAX)==f.jump(entry,LLONG_MAX%len));}
    }
}
void structures(){
    fore(it,0,120){
        int n=rnd(1,30);freq::FenwickOrder f(n);vector<ll> a(n);
        fore(q,0,100){int p=rnd(0,n-1);ll delta=a[p]&&rnd(0,1)?-1:1;a[p]+=delta;f.add(p,delta);
            int l=rnd(0,n),r=rnd(l,n);CHECK(f.sum(l,r)==accumulate(a.begin()+l,a.begin()+r,0LL));
            vector<int> values;fore(i,0,n)fore(j,0,a[i])values.pb(i);
            fore(k,0,SZ(values))CHECK(f.kth(k)==values[k]);CHECK(f.kth(SZ(values))==-1);CHECK(f.kth(-1)==-1);
        }
        freq::LiChaoTree tree(n);vector<tuple<ll,ll,int,int>> lines;
        fore(q,0,40){ll m=rnd(-10,10),b=rnd(-30,30);int l=rnd(0,n-1),r=rnd(l+1,n);
            if(rnd(0,1))l=0,r=n;tree.add(freq::Line(m,b),l,r);lines.pb({m,b,l,r});
            fore(x,0,n){ll best=-freq::INF;for(auto [m,b,l,r]:lines)if(l<=x&&x<r)best=max(best,m*x+b);CHECK(tree.query(x)==best);}
        }
        vector<int> arr(n);for(int &x:arr)x=rnd(-20,20);
        persistent::STree st(n);vector<int> roots={st.init(arr.data())};vector<vector<int>> ver={arr};
        fore(q,0,40){int old=rnd(0,SZ(roots)-1),p=rnd(0,n-1),v=rnd(-20,20);auto a=ver[old];a[p]=v;
            roots.pb(st.upd(roots[old],p,v));ver.pb(a);
            int ix=rnd(0,SZ(roots)-1),l=rnd(0,n-1),r=rnd(l+1,n);
            CHECK(st.query(roots[ix],l,r)==*min_element(ver[ix].begin()+l,ver[ix].begin()+r));}
        lazycheck::STree lazy(n);lazy.init(arr.data());
        fore(q,0,50){int l=rnd(0,n-1),r=rnd(l+1,n),v=rnd(-10,10);lazy.upd(l,r,v);fore(i,l,r)arr[i]+=v;
            l=rnd(0,n-1);r=rnd(l+1,n);CHECK(lazy.query(l,r)==accumulate(arr.begin()+l,arr.begin()+r,0));}
        freq::disjoint_intervals covered;set<int> cells;
        fore(q,0,50){int l=rnd(-10,10),r=rnd(l,15);covered.insert({l,r});fore(x,l,r)cells.insert(x);
            set<int> got;int last=INT_MIN;for(auto [a,b]:covered.s){CHECK(a>last);last=b;fore(x,a,b)got.insert(x);}CHECK(got==cells);}
    }
    fore(it,0,100){
        int n=rnd(1,20);fore(u,0,n)hldcheck::g[u].clear();
        vector<int> val(n);for(int &v:val)v=rnd(-20,20);
        fore(u,1,n){int p=rnd(0,u-1);hldcheck::g[u].pb(p);hldcheck::g[p].pb(u);}
        hldcheck::hld_init();vector<int> base(n);fore(u,0,n)base[hldcheck::pos[u]]=val[u];hldcheck::STree st(n);st.init(base.data());
        fore(q,0,50){int u=rnd(0,n-1),v=rnd(0,n-1);vector<vector<int>> g(n);fore(x,0,n)g[x]=hldcheck::g[x];auto [d,p]=graph::bfs(g,{u});int ans=INT_MAX;
            for(int x=v;x!=-1;x=p[x])ans=min(ans,val[x]);CHECK(hldcheck::query(u,v,st)==ans);
            int w=rnd(0,n-1);val[w]=rnd(-20,20);st.upd(hldcheck::pos[w],val[w]);}
    }
    fore(it,0,100){
        fore(i,0,sat::MAXN)sat::g[i].clear();int n=rnd(1,6);vector<pair<int,int>> clauses;
        fore(j,0,rnd(0,15)){int a=rnd(0,n-1),b=rnd(0,n-1);if(rnd(0,1))a=sat::neg(a);if(rnd(0,1))b=sat::neg(b);sat::addor(a,b);clauses.pb({a,b});}
        auto valid=[&](int mask){auto lit=[&](int x){return x<n?bool(mask>>x&1):!bool(mask>>sat::neg(x)&1);};for(auto [a,b]:clauses)if(!lit(a)&&!lit(b))return false;return true;};
        bool exists=false;fore(mask,0,1<<n)exists|=valid(mask);CHECK(sat::satisf(n)==exists);
        if(exists){int mask=0;fore(i,0,n)if(sat::truth[sat::cmp[i]])mask|=1<<i;CHECK(valid(mask));}
    }
    cuts::n=3;fore(i,0,3)cuts::g[i].clear();cuts::e.clear();cuts::add_edge(0,1);cuts::doit();
    CHECK(cuts::art[0]==0&&cuts::art[1]==0&&cuts::art[2]==0&&cuts::e[0].bridge);
}
void mathematics(){
    num::Comb comb(100,1000000007);vector<vector<ll>> pascal(101,vector<ll>(101));
    pascal[0][0]=1;fore(n,0,101){if(n){pascal[n][0]=1;fore(k,1,n+1)pascal[n][k]=(pascal[n-1][k-1]+pascal[n-1][k])%comb.p;}
        fore(k,0,n+1)CHECK(comb.C(n,k)==pascal[n][k]);}
    CHECK(num::modpow(-3,3,11)==6);
    fore(n,0,4000){bool prime=n>=2;for(int d=2;d*d<=n;d++)if(n%d==0)prime=false;CHECK(num::rabin(n)==prime);}
    for(ll n:{1LL,4LL,8LL,561LL,3215031751LL,1000000007LL*1000000009LL,9223372036854775807LL}){
        map<ll,int> f;num::fact(n,f);__int128 product=1;
        for(auto [p,e]:f){CHECK(num::rabin(p));fore(i,0,e)product*=p;}
        CHECK(product==n);
        if(n<100000){vector<pair<ll,int>> v(ALL(f));auto div=num::divisors(v);sort(ALL(div));vector<ll> want;fore(d,1,n+1)if(n%d==0)want.pb(d);CHECK(div==want);}
    }
    for(int p:{2,3,5,7,13,17,41,97})fore(n,0,p){
        ll root=num::tonelli_shanks(n,p);bool exists=false;fore(x,0,p)exists|=x*x%p==n;
        CHECK((root>=0)==exists);if(root>=0)CHECK(root*root%p==n);
    }
    fore(m,1,60)fore(a,0,m)fore(b,0,m){
        int want=-1;ll v=1%m;fore(e,0,m+1){if(v==b){want=e;break;}v=v*a%m;}
        CHECK(num::discrete_log(a,b,m)==want);
    }
    fore(it,0,100){
        num::XorBasis b;vector<unsigned long long> values={0};int n=rnd(0,10);
        fore(i,0,n){unsigned long long x=rnd(0,127);b.add(x);int z=SZ(values);fore(j,0,z)values.pb(values[j]^x);}
        auto max=*max_element(ALL(values));CHECK(b.maximum()==max);
        fore(x,0,128)CHECK(b.has(x)==(find(ALL(values),x)!=values.end()));
        sort(ALL(values));values.erase(unique(ALL(values)),values.end());CHECK(SZ(values)==(1<<b.rank));
    }
    num::XorBasis high;high.add(1ULL<<63);CHECK(high.maximum()==(1ULL<<63));
    fore(a,-15,16)fore(b,-15,16)if(a||b){auto [x,y]=num::extendedEuclid(a,b);CHECK(a*x+b*y==gcd(a,b));}
    fore(x,-20,21)fore(y,-10,11)if(y){ll q,r;num::floordiv(x,y,q,r);CHECK(q==(ll)floor((double)x/y));CHECK(q*y+r==x);}
    fore(a,1,9)fore(b,1,9)fore(c,0,45){ll count=0;fore(x,1,46)fore(y,1,46)count+=a*x+b*y<=c;CHECK(num::f(a,b,c)==count);}
    fore(n,0,300){ll count=0;fore(x,2,n+1)count+=num::rabin(x);CHECK(num::prime_count(n)==count);}
    CHECK(num::crt({{1,2,3},{1,3,5}})==make_pair(8LL,15LL));
    CHECK(num::crt({{1,0,2},{1,1,4}})==make_pair(-1LL,-1LL));
    CHECK(num::crt({{1,3999999999999999999LL,4000000000000000001LL},{1,0,2}})==make_pair(8000000000000000000LL,8000000000000000002LL));
    fore(it,0,200){
        vector<tuple<ll,ll,ll>> cond;ll period=1;
        fore(i,0,3){ll a=rnd(-5,5),b=rnd(-20,20),m=rnd(1,14);cond.pb({a,b,m});period=lcm(period,m/gcd(a,m));}
        ll first=-1;
        fore(x,0,period){bool ok=true;for(auto [a,b,m]:cond)if((a*x-b)%m)ok=false;if(ok){first=x;break;}}
        auto got=num::crt(cond);CHECK(got==(first<0?make_pair(-1LL,-1LL):make_pair(first,period)));
    }
    vector<int> terms={1,1},trans={2,1};num::LinearRec rec(terms,trans);
    vector<int> want={1,1};fore(i,2,100)want.pb((2LL*want[i-1]+want[i-2])%num::MOD);
    fore(i,0,100)CHECK(rec.calc(i+1)==want[i]);CHECK(num::BM(want)==trans);
    CHECK(rec.calc(1000000000000000000LL)>=0);
    CHECK(seq::partition_dp(1,2,[](int,int){return 0;})==seq::INF_DP);
    fore(it,0,120){
        int n=rnd(0,45),m=rnd(0,45);vector<ll> a(n),b(m);for(ll &x:a)x=rnd(0,30);for(ll &x:b)x=rnd(0,30);
        auto want=convolution(a,b);
        CHECK(fftcheck::multiply(a,b)==want);CHECK(karacheck::multiply(a,b)==want);
        CHECK(nttcheck::conv_small(a,b)==want);CHECK(nttcheck::conv_big(a,b)==want);
        CHECK(nttcheck::conv_sunzi(a,b,1000000007)==want);
        if(n&&m){int size=1;while(size<max(n,m))size*=2;vector<ll> x(size);
            fore(i,0,n)fore(j,0,m)x[i^j]+=a[i]*b[j];CHECK(fhtcheck::multiply(a,b)==x);}
        else CHECK(fhtcheck::multiply(a,b).empty());
    }
    fore(it,0,40){
        int n=rnd(1,15);series::poly p(n);p[0]=1;fore(i,1,n)p[i]=rnd(0,20);
        auto inv=series::invert(p,n);auto product=series::multiply(p,inv);CHECK(product[0]==1);fore(i,1,n)CHECK(product[i]==0);
        auto log=series::log(p,n),exp=series::exp(log,n);exp.resize(n);CHECK(exp==p);
        vector<ll> x(n),y(n);iota(ALL(x),0);y=series::evaluate(p,x);
        fore(i,0,n){ll value=0;for(int j=n-1;j>=0;j--)value=(value*x[i]+p[j])%series::MOD;CHECK(y[i]==value);}
        auto interpolated=series::interpolate(x,y);interpolated.resize(n);CHECK(interpolated==p);
        series::poly divisor={1,1};auto [q,r]=series::divide(p,divisor);auto restored=series::multiply(q,divisor);restored.resize(max(SZ(restored),SZ(r)));
        fore(i,0,SZ(r))restored[i]=(restored[i]+r[i])%series::MOD;
        restored.resize(n);CHECK(restored==p);
        series::poly zero={0};CHECK(series::evaluate(zero,x)==vector<ll>(n));
    }
}
bool tree_has(str::SuffixTree &t,const string &pattern){
    int v=0,i=0;
    while(i<SZ(pattern)){
        auto it=t.to[v].find(pattern[i]);if(it==t.to[v].end())return false;
        v=it->second;int len=min(t.len[v],t.n-t.fpos[v]);
        fore(j,0,len){if(i==SZ(pattern))return true;if(pattern[i++]!=t.s[t.fpos[v]+j])return false;}
    }
    return true;
}
void strings(){
    fore(it,0,200){
        string s;fore(i,0,rnd(0,25))s+=char('a'+rnd(0,2));int n=SZ(s);
        vector<int> want(n);iota(ALL(want),0);sort(ALL(want),[&](int a,int b){return s.substr(a)<s.substr(b);});
        auto fast=sa::constructSA(s);CHECK(fast==want);CHECK(saslow::constructSA(s)==want);
        auto lcp=sa::computeLCP(s,fast);fore(i,1,n){int k=0;while(fast[i]+k<n&&fast[i-1]+k<n&&s[fast[i]+k]==s[fast[i-1]+k])k++;CHECK(lcp[i]==k);}
        auto z=str::z_function(s),b=str::kmppre(s);fore(i,1,n){int k=0;while(i+k<n&&s[k]==s[i+k])k++;CHECK(z[i]==k);}
        fore(i,1,n+1){int k=i-1;while(k>0&&s.substr(0,k)!=s.substr(i-k,k))k--;CHECK(b[i]==k);}
        str::manacher(s);set<string> distinct,pals;vector<ll> counts;
        str::palindromic_tree pt;str::sa_init();auto tree=make_unique<str::SuffixTree>();
        fore(i,0,n){pt.add(i,s);str::sa_extend(s[i]);tree->add(s[i]);}
        tree->add('$');hashing::Hash hash(s);hash128::Hash h128(s);
        fore(l,0,n)fore(r,l+1,n+1){string sub=s.substr(l,r-l),rev=sub;reverse(ALL(rev));distinct.insert(sub);if(sub==rev)pals.insert(sub);}
        CHECK(SZ(pt.ns)-2==SZ(pals));ll distinct_count=0;fore(v,1,str::sz)distinct_count+=str::st[v].len-str::st[str::st[v].link].len;CHECK(distinct_count==SZ(distinct));
        for(int v=SZ(pt.ns)-1;v>=2;v--)pt.ns[pt.ns[v].link].cnt+=pt.ns[v].cnt;
        map<pair<int,ll>,int> pal_stat,expected_stat;
        fore(v,2,SZ(pt.ns))pal_stat[{pt.ns[v].len,pt.ns[v].cnt}]++;
        for(auto &p:pals){ll c=0;fore(i,0,n-SZ(p)+1)c+=s.compare(i,SZ(p),p)==0;expected_stat[{SZ(p),c}]++;}CHECK(pal_stat==expected_stat);
        fore(i,0,n){int odd=1,even=0;while(i-odd>=0&&i+odd<n&&s[i-odd]==s[i+odd])odd++;while(i-even-1>=0&&i+even<n&&s[i-even-1]==s[i+even])even++;CHECK(str::d1[i]==odd&&str::d2[i]==even);}
        string best=s;int pos=str::minimal_rotation(s);fore(i,0,n)best=min(best,s.substr(i)+s.substr(0,i));CHECK(s.substr(pos)+s.substr(0,pos)==best);
        fore(q,0,20){string p;fore(i,0,rnd(1,7))p+=char('a'+rnd(0,2));bool exists=s.find(p)!=string::npos;CHECK(tree_has(*tree,p)==exists);
            int v=0;bool sam=true;for(char c:p){auto it=str::st[v].next.find(c);if(it==str::st[v].next.end()){sam=false;break;}v=it->second;}CHECK(sam==exists);
            int len=rnd(0,n),l=rnd(0,n-len),r=rnd(0,n-len);bool same=s.compare(l,len,s,r,len)==0;CHECK((hash.get(l,l+len)==hash.get(r,r+len))==same);CHECK((h128.get(l,l+len)==h128.get(r,r+len))==same);
        }
        str::aho_init();vector<string> patterns;vector<int> terminal;
        fore(i,0,8){string p;fore(j,0,rnd(1,5))p+=char('a'+rnd(0,2));patterns.pb(p);str::add_string(p,i);int v=0;for(char c:p)v=str::t[v].next.at(c);terminal.pb(v);}
        int m=SZ(str::t);vector<vector<int>> children(m);fore(v,1,m)children[str::get_link(v)].pb(v);
        vector<int> order={0};for(int i=0;i<SZ(order);i++)for(int v:children[order[i]])order.pb(v);
        vector<ll> count(m);int v=0;for(char c:s)v=str::go(v,c),count[v]++;
        for(int i=SZ(order)-1;i>0;i--)count[str::get_link(order[i])]+=count[order[i]];
        fore(i,0,SZ(patterns)){ll expected=0;fore(j,0,n-SZ(patterns[i])+1)expected+=s.compare(j,SZ(patterns[i]),patterns[i])==0;CHECK(count[terminal[i]]==expected);}
    }
}
void flows(){
    fore(it,0,120){
        int n=rnd(1,5),m=rnd(1,5),S=n+m,T=S+1;vector<vector<int>> costs(n,vector<int>(m));
        flow::Dinic d(T+1);flow::MCF f(T+1);hk::n=n;hk::m=m;fore(u,0,n)hk::g[u].clear();
        fore(u,0,n){d.add_edge(S,u,1);f.add_edge(S,u,1,0);}
        fore(v,0,m){d.add_edge(n+v,T,1);f.add_edge(n+v,T,1,0);}
        fore(u,0,n)fore(v,0,m){costs[u][v]=rnd(-10,10);if(rnd(0,3)){hk::g[u].pb(v);d.add_edge(u,n+v,1);f.add_edge(u,n+v,1,costs[u][v]);}}
        pair<int,ll> best={-1,0};function<void(int,int,int,ll)> brute=[&](int u,int mask,int count,ll cost){
            if(u==n){if(count>best.first||(count==best.first&&cost<best.second))best={count,cost};return;}
            brute(u+1,mask,count,cost);for(int v:hk::g[u])if(!(mask>>v&1))brute(u+1,mask|(1<<v),count+1,cost+costs[u][v]);
        };brute(0,0,0,0);
        CHECK(d.max_flow(S,T)==best.first);CHECK(hk::mm()==best.first);CHECK(f.get_flow(S,T)==make_pair((ll)best.first,best.second));
        int k=rnd(1,6);assignment::Hungarian h(k,k);vector<vector<int>> c(k,vector<int>(k));
        fore(u,0,k)fore(v,0,k)c[u][v]=rnd(-10,10),h.set(u,v,c[u][v]);
        vector<int> p(k);iota(ALL(p),0);ll opt=LLONG_MAX;
        do{ll cost=0;fore(u,0,k)cost+=c[u][p[u]];opt=min(opt,cost);}while(next_permutation(ALL(p)));
        CHECK(fabsl(h.assign()-opt)<1e-8);
    }
    flow::MCF f(3);f.add_edge(0,1,3000000000LL,2);f.add_edge(1,2,3000000000LL,1);
    CHECK(f.get_flow(0,2,2000000000LL)==make_pair(2000000000LL,6000000000LL));
    CHECK(f.get_flow(0,2)==make_pair(1000000000LL,3000000000LL));
    flow::MCF negative(3);negative.add_edge(0,1,2,-2);negative.add_edge(1,0,2,1);negative.add_edge(1,2,1,0);
    bool rejected=false;try{negative.get_flow(0,2);}catch(const invalid_argument&){rejected=true;}CHECK(rejected);
    flow::Dinic self(2);self.add_edge(0,0,5);self.add_edge(0,1,3);CHECK(self.max_flow(0,1)==3);
}
void geometry(){
    CHECK(geo::chull({}).empty());CHECK(SZ(geo::chull({{2,3}}))==1);
    geo::ln horizontal({0,0},{1,0}),vertical({2,-1},{2,1});auto inter=horizontal^vertical;CHECK(abs(inter.x-2)<1e-8&&abs(inter.y)<1e-8);
    geo::circle c({0,0},1),same({0,0},1);CHECK((c^same).empty());CHECK(c.tang({0,0}).empty());CHECK(SZ(c^horizontal)==2);
    vector<geo::halfplane> h={{{0,0},{1,0}},{{1,0},{1,1}},{{1,1},{0,1}},{{0,1},{0,0}}};
    auto square=geo::intersect(h);CHECK(abs(geo::pol(square).area()-1)<1e-7);
    fore(it,0,80){
        vector<geo::pt> p;fore(i,0,rnd(1,30))p.pb({(double)rnd(-20,20),(double)rnd(-20,20)});
        geo::KDTree kd(p);fore(q,0,20){geo::pt x(rnd(-20,20),rnd(-20,20));double best=1e100;for(auto y:p)best=min(best,(x-y).norm2());CHECK(abs(kd.nearest(x).first-best)<1e-8);}
        auto hull=geo::chull(p);if(SZ(hull)>=3){geo::pol pol(hull);for(auto x:p)CHECK(pol.has(x));}
        vector<geo::pt> unique=p;sort(ALL(unique));unique.erase(std::unique(ALL(unique)),unique.end());auto dg=geo::delaunay(unique);CHECK(SZ(dg)==SZ(unique));
        fore(u,0,SZ(dg))for(int v:dg[u])CHECK(find(ALL(dg[v]),u)!=dg[v].end());
    }
    vector<geo::pt> a={{0,0},{1,0},{1,1},{0,1}},b={{0,0},{2,0},{2,2},{0,2}};
    auto sum=geo::minkowski_sum(a,b);CHECK(abs(geo::pol(sum).area()-9)<1e-8);
}
int main(){
    sequences();graphs();structures();mathematics();strings();flows();geometry();
    cout<<"OK: "<<checked<<" deterministic regression/stress assertions\n";
}
