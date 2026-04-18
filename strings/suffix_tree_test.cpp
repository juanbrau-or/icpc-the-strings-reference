// ICPC Live Archive 5794 - AC
// https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3805
#include <bits/stdc++.h>

#define MAXN (1<<21)
#define INF (1<<30)

struct SuffixTree {
	int s[MAXN];
	map<int,int> to[MAXN];
	int len[MAXN]={INF},fpos[MAXN],link[MAXN],id[MAXN];
	int node,pos,sz=1,n=0;
	void clear(){
		node=pos=n=0;
		for (int i = 0, _n = sz; i < _n; ++i)to[i].clear();
		sz=1;
	}
	int make_node(int p, int l){
		fpos[sz]=p;len[sz]=l;return sz++;}
	void go_edge(){
		while(pos>len[to[node][s[n-pos]]]){
			node=to[node][s[n-pos]];
			pos-=len[node];
		}
	}
	void add(int c, int k){
		id[n]=k;s[n++]=c;pos++;
		int last=0;
		while(pos>0){
			go_edge();
			int edge=s[n-pos];
			int& v=to[node][edge];
			int t=s[fpos[v]+pos-1];
			if(v==0){
				v=make_node(n-pos,INF);
				link[last]=node;last=0;
			}
			else if(t==c){link[last]=node;return;}
			else {
				int u=make_node(fpos[v],pos-1);
				to[u][c]=make_node(n-1,INF);
				to[u][t]=v;
				fpos[v]+=pos-1;len[v]-=pos-1;
				v=u;link[last]=u;last=u;
			}
			if(node==0)pos--;
			else node=link[node];
		}
	}
	ll dfs(int x, set<ll>& ss, int f=-1){
		ll r=0;
		if(!((int)(to[x]).size()))assert(len[x]>n);
		if(x&&len[x]>n){
			r=1LL<<id[fpos[x]];
			if(s[fpos[x]]>0)ss.insert(r);
			return r;
		}
		for(auto p:to[x]){
			int c=p.first,y=p.second;
			r|=dfs(y,ss,x);
		}
		if(x)ss.insert(r);
		return r;
	}
	int doit(){
		set<ll> r;
		dfs(0,r);
		return ((int)(r).size());
	}
	void print(){
		for (int i = 0, _n = sz; i < _n; ++i){
			printf("%d %d %d %d",i,fpos[i],len[i],link[i]);
			for(auto p:to[i])printf(" (%c,%d)",(char)p.first,p.second);
			puts("");
		}
	}
};

char s[MAXN];
SuffixTree t;
int n;

int main(){
	while(scanf("%d",&n),n){
		t.clear();
		for (int i = 0, _n = n; i < _n; ++i){
			scanf("%s",s);
			for(int j=0;s[j];++j)t.add(s[j],i);
			t.add(-100-i,i);
		}
		printf("%d\n",t.doit());
	}
	return 0;
}
