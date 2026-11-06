// First true in [lo,hi); hi if none. Predicate: false...false,true...true.
// Bounds and hi-lo must fit in ll. Never evaluates ok(hi).
template<class F> ll first_true(ll lo,ll hi,F ok){
    while(lo<hi){ll mid=lo+(hi-lo)/2;if(ok(mid))hi=mid;else lo=mid+1;}
    return lo;
}
