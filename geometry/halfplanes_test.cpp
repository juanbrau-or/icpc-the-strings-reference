// Codechef CHN02 - AC
// https://www.codechef.com/problems/CHN02

#include <bits/stdc++.h>
#define first first
#define second second
#define for (int i = a, _n = b; i < _n; ++i) for(int i=a,ThxDem=b;i<ThxDem;++i)
#define push_back push_back
#define ALL(s) s.begin(),s.end()
#define FIN ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define ((int)(n).size()) ((int)(n).size())
using namespace std;
typedef long long ll;
typedef pair<int,int> ii;

const double EPS = 1e-7, DINF = 1e100;

struct pt {
  double x,y;
  pt(double x, double y):x(x),y(y){}
  pt(){}
  double norm2(){return *this**this;}
  double norm(){return sqrt(norm2());}
  bool operator==(pt p){return abs(x-p.x)<EPS&&abs(y-p.y)<EPS;}
  pt operator+(pt p){return pt(x+p.x,y+p.y);}
  pt operator-(pt p){return pt(x-p.x,y-p.y);}
  pt operator*(double t){return pt(x*t,y*t);}
  pt operator/(double t){return pt(x/t,y/t);}
  double operator*(pt p){return x*p.x+y*p.y;}
  pt unit(){return *this/norm();}
  double operator%(pt p){return x*p.y-y*p.x;}
  bool left(pt p, pt q){ // is it to the left of directed line pq?
  return (q-p)%(*this-p)>-EPS;}
};

int sgn2(double x){return x<0?-1:1;}
struct ln {
	pt p,pq;
	ln(pt p, pt q):p(p),pq(q-p){}
	ln(){}
	bool has(pt r){return dist(r)<=EPS;}
	bool seghas(pt r){return has(r)&&(r-p)*(r-(p+pq))<=EPS;}
//	bool operator /(ln l){return (pq.unit()^l.pq.unit()).norm()<=EPS;} // 3D
	bool operator/(ln l){return abs(pq.unit()%l.pq.unit())<=EPS;} // 2D
	bool operator==(ln l){return *this/l&&has(l.p);}
	pt operator^(ln l){ // intersection
		if(*this/l)return pt(DINF,DINF);
		pt r=l.p+l.pq*((p-l.p)%pq/(l.pq%pq));
//		if(!has(r)){return pt(NAN,NAN,NAN);} // check only for 3D
		return r;
	}
	int side(pt r){return has(r)?0:sgn2(pq%(r-p));} // 2D
	pt proj(pt r){return p+pq*((r-p)*pq/pq.norm2());}
	pt ref(pt r){return proj(r)*2-r;}
	double dist(pt r){return (r-proj(r)).norm();}
//	double dist(ln l){ // only 3D
//		if(*this/l)return dist(l.p);
//		return abs((l.p-p)*(pq^l.pq))/(pq^l.pq).norm();
//	}
};

int sgn(double x){return x<-EPS?-1:x>EPS;}

struct pol {
  int n;vector<pt> p;
  pol(){}
  pol(vector<pt> _p){p=_p;n=p.size();}
  double area(){
    double r=0.;
    for(int i = 0; i < n; i++)r+=p[i]%p[(i+1)%n];
    return abs(r)/2;
  }
};

// polygon intersecting left side of halfplanes
struct halfplane:public ln{
	double angle;
	halfplane(){}
	halfplane(pt a,pt b){p=a; pq=b-a; angle=atan2(pq.y,pq.x);}
	bool operator<(halfplane b)const{return angle<b.angle;}
	bool out(pt q){return pq%(q-p)<-EPS;}
};
vector<pt> intersect(vector<halfplane> b){
	vector<pt>bx={{DINF,DINF},{-DINF,DINF},{-DINF,-DINF},{DINF,-DINF}};
	for (int i = 0, _n = 4; i < _n; ++i) b.push_back(halfplane(bx[i],bx[(i+1)%4]));
	sort(ALL(b));
	int n=((int)(b).size()),q=1,h=0;
	vector<halfplane> c(((int)(b).size())+10);
	for (int i = 0, _n = n; i < _n; ++i){
		while(q<h&&b[i].out(c[h]^c[h-1])) h--;
		while(q<h&&b[i].out(c[q]^c[q+1])) q++;
		c[++h]=b[i];
		if(q<h&&abs(c[h].pq%c[h-1].pq)<EPS){
			if(c[h].pq*c[h-1].pq<=0) return {};
			h--;
			if(b[i].out(c[h].p)) c[h]=b[i];
		}
	}
	while(q<h-1&&c[q].out(c[h]^c[h-1]))h--;
	while(q<h-1&&c[h].out(c[q]^c[q+1]))q++;
	if(h-q<=1)return {};
	c[h+1]=c[q];
	vector<pt> s;
	for (int i = q, _n = h+1; i < _n; ++i) s.push_back(c[i]^c[i+1]);
	return s;
}

int main(){FIN;
  int n; cin >> n;
  vector<halfplane> v;
  for (int i = 0, _n = n; i < _n; ++i){
    int c; cin >> c;
    vector<pt> p(c);
    for (int i = 0, _n = c; i < _n; ++i) cin >> p[i].x >> p[i].y;
    for (int i = 0, _n = c; i < _n; ++i) v.push_back(halfplane(p[i],p[(i+1)%c]));
  }
  pol p(intersect(v));
  cout<<fixed<<setprecision(10)<<p.area()<<"\n";
}
