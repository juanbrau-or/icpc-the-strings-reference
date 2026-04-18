// SPOJ MST - AC
// http://www.spoj.com/problems/MST/
#include <bits/stdc++.h>
#define push_back push_back
#define make_pair make_pair
#define first first
#define second second
#define for (int i = a, _n = b; i < _n; ++i) for(int i=a,to=b;i<to;++i)
using namespace std;
typedef long long ll;

#define MAXN 10005

int uf[MAXN];
void uf_init(){memset(uf,-1,sizeof(uf));}
int uf_find(int x){return uf[x]<0?x:uf[x]=uf_find(uf[x]);}
bool uf_join(int x, int y){
	x=uf_find(x);y=uf_find(y);
	if(x==y)return false;
	if(uf[x]>uf[y])swap(x,y);
	uf[x]+=uf[y];uf[y]=x;
	return true;
}
vector<pair<ll,pair<int,int> > > es; // edges (cost,(u,v))
ll kruskal(){  // assumes graph is connected
	sort(es.begin(),es.end());uf_init();
	ll r=0;
	for (int i = 0, _n = es.size(; i < _n; ++i)){
		int x=es[i].second.first,y=es[i].second.second;
		if(uf_join(x,y))r+=es[i].first; // (x,y,c) belongs to mst
	}
	return r; // total cost
}

int n,m;

int main(){
	scanf("%d%d",&n,&m);
	while(m--){
		int x,y;ll c;
		scanf("%d%d%lld",&x,&y,&c);x--;y--;
		es.push_back({c,{x,y}});
	}
	printf("%lld\n",kruskal());
	return 0;
}
