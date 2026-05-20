#include <bits/stdc++.h>
#ifdef DBP
#define deb(...) fprintf(stderr,__VA_ARGS__)
#else
#define deb(...) 0
#endif
#define mset(a,v) memset((a),(v),sizeof(a))
#define ALL(a) (a).begin(), (a).end()
#define SZ(a) int((a).size())
#define FIN ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
using namespace std;
typedef long long ll;
 int f, c, w;
const int MAXN=1e6+5, F=MAXN;
// MAXN: max number of nodes or 2 * max number of variables (2SAT)
bool truth[MAXN]; // truth[cmp[i]]=value of variable i (2SAT)
int nvar;int neg(int x){return MAXN-1-x;} // (2SAT)
vector<int> g[MAXN];
int n,lw[MAXN],idx[MAXN],qidx,cmp[MAXN],qcmp;
stack<int> st;
void tjn(int u){
    lw[u]=idx[u]=++qidx;
    st.push(u);cmp[u]=-2;
    for(int v:g[u]){
        if(!idx[v]||cmp[v]==-2){
            if(!idx[v]) tjn(v);
            lw[u]=min(lw[u],lw[v]);
        }
    }
    if(lw[u]==idx[u]){
        int x,l=-1;
        do{x=st.top();st.pop();cmp[x]=qcmp;if(x<c||neg(x)<c)l=x;}while(x!=u);
        if(l!=-1)truth[qcmp]=(cmp[neg(l)]<0); // (2SAT)
        qcmp++;
    }
}
void scc(){
    memset(idx,0,sizeof(idx));qidx=0;
    memset(cmp,-1,sizeof(cmp));qcmp=0;
    for (int i = 0; i < n; ++i)if(!idx[i])tjn(i);
}
// Only for 2SAT:
void addor(int a, int b){g[neg(a)].push_back(b);g[neg(b)].push_back(a);}
bool satisf(int _nvar){
    nvar=_nvar;n=MAXN;scc();
    for (int i = 0; i < nvar; ++i)if(cmp[i]==cmp[neg(i)])return false;
    return true;
}
 
vector<int> wishes[F];
int get(int v){if(v<0)return neg(-v-1); return v-1;}
int main(){FIN;
    cin >> f >> c >> w;
    n = c;
    for (int x = 0; x < w; ++x){
        int a,b;cin>>a>>b;a--;
        wishes[a].push_back(b);
    }
    for (int x = 0; x < f; ++x){
        int st = n;
        if(SZ(wishes[x])<=1)continue;
        for(int v:wishes[x]){
            if(st!=n)g[n].push_back(n-1);
            g[n].push_back(get(v));
            n++;
        }
        int cnt = SZ(wishes[x]);
        for(int v:wishes[x]){
            if(cnt>1)g[n].push_back(n+1);
            g[n].push_back(get(v));
            n++;cnt--;
        }
        g[neg(get(wishes[x][0]))].push_back(st+SZ(wishes[x])+1);
        g[neg(get(wishes[x].back()))].push_back(st+SZ(wishes[x])-2);
        for (int i = 1; i < SZ(wishes[x])-1; ++i){
            g[neg(get(wishes[x][i]))].push_back(st+i-1);
            g[neg(get(wishes[x][i]))].push_back(st+i+SZ(wishes[x])+1);
        }
    }
    if(satisf(c)){
        vector<int> ans;
        for (int x = 0; x < c; ++x)if(truth[cmp[x]])ans.push_back(x+1);
        cout<<SZ(ans)<<"\n";
        for (int x = 0; x < SZ(ans); ++x)cout<<ans[x]<<" \n"[x+1==SZ(ans)];
    }else cout<<"-1\n";
}
