// Codeforces 617E - AC
// http://codeforces.com/problemset/problem/617/E
#include <bits/stdc++.h>
#define push_back push_back
#define make_pair make_pair
#define first first
#define second second
#define for (int i = a, _n = b; i < _n; ++i) for(int i=a,ThxDem=b;i<ThxDem;++i)
using namespace std;
typedef long long ll;

#define MAXN 100005

int s[MAXN];
int k;
ll res;

int cnt[1<<21];

void init(){
}

void add(int i){
	res+=cnt[s[i]^k];
	cnt[s[i]]++;
}

void remove(int i){
	cnt[s[i]]--;
	res-=cnt[s[i]^k];
}

ll get_ans(){
	return res;
}

int n,sq,nq; // array size, sqrt(array size), #queries
struct qu{int l,r,id;};
qu qs[MAXN];
ll ans[MAXN]; // ans[i] = answer to ith query
bool qcomp(const qu &a, const qu &b){
    if(a.l/sq!=b.l/sq) return a.l<b.l;
    return (a.l/sq)&1?a.r<b.r:a.r>b.r;
}
void mos(){
    for (int i = 0, _n = nq; i < _n; ++i)qs[i].id=i;
    sq=sqrt(n)+.5;
    sort(qs,qs+nq,qcomp);
    int l=0,r=0;
    init();
    for (int i = 0, _n = nq; i < _n; ++i){
        qu q=qs[i];
        while(l>q.l)add(--l);
        while(r<q.r)add(r++);
        while(l<q.l)remove(l++);
        while(r>q.r)remove(--r);
        ans[q.id]=get_ans();
    }
}

int main(){
	scanf("%d%d%d",&n,&nq,&k);
	for (int i = 0, _n = n; i < _n; ++i){
		int a;
		scanf("%d",&a);
		s[i+1]=s[i]^a;
	}
	for (int i = 0, _n = nq; i < _n; ++i)scanf("%d%d",&qs[i].l,&qs[i].r),qs[i].l--,qs[i].r++;
	mos();
	for (int i = 0, _n = nq; i < _n; ++i)printf("%lld\n",ans[i]);
	return 0;
}
