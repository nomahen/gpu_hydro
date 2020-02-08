#include "decs.h"

void bc_apply()
{
	if(sim_bcType=='outflow'){
		bc_outflow(gr_V);
	}
	else if(sim_bcType=='reflect'){
	}
	else if(sim_bcType=='periodic'){
	}
	else if(sim_bcType=='user'){
	}

	return;
}

void bc_outflow(double *V)
{
	/* Apply ouflow boundary conditions here */
	return;
}
