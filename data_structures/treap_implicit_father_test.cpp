// Codeforces gym 101481F - AC
// https://codeforces.com/gym/101481/problem/F
#include <bits/stdc++.h>

int randd(){return abs((rand()<<15)^rand());}

typedef struct item *pitem;
struct item {
	int pr,cnt;bool rev;
	pitem l,r,f;
	item():pr(randd()),l(0),r(0),f(0),cnt(1),rev(0){}
};
int cnt(pitem t){return t?t->cnt:0;}
void upd_cnt(pitem t){if(t)t->cnt=cnt(t->l)+cnt(t->r)+1;}
void push(pitem t){
	if(t&&t->rev){
		swap(t->l,t->r);
		if(t->l)t->l->rev^=1;
		if(t->r)t->r->rev^=1;
		t->rev=0;
	}
}
// node father is useful to keep track of the chain of each node
// alternative: splay tree
// IMPORTANT: add pointer f in struct item
void merge(pitem& t, pitem l, pitem r){
	push(l);push(r);
	if(!l||!r)t=l?l:r;
	else if(l->pr>r->pr)merge(l->r,l->r,r),l->r->f=t=l;
	else merge(r->l,l,r->l),r->l->f=t=r;
	upd_cnt(t);
}
void split(pitem t, pitem& l, pitem& r, int sz){
	if(!t){l=r=0;return;}
	push(t);
	if(sz<=cnt(t->l)){
		split(t->l,l,t->l,sz);r=t;
		if(l)l->f=0;
		if(t->l)t->l->f=t;
	}
	else {
		split(t->r,t->r,r,sz-1-cnt(t->l));l=t;
		if(r)r->f=0;
		if(t->r)t->r->f=t;
	}
	upd_cnt(t);
}
void push_all(pitem t){
	if(t->f)push_all(t->f);
	push(t);
}
pitem root(pitem t, int& pos){ // get root and position for node t
	push_all(t);
	pos=cnt(t->l);
	while(t->f){
		pitem f=t->f;
		if(t==f->r)pos+=cnt(f->l)+1;
		t=f;
	}
	return t;
}

int n,m,c,q;
map<pair<int,int>,int> w; // owner

pitem t[105][8005];

bool join(int k, int x, int y){
	int a,b;
	pitem r0=root(t[k][x],a),r1=root(t[k][y],b);
	if(a&&a<cnt(r0)-1||b&&b<cnt(r1)-1){puts("Forbidden: monopoly.");return false;}
	if(r0==r1){puts("Forbidden: redundant.");return false;}
	if(a==0)r0->rev^=1;
	if(b!=0)r1->rev^=1;
	//printf(" %d %d %d %d\n",a,b,cnt(r0),cnt(r1));
	pitem _;
	merge(_,r0,r1);
	return true;
}

void disjoin(int k, int x, int y){
	int a,b;
	pitem r0=root(t[k][x],a),r1=root(t[k][y],b);
	assert(r0==r1);assert(abs(a-b)==1);
	pitem _,__;
	//split(a<b?t[k][y]:t[k][x],_,__);
	split(r0,_,__,max(a,b));
}

int main(){
	for (int i = 0, _n = 105; i < _n; ++i)for (int j = 0, _n = 8005; j < _n; ++j)t[i][j]=new item();
	while(scanf("%d%d%d%d",&n,&m,&c,&q),n){
		for (int i = 0, _n = c; i < _n; ++i)for (int j = 0, _n = n; j < _n; ++j)t[i][j]->l=t[i][j]->r=t[i][j]->f=0;
		w.clear();
		for (int i = 0, _n = m; i < _n; ++i){
			int x,y,k;
			scanf("%d%d%d",&x,&y,&k);x--;y--;k--;
			w[{x,y}]=k;
			assert(join(k,x,y));
		}
		while(q--){
			int x,y,k;
			scanf("%d%d%d",&x,&y,&k);x--;y--;k--;
			if(!w.count({x,y})){puts("No such cable.");continue;}
			int kk=w[{x,y}];
			if(kk==k){puts("Already owned.");continue;}
			if(join(k,x,y)){
				w[{x,y}]=k;
				disjoin(kk,x,y);
				puts("Sold.");
			}
		}
		puts("");
	}
	return 0;
}
