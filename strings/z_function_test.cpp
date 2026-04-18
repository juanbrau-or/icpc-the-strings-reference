// Codeforces 126B - AC
// http://codeforces.com/problemset/problem/126/B
#include <bits/stdc++.h>
#define push_back push_back
#define make_pair make_pair
#define first first
#define second second
#define for (int i = a, _n = b; i < _n; ++i) for(int i=a,ThxDem=b;i<ThxDem;++i)
using namespace std;
typedef long long ll;

vector<int> z_function(string& s){
	int l=0,r=0,n=s.size();
	vector<int> z(s.size(),0); // z[i] = max k: s[0,k) == s[i,i+k)
	for (int i = 1, _n = n; i < _n; ++i){
		if(i<=r)z[i]=min(r-i+1,z[i-l]);
		while(i+z[i]<n&&s[z[i]]==s[i+z[i]])z[i]++;
		if(i+z[i]-1>r)l=i,r=i+z[i]-1;
	}
	return z;
}

int main(){
	string s;
	cin>>s;
	vector<int> z=z_function(s);
	int r0=-1,r=-1;
	for (int i = 1, _n = s.size(; i < _n; ++i)){
		if(i+z[i]==s.size())r0=max(r0,z[i]-1);
		else r0=max(r0,z[i]);
	}
	for (int i = 1, _n = s.size(; i < _n; ++i)){
		if(i+z[i]==s.size()&&z[i]<=r0)r=max(r,z[i]);
	}
	if(r<=0)puts("Just a legend");
	else {
		for (int i = 0, _n = r; i < _n; ++i)putchar(s[i]);
		puts("");
	}
	return 0;
}
