#include "decs.h"

void soln_getFlux(int d)
{
	int id=0,jd=0,kd=0;
	int i,j,k;
        int iext=1,jext=1,kext=1;

	// Set index for which direction we're using a Riemann solver
	if((d==0) && (gr_ngcx != 0))id=1;
	else if((d==1) && (gr_ngcy != 0))jd=1;
	else if((d==2) && (gr_ngcz != 0))kd=1;

	// If dimension is trivial, don't try to get interface of guard cells
	if(gr_ngcx == 0)iext=0;
	if(gr_ngcy == 0)jext=0;
	if(gr_ngcz == 0)kext=0;
    /*
     flux solver:
     1 == hll
     2 == hllc
     3 == roe
     */
	if(sim_riemann==1){
	    CLOOP(gr_ibegx,gr_iendx+iext,gr_ibegy,gr_iendy+jext,gr_ibegz,gr_iendz+kext){
                hll(gr_vR[index_3d(i-id,j-jd,k-kd)], gr_vL[index_3d(i,j,k)], gr_flux[index_3d(i,j,k)], d);
            }
	}
	else if(sim_riemann==2){
	}
	else if(sim_riemann==3){
	}

	return;
}
