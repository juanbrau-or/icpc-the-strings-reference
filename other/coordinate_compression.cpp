template<class T> struct Compression{
    vector<T> values;
    Compression(vector<T> a):values(a){
        sort(ALL(values));values.erase(unique(ALL(values)),values.end());
    }
    int rank(T x)const{return lower_bound(ALL(values),x)-values.begin();}
    // rank(x) is an insertion position; x need not be present.
    T value(int r)const{return values[r];}
};
