#include "decs.h"

void cfl(float *dt)
{
	float	maxSpeed, lambda, cs;

    maxSpeed = -100.0;
    for (int i = gr_ibeg; i < gr_iend; i++) {
        cs = sqrt(gr_V[i][GAMC_VAR] * gr_V[i][PRES_VAR] / gr_V[i][DENS_VAR]);
        lambda=fabs(gr_V[i][VELX_VAR]) + cs;
        maxSpeed=fmax(maxSpeed,lambda);
    }

    *dt = sim_cfl*gr_dx/maxSpeed;
	return;
}
