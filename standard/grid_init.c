#include "decs.h"
#include "sim_params.h"

void grid_init()
{
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
    gr_xCoord = (float(*)) calloc(gr_nx+2*gr_ngc, sizeof(float));

    // the first and the last interior cell index
    gr_ibeg = gr_ngc;
    gr_iend = gr_ngc + gr_nx - 1;

    // the min and max of the entire cell index
    gr_i0   = 0;
    gr_imax = 2*gr_ngc + gr_nx - 1;

    // grid delta
    gr_dx = (gr_xend - gr_xbeg)/gr_nx;


    // generate x-coordinate
    for(int i = gr_i0; i <= gr_imax; i++) {
        gr_xCoord[i] = gr_xbeg + ((float)(i-gr_ngc+1)-0.5)*gr_dx;
    }

    // allocate grid variables
    gr_U = (float(*) [NSYS_VAR]) calloc(gr_imax+1,sizeof(float[NSYS_VAR]));
    gr_V = (float(*) [NUMB_VAR]) calloc(gr_imax+1,sizeof(float[NUMB_VAR]));
    gr_W = (float(*) [NSYS_VAR]) calloc(gr_imax+1,sizeof(float[NSYS_VAR]));

    // allocate grid Riemann states
    gr_vL = (float(*) [NUMB_VAR]) calloc(gr_imax+1,sizeof(float[NUMB_VAR]));
    gr_vR = (float(*) [NUMB_VAR]) calloc(gr_imax+1,sizeof(float[NUMB_VAR]));

    // allocate grid fluxes
    gr_flux = (float(*) [NSYS_VAR]) calloc(gr_imax+1,sizeof(float[NSYS_VAR]));

    // allocate grid eigensystem
    gr_eigval = (float(*) [NUMB_WAVE]) calloc(gr_imax+1,sizeof(float[NUMB_WAVE]));
    gr_leigvc = (float(*) [NSYS_VAR*NUMB_WAVE]) calloc(gr_imax+1,sizeof(float[NSYS_VAR*NUMB_WAVE]));
    gr_reigvc = (float(*) [NSYS_VAR*NUMB_WAVE]) calloc(gr_imax+1,sizeof(float[NSYS_VAR*NUMB_WAVE]));

    return;
}
