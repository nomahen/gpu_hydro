#include "decs.h"

void soln_update(float dt)
{/*
	float	dtx = dt / gr_dx;

	// Update conservative variables here
    for(int i = gr_ibeg; i <= gr_iend; i++) {
        prim2cons(gr_V[i], gr_U[i]);

        for(int k = DENS_VAR; k <= ENER_VAR; k++) {
            gr_U[i][k] = gr_U[i][k] - dtx * (gr_flux[i+1][k] - gr_flux[i][k]);
        }
    }

	// Get updated primitive variables from updated conservative variables here
    for(int i = gr_ibeg; i <= gr_iend; i++) {
        cons2prim(gr_U[i], gr_V[i]);
    }
*/
	return;
}

void soln_update_split(float dt, int d)
{
	int id=0,jd=0,kd=0;
	int i,j,k;
	float dx;

	// Check which direction we're updating for
	if((d==0) && (gr_ngcx != 0)){
		id=1;
		dx = gr_dx;
	}
	else if((d==1) && (gr_ngcy != 0)){
		jd=1;
		dx = gr_dy;
	}
	else if((d==2) && (gr_ngcz != 0)){
		kd=1;
		dx = gr_dz;
	}

	float dtx = dt / dx;
	
	
        CLOOP(gr_ibegx,gr_iendx,gr_ibegy,gr_iendy,gr_ibegz,gr_iendz){
	    prim2cons(gr_V[index_3d(i,j,k)], gr_U[index_3d(i,j,k)]);
	    for(int m = DENS_VAR; m <= ENER_VAR; m++){
	            gr_U[index_3d(i,j,k)][m] = gr_U[index_3d(i,j,k)][m] - dtx * (gr_flux[index_3d(i+id,j+jd,k+kd)][m] - gr_flux[index_3d(i,j,k)][m]);
            cons2prim(gr_U[index_3d(i,j,k)], gr_V[index_3d(i,j,k)]);
	    }
	}


}
