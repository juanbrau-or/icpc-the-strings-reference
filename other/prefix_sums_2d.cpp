struct Prefix2D{
    vector<vector<ll>> p;
    Prefix2D(const vector<vector<ll>>& a):
        p(SZ(a)+1,vector<ll>(a.empty()?1:SZ(a[0])+1)){
        fore(i,0,SZ(a))fore(j,0,SZ(a[i]))
            p[i+1][j+1]=a[i][j]+p[i][j+1]+p[i+1][j]-p[i][j];
    }
    ll query(int x0,int x1,int y0,int y1)const{
        return p[x1][y1]-p[x0][y1]-p[x1][y0]+p[x0][y0];
    }
};
