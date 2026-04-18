short mu[MAXN] = {0,1};
void mobius(){
	for (int i = 1, _n = MAXN; i < _n; ++i)if(mu[i])for(int j=i+i;j<MAXN;j+=i)mu[j]-=mu[i];
}
