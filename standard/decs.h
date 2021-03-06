#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "config.h"
#include "sim_decs.h"

/////////////////////////////////////////////
/* define all externals that are in defs.h */
/////////////////////////////////////////////

/* Simulation Data */

// numerics
extern float	sim_cfl, sim_tmax ;
extern int	    sim_order, sim_nStep ;
extern int	    sim_charLimiting ;

// misc hydro conditions
extern float	sim_gamma ;
extern float	sim_smallPres ;

// boundary conditions, flux solver
extern int      sim_bcType, sim_riemann;

// input/output
extern int	    sim_ioNfreq ;
extern float	sim_ioTfreq ;

/* Grid Data */
extern float	*gr_xCoord, *gr_yCoord, *gr_zCoord;
extern float	gr_xbeg,gr_xend,gr_dx ;
extern float	gr_ybeg,gr_yend,gr_dy ;
extern float	gr_zbeg,gr_zend,gr_dz ;
extern int	gr_ibegx,gr_iendx,gr_imaxx,gr_ngcx,gr_nx ;
extern int	gr_ibegy,gr_iendy,gr_imaxy,gr_ngcy,gr_ny ;
extern int	gr_ibegz,gr_iendz,gr_imaxz,gr_ngcz,gr_nz ;
extern int gr_i0; // initial index will be 0 regardless of dimension

extern float	(*gr_U)[NSYS_VAR]; // conservative variables
extern float	(*gr_V)[NUMB_VAR]; // primitive variables
extern float	(*gr_W)[NSYS_VAR]; // characteristic variables

extern float	(*gr_vL)[NUMB_VAR]; // left Riemann states
extern float	(*gr_vR)[NUMB_VAR]; // right Riemann states
extern float	(*gr_flux)[NSYS_VAR]; // fluxes

extern float    (*gr_eigval)[NUMB_WAVE]; // eigenvalues
extern float    (*gr_reigvc)[NUMB_WAVE*NSYS_VAR]; // right eigenvectors
extern float    (*gr_leigvc)[NUMB_WAVE*NSYS_VAR]; // left eigenvectors


///////////////////////////
/* FUNCTION DECLARATIONS */
///////////////////////////

void sim_init() ; // Initializes simulation variables, reads in from parameter file
void sim_initBlock() ; // Initializes computational domain
void grid_init() ; // Initializes grid variables
void cfl(float *dt) ; // Calculates CFL condition and updates timestep dt
void soln_ReconEvolveAvg(float dt, int d) ; // Calls data reconstruction and Riemann solver routines
void soln_reconstruct(float dt, int d) ; // Call different data recon. routines depending on desired order
void soln_FOG() ; // Call first order Godunov data reconstruction
void soln_PLM(float dt,int d) ; // Call piecewise linear data reconstruction
void vanLeer(float a, float b, float *delta) ; // Call van Leer slope limiter
void soln_getFlux(int d) ;	// Call desired Riemann solver
void hll(float *vL, float *vR, float *Flux, int d) ; // HLL Riemann solver
void prim2cons(float *V, float *U, int d) ; // Calculate conservative variables from primitive variables
void cons2prim(float *U, float *V, int d) ; // Calculate primitive variables from conservative variables
void prim2flux(float *V, float *Flux, int d) ; // Calculate fluxes from primitive variables
void soln_update(float dt) ; // Updates all grid variables at the given timestep
void soln_update_split(float dt, int d) ; // Updates all grid variables at the given timestep
void bc_apply() ; // Calls different boundary conditions
void bc_outflow(float (*V)[NUMB_VAR]) ; // Apply outflow boundary conditions
void grid_finalize() ; // For finalizing and deallocating memory
void io_writeOutput(int ioCounter, float t) ; // For writing output files
int  index_3d(int i, int j, int k) ; // Get i,j,k index inside loop over all cell elements
float dot_product(float *a, float *b, int length) ; // Return dot product of arrays a and b of length length
void eigenvalues(float *V, float *lambda, int d) ; // Get eigenvalues for PLM data reconstruction
void right_eigenvectors(float *V, float (*reig)[NSYS_VAR], int d) ; // Get right eigenvectors for PLM data reconstruction
void left_eigenvectors(float *V, float (*leig)[NSYS_VAR], int d) ; // Get left eigenvectors for PLM data reconstruction
