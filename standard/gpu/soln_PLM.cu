#include "decs.h"

void soln_PLM(float dt,int d)
{
    int i,j,k,nVar,kWaveNum;
    int iext=1,jext=1,kext=1;
    int idir=0,jdir=0,kdir=0;
    float dx, lambdaDtDx;
    float lambda[NUMB_WAVE];
    float vecL[NSYS_VAR],vecR[NSYS_VAR],sigL[NSYS_VAR],sigR[NSYS_VAR];
    float delV[NUMB_VAR],delL[NUMB_VAR],delR[NUMB_VAR];
    float delW[NUMB_WAVE];
    float leig[NUMB_WAVE][NSYS_VAR], reig[NUMB_WAVE][NSYS_VAR];

    // If dimension is trivial, don't try to get interface of guard cells
    if(gr_ngcx == 0)iext=0;
    if(gr_ngcy == 0)jext=0;
    if(gr_ngcz == 0)kext=0;

    // Which dimension are we updating right now?
    if(d == 0){
    	idir=1;
    	dx = gr_dx;
    }
    if(d == 1){
    	jdir=1;
    	dx = gr_dy;
    }
    if(d == 2){
    	idir=1;
    	dx = gr_dz;
    }

    // Loop through all cells
    CLOOP(gr_ibegx-iext,gr_iendx+iext,gr_ibegy-jext,gr_iendy+jext,gr_ibegz-kext,gr_iendz+kext){
    	eigenvalues(gr_V[index_3d(i,j,k)],lambda,d);
    	left_eigenvectors(gr_V[index_3d(i,j,k)],leig,d);
    	right_eigenvectors(gr_V[index_3d(i,j,k)],reig,d);

    	// Do primitive limiting (i.e., not characteristic limiting) (what does this even mean?)
    	for (nVar = DENS_VAR; nVar < NSYS_VAR; nVar++){
    	    delL[nVar] = gr_V[index_3d(i,j,k)][nVar] - gr_V[index_3d(i-idir,j-jdir,k-kdir)][nVar];
    	    delR[nVar] = gr_V[index_3d(i+idir,j+jdir,k+kdir)][nVar] - gr_V[index_3d(i,j,k)][nVar];

    	    if(1){ // Later add check for which slope limiter!!
    	        vanLeer(delL[nVar],delR[nVar],&delV[nVar]);
            }
        }

    	for (kWaveNum = 0; kWaveNum < NUMB_WAVE; kWaveNum++){
    	       delW[kWaveNum] = dot_product(leig[kWaveNum],delV,PRES_VAR+1);
        }

        // Zero arrays for flux calculation
        for (nVar = DENS_VAR; nVar < NSYS_VAR; nVar++) {
    	    sigL[nVar] = 0.;
    	    sigR[nVar] = 0.;
    	    vecL[nVar] = 0.;
    	    vecR[nVar] = 0.;
        }

    	// Prepare flux calculation
        for (kWaveNum = 0; kWaveNum < NUMB_WAVE; kWaveNum++){
    	    lambdaDtDx = lambda[kWaveNum]*dt/dx;

    	    for (nVar = DENS_VAR; nVar < NSYS_VAR; nVar++) {

                vecR[nVar] = 0.5*(1.0 - lambdaDtDx)*reig[kWaveNum][nVar]*delW[kWaveNum];
                sigR[nVar] = sigR[nVar] + vecR[nVar];

                vecL[nVar] = 0.5*(-1.0 - lambdaDtDx)*reig[kWaveNum][nVar]*delW[kWaveNum];
                sigL[nVar] = sigL[nVar] + vecL[nVar];
            }
        }

        //  Finalize flux calculation for system of variables
    	for (nVar = DENS_VAR; nVar < NSYS_VAR; nVar++) {
            gr_vL[index_3d(i,j,k)][nVar] = gr_V[index_3d(i,j,k)][nVar] + sigL[nVar];
            gr_vR[index_3d(i,j,k)][nVar] = gr_V[index_3d(i,j,k)][nVar] + sigR[nVar];
        }

        // Just use Godunov for extraneous primitive variables
    	for (nVar = NSYS_VAR; nVar < NUMB_VAR; nVar++) {
            gr_vL[index_3d(i,j,k)][nVar] = gr_V[index_3d(i,j,k)][nVar];
            gr_vR[index_3d(i,j,k)][nVar] = gr_V[index_3d(i,j,k)][nVar];
        }
	}

	return;
}
