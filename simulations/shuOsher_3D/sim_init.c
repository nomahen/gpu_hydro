#include "decs.h"
#include "sim_params.h"

void sim_init()
{

    // Initialize standard variables.
    // Should move to its own init.
    sim_order = ORDER;
    sim_nStep = NSTEP;
    sim_cfl = CFL;
    sim_tmax = TMAX;
    sim_riemann = RIEMANN;
    sim_gamma = GAMMA;
    sim_smallPres = MINPRES;
    sim_bcType = BCTYPE;
    sim_ioTfreq = TFREQ;
    sim_ioNfreq = NFREQ;

    // Initialize simulation-specific variables
    sim_densL = DENSL;
    sim_velxL = VELXL;
    sim_presL = PRESL;
    sim_densR = DENSR;
    sim_velxR = VELXR;
    sim_presR = PRESR;
    sim_shockLocL = SHOCKLOCL;
    sim_shockLocR = SHOCKLOCR;

    // Call simulation init block
    sim_initBlock();

}
