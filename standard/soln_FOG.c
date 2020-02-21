#include "decs.h"

void soln_FOG()
{
    for(int i = gr_ibeg-1; i <= gr_iend+1; i++) {
        for (int k = DENS_VAR; k < NUMB_VAR; k++) {
            gr_vL[i][k] = gr_V[i][k];
            gr_vR[i][k] = gr_V[i][k];
        }
    }

	return;
}
