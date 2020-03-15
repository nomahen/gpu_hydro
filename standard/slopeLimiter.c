#include "decs.h"

void vanLeer(float a, float b, float *delta)
{
	if(a*b <=0){
	    *delta = 0.0;
	    }
	else{
	    *delta = 2.*a*b/(a+b);
	    }
}
