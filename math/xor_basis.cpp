struct XorBasis{
    array<unsigned long long,64> b{};int rank=0;
    bool add(unsigned long long x){
        for(int i=63;i>=0;--i)if((x>>i)&1ULL){
            if(!b[i]){b[i]=x;rank++;return true;}x^=b[i];
        }
        return false;
    }
    bool has(unsigned long long x)const{
        for(int i=63;i>=0;--i)if((x>>i)&1ULL)x^=b[i];return x==0;
    }
    unsigned long long maximum(unsigned long long x=0)const{
        for(int i=63;i>=0;--i)x=max(x,x^b[i]);return x;
    }
};
