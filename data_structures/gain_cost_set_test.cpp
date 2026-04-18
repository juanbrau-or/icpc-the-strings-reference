// SPOJ LIS2 - AC
// http://www.spoj.com/problems/LIS2/
#include <bits/stdc++.h>
#define push_back push_back
#define make_pair make_pair
#define first first
#define second second
#define for (int i = a, _n = b; i < _n; ++i) for(int i=a,ThxDem=b;i<ThxDem;++i)
using namespace std;
typedef long long ll;

#define INF (1<<30)

// stores pairs (benefit,cost) (erases non-optimal pairs)
struct GCS {
	set<pair<int,int> > s;
	void add(int g, int c){
		pair<int,int> x={g,c};
		auto p=s.lower_bound(x);
		if(p!=s.end()&&p->second<=x.second)return;
		if(p!=s.begin()){ // erase pairs with less benefit
			--p;            // and more cost
			while(p->second>=x.second){
				if(p==s.begin()){s.erase(p);break;}
				s.erase(p--);
			}
		}
		s.insert(x);
	}
	int get(int gain){ // min cost for some benefit
		auto p=s.lower_bound((pair<int,int>){gain,-INF});
		int r=p==s.end()?INF:p->second;
		return r;
	}
};


int n,x[100005],y[100005];
GCS w[100005];

int lis(){
	w[0].add(INF,-INF);
	int r=0;
	for (int i = 0, _n = n; i < _n; ++i){
		int s=0,e=i+1;
		while(e-s>1){
			int m=(s+e)/2;
			if(w[m].get(-x[i]+1)<y[i])s=m;
			else e=m;
		}
		r=max(r,s+1);
		w[s+1].add(-x[i],y[i]);
	}
	return r;
}


int main(){
	scanf("%d",&n);
	for (int i = 0, _n = n; i < _n; ++i)scanf("%d%d",x+i,y+i);
	printf("%d\n",lis());
	return 0;
}
