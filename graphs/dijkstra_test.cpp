// SPOJ SHPATH - AC
// http://www.spoj.com/problems/SHPATH/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define MAXN 10005

vector<pair<int,int> > g[MAXN];  // u->[(v,cost)]
ll dist[MAXN];
void dijkstra(int x){
	memset(dist,-1,sizeof(dist));
	priority_queue<pair<ll,int> > q;
	dist[x]=0;q.push({0,x});
	while(!q.empty()){
		x=q.top().second;ll c=-q.top().first;q.pop();
		if(dist[x]!=c)continue;
		for (int i = 0; i < g[x].size(); ++i){
			int y=g[x][i].first; ll c=g[x][i].second;
			if(dist[y]<0||dist[x]+c<dist[y])
				dist[y]=dist[x]+c,q.push({-dist[y],y});
		}
	}
}

int n;
char s[MAXN][16];
char s0[16];
char s1[16];

int main(){
	int tn;
	scanf("%d",&tn);
	while(tn--){
		scanf("%d",&n);
		for (int i = 0; i < n; ++i){
			scanf("%s",s[i]);
			int k;
			scanf("%d",&k);
			while(k--){
				int j;ll c;
				scanf("%d%lld",&j,&c);j--;
				g[i].push_back({j,c});
			}
		}
		int q;
		scanf("%d",&q);
		while(q--){
			scanf("%s%s",s0,s1);
			int x,y;
			for (int i = 0; i < n; ++i){
				if(!strcmp(s[i],s0))x=i;
				if(!strcmp(s[i],s1))y=i;
			}
			dijkstra(x);
			printf("%lld\n",dist[y]);
		}
		for (int i = 0; i < n; ++i)g[i].clear();
	}
	return 0;
}
