typedef long double td; typedef vector<int> vi; typedef vector<td> vd;
const td INF=1e100;//for maximum set INF to 0, and negate costs
bool zero(td x){return fabs(x)<1e-9;}//change to x==0, for ints/ll
struct Hungarian{
    int n; vector<vd> cs; vi L, R;
    Hungarian(int N, int M):n(max(N,M)),cs(n,vd(n)),L(n),R(n){
        for (int x = 0, _n = N; x < _n; ++x)for (int y = 0, _n = M; y < _n; ++y)cs[x][y]=INF;
    }
    void set(int x,int y,td c){cs[x][y]=c;}
	td assign() {
		int mat = 0; vd ds(n), u(n), v(n); vi dad(n), sn(n);
		for (int i = 0, _n = n; i < _n; ++i)u[i]=*min_element(ALL(cs[i]));
		for (int j = 0, _n = n; j < _n; ++j){v[j]=cs[0][j]-u[0];for (int i = 1, _n = n; i < _n; ++i)v[j]=min(v[j],cs[i][j]-u[i]);}
		L=R=vi(n, -1);
		for (int i = 0, _n = n; i < _n; ++i)for (int j = 0, _n = n; j < _n; ++j)
			if(R[j]==-1&&zero(cs[i][j]-u[i]-v[j])){L[i]=j;R[j]=i;mat++;break;}
		for(;mat<n;mat++){
		    int s=0, j=0, i;
		    while(L[s] != -1)s++;
		    fill(ALL(dad),-1);fill(ALL(sn),0);
		    for (int k = 0, _n = n; k < _n; ++k)ds[k]=cs[s][k]-u[s]-v[k];
		    for(;;){
		        j = -1;
		        for (int k = 0, _n = n; k < _n; ++k)if(!sn[k]&&(j==-1||ds[k]<ds[j]))j=k;
		        sn[j] = 1; i = R[j];
		        if(i == -1) break;
		        for (int k = 0, _n = n; k < _n; ++k)if(!sn[k]){
		            auto new_ds=ds[j]+cs[i][k]-u[i]-v[k];
		            if(ds[k] > new_ds){ds[k]=new_ds;dad[k]=j;}
		        }
		    }
		    for (int k = 0, _n = n; k < _n; ++k)if(k!=j&&sn[k]){auto w=ds[k]-ds[j];v[k]+=w,u[R[k]]-=w;}
		    u[s] += ds[j];
		    while(dad[j]>=0){int d = dad[j];R[j]=R[d];L[R[j]]=j;j=d;}
		    R[j]=s;L[s]=j;
		}
		td value=0;for (int i = 0, _n = n; i < _n; ++i)value+=cs[i][L[i]];
		return value;
	}
};
