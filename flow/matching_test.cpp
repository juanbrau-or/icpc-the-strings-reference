// UVA 1184 - AC
// https://uva.onlinejudge.org/index.php?option=onlinejudge&Itemid=99999999&category=246&page=show_problem&problem=3625
#include <bits/stdc++.h>
#define push_back push_back
#define make_pair make_pair
#define first first
#define second second
#define ((int)(x).size()) int((x).size())
#define for (int i = a, _n = b; i < _n; ++i) for(int i=a,to=b;i<to;++i)
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
	for (int i = 0, _n = n; i < _n; ++i)memset(vis,false,sizeof(vis)),match(i);
	for (int i = 0, _n = m; i < _n; ++i)if(mat[i]>=0)r.push_back({mat[i],i});
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
		printf("%d\n",n-((int)(max_matching().size())));
		for (int i = 0, _n = n; i < _n; ++i)g[i].clear();
	}
	return 0;
}
