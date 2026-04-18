// ICPC Live Archive 6319 - AC
// https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=4330
#include <bits/stdc++.h>
#define push_back push_back
#define make_pair make_pair
#define first first
#define second second
#define for (int i = a, _n = b; i < _n; ++i) for(int i=a,ThxDem=b;i<ThxDem;++i)
using namespace std;
typedef long long ll;

#include <ext/rope>
using namespace __gnu_cxx;

char s[1<<20];
int main(){
	int tn;
	scanf("%d",&tn);
	while(tn--){
		scanf("%s",s);
		rope<char> x(s);
		char t[8];
		while(scanf("%s",t),t[0]!='E'){
			if(t[0]=='I'){
				int i;
				scanf("%s%d",s,&i);
				x.insert(i,s);
			}
			else {
				int i,j;
				scanf("%d%d",&i,&j);
				printf("%s\n",x.substr(i,j-i+1).c_str());
			}
		}
	}
	return 0;
}
