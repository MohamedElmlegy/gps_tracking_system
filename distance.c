# include<F:/Dell/Documents/tm4c123gh6pm.h>
# include<stdio.h>
# include<stdlib.h>
# include<Math.h>
void SystemInit(){}
int dstnc(double x, double y);
double radian(double x);
int main()
{
	
	
	return 0; 
}
int dstnc(double x, double y)
{
	const double RADIUS = 6378.16;
	
	static double t;
	static int total_distance;
	static double loc_x;
	static double loc_y;
	double d_x ;
	double d_y ;
	if (t == 0)
	{
		loc_x = x;
		loc_y = y;
		t++;
		return 0;
	}
	else
	{
		double d_x  = radian(x - loc_x);
		double d_y  = radian(y - loc_y);
		double a = ( sin(d_y / 2) * sin(d_y / 2)) + cos(radian(loc_y)) * cos(radian(y)) * (sin(d_x / 2) * sin(d_x / 2));
    double angle = 2 * atan2(sqrt(a), sqrt(1 - a));
		double d_km = angle * RADIUS ;
		int d_meter = d_km *1000 ;
		loc_x = x;
		loc_y = y;
		total_distance = total_distance + d_meter ;
		return total_distance;
	}
	

}
double radian(double x)
{
		const double PIx = 3.141592653589793;
		return x*PIx /180;
}
