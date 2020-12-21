/* rk4.c �����������̉�@(�S���̃����Q�E�N�b�^�@) */
#include <stdio.h>
void rk4(void (*f_ptr)(),double x,double y[],double f[],int n,double h,double yw[],double k[][5])
{
	int i,j;
	double xw;
	static double c[4]={0.0,0.5,0.5,1.0};
	
	for(i=0;i<4;i++){
		xw=x+c[i]*h;
		for(j=0;j<n;j++)
		yw[j]=y[j]+c[i]*k[j][i];
		(*f_ptr)(xw,yw,f);

		for(j=0;j<n;j++)
		k[j][i+1]=h*f[j];
	}
	for(j=0;j<n;j++){
		y[j]+=(k[j][1]+2.*k[j][2]+2.*k[j][3]+k[j][4])/6.;
	}
}
