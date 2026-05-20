#define RB(x) (x<n?r[x]:0)
void csort(vector<int>& sa, vector<int>& r, int k){
	int n=sa.size(),top=max(255,n+1);
	vector<int> f(top,0),t(n);
	for (int i = 0; i < n; ++i)f[RB(i+k)]++;
	int sum=0;
	for (int i = 0; i < top; ++i)f[i]=(sum+=f[i])-f[i];
	for (int i = 0; i < n; ++i)t[f[RB(sa[i]+k)]++]=sa[i];
	sa=t;
}
vector<int> constructSA(string& s){ // O(n logn)
	int n=s.size(),rank;
	vector<int> sa(n),r(n),t(n);
	for (int i = 0; i < n; ++i)sa[i]=i,r[i]=s[i];
	for(int k=1;k<n;k*=2){
		csort(sa,r,k);csort(sa,r,0);
		t[sa[0]]=rank=1;
		for (int i = 1; i < n; ++i){
			if(r[sa[i]]!=r[sa[i-1]]||RB(sa[i]+k)!=RB(sa[i-1]+k))rank++;
			t[sa[i]]=rank;
		}
		r=t;
		if(r[sa[n-1]]==n)break;
	}
	return sa;
}
