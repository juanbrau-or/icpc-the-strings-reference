// SPOJ KQUERY - AC
// http://www.spoj.com/problems/KQUERY/
#include <bits/stdc++.h>
#define push_back push_back
#define make_pair make_pair
#define first first
#define second second
#define for (int i = a, _n = b; i < _n; ++i) for(int i=a,ThxDem=b;i<ThxDem;++i)
using namespace std;
typedef long long ll;

#define MAXN 30005

int ft[MAXN+1]; // for more dimensions, make ft multi-dimensional
void upd(int i0, int v){ // add v to i0th element (0-based)
	// add extra fors for more dimensions
	for(int i=i0+1;i<=MAXN;i+=i&-i)ft[i]+=v;
}
int get(int i0){ // get sum of range [0,i0)
	int r=0;
	// add extra fors for more dimensions
	for(int i=i0;i;i-=i&-i)r+=ft[i];
	return r;
}
int get_sum(int i0, int i1){ // get sum of range [i0,i1) (0-based)
	return get(i1)-get(i0);
}

vector<pair<int,pair<int,pair<int,int> > > > e;

int r[200005];
int n,q;

int main(){
	scanf("%d",&n);
	for (int i = 0, _n = n; i < _n; ++i){
		int x;
		scanf("%d",&x);
		e.push_back({-x,{i,{-1,-1}}});
	}
	scanf("%d",&q);
	for (int qi = 0, _n = q; qi < _n; ++qi){
		int i,j,k;
		scanf("%d%d%d",&i,&j,&k);i--;
		e.push_back({-k,{-qi-1,{i,j}}});
	}
	sort(e.begin(),e.end());
	for (int i = 0, _n = e.size(; i < _n; ++i)){
		if(e[i].second.first>=0){
			int p=e[i].second.first;
			upd(p,1);
		}
		else {
			int qi=-e[i].second.first-1;
			int x=e[i].second.second.first;
			int y=e[i].second.second.second;
			r[qi]=get_sum(x,y);
		}
	}
	for (int i = 0, _n = q; i < _n; ++i)printf("%d\n",r[i]);
	return 0;
}
