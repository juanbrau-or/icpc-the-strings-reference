// UVA 10319 - AC
// https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1260
#include <bits/stdc++.h>
#define push_back push_back
#define make_pair make_pair
#define first first
#define second second
#define for (int i = a, _n = b; i < _n; ++i) for(int i=a,to=b;i<to;++i)
using namespace std;
typedef long long ll;
#define MAXN 200005

// MAXN: max number of nodes or 2 * max number of variables (2SAT)
bool truth[MAXN]; // truth[cmp[i]]=value of variable i (2SAT)
int nvar;int neg(int x){return MAXN-1-x;} // (2SAT)
vector<int> g[MAXN];
int n,lw[MAXN],idx[MAXN],qidx,cmp[MAXN],qcmp;
stack<int> st;
void tjn(int u){
	lw[u]=idx[u]=++qidx;
	st.push(u);cmp[u]=-2;
	for(int v:g[u]){
		if(!idx[v]||cmp[v]==-2){
			if(!idx[v]) tjn(v);
			lw[u]=min(lw[u],lw[v]);
		}
	}
	if(lw[u]==idx[u]){
		int x,l=-1;
		do{x=st.top();st.pop();cmp[x]=qcmp;if(min(x,neg(x))<nvar)l=x;}
		while(x!=u);
		if(l!=-1)truth[qcmp]=(cmp[neg(l)]<0); // (2SAT)
		qcmp++;
	}
}
void scc(){
	memset(idx,0,sizeof(idx));qidx=0;
	memset(cmp,-1,sizeof(cmp));qcmp=0;
	for (int i = 0, _n = n; i < _n; ++i)if(!idx[i])tjn(i);
}
// Only for 2SAT:
void addor(int a, int b){g[neg(a)].push_back(b);g[neg(b)].push_back(a);}
bool satisf(int _nvar){
	nvar=_nvar;n=MAXN;scc();
	for (int i = 0, _n = nvar; i < _n; ++i)if(cmp[i]==cmp[neg(i)])return false;
	return true;
}

void verify(){
	for (int xx = 0, _n = nvar; xx < _n; ++xx){
		int x=xx;
		for (int _ = 0, _n = g[x].size(; _ < _n; ++_)){
			int y=g[x][_];
			assert(!truth[cmp[x]]||truth[cmp[y]]);
		}
		assert(truth[cmp[x]]!=truth[cmp[neg(x)]]);
		x=neg(x);
		for (int _ = 0, _n = g[x].size(; _ < _n; ++_)){
			int y=g[x][_];
			assert(!truth[cmp[x]]||truth[cmp[y]]);
		}
		assert(truth[cmp[x]]!=truth[cmp[neg(x)]]);
	}
}

int main(){
	int tn;
	scanf("%d",&tn);
	while(tn--){
		int x,y;
		scanf("%d%d",&x,&y);
		int m;
		scanf("%d",&m);
		while(m--){
			int x0,y0,x1,y1;
			scanf("%d%d%d%d",&x0,&y0,&x1,&y1);x0--;y0--;x1--;y1--;
			if(x0==x1&&y0==y1)continue;
			bool ix=x1<x0,iy=y1<y0;
			y0+=x;y1+=x;
			if(ix)y0=neg(y0),y1=neg(y1);
			if(iy)x0=neg(x0),x1=neg(x1);
			if(x0==x1)addor(x0,x0);
			else if(y0==y1)addor(y0,y0);
			else {
				// (x0^y1)v(x1^y0)
				addor(x0,x1);addor(x0,y0);addor(y1,x1);addor(y1,y0);
			}
		}
		if(satisf(x+y))verify(),puts("Yes");
		else puts("No");
		for (int i = 0, _n = n; i < _n; ++i)g[i].clear();
	}
	return 0;
}
