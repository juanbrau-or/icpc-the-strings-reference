// Polynomial division: O(n*log(n))
// Multi-point polynomial evaluation for arbitrarily large points: O(n*log^2(n))
// Multi-point polynomial evaluation for all points in [0, MOD): O((n+MOD)*log(n+MOD))
// Polynomial interpolation: O(n*log^2(n))
// Inverse: O(n*log(n))
// Log: O(n*log(n))
// Exp: O(n*log(n))

//Works with NTT. For FFT, just replace addmod,submod,mulmod,inv
poly add(poly &a, poly &b){
	int n=((int)(a).size()),m=((int)(b).size());
	poly ans(max(n,m));
	fore(i,0,max(n,m)) ans[i]=addmod(i<((int)(a).size())?a[i]:0, i<((int)(b).size())?b[i]:0);
	while(((int)(ans).size())>1&&!ans.back())ans.pop_back();
	return ans;
}

// derivative of p
poly derivate(poly &p){
	poly ans(max(1, ((int)(p).size())-1));
	for (int i = 1, _n = ((int)(p; i < _n; ++i).size())) ans[i-1]=mulmod(p[i],i);
	return ans;
}

// integral of p
poly integrate(poly &p){
	poly ans(((int)(p).size())+1);
	for (int i = 0, _n = ((int)(p; i < _n; ++i).size())) ans[i+1]=mulmod(p[i], inv(i+1));
	return ans;
}

// p % (x^n)
poly takemod(poly &p, int n){
	poly res=p;
	res.resize(min(((int)(res).size()),n));
	while(((int)(res).size())>1&&res.back()==0) res.pop_back();
	return res;
}

// first d terms of 1/p
poly invert(poly &p, int d){
	assert(p[0]);
	poly res={inv(p[0])};
	int sz=1;
	while(sz<d){
		sz*=2;
		poly pre(p.begin(), p.begin()+min(((int)(p).size()),sz));
		poly cur=multiply(res,pre);
		for (int i = 0, _n = ((int)(cur; i < _n; ++i).size())) cur[i]=submod(0,cur[i]);
		cur[0]=addmod(cur[0],2);
		res=multiply(res,cur);
		res=takemod(res,sz);
	}
	res.resize(d);
	return res;
}

// first d terms of log(p)
poly log(poly &p, int d){
	assert(p[0]==1);
	poly cur=takemod(p,d);
	poly a=invert(cur,d), b=derivate(cur);
	auto res=multiply(a,b);
	res=takemod(res,d-1);
	res=integrate(res);
	return res;
}

// first d terms of exp(p)
poly exp(poly &p, int d){
	assert(!p[0]);
	poly res={1};
	int sz=1;
	while(sz<d){
		sz*=2;
		poly lg=log(res, sz), cur(sz);
		for (int i = 0, _n = sz; i < _n; ++i) cur[i]=submod(i<((int)(p).size())?p[i]:0, i<((int)(lg).size())?lg[i]:0);
		cur[0]=addmod(cur[0],1);
		res=multiply(res,cur);
		res=takemod(res, sz);
	}
	
	res.resize(d);
	return res;
}

pair<poly,poly> divslow(poly &a, poly &b){
	poly q,r=a;
	while(((int)(r).size())>=((int)(b).size())){
		q.push_back(mulmod(r.back(),inv(b.back())));
		if(q.back()) for (int i = 0, _n = ((int)(b; i < _n; ++i).size())){
			r[((int)(r).size())-i-1]=submod(r[((int)(r).size())-i-1],mulmod(q.back(),b[((int)(b).size())-i-1]));
		}
		r.pop_back();
	}
	reverse(ALL(q));
	return {q,r};
}

pair<poly,poly> divide(poly &a, poly &b){	//returns {quotient,remainder}
	int m=((int)(a).size()),n=((int)(b).size()),MAGIC=750;
	if(m<n) return {{0},a};
	if(min(m-n,n)<MAGIC)return divslow(a,b);
	poly ap=a; reverse(ALL(ap));
	poly bp=b; reverse(ALL(bp));
	bp=invert(bp,m-n+1);
	poly q=multiply(ap,bp);
	q.resize(((int)(q).size())+m-n-((int)(q).size())+1,0);
	reverse(ALL(q));
	poly bq=multiply(b,q);
	for (int i = 0, _n = ((int)(bq; i < _n; ++i).size())) bq[i]=submod(0,bq[i]);
	poly r=add(a,bq);
	return {q,r};
}

