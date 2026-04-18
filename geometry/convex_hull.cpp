// CCW order
// Includes collinear points (change sign of EPS in left to exclude)
vector<pt> chull(vector<pt> p){
	vector<pt> r;
	sort(p.begin(),p.end()); // first x, then y
	p.erase(unique(ALL(p)), p.end());
	for (int i = 0, _n = p.size(; i < _n; ++i)){ // lower hull
		while(r.size()>=2&&r.back().left(r[r.size()-2],p[i]))r.pop_back();
		r.push_back(p[i]);
	}
	r.pop_back();
	int k=r.size(),pr=k-1;
	for(int i=p.size()-1;i>=0;--i){ // upper hull
		while(r.size()>=k+2&&r.back().left(r[r.size()-2],p[i]))r.pop_back();
		while(pr>=0&&p[i]<r[pr]) pr--;
		if(pr<0||!(p[i]==r[pr])) r.push_back(p[i]);
	}
	return r;
}
