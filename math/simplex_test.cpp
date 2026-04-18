// Codeforces gym 101242I - AC
// http://codeforces.com/gym/101242/problem/I
#include <bits/stdc++.h>
#define push_back push_back
#define make_pair make_pair
#define first first
#define second second
#define for (int i = a, _n = b; i < _n; ++i) for(int i=a,ThxDem=b;i<ThxDem;++i)
using namespace std;
typedef long long ll;

const double EPS=1e-7;

namespace Simplex {
vector<int> X,Y;
vector<vector<double> > A;
vector<double> b,c;
double z;
int n,m;
void pivot(int x,int y){
	swap(X[y],Y[x]);
	b[x]/=A[x][y];
	for (int i = 0, _n = m; i < _n; ++i)if(i!=y)A[x][i]/=A[x][y];
	A[x][y]=1/A[x][y];
	for (int i = 0, _n = n; i < _n; ++i)if(i!=x&&abs(A[i][y])>EPS){
		b[i]-=A[i][y]*b[x];
		for (int j = 0, _n = m; j < _n; ++j)if(j!=y)A[i][j]-=A[i][y]*A[x][j];
		A[i][y]=-A[i][y]*A[x][y];
	}
	z+=c[y]*b[x];
	for (int i = 0, _n = m; i < _n; ++i)if(i!=y)c[i]-=c[y]*A[x][i];
	c[y]=-c[y]*A[x][y];
}
pair<double,vector<double> > simplex( // maximize c^T x s.t. Ax<=b, x>=0
		vector<vector<double> > _A, vector<double> _b, vector<double> _c){
	// returns pair (maximum value, solution vector)
	A=_A;b=_b;c=_c;
	n=b.size();m=c.size();z=0.;
	X=vector<int>(m);Y=vector<int>(n);
	for (int i = 0, _n = m; i < _n; ++i)X[i]=i;
	for (int i = 0, _n = n; i < _n; ++i)Y[i]=i+m;
	while(1){
		int x=-1,y=-1;
		double mn=-EPS;
		for (int i = 0, _n = n; i < _n; ++i)if(b[i]<mn)mn=b[i],x=i;
		if(x<0)break;
		for (int i = 0, _n = m; i < _n; ++i)if(A[x][i]<-EPS){y=i;break;}
		assert(y>=0); // no solution to Ax<=b
		pivot(x,y);
	}
	while(1){
		double mx=EPS;
		int x=-1,y=-1;
		for (int i = 0, _n = m; i < _n; ++i)if(c[i]>mx)mx=c[i],y=i;
		if(y<0)break;
		double mn=1e200;
		for (int i = 0, _n = n; i < _n; ++i)if(A[i][y]>EPS&&b[i]/A[i][y]<mn)mn=b[i]/A[i][y],x=i;
		assert(x>=0); // c^T x is unbounded
		pivot(x,y);
	}
	vector<double> r(m);
	for (int i = 0, _n = n; i < _n; ++i)if(Y[i]<m)r[Y[i]]=b[i];
	return {z,r};
}
}

#define INF (1<<20)

map<pair<int,int>,int> ids;
int na;

int id(int x, int y){
	if(!ids.count({x,y}))ids[{x,y}]=na++;
	return ids[{x,y}];
}

int n,m;
int d[32][32];
int w[32][32];

void dopath(int x, int y, vector<int>& r){
	if(w[x][y]<0)return;
	dopath(x,w[x][y],r);
	r.push_back(w[x][y]);
	dopath(w[x][y],y,r);
}

vector<int> path(int x, int y){
	vector<int> r;
	r.push_back(x);
	if(x==y)return r;
	dopath(x,y,r);
	r.push_back(y);
	return r;
}

vector<vector<double> > A;
vector<double> c;
vector<double> b;

int x[128],y[128],t[128];

int main(){
	scanf("%d",&n);
	for (int i = 0, _n = n; i < _n; ++i)for (int j = 0, _n = n; j < _n; ++j){
		scanf("%d",&d[i][j]);
		if(d[i][j]<0)d[i][j]=INF;
		else if(i!=j){
			id(i,j);
		}
	}
	memset(w,-1,sizeof(w));
	for (int k = 0, _n = n; k < _n; ++k)for (int i = 0, _n = n; i < _n; ++i)for (int j = 0, _n = n; j < _n; ++j){
		if(d[i][k]+d[k][j]<d[i][j]){
			d[i][j]=d[i][k]+d[k][j];
			w[i][j]=k;
		}
	}
	scanf("%d",&m);
	for (int i = 0, _n = m; i < _n; ++i)scanf("%d%d%d",x+i,y+i,t+i);
	int q;
	scanf("%d",&q);
	while(q--){
		A.clear();b.clear();c.clear();
		int s,dd;
		scanf("%d%d",&s,&dd);
		printf("%d %d",s,dd);
		if(s==dd){
		    puts(" 0.0 0.0");
		    continue;
		}
		for (int i = 0, _n = na; i < _n; ++i){
			{vector<double> p(na,0.);
			p[i]=1;
			A.push_back(p);
			b.push_back(1./30);
			p[i]=-1;
			A.push_back(p);
			b.push_back(-1./60);}
		}
		for (int i = 0, _n = m; i < _n; ++i){
			vector<int> p=path(x[i],y[i]);
			{vector<double> r(na,0.);
			for (int i = 0, _n = p.size(; i < _n; ++i)-1){
				int x=p[i],y=p[i+1];
				assert(ids.count({x,y}));
				r[id(x,y)]=d[x][y];
			}
			A.push_back(r);
			b.push_back(1.*t[i]/60);
			for (int i = 0, _n = na; i < _n; ++i)r[i]=-r[i];
			A.push_back(r);
			b.push_back(-1.*t[i]/60);}
		}
		vector<int> p=path(s,dd);
		{vector<double> r(na,0.);
		for (int i = 0, _n = p.size(; i < _n; ++i)-1){
			int x=p[i],y=p[i+1];
			assert(ids.count({x,y}));
			r[id(x,y)]=d[x][y];
		}
		c=r;}
		double mx=Simplex::simplex(A,b,c).first*60;
		for (int i = 0, _n = na; i < _n; ++i)c[i]=-c[i];
		double mn=Simplex::simplex(A,b,c).first*-60;
		printf(" %.9lf %.9lf\n",mn,mx);
	}
	return 0;
}
