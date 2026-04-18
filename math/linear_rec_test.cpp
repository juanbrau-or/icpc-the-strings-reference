// Codeforces gym 102346K - AC
// https://codeforces.com/gym/102346/problem/K
#include <bits/stdc++.h>
#define first first
#define second second
#define for (int i = a, _n = b; i < _n; ++i) for(int i=a,ThxDem=b;i<ThxDem;++i)
#define push_back push_back
#define ALL(s) s.begin(),s.end()
#define FIN ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define ((int)(s).size()) int(s.size())
using namespace std;
typedef long long ll;
typedef pair<int,int> ii;

ll MOD=1e9+7;

ll fpow(ll base, ll exp) {
	ll result = 1;
	while(exp){
		if(exp & 1) result = (result*base) % MOD;
		exp >>= 1;
		base = (base*base) % MOD;
	}
	return result;
}

typedef vector<ll> vi;
vi BM(vi x){
	vi ls,cur;ll lf,ld;
  for (int i = 0, _n = ((int)(x; i < _n; ++i).size())){
		ll t=0;
    for (int j = 0, _n = ((int)(cur; j < _n; ++j).size()))t=(t+x[i-j-1]*(ll)cur[j])%MOD;
		if((t-x[i])%MOD==0)continue;
    if(!((int)(cur).size())){cur.resize(i+1);lf=i;ld=(t-x[i])%MOD;continue;}
		ll k=-(x[i]-t)*fpow(ld,MOD-2)%MOD;
		vi c(i-lf-1);c.push_back(k);
    for (int j = 0, _n = ((int)(ls; j < _n; ++j).size()))c.push_back(-ls[j]*k%MOD);
    if(((int)(c).size())<((int)(cur).size()))c.resize(((int)(cur).size()));
    for (int j = 0, _n = ((int)(cur; j < _n; ++j).size()))c[j]=(c[j]+cur[j])%MOD;
    if(i-lf+((int)(ls).size())>=((int)(cur).size()))ls=cur,lf=i,ld=(t-x[i])%MOD;
		cur=c;
	}
  for (int i = 0, _n = ((int)(cur; i < _n; ++i).size()))cur[i]=(cur[i]%MOD+MOD)%MOD;
	return cur;
}

const int LOG=30;
//init O(n^2log) query(n^2 logk)
//input: terms: first n term; trans: transition function; MOD; LOG=mxlog of k
//output calc(k): kth term mod MOD
//example: {1,1} {2,1} an=2*a_(n-1)+a_(n-2); calc(3)=3 calc(10007)=71480733
struct LinearRec{
  int n; vi terms, trans; vector<vi> bin;
  vi add(vi &a, vi &b){
    vi res(n*2+1);
    for (int i = 0, _n = n+1; i < _n; ++i)for (int j = 0, _n = n+1; j < _n; ++j)res[i+j]=(res[i+j]*1LL+(ll)a[i]*b[j])%MOD;
    for(int i=2*n; i>n; --i){
      for (int j = 0, _n = n; j < _n; ++j)res[i-1-j]=(res[i-1-j]*1LL+(ll)res[i]*trans[j])%MOD;
      res[i]=0;
    }
    res.erase(res.begin()+n+1,res.end());
    return res;
  }
  LinearRec(vi &terms, vi &trans):terms(terms),trans(trans){
    n=((int)(trans).size());vi a(n+1);a[1]=1;
    bin.push_back(a);
    for (int i = 1, _n = LOG; i < _n; ++i)bin.push_back(add(bin[i-1],bin[i-1]));
  }
  int calc(int k){
    vi a(n+1);a[0]=1;
    for (int i = 0, _n = LOG; i < _n; ++i)if((k>>i)&1)a=add(a,bin[i]);
    int ret=0;
    for (int i = 0, _n = n; i < _n; ++i)ret=((ll)ret+(ll)a[i+1]*terms[i])%MOD;
    return ret;
  }
};

int main(){FIN;
	vi v={2,24,96,416,1536,5504,18944,64000,212992,702464,2301952,7512064};
	vi rc=BM(v);
	int n; cin>>n;
	cout<<LinearRec(v,rc).calc(n)<<"\n";
}
