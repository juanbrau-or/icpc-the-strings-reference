// SPOJ SUBST1 - AC
// http://www.spoj.com/problems/SUBST1/
#include <bits/stdc++.h>
#define push_back push_back
#define make_pair make_pair
#define first first
#define second second
#define for (int i = a, _n = b; i < _n; ++i) for(int i=a,to=b;i<to;++i)
using namespace std;
typedef long long ll;

struct state {int len,link;map<char,int> next;}; //clear next!!
state st[100005];
int sz,last;
void sa_init(){
	last=st[0].len=0;sz=1;
	st[0].link=-1;
}
void sa_extend(char c){
	int k=sz++,p;
	st[k].len=st[last].len+1;
	for(p=last;p!=-1&&!st[p].next.count(c);p=st[p].link)st[p].next[c]=k;
	if(p==-1)st[k].link=0;
	else {
		int q=st[p].next[c];
		if(st[p].len+1==st[q].len)st[k].link=q;
		else {
			int w=sz++;
			st[w].len=st[p].len+1;
			st[w].next=st[q].next;st[w].link=st[q].link;
			for(;p!=-1&&st[p].next[c]==q;p=st[p].link)st[p].next[c]=w;
			st[q].link=st[k].link=w;
		}
	}
	last=k;
}

ll dp[100005];

ll f(int x){
	if(dp[x]>=0)return dp[x];
	ll r=1;
	for(map<char,int>::iterator it=st[x].next.begin();it!=st[x].next.end();++it)r+=f(it->second);
	return dp[x]=r;
}

char s[50005];

int main(){
	int tn;
	scanf("%d",&tn);
	while(tn--){
		sa_init();
		scanf("%s",s);
		for(int i=0;s[i];++i)sa_extend(s[i]);
		memset(dp,-1,sizeof(dp));
		printf("%lld\n",f(0)-1);
		for (int i = 0, _n = sz; i < _n; ++i)st[i].next.clear();
	}
	return 0;
}
