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

void bc_outflow(float (*V)[NUMB_VAR])
{
    int i,j,k;

    /* Apply ouflow boundary conditions here */
    // x BC for all y,z
    if(gr_ngcx > 0){
	    CLOOP(gr_i0,gr_ngcx-1,gr_ibegy,gr_iendy,gr_ibegz,gr_iendz){
	    	    for(int m = 0; m < NUMB_VAR; m++) { 
		    	    V[index_3d(i,j,k)][m] = V[index_3d(gr_ibegx,j,k)][m]; 
		    	    V[index_3d(gr_iendx+i+1,j,k)][m] = V[index_3d(gr_iendx,j,k)][m]; 
		    }
	    }
    }

    // y BC for all x,z
    if(gr_ngcy > 0){
	    CLOOP(gr_ibegx,gr_iendx,gr_i0,gr_ngcy-1,gr_ibegz,gr_iendz){
	    	    for(int m = 0; m < NUMB_VAR; m++) { 
		    	    V[index_3d(i,j,k)][m] = V[index_3d(i,gr_ibegy,k)][m]; 
		    	    V[index_3d(i,gr_iendy+j+1,k)][m] = V[index_3d(i,gr_iendy,k)][m]; 
		    }
	    }
    }

    // z BC for all x,y
    if(gr_ngcz > 0){
	    CLOOP(gr_ibegx,gr_iendx,gr_ibegy,gr_iendy,gr_i0,gr_ngcz-1){
	    	    for(int m = 0; m < NUMB_VAR; m++) { 
		    	    V[index_3d(i,j,k)][m] = V[index_3d(i,j,gr_ibegz)][m]; 
		    	    V[index_3d(i,j,gr_iendz+k+1)][m] = V[index_3d(i,j,gr_iendz)][m]; 
		    }
	    }
    }

    return;
}
