#include "decs.h"

void soln_reconstruct(float dt, int d) 
{
	if(sim_order==1){
		soln_FOG(); // first order godunov
	}
	else if(sim_order==2){
		soln_PLM(dt,d); // 2nd order PLM
	}
	
	return;
}
