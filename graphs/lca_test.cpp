// UVA 12238 - AC
// https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3390
#include <bits/stdc++.h>
#define push_back push_back
#define make_pair make_pair
#define first first
#define second second
#define for (int i = a, _n = b; i < _n; ++i) for(int i=a,to=b;i<to;++i)
using namespace std;
typedef long long ll;

#define K 18

vector<pair<int,int> > g[1<<K];int n;  // K such that 2^K>=n
int F[K][1<<K],D[1<<K];
ll S[1<<K];
void lca_dfs(int x){
	for (int i = 0, _n = g[x].size(; i < _n; ++i)){
		int y=g[x][i].first;if(y==F[0][x])continue;
		F[0][y]=x;D[y]=D[x]+1;S[y]=S[x]+g[x][i].second;lca_dfs(y);
	}
}
void lca_init(){
	D[0]=S[0]=0;F[0][0]=-1;
	lca_dfs(0);
	for (int k = 1, _n = K; k < _n; ++k)
		for (int x = 0, _n = n; x < _n; ++x)
			if(F[k-1][x]<0)F[k][x]=-1;
			else F[k][x]=F[k-1][F[k-1][x]];
}
int lca(int x, int y){
	if(D[x]<D[y])swap(x,y);
	for(int k=K-1;k>=0;--k)if(D[x]-(1<<k)>=D[y])x=F[k][x];
	if(x==y)return x;
	for(int k=K-1;k>=0;--k)if(F[k][x]!=F[k][y])x=F[k][x],y=F[k][y];
	return F[0][x];
}

int main(){
	while(scanf("%d",&n),n){
		for (int i = 1, _n = n; i < _n; ++i){
			int j,l;
			scanf("%d%d",&j,&l);
			g[i].push_back({j,l});
			g[j].push_back({i,l});
		}
		lca_init();
		int q;
		scanf("%d",&q);
		bool p=false;
		while(q--){
			int x,y;
			scanf("%d%d",&x,&y);
			if(p)putchar(' ');
			p=true;
			printf("%lld",S[x]+S[y]-2*S[lca(x,y)]);
		}
		puts("");
		for (int i = 0, _n = n; i < _n; ++i)g[i].clear();
	}
	return 0;
}
