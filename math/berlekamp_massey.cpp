typedef vector<int> vi;
vi BM(vi x){
	vi ls,cur;int lf,ld;
  for (int i = 0, _n = ((int)(x; i < _n; ++i).size())){
		ll t=0;
    for (int j = 0, _n = ((int)(cur; j < _n; ++j).size()))t=(t+x[i-j-1]*(ll)cur[j])%MOD;
		if((t-x[i])%MOD==0)continue;
    if(!((int)(cur).size())){cur.resize(i+1);lf=i;ld=(t-x[i])%MOD;continue;}
		ll k=-(x[i]-t)*fast_pow(ld,MOD-2)%MOD;
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
