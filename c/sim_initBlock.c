#include "decs.h" 

void sim_initBlock() 
{
    float arho = 0.2, frho = 5.0;
    
    for(int i = gr_i0; i < gr_imax; i++) {
        if (gr_xCoord[i] < sim_shockLocL) {
            gr_V[i][DENS_VAR] = sim_densL;
            gr_V[i][VELX_VAR] = sim_velxL;
            gr_V[i][PRES_VAR] = sim_presL;
        }
        else {
            gr_V[i][DENS_VAR] = 1.0 + arho*sin(frho*gr_xCoord[i]);
            gr_V[i][VELX_VAR] = sim_velxR;
            gr_V[i][PRES_VAR] = sim_presR;
        }
                    
        gr_V[i][GAMC_VAR] = sim_gamma;
        gr_V[i][GAME_VAR] = sim_gamma;
        gr_V[i][EINT_VAR] = gr_V[i][PRES_VAR]/(gr_V[i][GAME_VAR]-1.);
    }
    
    for(int i = gr_i0; i < gr_imax; i++) {
        prim2cons(gr_V[i], gr_U[i]);
    }
}
