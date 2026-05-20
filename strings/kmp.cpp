vector<int> kmppre(string& t){ // r[i]: longest border of t[0,i)
	vector<int> r(t.size()+1);r[0]=-1;
	int j=-1;
	for (int i = 0; i < t.size(); ++i){
		while(j>=0&&t[i]!=t[j])j=r[j];
		r[i+1]=++j;
	}
	return r;
}
void kmp(string& s, string& t){ // find t in s
	int j=0;vector<int> b=kmppre(t);
	for (int i = 0; i < s.size(); ++i){
		while(j>=0&&s[i]!=t[j])j=b[j];
		if(++j==t.size())printf("Match at %d\n",i-j+1),j=b[j];
	}
}
