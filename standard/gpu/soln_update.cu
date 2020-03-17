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

__device__ void soln_update_split(float dt, int d, float *dr_V, float *dr_flux)
{
	int id=0,jd=0,kd=0;
	int i,j,k;
	float dx;
    float dr_U[NSYS_VAR];

	// Check which direction we're updating for
	if(d==0){
        if (gr_ngcx == 0) return;
		id=1;
		dx = gr_dx;
	}
	else if(d==1){
        if (gr_ngcy == 0) return;
		jd=1;
		dx = gr_dy;
	}
	else if(d==2){
        if (gr_ngcz == 0) return;
		kd=1;
		dx = gr_dz;
	}

	float dtx = dt / dx;

    CLOOP(gr_ibegx,gr_iendx,gr_ibegy,gr_iendy,gr_ibegz,gr_iendz){
        uint index_3d_GPU = NUMB_VAR * (i * (NY/NBY + 2 * gr_ngcy) * (NZ/NBZ + 2 * gr_ngcz) + j * (NZ/NBZ + 2 * gr_ngcz) + k) + m;
        uint index_3d_GPU_R = NUMB_VAR * ((i+id) * (NY/NBY + 2 * gr_ngcy) * (NZ/NBZ + 2 * gr_ngcz) + (j+jd) * (NZ/NBZ + 2 * gr_ngcz) + k+kd) + m;

	    prim2cons(&dr_V[index_3d_GPU], dr_U, d);

        for(int m = DENS_VAR; m <= ENER_VAR; m++){
            dr_U[m] = dr_U[m] - dtx * (dr_flux[index_3d_GPU_R] - dr_flux[index_3d_GPU]);

            cons2prim(dr_U[m], &dr_V[index_3d_GPU], d);
        }
	}
}
