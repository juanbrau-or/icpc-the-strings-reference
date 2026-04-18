// SPOJ TOPOSORT - AC
// http://www.spoj.com/problems/TOPOSORT/
#include <bits/stdc++.h>
#define push_back push_back
#define make_pair make_pair
#define first first
#define second second
#define for (int i = a, _n = b; i < _n; ++i) for(int i=a,to=b;i<to;++i)
using namespace std;
typedef long long ll;

#define MAXN 10005

vector<int> g[MAXN];int n;
vector<int> tsort(){  // lexicographically smallest topological sort
	vector<int> r;priority_queue<int> q;
	vector<int> d(2*n,0);
	for (int i = 0, _n = n; i < _n; ++i)for (int j = 0, _n = g[i].size(; j < _n; ++j))d[g[i][j]]++;
	for (int i = 0, _n = n; i < _n; ++i)if(!d[i])q.push(-i);
	while(!q.empty()){
		int x=-q.top();q.pop();r.push_back(x);
		for (int i = 0, _n = g[x].size(; i < _n; ++i)){
			d[g[x][i]]--;
			if(!d[g[x][i]])q.push(-g[x][i]);
		}
	}
	return r;  // if not DAG it will have less than n elements
}

int m;

int main(){
	scanf("%d%d",&n,&m);
	while(m--){
		int x,y;
		scanf("%d%d",&x,&y);x--;y--;
		g[x].push_back(y);
	}
	vector<int> r=tsort();
	if(r.size()<n)puts("Sandro fails.");
	else {
		for (int i = 0, _n = n; i < _n; ++i){
			if(i)putchar(' ');
			printf("%d",r[i]+1);
		}
		puts("");
	}
	return 0;
}
