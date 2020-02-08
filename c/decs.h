
! slope limiters
#define MINMOD  0
#define MC      1
#define VANLEER 2

! Riemann solvers
#define HLL     0
#define ROE     1

! primitive vars
#define DENS_VAR 0
#define VELX_VAR 1
#define PRES_VAR 2
#define EINT_VAR 3
#define GAMC_VAR 4
#define GAME_VAR 5
#define NUMB_VAR 6
#define NSYS_VAR 3 /* total number of equations of the conservative system */

! conservative vars
#define MOMX_VAR 2
#define ENER_VAR 3

! waves
#define SHOCKLEFT 0
#define CTENTROPY 1
#define SHOCKRGHT 2
#define NUMB_WAVE 3

! setup parameters
#define MAX_STRING_LENGTH 80

! BC
#define OUTFLOW  0
#define PERIODIC 1
#define REFLECT  2
#define USER     3


/////////////////////////////////////////////
/* define all externals that are in defs.h */
/////////////////////////////////////////////

/* Simulation Data */

// numerics
extern double	sim_cfl, sim_tmax ;
extern int	sim_order, sim_nStep ;
extern char	sim_name[MAX_STRING_LENGTH], sim_limiter[MAX_STRING_LENGTH], sim_riemann[MAX_STRING_LENGTH] ;
extern bool	sim_charLimiting ;

// initial conditions
extern double	sim_gamma ;
extern double	sim_densL,sim_velxL,sim_presL ;
extern double	sim_densR,sim_velxR,sim_presR ;
extern double	sim_densM,sim_velxM,sim_presM ;
extern double	sim_shockLocL, sim_shockLocR ;
extern double	sim_smallPres ;

// boundary conditions
extern char	sim_bcType[MAX_STRING_LENGTH] ;

// input/output
extern int	sim_ioNfreq ;
extern double	sim_ioTfreq ;

/* Grid Data */
extern double	*gr_xCoord ;
extern double	gr_xbeg,gr_xend,gr_dx ;
extern int	gr_i0,gr_ibeg,gr_iend,gr_imax,gr_ngc,gr_nx ;

extern double	*gr_U ; // conservative variables
extern double	*gr_V ; // primitive variables
extern double	*gr_W ; // characteristic variables

extern double	*gr_vL ; // left Riemann states
extern double	*gr_vR ; // right Riemann states
extern double	*gr_flux ; // fluxes

extern double *gr_eigval ; // eigenvalues
extern double *gr_reigvc ; // right eigenvectors
extern double *gr_leigvc ; // left eigenvectors


///////////////////////////
/* FUNCTION DECLARATIONS */
///////////////////////////

void sim_init() ; // Initializes simulation variables, reads in from parameter file
void sim_initBlock() ; // Initializes computational domain
void grid_init() ; // Initializes grid variables
void cfl(double *dt) ; // Calculates CFL condition and updates timestep dt
void soln_ReconEvolveAvg(double dt) ; // Calls data reconstruction and Riemann solver routines
void soln_reconstruct(double dt) ; // Call different data recon. routines depending on desired order
void soln_FOG() ; // Call first order Godunov data reconstruction
void soln_getFlux() ;	// Call desired Riemann solver
void hll(double *vL, double *vR, double *Flux) ; // HLL Riemann solver 
void prim2cons(*V,*U) ; // Calculate conservative variables from primitive variables
void prim2cons(*U,*V) ; // Calculate primitive variables from conservative variables
void prim2flux(*V,*Flux) ; // Calculate fluxes from primitive variables
void soln_update(double dt) ; // Updates all grid variables at the given timestep
void bc_apply() ; // Calls different boundary conditions
void bc_outflow(double *V) ; // Apply outflow boundary conditions
void grid_finalize() ; // For finalizing and deallocating memory
