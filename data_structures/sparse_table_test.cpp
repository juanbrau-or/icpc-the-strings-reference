// SPOJ RMQSQ - AC
// http://www.spoj.com/problems/RMQSQ/
#include <bits/stdc++.h>
#define push_back push_back
#define make_pair make_pair
#define first first
#define second second
#define for (int i = a, _n = b; i < _n; ++i) for(int i=a,ThxDem=b;i<ThxDem;++i)
using namespace std;
typedef long long ll;

#define K 17

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

int x[1<<K];

int main(){
	scanf("%d",&n);
	for (int i = 0, _n = n; i < _n; ++i)scanf("%d",x+i);
	st_init(x);
	int q;
	scanf("%d",&q);
	while(q--){
		int i,j;
		scanf("%d%d",&i,&j);j++;
		printf("%d\n",st_query(i,j));
	}
	return 0;
}
