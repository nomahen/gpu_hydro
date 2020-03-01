#include "decs.h"

void sim_initBlock()
{
    float arho = 0.2, frho = 5.0;
    int i,j,k;

    CLOOP(gr_i0,gr_imax,gr_j0,gr_jmax,gr_k0,gr_kmax){
        if (gr_xCoord[i][j][k] < sim_shockLocL) {
            gr_V[i][j][k][DENS_VAR] = sim_densL;
            gr_V[i][j][k][VELX_VAR] = sim_velxL;
            gr_V[i][j][k][VELY_VAR] = 0.0;
            gr_V[i][j][k][VELZ_VAR] = 0.0;
            gr_V[i][j][k][PRES_VAR] = sim_presL;
        }
        else {
            gr_V[i][j][k][DENS_VAR] = 1.0 + arho*sin(frho*gr_xCoord[i]);
            gr_V[i][j][k][VELX_VAR] = sim_velxR;
            gr_V[i][j][k][VELY_VAR] = 0.0;
            gr_V[i][j][k][VELZ_VAR] = 0.0;
            gr_V[i][j][k][PRES_VAR] = sim_presR;
        }

        gr_V[i][j][k][GAMC_VAR] = sim_gamma;
        gr_V[i][j][k][GAME_VAR] = sim_gamma;
        gr_V[i][j][k][EINT_VAR] = gr_V[i][j][k][PRES_VAR]/(gr_V[i][j][k][GAME_VAR]-1.);
    }

    CLOOP(gr_i0,gr_imax,gr_j0,gr_jmax,gr_k0,gr_kmax){
        prim2cons(gr_V[i][j][k], gr_U[i][j][k]);
    }
}
