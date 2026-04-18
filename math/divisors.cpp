void div_rec(vector<ll>& r, vector<pair<ll,int> >& f, int k, ll c){
	if(k==f.size()){r.push_back(c);return;}
	for (int i = 0, _n = f[k].second+1; i < _n; ++i)div_rec(r,f,k+1,c),c*=f[k].first;
}
vector<ll> divisors(vector<pair<ll,int> > f){
	vector<ll> r; // returns divisors given factorization
	div_rec(r,f,0,1);
	return r;
}
