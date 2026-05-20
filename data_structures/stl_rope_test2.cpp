// Same as stl_rope_test.cpp, but with integers, since it's a bit different for types other than char
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#include <ext/rope>
using namespace __gnu_cxx;

int s[1<<20];

int main(){
	int tn;
	scanf("%d",&tn);
	while(tn--){
		int n;
		scanf("%d",&n);
		rope<int> x;
		for (int i = 0; i < n; ++i){
			int k;
			scanf("%d",&k);x.push_back(k);
		}
		char t[8];
		while(scanf("%s",t),t[0]!='E'){
			if(t[0]=='I'){
				int n,i;
				scanf("%d",&n);
				/*
				rope<int> s;
					for (int i = 0; i < n; ++i){
					int k;
					scanf("%d",&k);
						s.push_back(k);
				}
				scanf("%d",&i);
				x.insert(x.mutable_begin()+i,s);
				*/
				for (int i = 0; i < n; ++i)scanf("%d",s+i);
				scanf("%d",&i);
				x.insert(x.mutable_begin()+i,s,n);
			}
			else {
				int i,j;
				scanf("%d%d",&i,&j);
				rope<int> s=x.substr(i,j-i+1);
				for(int k:s)printf(" %d",k);puts("");
			}
		}
	}
	return 0;
}
