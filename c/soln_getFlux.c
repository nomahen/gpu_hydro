#include "decs.h"

void soln_getFlux()
{
	if(sim_riemann=="hll"){ 
		for(int i=gr_ibeg;i<gr_iend;i++){
			hll(gr_vR(DENS_VAR:GAME_VAR,i-1),
			    gr_vL(DENS_VAR:GAME_VAR,i),
			    &gr_flux(DENS_VAR:ENER_VAR,i))
			}
	}
	else if(sim_riemann=="hllc"){
	}
	else if(sim_riemann=="roe"){
	}
	
	return;
}
