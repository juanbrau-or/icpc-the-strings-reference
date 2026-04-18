//O(n*m) minimum spanning tree in directed graph
//returns -1 if not possible
//included i-th edge if take[i]!=0
typedef int tw; tw INF=1ll<<30;
struct edge{int u,v,id;tw len;};
struct ChuLiu{
	int n; vector<edge> e;
	vector<int> inc,dec,take,pre,num,id,vis;
	vector<tw> inw;
	void add_edge(int x, int y, tw w){
		inc.push_back(0); dec.push_back(0); take.push_back(0);
		e.push_back({x,y,((int)(e).size()),w});
	}
	ChuLiu(int n):n(n),pre(n),num(n),id(n),vis(n),inw(n){}
	tw doit(int root){
		auto e2=e;
		tw ans=0; int eg=((int)(e).size())-1,pos=((int)(e).size())-1;
		while(1){
			for (int i = 0, _n = n; i < _n; ++i) inw[i]=INF,id[i]=vis[i]=-1;
			for(auto ed:e2) if(ed.len<inw[ed.v]){
				inw[ed.v]=ed.len; pre[ed.v]=ed.u;
				num[ed.v]=ed.id;
			}
			inw[root]=0;
			for (int i = 0, _n = n; i < _n; ++i) if(inw[i]==INF) return -1;
			int tot=-1;
			for (int i = 0, _n = n; i < _n; ++i){
				ans+=inw[i];
				if(i!=root)take[num[i]]++;
				int j=i;
				while(vis[j]!=i&&j!=root&&id[j]<0)vis[j]=i,j=pre[j];
				if(j!=root&&id[j]<0){
					id[j]=++tot;
					for(int k=pre[j];k!=j;k=pre[k]) id[k]=tot;
				}
			}
			if(tot<0)break;
			for (int i = 0, _n = n; i < _n; ++i) if(id[i]<0)id[i]=++tot;
			n=tot+1; int j=0;
			for (int i = 0, _n = ((int)(e2; i < _n; ++i).size())){
				int v=e2[i].v;
				e2[j].v=id[e2[i].v];
				e2[j].u=id[e2[i].u];
				if(e2[j].v!=e2[j].u){
					e2[j].len=e2[i].len-inw[v];
					inc.push_back(e2[i].id);
					dec.push_back(num[v]);
					take.push_back(0);
					e2[j++].id=++pos;
				}
			}
			e2.resize(j);
			root=id[root];
		}
		while(pos>eg){
			if(take[pos]>0) take[inc[pos]]++, take[dec[pos]]--;
			pos--;
		}
		return ans;
	}
};
