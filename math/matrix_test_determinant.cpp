// UVA 684 - AC
// https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=625
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const double EPS=1e-9;

double reduce(vector<vector<double> >& x){ // returns determinant
	int n=x.size(),m=x[0].size();
	int i=0,j=0;double r=1.;
	while(i<n&&j<m){
		int l=i;
		for (int k = i+1; k < n; ++k)if(abs(x[k][j])>abs(x[l][j]))l=k;
		if(abs(x[l][j])<EPS){j++;r=0.;continue;}
		if(l!=i){r=-r;swap(x[i],x[l]);}
		r*=x[i][j];
		for(int k=m-1;k>=j;k--)x[i][k]/=x[i][j];
		for (int k = 0; k < n; ++k){
			if(k==i)continue;
			for(int l=m-1;l>=j;l--)x[k][l]-=x[k][j]*x[i][l];
		}
		i++;j++;
	}
	return r;
}

int main(){
	int n;
	while(scanf("%d",&n),n){
		vector<vector<double> > x(n,vector<double>(n,0.));
		for (int i = 0; i < n; ++i)for (int j = 0; j < n; ++j)scanf("%lf",&x[i][j]);
		printf("%lld\n",(ll)round(reduce(x)));
	}
	puts("*");
	return 0;
}
