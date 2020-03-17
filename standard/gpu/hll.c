#include "decs.h"

__device__ void hll(float *vL, float *vR, float *Flux, int d)
{
	float FL[NSYS_VAR], FR[NSYS_VAR], uL[NSYS_VAR], uR[NSYS_VAR];
	float sL,sR,aL,aR;

	// Calculate flux + conservative variables
  	prim2flux(vL,FL,d);
  	prim2flux(vR,FR,d);
  	prim2cons(vL,uL,d);
  	prim2cons(vR,uR,d);

    // left and right sound speed a
    aL = sqrt(vL[GAMC_VAR]*vL[PRES_VAR]/vL[DENS_VAR]);
    aR = sqrt(vR[GAMC_VAR]*vR[PRES_VAR]/vR[DENS_VAR]);

    // fastest left and right going velocities
    sL = fmin(vL[VELX_VAR + d] - aL, vR[VELX_VAR + d] - aR);
    sR = fmax(vL[VELX_VAR + d] + aL, vR[VELX_VAR + d] + aR);

    // numerical flux
    if (sL >= 0.) {
        for(int k = DENS_VAR; k <= ENER_VAR; k++) {
            Flux[k] = FL[k];
        }
    }

    else if (sL < 0. && sR >= 0.) {
        for(int k = DENS_VAR; k <= ENER_VAR; k++) {
            Flux[k] = (sR*FL[k]-sL*FR[k]+sR*sL*(uR[k]-uL[k]))/(sR-sL);
        }
    }

    else {
        for(int k = DENS_VAR; k <= ENER_VAR; k++) {
            Flux[k] = FR[k];
        }
    }

	return;
}
