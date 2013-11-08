// Area & perimeter of a union of discs. Copied from Waterloo codebook
// TODO: What's the running time?
#define ld long double
#define FOR(i,n) for (int i=0;i<(n);i++)
#define PB push_back
#define point complex<ld>
#define BEND(x) (x).begin(),(x).end()
#define FORI(i,s) FOR(i,s.size())

struct circle {
 point p; ld r;
 vector<ld> k1, k2;
 circle(ld a,ld b,ld c): p(a,b), r(c) {}

 void kill(point q, ld rr) {
  ld d = abs(p-q), e = arg(p-q);
  if (d>=rr+r||d<=r-rr) return;
  if (d<=rr-r) k1.PB(0),k2.PB(7);
  else {
   ld f = acos((r*r-rr*rr+d*d)/2/d/r);
   for (int i = -3; i < 4; i+=2)
    k1.PB(e-f+i*M_PI),k2.PB(e+f+i*M_PI);
  }
 }

 void kill(circle c) { kill(c.p,c.r); }

 void pack() {
  sort(BEND(k1)); sort(BEND(k2));
  vector<ld> q1, q2;
  for (int i=0, j; i<k1.size(); i=j) {
   for (j = i+1; j < k1.size()
    && k1[j] <= k2[j-1]; j++);
   q1.PB((k1[i] >? 0) <? 2*M_PI);
   q2.PB((k2[j-1] >? 0) <? 2*M_PI);
  }
  k1=q1; k2=q2;
 }

 ld perim() {
  pack(); ld ans=0;
  FORI(i,k1) ans += r*fabs(k2[i]-k1[i]);
  return 2*M_PI*r - ans;
 }

 ld area() {
  pack(); ld ans=M_PI*r*r, y0=p.real();
#define doarc(a,b) (r*(r*(sin(2*a) - \
 sin(2*b))/2 + r*(a-b) + 2*y0*(sin(a) \
 - sin(b)))/2)
 FORI(i,k1) ans += doarc(k1[i], k2[i]);
 return ans;
 }
};

#define R (drand48()*1e-10)
void doit() {
 int n; ld p=0, a=0;
 if (1 != scanf("%i",&n) || !n) exit(0);
 vector<circle> da;
 FOR(i,n) {
  ld a,b,c;
  scanf("%Lf%Lf%Lf", &a,&b,&c);
  da.PB(circle(a+R, b+R, c+R));
 }
 FORI(i,da) {
  FORI(j,da) if (i-j) da[i].kill(da[j]);
  p += da[i].perim(); a += da[i].area();
 }
 printf("%.6Lf %.6Lf\n", p, a);
}

int main() { while (1) doit(); }
