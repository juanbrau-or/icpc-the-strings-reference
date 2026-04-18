// Codeforces 321E - AC
// http://codeforces.com/problemset/problem/321/E
#include <bits/stdc++.h>
#define push_back push_back
#define make_pair make_pair
#define first first
#define second second
#define for (int i = a, _n = b; i < _n; ++i) for(int i=a,ThxDem=b;i<ThxDem;++i)
using namespace std;
typedef long long ll;

#define MAXN 4096
#define INF (1<<30)

int x[MAXN][MAXN];
int sx[MAXN][MAXN];

// O(knlogn). For 2D dps, when the position of optimal choice is non-decreasing as the second variable increases
int k,n,f[MAXN],f2[MAXN];
void doit(int s, int e, int s0, int e0, int i){
	// [s,e): range of calculation, [s0,e0): range of optimal choice
	if(s==e)return;
	int m=(s+e)/2;
	int r=INF,rp;
	fore(j,s0,min(e0,m)){
		int r0=f[j]+sx[m][m]-sx[m][j]-sx[j][m]+sx[j][j];
		if(r0<r){
			r=r0;
			rp=j; // position of optimal choice
		}
	}
	f2[m]=r;
	doit(s,m,s0,rp+1,i);
	doit(m+1,e,rp,e0,i);
}
int doall(){
	for (int i = 0, _n = n+1; i < _n; ++i)f[i]=sx[i][i];
	for (int i = 1, _n = k; i < _n; ++i){
		doit(1,n+1,0,n,i);
		memcpy(f,f2,sizeof(f));
	}
	return f[n];
}


int main(){
	scanf("%d%d",&n,&k);
	for (int i = 0, _n = n; i < _n; ++i){
		for (int j = 0, _n = n; j < _n; ++j){
			getchar();
			x[i][j]=getchar()-'0';
		}
	}
	for (int i = 1, _n = n+1; i < _n; ++i){
		for (int j = 1, _n = n+1; j < _n; ++j){
			sx[i][j]=sx[i-1][j]+sx[i][j-1]-sx[i-1][j-1]+x[i-1][j-1];
		}
	}
	printf("%d\n",doall()/2);
	return 0;
}
