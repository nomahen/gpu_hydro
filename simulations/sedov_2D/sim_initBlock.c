#include "decs.h"

void sim_initBlock()
{
    float arho = 1.0;
    float r_cyl;
    int i,j,k;

    CLOOP(gr_i0,gr_imaxx,gr_i0,gr_imaxy,gr_i0,gr_imaxz){

        r_cyl = sqrt(gr_xCoord[i] * gr_xCoord[i] + gr_yCoord[j] * gr_yCoord[j]);

        if (r_cyl < sim_shockLoc) {
            gr_V[index_3d(i,j,k)][PRES_VAR] = sim_p_0_prime;
        }
        else {
            gr_V[index_3d(i,j,k)][PRES_VAR] = sim_p_0;
        }

        gr_V[index_3d(i,j,k)][DENS_VAR] = arho;
        gr_V[index_3d(i,j,k)][VELX_VAR] = 0.0;
        gr_V[index_3d(i,j,k)][VELY_VAR] = 0.0;
        gr_V[index_3d(i,j,k)][VELZ_VAR] = 0.0;
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
