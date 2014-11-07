#include<iostream>
#include<vector>
#include<algorithm>
#include<math.h>
#include<stdlib.h>
#define pb push_back
#define PI (4*atan(1))
using namespace std;

double eps = 1E-9;

struct point
{
	double a;
	int x, y;
};

int N, X, Y, f;
int x[103];
int y[103];
point p[103];
double dot(int i, int j)
{
	return x[i]*x[j] + y[i]*y[j];
}

double cross(int i, int j)
{
	return y[j]*x[i] - x[j]*y[i];
}

double dist(int i)
{
	return sqrt(dot(i, i));
}

bool comp(const point &a, const point& b)
{
	return a.a < b.a;
}

double angle(int i, int j)
{
	double c = (dot(i, j)/dist(i))/dist(j);
	double s = (cross(i, j)/dist(i))/dist(j);
	double ans = fabs(asin(s)*180.0/PI);
	//cout << ans << " " << c << " " << s << " " << asin(s) << endl;
	if(s < 0 && c >= 0)
		ans = 360 - ans;
	else if(s < 0 && c <= 0)
		ans = 180 + ans;
	else if(s > 0 && c <= 0)
		ans = 180 - ans;
	else if(ans < eps && c < 0)
		ans = 180;
	return ans;
}


