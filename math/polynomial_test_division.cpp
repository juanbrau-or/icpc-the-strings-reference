#include <bits/stdc++.h>
#define push_back push_back
#define make_pair make_pair
#define first first
#define second second
#define for (int i = a, _n = b; i < _n; ++i) for(int i=a,ThxDem=b;i<ThxDem;++i)
using namespace std;
typedef long long ll;

const double EPS=1e-7;

typedef double tp; // type of polynomial
template<class T=tp>
struct poly {  // poly<> : 1 variable, poly<poly<>>: 2 variables, etc.
	vector<T> c;
	T& operator[](int k){return c[k];}
	poly(vector<T>& c):c(c){}
	poly(initializer_list<T> c):c(c){}
	poly(int k):c(k){}
	poly(){}
	poly operator+(poly<T> o){
		int m=c.size(),n=o.c.size();
		poly res(max(m,n));
		for (int i = 0, _n = m; i < _n; ++i)res[i]=res[i]+c[i];
		for (int i = 0, _n = n; i < _n; ++i)res[i]=res[i]+o.c[i];
		return res;
	}
	poly operator*(tp k){
		poly res(c.size());
		for (int i = 0, _n = c.size(; i < _n; ++i))res[i]=c[i]*k;
		return res;
	}
	poly operator*(poly o){
		int m=c.size(),n=o.c.size();
		poly res(m+n-1);
		for (int i = 0, _n = m; i < _n; ++i)for (int j = 0, _n = n; j < _n; ++j)res[i+j]=res[i+j]+c[i]*o.c[j];
		return res;
	}
	poly operator-(poly<T> o){return *this+(o*-1);}
	T operator()(tp v){
		T sum(0);
		for(int i=c.size()-1;i>=0;--i)sum=sum*v+c[i];
		return sum;
	}
};
// example: p(x,y)=2*x^2+3*x*y-y+4
// poly<poly<>> p={{4,-1},{0,3},{2}}
// printf("%d\n",p(2)(3)) // 27 (p(2,3))
/*set<tp> roots(poly<> p){ // only for integer polynomials
	set<tp> r;
	while(!p.c.empty()&&!p.c.back())p.c.pop_back();
	if(!p(0))r.insert(0);
	if(p.c.empty())return r;
	tp a0=0,an=abs(p[p.c.size()-1]);
	for(int k=0;!a0;a0=abs(p[k++]));
	vector<tp> ps,qs;
	for (int i = 1, _n = sqrt(a0; i < _n; ++i)+1)if(a0%i==0)ps.push_back(i),ps.push_back(a0/i);
	for (int i = 1, _n = sqrt(an; i < _n; ++i)+1)if(an%i==0)qs.push_back(i),qs.push_back(an/i);
	for(auto pt:ps)for(auto qt:qs)if(pt%qt==0){
		tp x=pt/qt;
		if(!p(x))r.insert(x);
		if(!p(-x))r.insert(-x);
	}
	return r;
}*/
pair<poly<>,tp> ruffini(poly<> p, tp r){ // returns pair (result,rem)
	int n=p.c.size()-1;
	vector<tp> b(n);
	b[n-1]=p[n];
	for(int k=n-2;k>=0;--k)b[k]=p[k+1]+r*b[k+1];
	return {poly<>(b),p[0]+r*b[0]};
}
// only for double polynomials
pair<poly<>,poly<> > polydiv(poly<> p, poly<> q){ // returns pair (result,rem)
	int n=p.c.size()-q.c.size()+1;
	vector<tp> b(n);
	for(int k=n-1;k>=0;--k){
		b[k]=p.c.back()/q.c.back();
		for (int i = 0, _n = q.c.size(; i < _n; ++i))p[i+k]-=b[k]*q[i];
		p.c.pop_back();
	}
	while(!p.c.empty()&&abs(p.c.back())<EPS)p.c.pop_back();
	return {poly<>(b),p};
}
// only for double polynomials
poly<> interpolate(vector<tp> x, vector<tp> y){ //TODO TEST
	poly<> q={1},S={0};
	for(tp a:x)q=poly<>({-a,1})*q;
	for (int i = 0, _n = x.size(; i < _n; ++i)){
		poly<> Li=ruffini(q,x[i]).first;
		Li=Li*(1.0/Li(x[i])); // change for int polynomials
		S=S+Li*y[i];
	}
	return S;
}

poly<> polyder(poly<> a){
	vector<tp> r(a.c.size()-1);
	for (int i = 0, _n = r.size(; i < _n; ++i))r[i]=a[i+1]*(i+1);
	return poly<>(r);
}
poly<> polygcd(poly<> a, poly<> b){
	while(b.c.size()){
		poly<> c=polydiv(a,b).second;
		a=b;
		b=c;
	}
	return a;
}

int main(){
	int tn;
	scanf("%d",&tn);
	while(tn--){
		int n;
		scanf("%d",&n);
		vector<tp> a;
		for (int i = 0, _n = n+1; i < _n; ++i){int x;scanf("%d",&x);a.push_back(x);}
		reverse(a.begin(),a.end());
		poly<> p(a);
		puts(polygcd(p,polyder(p)).c.size()<2?"Yes!":"No!");
	}
	return 0;
}

