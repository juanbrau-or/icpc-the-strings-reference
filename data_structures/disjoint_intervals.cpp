// stores disjoint intervals as [first, second)
struct disjoint_intervals {
	set<pair<int,int> > s;
	void insert(pair<int,int> v){
		if(v.fst>=v.snd) return;
		auto at=s.lower_bound(v);auto it=at;
		if(at!=s.begin()&&(--at)->second>=v.fst)v.fst=at->first,--it;
		for(;it!=s.end()&&it->first<=v.snd;s.erase(it++))
			v.snd=max(v.snd,it->second);
		s.insert(v);
	}
};
