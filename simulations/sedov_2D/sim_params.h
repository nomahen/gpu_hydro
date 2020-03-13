/* All user parameters should be set here. */
/* For every variable in sim_defs.h/sim_decs.h, there needs to be a declaration here.
 * Additionally there are some parameters from defs.h/decs.h that should be set here as well:
 * TMAX		::	sim_tmax		[float]
 * NSTEP	::	sim_nStep		[integer]
 * CFL		::	sim_cfl			[float]
 * ORDER	::	sim_order		[integer]
 * GAMMA	::	sim_gamma		[float]
 * MINPRES	::	sim_smallPres		[float]
 * BCTYPE	::	sim_bcType		[integer]
 * RIEMANN	::	sim_riemann		[integer]
 * NX		::	gr_nx			[integer]
 * NGC		::	gr_ngc			[integer]
 * XMIN		::	gr_xbeg			[float]
 * XMAX		::	gr_xend			[float]
 * TFREQ	::	sim_ioTfreq		[float]
 * NFREQ	::	sim_ioNfreq		[integer]
*/


// Standard variables
#define TMAX	(1.8)
#define NSTEP	(100000)
#define CFL	(0.8)
#define ORDER	(1)
#define GAMMA	(1.4)
#define MINPRES	(1.e-12)
#define BCTYPE	(1)
#define RIEMANN	(1)
#define NX	(128)
#define NY	(128)
#define NZ	(1)
#define NGC	(2)
#define XMIN	(-4.5)
#define XMAX	(4.5)
#define YMIN	(-4.5)
#define YMAX	(4.5)
#define ZMIN	(-4.5)
#define ZMAX	(4.5)
#define TFREQ	(0.1)
#define NFREQ	(0.0)

// Simulation-specific variables
#define NU          (2.0)
#define PRES_FLOOR  (1.0e-5)
#define SHOCKLOC    (XMAX - XMIN) / NX * 3.5
