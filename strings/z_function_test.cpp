// Codeforces 126B - AC
// http://codeforces.com/problemset/problem/126/B
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int> z_function(string& s){
	int l=0,r=0,n=s.size();
	vector<int> z(s.size(),0); // z[i] = max k: s[0,k) == s[i,i+k)
	for (int i = 1; i < n; ++i){
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
	for (int i = 1; i < s.size(); ++i){
		if(i+z[i]==s.size())r0=max(r0,z[i]-1);
		else r0=max(r0,z[i]);
	}
	for (int i = 1; i < s.size(); ++i){
		if(i+z[i]==s.size()&&z[i]<=r0)r=max(r,z[i]);
	}
	if(r<=0)puts("Just a legend");
	else {
		for (int i = 0; i < r; ++i)putchar(s[i]);
		puts("");
	}
	return 0;
}
