#include "decs.h"

void sim_init()
{

// To start: we want to put variable declarations from slug.init here, and then do input/output later
    sim_order = 1;
    sim_nStep = 100000;
    sim_cfl = 0.8;
    sim_tmax = 1.8;
    
    /*
     flux solver:
     1 == hll
     2 == hllc
     3 == roe
     */
    sim_riemann = 3;
    
    sim_charLimiting = 1;
    sim_densL = 3.857143;
    sim_velxL = 2.629369;
    sim_presL = 10.3333;
    sim_densR = 1.0;
    sim_velxR = 0.0;
    sim_presR = 1.0;
    // sim_densM = ;
    // sim_velxM = ;
    // sim_presM = ;
    sim_gamma = 1.4;
    sim_shockLocL = -4.0;
    sim_shockLocR = 0.9;
    sim_smallPres = 1.0e-12;
    
    /*
     boundary conditions type
     1 == outflow
     2 == reflective
     3 == periodic
     4 == user
     */
    sim_bcType = 4;
    
    
    sim_ioTfreq = 0.1;
    sim_ioNfreq = 0;

    sim_initBlock();

/*
  call read_initFileInt ('slug.init','sim_order',  sim_order)
  call read_initFileInt ('slug.init','sim_nStep',  sim_nStep)
  call read_initFileReal('slug.init','sim_cfl',    sim_cfl)
  call read_initFileReal('slug.init','sim_tmax',   sim_tmax)

  call read_initFileChar('slug.init','sim_riemann',sim_riemann)
  call read_initFileChar('slug.init','sim_limiter',sim_limiter)
  call read_initFileChar('slug.init','sim_name',sim_name)
  call read_initFileBool('slug.init','sim_charLimiting',sim_charLimiting)

  call read_initFileReal('slug.init','sim_densL',    sim_densL)
  call read_initFileReal('slug.init','sim_velxL',    sim_velxL)
  call read_initFileReal('slug.init','sim_presL',    sim_presL)

  call read_initFileReal('slug.init','sim_densR',    sim_densR)
  call read_initFileReal('slug.init','sim_velxR',    sim_velxR)
  call read_initFileReal('slug.init','sim_presR',    sim_presR)

  call read_initFileReal('slug.init','sim_densM',    sim_densM)
  call read_initFileReal('slug.init','sim_velxM',    sim_velxM)
  call read_initFileReal('slug.init','sim_presM',    sim_presM)

  call read_initFileReal('slug.init','sim_gamma',    sim_gamma)
  call read_initFileReal('slug.init','sim_shockLocL', sim_shockLocL)
  call read_initFileReal('slug.init','sim_shockLocR', sim_shockLocR)

  call read_initFileReal('slug.init','sim_smallPres', sim_smallPres)

  call read_initFileChar('slug.init','sim_bcType',sim_bcType); print*,sim_bcType

  call read_initFileReal('slug.init','sim_ioTfreq',  sim_ioTfreq)
  call read_initFileInt ('slug.init','sim_ioNfreq',  sim_ioNfreq)

  call sim_initBlock()
*/

}
