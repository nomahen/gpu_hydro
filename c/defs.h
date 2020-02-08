/* Simulation Data */

// numerics
double	sim_cfl, sim_tmax ;
int	sim_order, sim_nStep ;
char	sim_name[MAX_STRING_LENGTH], sim_limiter[MAX_STRING_LENGTH], sim_riemann[MAX_STRING_LENGTH] ;
bool	sim_charLimiting ;

// initial conditions
double	sim_gamma ;
double	sim_densL,sim_velxL,sim_presL ;
double	sim_densR,sim_velxR,sim_presR ;
double	sim_densM,sim_velxM,sim_presM ;
double	sim_shockLocL, sim_shockLocR ;
double	sim_smallPres ;

// boundary conditions
char	sim_bcType[MAX_STRING_LENGTH] ;

// input/output
int	sim_ioNfreq ;
double	sim_ioTfreq ;

/* Grid Data */
double	*gr_xCoord ;
double	gr_xbeg,gr_xend,gr_dx ;
int	gr_i0,gr_ibeg,gr_iend,gr_imax,gr_ngc,gr_nx ;

double	*gr_U ; // conservative variables
double	*gr_V ; // primitive variables
double	*gr_W ; // characteristic variables

double	*gr_vL ; // left Riemann states
double	*gr_vR ; // right Riemann states
double	*gr_flux ; // fluxes

double *gr_eigval ; // eigenvalues
double *gr_reigvc ; // right eigenvectors
double *gr_leigvc ; // left eigenvectors
