#include "decs.h"

void hll(float *vL, float *vR, float *Flux)
{
	float FL[NSYS_VAR], FR[NSYS_VAR], uL[NSYS_VAR], uR[NSYS_VAR];
	float sL,sR,aL,aR;

	// Calculate flux + conservative variables
  	prim2flux(vL,FL);
  	prim2flux(vR,FR);
  	prim2cons(vL,uL);
  	prim2cons(vR,uR);

    // left and right sound speed a
    aL = sqrt(vL[GAMC_VAR]*vL[PRES_VAR]/vL[DENS_VAR]);
    aR = sqrt(vR[GAMC_VAR]*vR[PRES_VAR]/vR[DENS_VAR]);

    // fastest left and right going velocities
    sL = fmin(vL[VELX_VAR] - aL, vR[VELX_VAR] - aR);
    sR = fmax(vL[VELX_VAR] + aL, vR[VELX_VAR] + aR);

    // numerical flux
    if (sL >= 0.) {
        for(int k = DENS_VAR; k < ENER_VAR+1; k++) {
            Flux[k] = FL[k];
        }
    }

    else if (sL < 0. && sR >= 0.) {
        for(int k = DENS_VAR; k < ENER_VAR+1; k++) {
            Flux[k] = (sR*FL[k]-sL*FR[k]+sR*sL*(uR[k]-uL[k]))/(sR-sL);
        }
    }

    else {
        for(int k = DENS_VAR; k < ENER_VAR+1; k++) {
            Flux[k] = FR[k];
        }
    }

	return;
}
