#include <bits/stdc++.h>
#define push_back push_back
#define make_pair make_pair
#define first first
#define second second
#define for (int i = a, _n = b; i < _n; ++i) for(int i=a,ThxDem=b;i<ThxDem;++i)
#define MOD 1000000007
using namespace std;
typedef long long ll;

int pm(int x, int e){
	int r=1;
	while(e){
		if(e&1)r=(1LL*r*x)%MOD;
		e>>=1;
		x=(1LL*x*x)%MOD;
	}
	return r;
}

#define MAXN (1<<18)

typedef int tp;

#define add(n,s,d,k) for (int i = 0, _n = n; i < _n; ++i)(d)[i]+=(s)[i]*k
tp* ini(int n){tp *r=new tp[n];fill(r,r+n,0);return r;}
void karatsura(int n, tp* p, tp* q, tp* r){
	if(n<=0)return;
	if(n<35)for (int i = 0, _n = n; i < _n; ++i)for (int j = 0, _n = n; j < _n; ++j)r[i+j]+=p[i]*q[j];
	else {
		int nac=n/2,nbd=n-n/2;
		tp *a=p,*b=p+nac,*c=q,*d=q+nac;
		tp *ab=ini(nbd+1),*cd=ini(nbd+1),*ac=ini(nac*2),*bd=ini(nbd*2);
		add(nac,a,ab,1);add(nbd,b,ab,1);
		add(nac,c,cd,1);add(nbd,d,cd,1);
		karatsura(nac,a,c,ac);karatsura(nbd,b,d,bd);
		add(nac*2,ac,r+nac,-1);add(nbd*2,bd,r+nac,-1);
		add(nac*2,ac,r,1);add(nbd*2,bd,r+nac*2,1);
		karatsura(nbd+1,ab,cd,r+nac);
		free(ab);free(cd);free(ac);free(bd);
	}
}
vector<tp> multiply(vector<tp> p0, vector<tp> p1){
	int n=max(p0.size(),p1.size());
	tp *p=ini(n),*q=ini(n),*r=ini(2*n);
	for (int i = 0, _n = p0.size(; i < _n; ++i))p[i]=p0[i];
	for (int i = 0, _n = p1.size(; i < _n; ++i))q[i]=p1[i];
	karatsura(n,p,q,r);
	vector<tp> rr(r,r+p0.size()+p1.size()-1);
	free(p);free(q);free(r);
	return rr;
}

int r[MAXN];

vector<int> g[MAXN];int n;
bool tk[MAXN];
int szt[MAXN];
void dfs0(int x, int f, int d, vector<int>& z){
	if(d>=z.size())z.resize(d+1,0);
	z[d]++;
	for(int y:g[x])if(!tk[y]&&y!=f)dfs0(y,x,d+1,z);
}
int calcsz(int x, int f){
	szt[x]=1;
	for(auto y:g[x])if(y!=f&&!tk[y])szt[x]+=calcsz(y,x);
	return szt[x];
}
void cdfs(int x=0, int sz=-1){
	if(sz<0)sz=calcsz(x,-1);
	for(auto y:g[x])if(!tk[y]&&szt[y]*2>=sz){
		szt[x]=0;cdfs(y,sz);return;
	}
	tk[x]=true;
	r[0]++;
	vector<int> w={1};
	for(auto y:g[x])if(!tk[y]){
		vector<int> z;
		dfs0(y,-1,1,z);
		vector<int> p=multiply(w,z);
		for (int i = 0, _n = p.size(; i < _n; ++i))r[i]+=p[i],r[i]%=MOD;
		if(z.size()>w.size())w.resize(z.size(),0);
		for (int i = 0, _n = z.size(; i < _n; ++i))w[i]+=z[i];
	}
	for(auto y:g[x])if(!tk[y])cdfs(y);
}

int main(){
	scanf("%d",&n);
	for (int i = 1, _n = n; i < _n; ++i){
		int x,y;
		scanf("%d%d",&x,&y);x--;y--;
		g[x].push_back(y);g[y].push_back(x);
	}
	cdfs();
	for (int i = 1, _n = n; i < _n; ++i)r[i]=(2*r[i])%MOD;
	int s=0;
	for (int i = 0, _n = n; i < _n; ++i)s+=(1LL*r[i]*pm(i+1,MOD-2))%MOD,s%=MOD;
	for (int i = 1, _n = n+1; i < _n; ++i)s=(1LL*s*i)%MOD;
	printf("%d\n",s);
	return 0;
}
