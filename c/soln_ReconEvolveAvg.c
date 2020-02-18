#include "decs.h"

void soln_ReconEvolveAvg(float dt)
{
	// Call data reconstruction 
	soln_reconstruct(dt);
	// Call Riemann solvers to calculate flux
	soln_getFlux(); 

	return;
}
