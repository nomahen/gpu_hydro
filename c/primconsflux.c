#include "decs.h"

void prim2cons(float *V, float *U)
{
	float	ekin, eint;

	/* Calculate conservative variables from primitive variables here */
    U[DENS_VAR] = V[DENS_VAR];
    U[MOMX_VAR] = V[DENS_VAR] * V[VELX_VAR];
    
    ekin = 0.5 * V[DENS_VAR] * V[VELX_VAR] * V[VELX_VAR];
    eint = V[PRES_VAR]/(V[GAME_VAR]-1.);
    U[ENER_VAR] = ekin + eint;
    
	return;
}

void cons2prim(float *U, float *V)
{
	float	ekin, eint, pres;

	/* Calculate primitive variables from conservative variables here */
    V[DENS_VAR] = U[DENS_VAR];
    V[VELX_VAR] = U[MOMX_VAR]/U[DENS_VAR];
    ekin = 0.5 * V[DENS_VAR] * V[VELX_VAR] * V[VELX_VAR];
    eint = fmax(U[ENER_VAR] - ekin, sim_smallPres); // eint=rho*e
    eint = eint/U[DENS_VAR];
    // get pressure by calling eos
    // call eos_cell(U(DENS_VAR),eint,sim_gamma,pres)
    V[PRES_VAR] = pres;
    V[EINT_VAR] = eint*U[DENS_VAR];
    V[GAMC_VAR] = sim_gamma;
    V[GAME_VAR] = sim_gamma;

	return;
}

void prim2flux(float *V, float *Flux)
{
	float	ekin, eint, ener;

	/* Calculate fluxes from primitive variables here */
    Flux[DENS_VAR] = V[DENS_VAR]*V[VELX_VAR];
    Flux[MOMX_VAR] = Flux[DENS_VAR]*V[VELX_VAR] + V[PRES_VAR];
    ekin = 0.5*V[VELX_VAR]*V[VELX_VAR]*V[DENS_VAR];
    eint = V[PRES_VAR]/(V[GAME_VAR]-1.);
    ener = ekin + eint;
    Flux[ENER_VAR] = V[VELX_VAR]*(ener + V[PRES_VAR]);
    
	return;
}
