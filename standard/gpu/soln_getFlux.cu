#include "decs.h"

__device__ void soln_getFlux(int d, float *dr_V, float *dr_VL, float *dr_VR, float *dr_flux)
{
	int id=0,jd=0,kd=0;
	int i,j,k;
    int iext=1,jext=1,kext=1;

	// Set index for which direction we're using a Riemann solver
	if((d==0) && (gr_ngcx != 0)) id = 1;
	else if((d==1) && (gr_ngcy != 0)) jd = 1;
	else if((d==2) && (gr_ngcz != 0)) kd = 1;

	// If dimension is trivial, don't try to get interface of guard cells
	if(gr_ngcx == 0) iext = 0;
	if(gr_ngcy == 0) jext = 0;
	if(gr_ngcz == 0) kext = 0;

    /*
     flux solver:
     1 == hll
     2 == hllc
     3 == roe
     */
	if(sim_riemann==1){
	    CLOOP(gr_ibegx,gr_iendx+iext,gr_ibegy,gr_iendy+jext,gr_ibegz,gr_iendz+kext){
            uint index_3d_GPU = NUMB_VAR * (i * (NY/NBY + 2 * gr_ngcy) * (NZ/NBZ + 2 * gr_ngcz) + j * (NZ/NBZ + 2 * gr_ngcz) + k);
            uint index_3d_GPU_R = NUMB_VAR * ((i-id) * (NY/NBY + 2 * gr_ngcy) * (NZ/NBZ + 2 * gr_ngcz) + (j-jd) * (NZ/NBZ + 2 * gr_ngcz) + k-kd);

            hll(&gr_vR[index_3d_GPU_R], &gr_vL[index_3d_GPU], &gr_flux[index_3d_GPU], d);
        }
	}
	else if(sim_riemann==2){
	}
	else if(sim_riemann==3){
	}

	return;
}
