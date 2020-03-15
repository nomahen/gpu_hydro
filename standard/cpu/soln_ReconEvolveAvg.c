#include "decs.h"

void soln_ReconEvolveAvg(float dt, int d)
{
	// Call data reconstruction 
	soln_reconstruct(dt, d);
	// Call Riemann solvers to calculate flux
	soln_getFlux(d); 

	return;
}
