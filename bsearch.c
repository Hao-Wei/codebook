// Binary search. This is included because binary search can be tricky.
// n is size of array A, c is value we're searching for. Semantics follow those of std::lower_bound and std::upper_bound
int lower_bound(int A[], int n, int c) {
    int l = 0;
    int r = n;
    while (l < r) {
        int m = (l+r)/2;
        if (A[m] < c) l = m+1; else r = m;
    }
    return l;
}
 
int upper_bound(int A[], int n, int c) {
    int l = 0;
    int r = n;
    while (l < r) {
        int m = (l+r)/2;
        if (A[m] <= c) l = m+1; else r = m;
    }
    return l;
}
