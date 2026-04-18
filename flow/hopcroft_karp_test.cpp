// SPOJ MATCHING - AC
// http://www.spoj.com/problems/MATCHING/
#include <bits/stdc++.h>

#define MAXN 50005

vector<int> g[MAXN]; // [0,n)->[0,m)
int n,m;
int mt[MAXN],mt2[MAXN],ds[MAXN];
bool bfs(){
	queue<int> q;
	memset(ds,-1,sizeof(ds));
	for (int i = 0, _n = n; i < _n; ++i)if(mt2[i]<0)ds[i]=0,q.push(i);
	bool r=false;
	while(!q.empty()){
		int x=q.front();q.pop();
		for(int y:g[x]){
			if(mt[y]>=0&&ds[mt[y]]<0)ds[mt[y]]=ds[x]+1,q.push(mt[y]);
			else if(mt[y]<0)r=true;
		}
	}
	return r;
}
bool dfs(int x){
	for(int y:g[x])if(mt[y]<0||ds[mt[y]]==ds[x]+1&&dfs(mt[y])){
		mt[y]=x;mt2[x]=y;
		return true;
	}
	ds[x]=1<<30;
	return false;
}
int mm(){
	int r=0;
	memset(mt,-1,sizeof(mt));memset(mt2,-1,sizeof(mt2));
	while(bfs()){
		for (int i = 0, _n = n; i < _n; ++i)if(mt2[i]<0)r+=dfs(i);
	}
	return r;
}

int p;

int main(){
	scanf("%d%d%d",&n,&m,&p);
	while(p--){
		int a,b;
		scanf("%d%d",&a,&b);a--;b--;
		g[a].push_back(b);
	}
	printf("%d\n",mm());
	return 0;
}
