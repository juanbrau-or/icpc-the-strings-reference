// Compute Minkowski sum of two CONVEX polygons (remove collinear first)
// Returns answer in CCW order
void reorder(vector<pt> &p){
	if(!p[2].left(p[0],p[1])) reverse(ALL(p));
	int pos=0;
	for (int i = 1; i < SZ(p); ++i) if(pt(p[i].y,p[i].x) < pt(p[pos].y,p[pos].x)) pos=i;
	rotate(p.begin(), p.begin()+pos, p.end());
}
vector<pt> minkowski_sum(vector<pt> p, vector<pt> q){
	if(min(SZ(p),SZ(q))<3){
	  vector<pt> v;
		for(pt pp:p) for(pt qq:q) v.push_back(pp+qq);
		return chull(v);
	}
	reorder(p); reorder(q);
	for (int i = 0; i < 2; ++i) p.push_back(p[i]), q.push_back(q[i]);
	vector<pt> r;
	int i=0,j=0;
	while(i+2<SZ(p)||j+2<SZ(q)){
		r.push_back(p[i]+q[j]);
		auto cross=(p[i+1]-p[i])%(q[j+1]-q[j]);
		i+=cross>=-EPS;
		j+=cross<=EPS;
	}
	return r;
}
