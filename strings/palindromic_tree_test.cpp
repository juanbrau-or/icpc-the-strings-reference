#include <bits/stdc++.h>
#define for (int x = a, _n = b; x < _n; ++x) for(int x=a, qwerty=b; x<qwerty; x++)
#define ALL(a) (a).begin(),(a).end()
#define ((int)(a).size()) ((int)(a).size())
#define push_back push_back
#define FIN ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define first first
#define second second
using namespace std;
typedef long long ll;

struct palindromic_tree{
    static const int SIGMA=26;
    struct Node{
        int len, link, to[SIGMA];
        ll cnt;
        Node(int len, int link=0, ll cnt=1):len(len),link(link),cnt(cnt){
            memset(to,0,sizeof(to));
        }
    };
    vector<Node> ns;
    int last;
    palindromic_tree():last(0){ns.push_back(Node(-1));ns.push_back(Node(0));}
    void reset(){ns.clear();last=0;ns.push_back(Node(-1));ns.push_back(Node(0));}
    void add(int i, string &s){
        int p=last, c=s[i]-'a';
        while(s[i-ns[p].len-1]!=s[i])p=ns[p].link;
        if(ns[p].to[c]){
            last=ns[p].to[c];
            ns[last].cnt++;
        }else{
            int q=ns[p].link;
            while(s[i-ns[q].len-1]!=s[i])q=ns[q].link;
            q=max(1,ns[q].to[c]);
            last=ns[p].to[c]=((int)(ns).size());
            ns.push_back(Node(ns[p].len+2,q,1));
        }
    }
};

palindromic_tree pt1, pt2;
string s, t;

ll solve(int a, int b){
    ll ans = a > 1 && b > 1 ? pt1.ns[a].cnt * pt2.ns[b].cnt : 0;
    for (int c = 0, _n = pt1.SIGMA; c < _n; ++c)if(pt1.ns[a].to[c] && pt2.ns[b].to[c])
        ans += solve(pt1.ns[a].to[c],pt2.ns[b].to[c]);
    return ans;
}

int main(){FIN;
    int T; cin >> T;
    for (int tc = 1, _n = T+1; tc < _n; ++tc){
        pt1.reset();pt2.reset();
        cin >> s >> t;
        for (int i = 0, _n = ((int)(s; i < _n; ++i).size()))pt1.add(i,s);
        for (int i = 0, _n = ((int)(t; i < _n; ++i).size()))pt2.add(i,t);

        for(int i=((int)(pt1.ns).size())-1; i>=0; i--)
            pt1.ns[pt1.ns[i].link].cnt+=pt1.ns[i].cnt;
        for(int i=((int)(pt2.ns).size())-1; i>=0; i--)
            pt2.ns[pt2.ns[i].link].cnt+=pt2.ns[i].cnt;

        ll ans = solve(0,0) + solve(1,1);
        cout << "Case #"<<tc<<": "<< ans << "\n";
    }
}
