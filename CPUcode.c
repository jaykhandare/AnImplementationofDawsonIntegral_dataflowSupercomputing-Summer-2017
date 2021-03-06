/**
 * Document: MaxCompiler tutorial (maxcompiler-tutorial.pdf)
 * Chapter: 4      Example: 2      Name: Simple
 * MaxFile name: Simple
 * Summary:
 * 	 Takes a stream and for each value x calculates x^2 + x.
 */
#include <MaxSLiCInterface.h>
#include "Maxfiles.h"
#include <math.h>
#define H 0.4
#define A1 (2.0/3.0)
#define A2 0.4
#define A3 (2.0/7.0)
static float sqrarg;
#define SIGN(a,b) ((b) >= 0.0 ? fabs(a) : -fabs(a))
#define SQR(a) ((sqrarg=(a)) == 0.0 ? 0.0 : sqrarg*sqrarg)
const int NMAX = 7;

/*  syntsx to call kernel   */
//Simple(size, dataIn, dataOut);

void spacing(){
    printf("\n\n\n");
}

/*
Prints Dawson’s integral F (x) = exp(−x 2 ) 0 x exp(t 2 )dt for any real x.
*/

int main()
{
    float x = 10.0;
    int i,n0;
    float d1,d2,e1,e2,sum,x2,xp,xx,ans;
    static float cIn[NMAX+1],cOut1[NMAX+1],cOut2[NMAX+1];

    for (i=1;i<=NMAX;i++) {
        cIn[i] = i;
    }

    Simple(NMAX+1,cIn,cOut1);

    /*  Use Series Expansion*/      //possible kernel
/*
    for (i=1;i<=NMAX;i++) {
        cOut1[i] = exp(-SQR((2.0 * i - 1.0) * H));
    }
*/
    if (fabs(x) < 0.2) {
        x2=x*x;
        ans=x*(1.0-A1*x2*(1.0-A2*x2*(1.0-A3*x2)));
    }

/*  Use Sampling theorem representation*/
    else {
        xx=fabs(x);
        n0=2*(int)(0.5*xx/H+0.5);
        xp=xx-n0*H;
        e1=exp(2.0*xp*H);
        e2=e1*e1;
        d1=n0+1;
        d2=d1-2.0;
        sum=0.0;


        for (i=1;i<=NMAX;i++){   //possible kernel
            sum += cOut1[i]*(e1/d1+1.0/(d2*e1));
            d1+=2.0;
            d2-=2.0;
            e1*=e2;
        }

/*  kernel modification*/
/*
    Simple(NMAX+1,x,cOut1,cOut2);

    for(i = 1; i <= NMAX; i++){
        sum = sum + cOut2[i];
    }
*/

/*  1/sqrt(pie) = 0.5641895835*/
        ans= 0.5641895835*SIGN(exp(-xp*xp),x)*sum;
    }

    spacing();
    printf("Dawson's Integral\n");
    printf("For x = %f,\n",x);
    printf("F(x) = %f\n",ans);
    spacing();
    return 0;
}
