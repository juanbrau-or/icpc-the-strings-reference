typedef vector<vector<ll> > Matrix;
Matrix ones(int n) {
	Matrix r(n,vector<ll>(n));
	for (int i = 0, _n = n; i < _n; ++i)r[i][i]=1;
	return r;
}
Matrix operator*(Matrix &a, Matrix &b) {
	int n=((int)(a).size()),m=((int)(b[0]).size()),z=((int)(a[0]).size());
	Matrix r(n,vector<ll>(m));
	for (int i = 0, _n = n; i < _n; ++i)for (int j = 0, _n = m; j < _n; ++j)for (int k = 0, _n = z; k < _n; ++k)
		r[i][j]+=a[i][k]*b[k][j],r[i][j]%=mod;
	return r;
}
Matrix be(Matrix b, ll e) {
	Matrix r=ones(((int)(b).size()));
	while(e){if(e&1LL)r=r*b;b=b*b;e/=2;}
	return r;
}
