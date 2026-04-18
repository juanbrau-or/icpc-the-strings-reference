// SPOJ CERC07S - AC
// http://www.spoj.com/problems/CERC07S/
// (yet another example...)
#include <bits/stdc++.h>
#define push_back push_back
#define make_pair make_pair
#define first first
#define second second
#define for (int i = a, _n = b; i < _n; ++i) for(int i=a,ThxDem=b;i<ThxDem;++i)
using namespace std;
typedef long long ll;

typedef struct item *pitem;
struct item {
	int pr,cnt,val;
	int mn; // (paramters for range query)
	bool rev; // (parameters for lazy prop)
	pitem l,r;
	item(int val): pr(rand()),cnt(1),val(val),l(0),r(0),mn(val),rev(0) {}
};
void push(pitem it){
	if(it){
		if(it->rev){
			swap(it->l,it->r);
			if(it->l)it->l->rev^=true;
			if(it->r)it->r->rev^=true;
			it->rev=false;
		}
	}
}
int cnt(pitem it){return it?it->cnt:0;}
int mn(pitem it){return it?it->mn:1<<30;}
void upd_cnt(pitem it){
	if(it){
		it->cnt=cnt(it->l)+cnt(it->r)+1;
		it->mn=min(it->val,min(mn(it->l),mn(it->r)));
	}
}
void merge(pitem& t, pitem l, pitem r){
	push(l);push(r);
	if(!l||!r)t=l?l:r;
	else if(l->pr>r->pr)merge(l->r,l->r,r),t=l;
	else merge(r->l,l,r->l),t=r;
	upd_cnt(t);
}
void split(pitem t, pitem& l, pitem& r, int sz){ // sz:desired size of l
	if(!t){l=r=0;return;}
	push(t);
	if(sz<=cnt(t->l))split(t->l,l,t->l,sz),r=t;
	else split(t->r,t->r,r,sz-1-cnt(t->l)),l=t;
	upd_cnt(t);
}
void output(pitem t){ // useful for debugging
	if(!t)return;
	push(t);
	output(t->l);printf(" %d",t->val);output(t->r);
}
// use merge and split for range updates and queries

int find_min(pitem t){
	push(t);
	if(t->mn==t->val)return cnt(t->l);
	else if(t->l&&t->l->mn==t->mn)return find_min(t->l);
	else return cnt(t->l)+1+find_min(t->r);
}

pair<int,int> w[100005];
int x[100005];
int n;

int main(){
	while(scanf("%d",&n),n){
		for (int i = 0, _n = n; i < _n; ++i){
			int x;
			scanf("%d",&x);
			w[i]={x,i};
		}
		sort(w,w+n);
		for (int i = 0, _n = n; i < _n; ++i)x[w[i].second]=i;
		pitem t=0;
		for (int i = 0, _n = n; i < _n; ++i)merge(t,t,new item(x[i]));
		for (int i = 0, _n = n; i < _n; ++i){
			if(i)putchar(' ');
			int k=find_min(t);
			pitem t1,t2;
			split(t,t,t2,k+1);
			split(t,t,t1,k);
			if(t)t->rev^=true;
			merge(t,t,t2);
			printf("%d",i+k+1);
		}
		puts("");
	}
	return 0;
}
