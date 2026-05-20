#define oper min
int st[K][1<<K];int n;  // K such that 2^K>n
void st_init(int *a){
	for (int i = 0; i < n; ++i)st[0][i]=a[i];
	for (int k = 1; k < K; ++k)for (int i = 0; i < n-(1<<k)+1; ++i)
		st[k][i]=oper(st[k-1][i],st[k-1][i+(1<<(k-1))]);
}
int st_query(int s, int e){
	int k=31-__builtin_clz(e-s);
	return oper(st[k][s],st[k][e-(1<<k)]);
}
