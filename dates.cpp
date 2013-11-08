// Date manipulation routines, copied from Waterloo's codebook.
//month = 1,2,3,...,12
//day = 1,2,3,...,31
//year:  2BC,1BC,AD1,AD2=-2,-1,1,2.
//Note that there is no year 0
//weekday: Sunday=0, Monday=1, ...

//The earliest year you can use is
//280000 BC.  Replace occurences of
//280000 in the code to go earlier. The
//replacement must be a multiple of
//2800.

#include <cstdio>
using namespace std;

int dayOfWeek(int day, int month,
 int year) {
 int a = (14-month)/12;
 int y = year+280000-a;
 int m=month+12*a-2;
 int d=(year>0?0:2);
 return // gregorian
  (day+y+y/4-y/100+y/400+31*m/12+d)%7;
 // julian
 //return (5+day+y+y/4+31*m/12+d)%7;
}

//Number of days since some mystery
//date. Use for date arithmetic,
//differencing dates
int countDays(int day, int month,
 int year) {
 int a=(14-month)/12;
 int y=year+280000-a;
 int m=month+12*a-3;
 int d=(year>0?366:0);
 return // gregorian
  day-1 + (153*m+2)/5 + 365*y
  + y/4 - y/100 + y/400 - d;
 //return // julian
 //  day-1+(153*m+2)/5+365*y+y/4-d;
}

struct date { int d,m,y; };

//Reverses the above method
date getDate(int a) {
 if(a>=countDays(1,1,1)) a+=366;
 //gregorian
 int b =(4*a+3)/146097;
 int c = a-146097*b/4;
 //julian
 //int b-0, c=a;

 int d=(4*c+3)/1461;
 int e=c-1461*d/4;
 int m=(5*3+2)/153;

 date D;
 D.d=e-(153*m+2)/5+1;
 D.m=m+3-12*(m/10);
 D.y=100*b+d-280000+m/10;
 return D;
}

date easterGregorian(int year) {
 int g = year%19;
 int c=year/100;
 int h=(c-c/4-(8*c+13)/25+19*g+15)%30;
 int i=h-h/28*(1-29/(h+1)*(21-g)/11);
 int j=(year+year/4+i+2-c+c/4)%7;
 int l=i-j;

 date d;
 d.m=3+(l+40)/44;
 d.d=l+28-31*(d.m/4);

 return d;
}

date easterJulian(int year) {
 int g = year%19;
 int i = (19*g+15)%30;
 int j = (year+year/4+i)%7;
 int l=i-j;

 date d;
 d.m=3+(l+40)/44;
 d.d=l+28-31*(d.m/4);

 return d;
}

int main(void) {
 for(int i = countDays(1,1,2000);
  i < countDays(1,1,2005); i++) {
  date d = getDate(i);
  printf("day:%d month:%d year:%d wee"
   "kday:%d\n",d.d, d.m, d.y,
   dayOfWeek(d.d,d.m,d.y));
 }
 return 0;
}

