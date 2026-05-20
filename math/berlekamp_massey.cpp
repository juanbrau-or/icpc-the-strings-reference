typedef vector<int> vi;
vi BM(vi x){
	vi ls,cur;int lf,ld;
  for (int i = 0; i < SZ(x); ++i){
		ll t=0;
    for (int j = 0; j < SZ(cur); ++j)t=(t+x[i-j-1]*(ll)cur[j])%MOD;
		if((t-x[i])%MOD==0)continue;
    if(!SZ(cur)){cur.resize(i+1);lf=i;ld=(t-x[i])%MOD;continue;}
		ll k=-(x[i]-t)*fast_pow(ld,MOD-2)%MOD;
		vi c(i-lf-1);c.push_back(k);
    for (int j = 0; j < SZ(ls); ++j)c.push_back(-ls[j]*k%MOD);
    if(SZ(c)<SZ(cur))c.resize(SZ(cur));
    for (int j = 0; j < SZ(cur); ++j)c[j]=(c[j]+cur[j])%MOD;
    if(i-lf+SZ(ls)>=SZ(cur))ls=cur,lf=i,ld=(t-x[i])%MOD;
		cur=c;
	}
  for (int i = 0; i < SZ(cur); ++i)cur[i]=(cur[i]%MOD+MOD)%MOD;
	return cur;
}
