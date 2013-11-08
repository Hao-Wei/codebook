// Closest pair of points in O(n log n). Copied from Waterloo's codebook.
// Can be modified to use doubles. "dist" stores the square of the closest distance; mark[i] == cookie if the i-th point is within the closest pair distance of some other point.
// TODO: Clean this up (wrap it in a struct, add better comments?)
typedef long long T;
typedef valarray<T> P;
typedef vector<P> VP;
#define fu(i,n) for (int i = 0; i < (n); i++ )

bool ltx( const P& a, const P& b )
{ return a[0]<b[0] || a[0]==b[0] && a[1]<b[1]; }
bool lty( const P& a, const P& b )
{ return a[1]<b[1] || a[1]==b[1] && a[0]<b[0]; }

T dist=1ll<<62; int cookie=1, mark[100000];

void go( VP& X, VP& Y ) {
 VP XL, YL, XR, YR, S; int m = X.size()/2;
 fu(i,X.size()) {
  (ltx(X[i],X[m])?XL:XR).push_back(X[i]);
  (lty(Y[i],X[m])?YL:YR).push_back(Y[i]);
 }
 if( XR.size() > 1 ) { go(XL, YL); go(XR, YR); }
 fu(i,Y.size()) {
  T z = X[m][0]-Y[i][0];
  if ( z*z <= dist ) S.push_back(Y[i]);
 }
 fu(i,S.size()) fu(j,7) if(i+1+j<S.size()) {
  P p = S[i+1+j]-S[i];
  T z = p[0]*p[0] + p[1]*p[1];
  if( z < dist ) { ++cookie; dist = z; }
  if( z <= dist ) {
   mark[S[i][2]] = mark[S[i+1+j][2]] = cookie;
  }
 }
}

int main() {
 VP X, Y; T a, b; int c = 0; P p(3);
 while( scanf("%lld %lld",&a,&b)==2 ) {
  if( a+b < 0 ) break;
  p[0]=a; p[1]=b; p[2]=++c;
  X.push_back(p);
  Y.push_back(p);
 }
 sort(X.begin(), X.end(), ltx);
 sort(Y.begin(), Y.end(), lty);
 go(X, Y);
 fu(i, 99999) if( mark[i] == cookie )
  printf("%d\n", i);
}
