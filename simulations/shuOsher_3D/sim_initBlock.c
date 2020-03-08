#include "decs.h"

void sim_initBlock()
{
    float arho = 0.2, frho = 5.0;
    int i,j,k;

    CLOOP(gr_i0,gr_imaxx,gr_i0,gr_imaxy,gr_i0,gr_imaxz){
        if (gr_xCoord[i] < sim_shockLocL) {
            gr_V[index_3d(i,j,k)][DENS_VAR] = sim_densL;
            gr_V[index_3d(i,j,k)][VELX_VAR] = sim_velxL;
            gr_V[index_3d(i,j,k)][VELY_VAR] = 0.0;
            gr_V[index_3d(i,j,k)][VELZ_VAR] = 0.0;
            gr_V[index_3d(i,j,k)][PRES_VAR] = sim_presL;
        }
        else {
            gr_V[index_3d(i,j,k)][DENS_VAR] = 1.0 + arho*sin(frho*gr_xCoord[i]);
            gr_V[index_3d(i,j,k)][VELX_VAR] = sim_velxR;
            gr_V[index_3d(i,j,k)][VELY_VAR] = 0.0;
            gr_V[index_3d(i,j,k)][VELZ_VAR] = 0.0;
            gr_V[index_3d(i,j,k)][PRES_VAR] = sim_presR;
        }

        gr_V[index_3d(i,j,k)][GAMC_VAR] = sim_gamma;
        gr_V[index_3d(i,j,k)][GAME_VAR] = sim_gamma;
        gr_V[index_3d(i,j,k)][EINT_VAR] = gr_V[index_3d(i,j,k)][PRES_VAR]/(gr_V[index_3d(i,j,k)][GAME_VAR]-1.);
    }

    CLOOP(gr_i0,gr_imaxx,gr_i0,gr_imaxy,gr_i0,gr_imaxz){
        prim2cons(gr_V[index_3d(i,j,k)], gr_U[index_3d(i,j,k)],0);
        prim2cons(gr_V[index_3d(i,j,k)], gr_U[index_3d(i,j,k)],1);
        prim2cons(gr_V[index_3d(i,j,k)], gr_U[index_3d(i,j,k)],2);
    }
}
