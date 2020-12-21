#include <math.h>
#define SHUCHU
#ifdef SHUCHU
double psi(double theta)
{
	return((PSI-0.05)+0.05*cos(6.*theta));
}

double ppsi(double theta)
{
	return(-0.06*sin(6.*theta));
}
double psi1(double theta)
{
	return((PSI-0.05)+0.05*cos(6.*(theta+0.523599)));
}

#else
double psi(double theta)
{
	return(PSI);
}

double ppsi(double theta)
{
	return(0.0);
}

#endif
