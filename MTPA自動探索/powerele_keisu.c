#define KEISU 0.81649658
#define KEISU2 0.866025403
#include <math.h>

void ab2uvw(double vds, double vqs, double *u, double *v, double *w)
{
	*u=KEISU*vds;
	*v=KEISU*(-0.5*vds+KEISU2*vqs);
	*w=KEISU*(-0.5*vds-KEISU2*vqs);
}
void uvw2ab(double u, double v, double w ,double *vds, double *vqs )
{
	*vds=KEISU*(u+0.5*v+0.5*w);
	*vqs=KEISU*(v*KEISU2+w*KEISU2);
}
void ab2dq(double ids,double iqs,double theta, double *idse,double *iqse)
{
	*idse=ids*cos(theta)+iqs*sin(theta);
	*iqse=ids*(-sin(theta))+iqs*cos(theta);
}
void dq2ab(double ids,double iqs,double theta, double *idse,double *iqse)
{
	*idse=ids*cos(theta)-iqs*sin(theta);
	*iqse=ids*sin(theta)+iqs*cos(theta);
}
