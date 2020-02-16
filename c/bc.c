#include "decs.h"

void bc_apply()
{
    
    /*
     boundary conditions type
     1 == outflow
     2 == reflective
     3 == periodic
     4 == user
     */
	if(sim_bcType==1){
		bc_outflow(gr_V);
	}
	else if(sim_bcType==2){
	}
	else if(sim_bcType==3){
	}
	else if(sim_bcType==4){
	}

	return;
}

void bc_outflow(float (*V[NUMB_VAR]))
{
	/* Apply ouflow boundary conditions here */
    for(int i = 0; i < gr_ngc; i++) {
        for(int k = 0; k < NUMB_VAR; k++) {
            // on the left GC
            V[i][k] = V[gr_ibeg][k];
            
            // on the right GC
            V[gr_iend+i][k] = V[gr_iend][k];
        }
    }
            
    return;
}
