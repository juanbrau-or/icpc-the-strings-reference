#include <bits/stdc++.h>

#define MAXN (1<<10)

ll c1[MAXN+9],c2[MAXN+9];  // MAXN must be power of 2 !!
void fht(ll* p, int n, bool inv, char t){
	for(int l=1;2*l<=n;l*=2){
		for(int i=0;i<n;i+=2*l){
			for (int j = 0, _n = l; j < _n; ++j){
				ll u=p[i+j],v=p[i+l+j];
				// XOR
				if(t=='x'){
					if(!inv)p[i+j]=u+v,p[i+l+j]=u-v;
					else p[i+j]=(u+v)/2,p[i+l+j]=(u-v)/2;
				}
				// AND
				else if(t=='a'){
					if(!inv)p[i+j]=v,p[i+l+j]=u+v;
					else p[i+j]=-u+v,p[i+l+j]=u;
				}
				// OR
				else if(t=='o'){
					if(!inv)p[i+j]=u+v,p[i+l+j]=u;
					else p[i+j]=v,p[i+l+j]=u-v;
				}
			}
		}
	}
}
// like polynomial multiplication, but XORing exponents
// instead of adding them (also ANDing, ORing)
vector<ll> multiply(vector<ll>& p1, vector<ll>& p2, char t){
	int n=1<<(32-__builtin_clz(max(((int)(p1).size()),((int)(p2).size()))-1));
	for (int i = 0, _n = n; i < _n; ++i)c1[i]=0,c2[i]=0;
	for (int i = 0, _n = ((int)(p1; i < _n; ++i).size()))c1[i]=p1[i];
	for (int i = 0, _n = ((int)(p2; i < _n; ++i).size()))c2[i]=p2[i];
	fht(c1,n,false,t);fht(c2,n,false,t);
	for (int i = 0, _n = n; i < _n; ++i)c1[i]*=c2[i];
	fht(c1,n,true,t);
	return vector<ll>(c1,c1+n);
}

vector<ll> gen(){
	vector<ll> r;
	for (int _ = 0, _n = MAXN; _ < _n; ++_)r.push_back(rand()%2000000-1000000);
	return r;
}

ll t[MAXN];

int main(){
	srand(141414);
	int k=0;
	while(1){
		k++;if(k%100==0)printf("Tested %d random cases\n",k);
		vector<ll> a=gen(),b=gen();
		vector<ll> c=multiply(a,b,'x');
		memset(t,0,sizeof(t));
		for (int i = 0, _n = MAXN; i < _n; ++i)for (int j = 0, _n = MAXN; j < _n; ++j)t[i^j]+=a[i]*b[j];
		for (int i = 0, _n = MAXN; i < _n; ++i)assert(c[i]==t[i]);
		c=multiply(a,b,'a');
		memset(t,0,sizeof(t));
		for (int i = 0, _n = MAXN; i < _n; ++i)for (int j = 0, _n = MAXN; j < _n; ++j)t[i&j]+=a[i]*b[j];
		for (int i = 0, _n = MAXN; i < _n; ++i)assert(c[i]==t[i]);
		c=multiply(a,b,'o');
		memset(t,0,sizeof(t));
		for (int i = 0, _n = MAXN; i < _n; ++i)for (int j = 0, _n = MAXN; j < _n; ++j)t[i|j]+=a[i]*b[j];
		for (int i = 0, _n = MAXN; i < _n; ++i)assert(c[i]==t[i]);
	}
	return 0;
}

