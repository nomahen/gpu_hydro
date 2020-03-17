#include "decs.h"

__device__ void soln_ReconEvolveAvg(float dt, int d, float *dr_V, float *dr_VL, float *dr_VR, float *dr_flux)
{
	// Call data reconstruction
	soln_reconstruct(dt, d, dr_V, dr_VL, dr_VR);
	// Call Riemann solvers to calculate flux
    soln_getFlux(d, dr_V, dr_VL, dr_VR, dr_flux);

	return;
}
