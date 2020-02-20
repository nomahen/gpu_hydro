#include "decs.h"

void soln_reconstruct(float dt) 
{
	if(sim_order==1){
		soln_FOG(); // first order godunov
	}
	else if(sim_order==2){
		// PLM
	}
	
	return;
}
