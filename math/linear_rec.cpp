//init O(n^2log) query(n^2 logk)
//input: terms: first n term; trans: transition function; MOD; LOG=mxlog of k
//output calc(k): kth term mod MOD
//example: {1,1} {2,1} an=2*a_(n-1)+a_(n-2); calc(3)=3 calc(10007)=71480733
struct LinearRec{
  typedef vector<int> vi;
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
