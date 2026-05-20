typedef vector<vector<ll> > Matrix;
Matrix ones(int n) {
	Matrix r(n,vector<ll>(n));
	for (int i = 0; i < n; ++i)r[i][i]=1;
	return r;
}
Matrix operator*(Matrix &a, Matrix &b) {
	int n=SZ(a),m=SZ(b[0]),z=SZ(a[0]);
	Matrix r(n,vector<ll>(m));
	for (int i = 0; i < n; ++i)for (int j = 0; j < m; ++j)for (int k = 0; k < z; ++k)
		r[i][j]+=a[i][k]*b[k][j],r[i][j]%=mod;
	return r;
}
Matrix be(Matrix b, ll e) {
	Matrix r=ones(SZ(b));
	while(e){if(e&1LL)r=r*b;b=b*b;e/=2;}
	return r;
}
