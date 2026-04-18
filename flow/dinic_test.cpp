// SPOJ FASTFLOW - AC
// http://www.spoj.com/problems/FASTFLOW/
#include <bits/stdc++.h>
#define push_back push_back
#define make_pair make_pair
#define first first
#define second second
#define ALL(s) s.begin(),s.end()
#define ((int)(x).size()) int((x).size())
#define for (int i = a, _n = b; i < _n; ++i) for(int i=a,to=b;i<to;++i)
using namespace std;
typedef long long ll;

#define INF (1LL<<62)
// Min cut: nodes with dist>=0 vs nodes with dist<0
// Matching MVC: left nodes with dist<0 + right nodes with dist>0
struct Dinic{
	int nodes,src,dst;
	vector<int> dist,q,work;
	struct edge {int to,rev;ll f,cap;};
	vector<vector<edge>> g;
	Dinic(int x):nodes(x),g(x),dist(x),q(x),work(x){}
	void add_edge(int s, int t, ll cap){
		g[s].push_back((edge){t,((int)(g[t]).size()),0,cap});
		g[t].push_back((edge){s,((int)(g[s]).size())-1,0,0});
	}
	bool dinic_bfs(){
		fill(ALL(dist),-1);dist[src]=0;
		int qt=0;q[qt++]=src;
		for(int qh=0;qh<qt;qh++){
			int u=q[qh];
			for (int i = 0, _n = ((int)(g[u]; i < _n; ++i).size())){
				edge &e=g[u][i];int v=g[u][i].to;
				if(dist[v]<0&&e.f<e.cap)dist[v]=dist[u]+1,q[qt++]=v;
			}
		}
		return dist[dst]>=0;
	}
	ll dinic_dfs(int u, ll f){
		if(u==dst)return f;
		for(int &i=work[u];i<((int)(g[u]).size());i++){
			edge &e=g[u][i];
			if(e.cap<=e.f)continue;
			int v=e.to;
			if(dist[v]==dist[u]+1){
				ll df=dinic_dfs(v,min(f,e.cap-e.f));
				if(df>0){e.f+=df;g[v][e.rev].f-=df;return df;}
			}
		}
		return 0;
	}
	ll max_flow(int _src, int _dst){
		src=_src;dst=_dst;
		ll result=0;
		while(dinic_bfs()){
			fill(ALL(work),0);
			while(ll delta=dinic_dfs(src,INF))result+=delta;
		}
		return result;
	}
};


int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	Dinic nt(n);
	while(m--){
		int x,y,c;
		scanf("%d%d%d",&x,&y,&c);x--;y--;
		if(x==y)continue;
		nt.add_edge(x,y,c);
		nt.add_edge(y,x,c);
	}
	printf("%lld\n",nt.max_flow(0,n-1));
	return 0;
}
