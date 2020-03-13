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
    sim_nu = NU;
    sim_p_0_prime = 3.0 * (GAMMA - 1.0) * 1.0 / ( (NU + 1.0) * M_PI * pow(SHOCKLOC, NU) );
    sim_p_0 = PRES_FLOOR;
    sim_shockLoc = SHOCKLOC;

    // Call simulation init block
    sim_initBlock();

}
