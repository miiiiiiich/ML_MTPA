#include <math.h>

//x[0]:ia x[1]:ib x[2]:w x[3]:theta
//#define STATIONARY
#ifdef STATIONARY
void ipm(double time,double x[],double dx[])
{
	extern double Va,Vb;
	extern double t1;
	double nensei=0,kansei=J,ke;			/* �S���W���A�������[�����g�A�N�d�͌W�� */
	double ripm=R;							/* ������R */
	double ld=Ld,lq=Lq;						/* dq���C���_�N�^���X */

	double vapwm,vbpwm;
	double ia,ib,w,sintheta,costheta,cos2theta,sin2theta,trq;
	double lab,la,lb,l1,l2;
	double w11,w22;							/* ��Ɨp */
	
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

#else										/* ���d�C�̐��E�ōl���遄 */
void ipm_ele(double time,double x[],double dx[])
{
	extern double Va,Vb;					/* �Î~���W��̓d�� */
	extern double t1_e,trq_e;					/* ���׃g���N �d�C�g���N�i2018�N10���j */
	double nensei=0,kansei=J_e,ke;			/* �S���W���A�d�C�I�������[�����g���@�B�I�������[�����g/(�ɑΐ�^2)�A�N�d�͌W�� */
	double ripm=R;							/* ������R */
	double ld=Ld,lq=Lq;						/* dq���C���_�N�^���X */
	double vde,vqe;							/* ��]���W��̓d�� �������A�^�̍��W */
	double ide,iqe,w,theta;					/* dq���d�� �d�C�p���x ���ʒu */
	double w11,w22;							/* ��Ɨp */
	double psi;								/* �������� */
	double ppsi;							/* 0 */
	double pppsi;							/* 0 */
	
	ide=x[0];								/* d���d�� */
	iqe=x[1];								/* q���d�� */
	w=x[2];									/* �����x�i�d�C�p���x�j */
	theta=x[3];								/* ���ʒu */
	
	ke=PSI;									/* �N�d�͌W�� */
	pppsi=0;								/* 0 */
	
	/* dq���ϊ� */
	ab2dq ( Va, Vb, theta, &vde, &vqe );
	
	/* �d���������̔�����(�ߓn��ԂȂǂ̔���������������Ƃ�) */
	w11=ripm*ide+w*(-lq*iqe)+pppsi-vde;
	w22=ripm*iqe+w*(ld*ide)+w*ke-vqe;
	
	/* �d�C�g���N�� */
	trq_e=(ke*iqe+(ld-lq)*(ide*iqe));			/* "P*"���폜�A�C���[�W�́u�d�C�g���N�vPower=w*trq (2018�N10��) */
	
	/* ���������� */
	dx[0]=-w11/ld;							/* x[0]=ide */
	dx[1]=-w22/lq;							/* x[1]=iqe */
	dx[2]=(trq_e-t1_e-nensei*x[2])/kansei;	/* x[2]=omega_r_e */
	dx[3]=x[2];								/* x[3]=theta */
}

#endif
