#include "decs.h"

void prim2cons(float *V, float *U, int d)
{
	float	ekin, eint;

	/* Calculate conservative variables from primitive variables here */
    U[DENS_VAR] = V[DENS_VAR];
    U[MOMX_VAR + d] = V[DENS_VAR] * V[VELX_VAR + d];
    
    ekin = 0.5 * V[DENS_VAR] * V[VELX_VAR + d] * V[VELX_VAR + d];
    eint = V[PRES_VAR]/(V[GAME_VAR]-1.);
    U[ENER_VAR] = ekin + eint;
    
	return;
}

void cons2prim(float *U, float *V, int d)
{
	float	ekin, eint, pres;

	/* Calculate primitive variables from conservative variables here */
    V[DENS_VAR] = U[DENS_VAR];
    V[VELX_VAR + d] = U[MOMX_VAR + d]/U[DENS_VAR];
    ekin = 0.5*V[VELX_VAR + d]*V[VELX_VAR + d]*V[DENS_VAR];
    eint = fmax(U[ENER_VAR] - ekin, sim_smallPres); // eint=rho*e
    eint = eint/U[DENS_VAR];
    // get pressure by calling eos
    // call eos_cell(U(DENS_VAR),eint,sim_gamma,pres)
    pres = fmax((sim_gamma-1.)*V[DENS_VAR]*eint,sim_smallPres);
    V[PRES_VAR] = pres;
    V[EINT_VAR] = eint*U[DENS_VAR];
    V[GAMC_VAR] = sim_gamma;
    V[GAME_VAR] = sim_gamma;

	return;
}

void prim2flux(float *V, float *Flux, int d)
{
	float	ekin, eint, ener;

	/* Calculate fluxes from primitive variables here */
    Flux[DENS_VAR] = V[DENS_VAR]*V[VELX_VAR + d];
    Flux[MOMX_VAR + d] = Flux[DENS_VAR]*V[VELX_VAR + d] + V[PRES_VAR];
    ekin = 0.5*V[VELX_VAR + d]*V[VELX_VAR + d]*V[DENS_VAR];
    eint = V[PRES_VAR]/(V[GAME_VAR]-1.);
    ener = ekin + eint;
    Flux[ENER_VAR] = V[VELX_VAR + d]*(ener + V[PRES_VAR]);
    
	return;
}
