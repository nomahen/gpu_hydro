#include "decs.h"

void soln_reconstruct(float dt, int d, float *dr_V, float *dr_VL, float *dr_VR) 
{
	if(sim_order==1){
		soln_FOG(dr_V, dr_VL, dr_VR); // first order godunov
	}
	else if(sim_order==2){
		soln_PLM(dt,d); // 2nd order PLM
	}

	return;
}
