// Index of the lexicographically smallest cyclic rotation. Empty -> 0.
int minimal_rotation(const string& s){
    int n=SZ(s),i=0,j=1,k=0;
    while(i<n&&j<n&&k<n){
        char a=s[(i+k)%n],b=s[(j+k)%n];if(a==b){k++;continue;}
        if(a>b){i+=k+1;if(i==j)i++;}else{j+=k+1;if(i==j)j++;}k=0;
    }
    return min(i,j);
}
