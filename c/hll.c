#include "decs.h"

void hll(double *vL, double *vR, double *Flux)
{
	double FL[NSYS_VAR], FR[NSYS_VAR], uL[NSYS_VAR], uR[NSYS_VAR];
	double sL,sR,aL,aR;

	// Calculate flux + conservative variables
  	prim2flux(vL,FL);
  	prim2flux(vR,FR);
  	prim2cons(vL,uL);
  	prim2cons(vR,uR);

	/* HLL routine here */

	return;
}
