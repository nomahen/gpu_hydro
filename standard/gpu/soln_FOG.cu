#include "decs.h"

__device__ void soln_FOG(float *dr_V, float *dr_VL, float *dr_VR)
{
    int i,j,k;
    int iext=1,jext=1,kext=1;

    // If dimension is trivial, don't try to get interface of guard cells
    if (gr_ngcx == 0) iext = 0;
    if (gr_ngcy == 0) jext = 0;
    if (gr_ngcz == 0) kext = 0;

    CLOOP(gr_ibegx-iext,gr_iendx+iext,gr_ibegy-jext,gr_iendy+jext,gr_ibegz-kext,gr_iendz+kext){
        for (int m = DENS_VAR; m < NUMB_VAR; m++) {
            uint index_3d_GPU = NUMB_VAR * (i * (NY/NBY + 2 * gr_ngcy) * (NZ/NBZ + 2 * gr_ngcz) + j * (NZ/NBZ + 2 * gr_ngcz) + k) + m;
            dr_vL[index_3d_GPU] = dr_V[index_3d_GPU];
            dr_vR[index_3d_GPU] = dr_V[index_3d_GPU];
	    }
    }

	return;
}
