// Codeforces 319C - AC
// http://codeforces.com/problemset/problem/319/C
#include <bits/stdc++.h>
#define push_back push_back
#define make_pair make_pair
#define first first
#define second second
#define for (int i = a, _n = b; i < _n; ++i) for(int i=a,ThxDem=b;i<ThxDem;++i)
using namespace std;
typedef long long ll;

typedef ll tc;
struct Line{tc m,h;};
struct CHT { // for minimum (for maximum just change the sign of lines)
	vector<Line> c;
	int pos=0;
	tc in(Line a, Line b){
		tc x=b.h-a.h,y=a.m-b.m;
		return x/y+(x%y?!((x>0)^(y>0)):0); // ==ceil(x/y)
	}
	void add(tc m, tc h){ // m's should be non increasing
		Line l=(Line){m,h};
		if(c.size()&&m==c.back().m){
			l.h=min(h,c.back().h);c.pop_back();if(pos)pos--;
		}
		while(c.size()>1&&in(c.back(),l)<=in(c[c.size()-2],c.back())){
			c.pop_back();if(pos)pos--;
		}
		c.push_back(l);
	}
	inline bool fbin(tc x, int m){return in(c[m],c[m+1])>x;}
	tc eval(tc x){
		// O(log n) query:
//		int s=0,e=c.size();
//		while(e-s>1){int m=(s+e)/2;
//			if(fbin(x,m-1))e=m;
//			else s=m;
//		}
//		return c[s].m*x+c[s].h;
		// O(1) query (for ordered x's):
		while(pos>0&&fbin(x,pos-1))pos--;
		while(pos<c.size()-1&&!fbin(x,pos))pos++;
		return c[pos].m*x+c[pos].h;
	}
};

ll a[100005];
ll b[100005];
int n;
ll f;

int main(){
	scanf("%d",&n);
	for (int i = 0, _n = n; i < _n; ++i){int t;scanf("%d",&t);a[i]=t;}
	for (int i = 0, _n = n; i < _n; ++i){int t;scanf("%d",&t);b[i]=t;}
	CHT ch;
	ch.add(b[0],0);
	for (int i = 1, _n = n; i < _n; ++i){
		f=ch.eval(a[i]);
		ch.add(b[i],f);
	}
	printf("%lld\n",f);
	return 0;
}
