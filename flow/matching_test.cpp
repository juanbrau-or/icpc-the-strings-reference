// UVA 1184 - AC
// https://uva.onlinejudge.org/index.php?option=onlinejudge&Itemid=99999999&category=246&page=show_problem&problem=3625
#include <bits/stdc++.h>
#define SZ(x) int((x).size())
using namespace std;
typedef long long ll;

#define MAXN 128
#define MAXM 128

vector<int> g[MAXN]; // [0,n)->[0,m)
int n,m;
int mat[MAXM];bool vis[MAXN];
int match(int x){
	if(vis[x])return 0;
	vis[x]=true;
	for(int y:g[x])if(mat[y]<0||match(mat[y])){mat[y]=x;return 1;}
	return 0;
}
vector<pair<int,int> > max_matching(){
	vector<pair<int,int> > r;
	memset(mat,-1,sizeof(mat));
	for (int i = 0; i < n; ++i)memset(vis,false,sizeof(vis)),match(i);
	for (int i = 0; i < m; ++i)if(mat[i]>=0)r.push_back({mat[i],i});
	return r;
}

int main(){
	int tn;
	scanf("%d",&tn);
	while(tn--){
		int e;
		scanf("%d%d",&n,&e);m=n;
		while(e--){
			int x,y;
			scanf("%d%d",&x,&y);x--;y--;
			g[x].push_back(y);
		}
		printf("%d\n",n-SZ(max_matching()));
		for (int i = 0; i < n; ++i)g[i].clear();
	}
	return 0;
}