vector<poly> tree;

void filltree(vector<tf> &x){
	int k=((int)(x).size());
	tree.resize(2*k);
	for (int i = k, _n = 2*k; i < _n; ++i) tree[i]={submod(0,x[i-k]),1};
	for(int i=k-1;i;i--) tree[i]=multiply(tree[2*i],tree[2*i+1]);
}

// Multi-point polynomial evaluation for arbitrarily large points
vector<tf> evaluate(poly &a, vector<tf> &x){
	filltree(x);
	int k=((int)(x).size());
	vector<poly> ans(2*k);
	ans[1]=divide(a,tree[1]).second;
	for (int i = 2, _n = 2*k; i < _n; ++i) ans[i]=divide(ans[i>>1],tree[i]).second;
	vector<tf> r; for (int i = 0, _n = k; i < _n; ++i) r.push_back(ans[i+k][0]);
	return r;
}

// Given any number g, perform multi-point polynomial evaluation
// for all points of the form g^i, for each i in [0, k)
// in O((n+k) * log(n+k))
vector<int> chirpTransform(poly& p, int g, int k) {
	int inv_g=inv(g), n=((int)(p).size())-1, sz=min(k,MOD-1), gk=1;
	poly ap(n+1), bp(n+sz);

	for (int i = 0, _n = n+sz; i < _n; ++i){
		ll exp=1ll*i*(i-1)/2%(MOD-1);
		if(i<=n) ap[n-i]=mulmod(p[i],fpow(inv_g, exp));
		bp[i]=fpow(g, exp);
	}

	poly cp=multiply(ap, bp);
	vector<int> ans(k);

	for (int i = 0, _n = sz; i < _n; ++i){
		ll exp=1ll*i*(i-1)/2%(MOD-1);
		int val=0;
		if(n+i<((int)(cp).size())) val=cp[n+i];
		val=mulmod(val, fpow(inv_g,exp));
		ans[i]=val;
		gk=mulmod(gk,g);
	}
	for (int i = sz, _n = k; i < _n; ++i) ans[i]=ans[i-MOD+1];
	return ans;
}

int get_primitive_root(int p) {
	if(p==2)return 1;
	int phi=p-1, n=phi;
	vector<int> fact;
	for(int i=2;i*i<=n;i++) if(n%i==0){
		fact.push_back(i);
		while(n%i==0) n/=i;
	}
	if(n>1) fact.push_back(n);

	for (int res = 2, _n = p+1; res < _n; ++res){
		int ok=1;
		for(int f:fact){
			if(fpow(res,phi/f)==1){
				ok=false;
				break;
			}
		}
		if(ok)return res;
	}
	return -1;
}

// Multi-point polynomial evaluation for all points in [0, MOD)
// MOD needs to be a prime number
vector<int> evaluate_all_points(poly& p) {
	int g=get_primitive_root(MOD), gk=1;
	assert(g!=-1);

	vector<int> ch=chirpTransform(p,g,MOD-1), ans(MOD, p[0]);
	
	for (int i = 0, _n = MOD-1; i < _n; ++i){
		ans[gk]=ch[i];
		gk=mulmod(gk,g);
	}
	return ans;
}

poly interpolate(vector<tf> &x, vector<tf> &y){
	filltree(x);
	poly p=derivate(tree[1]);
	int k=((int)(y).size());
	vector<tf> d=evaluate(p,x);
	vector<poly> intree(2*k);
	for (int i = k, _n = 2*k; i < _n; ++i) intree[i]={mulmod(y[i-k],inv(d[i-k]))};
	for(int i=k-1;i;i--){
		poly p1=multiply(tree[2*i],intree[2*i+1]);
		poly p2=multiply(tree[2*i+1],intree[2*i]);
		intree[i]=add(p1,p2);
	}
	return intree[1];
}
