vector<vector<ll>> mult_mm(vector<vector<ll>>&A,vector<vector<ll>>&B){
	int n = A.size(), m = A[0].size(), p = B[0].size();
	vector<vector<ll>> ans(n, vector<ll>(p, 0));
	for( int i=0; i<n; i++ ){
		for( int j=0; j<m; j++ ){
			for( int k=0; k<p; k++ ){
				ans[i][k]+=A[i][j]*B[j][k];
				ans%=mod;
			}
		}
	}
	return ans;
}