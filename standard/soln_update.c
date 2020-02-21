#include "decs.h"

void soln_update(float dt)
{
	float	dtx = dt / gr_dx;

	/* Update conservative variables here */
    for(int i = gr_ibeg; i <= gr_iend; i++) {
        prim2cons(gr_V[i], gr_U[i]);

        for(int k = DENS_VAR; k <= ENER_VAR; k++) {
            gr_U[i][k] = gr_U[i][k] - dtx * (gr_flux[i+1][k] - gr_flux[i][k]);
        }
    }

	/* Get updated primitive variables from updated conservative variables here */
    for(int i = gr_ibeg; i <= gr_iend; i++) {
        cons2prim(gr_U[i], gr_V[i]);
    }

	return;
}
