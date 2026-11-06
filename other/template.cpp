#include <bits/stdc++.h>
#ifdef BRAULIO
#define deb(...) fprintf(stderr,__VA_ARGS__)
#define deb1(x) cerr << #x << " = " << x << endl
#else
#define deb(...) 0
#define deb1(x) 0
#endif

// --- DEBUGGING TOOLS ---
void void_debug() { std::cerr << std::endl; }
template<typename Head, typename... Tail>
void void_debug(const Head& H, const Tail&... T) { std::cerr << " " << H; void_debug(T...); }

#ifdef LOCAL
#define debug(...) std::cerr << "[" << #__VA_ARGS__ << "]:", void_debug(__VA_ARGS__)
#else
#define debug(...) ((void)0)
#endif

// Local: g++ -std=c++17 -O2 -Wall -Wextra -DLOCAL main.cpp


#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)
#define ALL(x) (x).begin(),(x).end()
#define SZ(x) ((int)(x).size())
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pl;

int main(){
	ios::sync_with_stdio(false);cin.tie(nullptr);
	return 0;
}
