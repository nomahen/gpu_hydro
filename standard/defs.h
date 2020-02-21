/* Simulation Data */
/* defs.h defines all simulation variables used in every simulation.
 * For simulation-specific variable definitions, use sim_defs.h. */

// numerics
float	sim_cfl, sim_tmax ;
int	    sim_order, sim_nStep ;
int	    sim_charLimiting ;

// misc hydro conditions
float	sim_gamma ;
float	sim_smallPres ;

// boundary conditions, flux solver
int     sim_bcType, sim_riemann;

// input/output
int	    sim_ioNfreq ;
float	sim_ioTfreq ;

/* Grid Data */
float	*gr_xCoord ;
float	gr_xbeg,gr_xend,gr_dx ;
int	    gr_i0,gr_ibeg,gr_iend,gr_imax,gr_ngc,gr_nx ;

float	(*gr_U)[NSYS_VAR] ; // conservative variables
float	(*gr_V)[NUMB_VAR] ; // primitive variables
float	(*gr_W)[NSYS_VAR] ; // characteristic variables

float	(*gr_vL)[NUMB_VAR] ; // left Riemann states
float	(*gr_vR)[NUMB_VAR] ; // right Riemann states
float	(*gr_flux)[NSYS_VAR] ; // fluxes

float (*gr_eigval)[NUMB_WAVE]; // eigenvalues
float (*gr_reigvc)[NUMB_WAVE*NSYS_VAR] ; // right eigenvectors
float (*gr_leigvc)[NUMB_WAVE*NSYS_VAR]; // left eigenvectors
