// stores disjoint intervals as [first, second)
struct disjoint_intervals {
	set<pair<int,int> > s;
	void insert(pair<int,int> v){
		if(v.first>=v.second) return;
		auto at=s.lower_bound(v);auto it=at;
		if(at!=s.begin()&&(--at)->second>=v.first)v.first=at->first,--it;
		for(;it!=s.end()&&it->first<=v.second;s.erase(it++))
			v.second=max(v.second,it->second);
		segs.insert(v);
	}
};
