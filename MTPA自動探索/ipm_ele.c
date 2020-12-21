#include <math.h>

//x[0]:ia x[1]:ib x[2]:w x[3]:theta
//#define STATIONARY
#ifdef STATIONARY
void ipm(double time,double x[],double dx[])
{
	extern double Va,Vb;
	extern double t1;
	double nensei=0,kansei=J,ke;			/* 粘性係数、慣性モーメント、起電力係数 */
	double ripm=R;							/* 巻線抵抗 */
	double ld=Ld,lq=Lq;						/* dq軸インダクタンス */

	double vapwm,vbpwm;
	double ia,ib,w,sintheta,costheta,cos2theta,sin2theta,trq;
	double lab,la,lb,l1,l2;
	double w11,w22;							/* 作業用 */
	
	ke=PSI;
	
	vapwm=Va; vbpwm=Vb;
	sintheta=sin(x[3]);
	costheta=cos(x[3]);
	cos2theta=costheta*costheta-sintheta*sintheta;
	sin2theta=2.0*sintheta*costheta;
	l1=(ld+lq)/2.0;
	l2=(ld-lq)/2.0;
	la=l1+l2*cos2theta;
	lb=l1-l2*cos2theta;
	lab=l2*sin2theta;
	
	ia=x[0];
	ib=x[1];
	w=x[2];
	
	w11=ripm*ia+w*(-2.0*lab*ia+(la-lb)*ib)+w*ke*(-sintheta)-vapwm;
	w22=ripm*ib+w*((la-lb)*ia+2.0*lab*ib)+w*ke*(costheta)-vbpwm;
	
	dx[0]=-(lb*w11-lab*w22)/(ld*lq);		/* x[0]=ia */
	dx[1]=-(-lab*w11+la*w22)/(ld*lq);		/* x[1]=ib */
	trq=-(ia*(lab*ia+lb*ib+ke*sintheta)+ib*(-la*ia-lab*ib-ke*costheta));
	dx[2]=(trq-t1-nensei*x[2])/kansei;		/* x[2]=omega */
	dx[3]=x[2];								/* x[3]=thetam */
}

#else										/* ＜電気の世界で考える＞ */
void ipm_ele(double time,double x[],double dx[])
{
	extern double Va,Vb;					/* 静止座標上の電圧 */
	extern double t1_e,trq_e;					/* 負荷トルク 電気トルク（2018年10月） */
	double nensei=0,kansei=J_e,ke;			/* 粘性係数、電気的慣性モーメント＝機械的慣性モーメント/(極対数^2)、起電力係数 */
	double ripm=R;							/* 巻線抵抗 */
	double ld=Ld,lq=Lq;						/* dq軸インダクタンス */
	double vde,vqe;							/* 回転座標上の電圧 ただし、真の座標 */
	double ide,iqe,w,theta;					/* dq軸電流 電気角速度 実位置 */
	double w11,w22;							/* 作業用 */
	double psi;								/* 鎖交磁束 */
	double ppsi;							/* 0 */
	double pppsi;							/* 0 */
	
	ide=x[0];								/* d軸電流 */
	iqe=x[1];								/* q軸電流 */
	w=x[2];									/* 実速度（電気角速度） */
	theta=x[3];								/* 実位置 */
	
	ke=PSI;									/* 起電力係数 */
	pppsi=0;								/* 0 */
	
	/* dq軸変換 */
	ab2dq ( Va, Vb, theta, &vde, &vqe );
	
	/* 電圧方程式の微分項(過渡状態などの微分項が発生するとき) */
	w11=ripm*ide+w*(-lq*iqe)+pppsi-vde;
	w22=ripm*iqe+w*(ld*ide)+w*ke-vqe;
	
	/* 電気トルク式 */
	trq_e=(ke*iqe+(ld-lq)*(ide*iqe));			/* "P*"を削除、イメージは「電気トルク」Power=w*trq (2018年10月) */
	
	/* 微分方程式 */
	dx[0]=-w11/ld;							/* x[0]=ide */
	dx[1]=-w22/lq;							/* x[1]=iqe */
	dx[2]=(trq_e-t1_e-nensei*x[2])/kansei;	/* x[2]=omega_r_e */
	dx[3]=x[2];								/* x[3]=theta */
}

#endif
