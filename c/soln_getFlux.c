#include "decs.h"

void soln_getFlux()
{
    /*
     flux solver:
     1 == hll
     2 == hllc
     3 == roe
     */
	if(sim_riemann==1){
		for(int i=gr_ibeg;i<=gr_iend+1;i++){
            hll(gr_vR[i-1], gr_vL[i], gr_flux[i]);
        }
	}
	else if(sim_riemann==2){
	}
	else if(sim_riemann==3){
	}

	return;
}
