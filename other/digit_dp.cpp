// Counts [0,N] without equal adjacent decimal digits. Includes zero.
ll count_no_adjacent(ll N){
    if(N<0)return 0;
    string s=to_string(N);ll memo[20][11][2];memset(memo,-1,sizeof(memo));
    function<ll(int,int,bool,bool)> go=[&](int i,int last,bool started,bool tight)->ll{
        if(i==SZ(s))return 1;
        ll &res=memo[i][last][started];if(!tight&&res!=-1)return res;
        int limit=tight?s[i]-'0':9;ll ans=0;
        fore(d,0,limit+1){
            bool ns=started||d!=0;if(started&&d==last)continue;
            ans+=go(i+1,ns?d:10,ns,tight&&d==limit);
        }
        if(!tight)res=ans;return ans;
    };
    return go(0,10,false,true);
}
