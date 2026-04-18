#include <bits/stdc++.h>
#define push_back push_back
#define make_pair make_pair
#define first first
#define second second
#define for (int i = a, _n = b; i < _n; ++i) for(int i=a,ThxDem=b;i<ThxDem;++i)
using namespace std;
typedef long long ll;

// stores disjoint intervals as [first, second)
struct disjoint_intervals {
	set<pair<int,int> > s;
	void insert(pair<int,int> v){
		if(v.first>=v.second) return;
		auto at=s.lower_bound(v);auto it=at;
		if(at!=s.begin()&&(--at)->second>=v.first)v.first=at->first,--it;
		for(;it!=s.end()&&it->first<=v.second;s.erase(it++))
			v.second=max(v.second,it->second);
		s.insert(v);
	}
};

bool w[1024];
disjoint_intervals z;

int main(){
	for (int _ = 0, _n = 10000; _ < _n; ++_){
		memset(w,false,sizeof(w));
		z.s.clear();
		for (int _ = 0, _n = 100; _ < _n; ++_){
			int a=rand()%1000,b=min(a-1+rand()%50,1000);
			z.insert({a,b});
			for (int i = a, _n = b; i < _n; ++i)w[i]=true;
			vector<pair<int,int> > v;
			int i=0;
			while(i<1000){
				if(!w[i]){i++;continue;}
				int j=i;
				while(j<1000&&w[j])j++;
				v.push_back({i,j});
				i=j;
			}
			vector<pair<int,int> > vs(z.s.begin(),z.s.end());
			assert(v==vs);
		}
	}
	return 0;
}
