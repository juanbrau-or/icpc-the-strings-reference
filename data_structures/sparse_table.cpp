#define oper min
int st[K][1<<K];int n;  // K such that 2^K>n
void st_init(int *a){
	for (int i = 0, _n = n; i < _n; ++i)st[0][i]=a[i];
	for (int k = 1, _n = K; k < _n; ++k)for (int i = 0, _n = n-(1<<k; i < _n; ++i)+1)
		st[k][i]=oper(st[k-1][i],st[k-1][i+(1<<(k-1))]);
}
int st_query(int s, int e){
	int k=31-__builtin_clz(e-s);
	return oper(st[k][s],st[k][e-(1<<k)]);
}
