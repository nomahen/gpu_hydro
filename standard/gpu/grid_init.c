#include "decs.h"
#include "sim_params.h"
#include "gpu_decs.h"
#include "gpu_params.h"

void grid_init()
{
    int i,j,k;

    // Initialize grid parameters. 
    gr_nx =     NX;
    gr_ny =     NY;
    gr_nz =     NZ;
    // Only allocate guard cells for not trivial dimensions
    gr_ngcx =    (NX>1)*NGC;
    gr_ngcy =    (NY>1)*NGC;
    gr_ngcz =    (NZ>1)*NGC;
    gr_xbeg =   XMIN;
    gr_xend =   XMAX;
    gr_ybeg =   YMIN;
    gr_yend =   YMAX;
    gr_zbeg =   ZMIN;
    gr_zend =   ZMAX;

    // Allocation of the arrays
    gr_xCoord = (float(*)) calloc(gr_nx+2*gr_ngcx, sizeof(float));
    gr_yCoord = (float(*)) calloc(gr_ny+2*gr_ngcy, sizeof(float));
    gr_zCoord = (float(*)) calloc(gr_nz+2*gr_ngcz, sizeof(float));

    // the first and the last interior cell index
    gr_ibegx = gr_ngcx;
    gr_ibegy = gr_ngcy;
    gr_ibegz = gr_ngcz;
    gr_iendx = gr_ngcx + gr_nx - 1;
    gr_iendy = gr_ngcy + gr_ny - 1;
    gr_iendz = gr_ngcz + gr_nz - 1;

    // the min and max of the entire cell index
    gr_i0   = 0;
    gr_imaxx = 2*gr_ngcx + gr_nx - 1;
    gr_imaxy = 2*gr_ngcy + gr_ny - 1;
    gr_imaxz = 2*gr_ngcz + gr_nz - 1;

    // grid delta
    gr_dx = (gr_xend - gr_xbeg)/gr_nx;
    gr_dy = (gr_yend - gr_ybeg)/gr_ny;
    gr_dz = (gr_zend - gr_zbeg)/gr_nz;


    // generate x-coordinate
    for(i = gr_i0; i <= gr_imaxx; i++) {
        gr_xCoord[i] = gr_xbeg + ((float)(i-gr_ngcx+1)-0.5)*gr_dx;
    }

    // generate y-coordinate
    for(j = gr_i0; j <= gr_imaxy; j++) {
        gr_yCoord[j] = gr_ybeg + ((float)(j-gr_ngcy+1)-0.5)*gr_dy;
    }

    // generate z-coordinate
    for(k = gr_i0; k <= gr_imaxz; k++) {
        gr_zCoord[k] = gr_zbeg + ((float)(k-gr_ngcz+1)-0.5)*gr_dz;
    }

    // allocate grid variables
    gr_U = (float(*) [NSYS_VAR]) calloc((gr_imaxx+1)*(gr_imaxy + 1)*(gr_imaxz + 1),sizeof(float[NSYS_VAR]));
    gr_V = (float(*) [NUMB_VAR]) calloc((gr_imaxx+1)*(gr_imaxy + 1)*(gr_imaxz + 1),sizeof(float[NUMB_VAR]));
    gr_W = (float(*) [NSYS_VAR]) calloc((gr_imaxx+1)*(gr_imaxy + 1)*(gr_imaxz + 1),sizeof(float[NSYS_VAR]));

    // allocate grid Riemann states
    gr_vL = (float(*) [NUMB_VAR]) calloc((gr_imaxx+1)*(gr_imaxy + 1)*(gr_imaxz + 1),sizeof(float[NUMB_VAR]));
    gr_vR = (float(*) [NUMB_VAR]) calloc((gr_imaxx+1)*(gr_imaxy + 1)*(gr_imaxz + 1),sizeof(float[NUMB_VAR]));

    // allocate grid fluxes
    gr_flux = (float(*) [NSYS_VAR]) calloc((gr_imaxx+1)*(gr_imaxy + 1)*(gr_imaxz + 1),sizeof(float[NSYS_VAR]));

    // allocate grid eigensystem
    gr_eigval = (float(*) [NUMB_WAVE]) calloc((gr_imaxx+1)*(gr_imaxy + 1)*(gr_imaxz + 1),sizeof(float[NUMB_WAVE]));
    gr_leigvc = (float(*) [NSYS_VAR*NUMB_WAVE]) calloc((gr_imaxx+1)*(gr_imaxy + 1)*(gr_imaxz + 1),sizeof(float[NSYS_VAR*NUMB_WAVE]));
    gr_reigvc = (float(*) [NSYS_VAR*NUMB_WAVE]) calloc((gr_imaxx+1)*(gr_imaxy + 1)*(gr_imaxz + 1),sizeof(float[NSYS_VAR*NUMB_WAVE]));

    /* gpu variables */

    // Blocks in each dimension
    gr_nbx = NBX;
    gr_nby = NBY;
    gr_nbz = NBZ;

    // Threads per block
    gr_nt  = NT;

    // (Temporary) only allow certain dimensions
    if ((gr_nx % gr_nbx) != 0 || (gr_ny % gr_nby) != 0 || (gr_nz % gr_nbz) != 0 || ((gr_nx*gr_ny*gr_nz)/(gr_nbx*gr_nby*gr_nbz) % gr_nt) != 0){
	printf("Oh no! Fix your god damn dimensions! This wont work!\n");
	}
    
    return;
}
