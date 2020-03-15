#include "decs.h"

void cfl(float *dt)
{
	float	maxSpeed, lambda, cs;
	int i,j,k;

    maxSpeed = -100.0;
    CLOOP(gr_ibegx,gr_iendx,gr_ibegy,gr_iendy,gr_ibegz,gr_iendz){
	    cs = sqrt(gr_V[index_3d(i,j,k)][GAMC_VAR] * gr_V[index_3d(i,j,k)][PRES_VAR] / gr_V[index_3d(i,j,k)][DENS_VAR]);
	    lambda=fmax(fmax((fabs(gr_V[index_3d(i,j,k)][VELX_VAR]) + cs)/gr_dx,
			     (fabs(gr_V[index_3d(i,j,k)][VELY_VAR]) + cs)/gr_dy),
			     (fabs(gr_V[index_3d(i,j,k)][VELZ_VAR]) + cs)/gr_dz);
            maxSpeed=fmax(maxSpeed,lambda);
    }

    *dt = sim_cfl/maxSpeed;
	return;
}
