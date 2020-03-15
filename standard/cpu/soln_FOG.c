#include "decs.h"

void soln_FOG()
{
    int i,j,k;
    int iext=1,jext=1,kext=1;

    // If dimension is trivial, don't try to get interface of guard cells
    if(gr_ngcx == 0)iext=0;
    if(gr_ngcy == 0)jext=0;
    if(gr_ngcz == 0)kext=0;

    CLOOP(gr_ibegx-iext,gr_iendx+iext,gr_ibegy-jext,gr_iendy+jext,gr_ibegz-kext,gr_iendz+kext){
        for (int m = DENS_VAR; m < NUMB_VAR; m++) {
            gr_vL[index_3d(i,j,k)][m] = gr_V[index_3d(i,j,k)][m];
            gr_vR[index_3d(i,j,k)][m] = gr_V[index_3d(i,j,k)][m];
	    }
        }

	return;
}
