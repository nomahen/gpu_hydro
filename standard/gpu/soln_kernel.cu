#include "decs.h"

void init_kernel()
{
    dim3 dimGrid(gr_nbx,gr_nby,gr_nbz);
    dim3 dimBlock(gr_nt);

    AllocatePrimitiveOnDevice();
    CopyPrimitiveToDevice();

    soln_kernel <<< dimGrid, dimBlock >>>;

    CopyPrimitiveToHost();
    DeallocatePrimitiveOnDevice();

    return;
}

void AllocatePrimitiveOnDevice()
{
    int size = sizeof(float)*NUMB_VAR*(gr_nx+2*gr_ngcx)*(gr_ny+2*gr_ngcy)*(gr_nz+2*gr_ngcz);
    cudaMalloc((void**)&dv_V,size);
    cudaMemset(dv_V, 0, size);

    return;
}

void CopyPrimitiveToDevice()
{
    int size = sizeof(float)*NUMB_VAR*(gr_nx+2*gr_ngcx)*(gr_ny+2*gr_ngcy)*(gr_nz+2*gr_ngcz);
    cudaMemcpy(dv_V,gr_V,size,"cudaMemcpyHostToDevice");

    return;
}

void CopyPrimitiveToHost()
{
    int size = sizeof(float)*NUMB_VAR*(gr_nx+2*gr_ngcx)*(gr_ny+2*gr_ngcy)*(gr_nz+2*gr_ngcz);
    cudaMemcpy(gr_V,dv_V,size,"cudaMemcpyDeviceToHost");

    return;
}

void DeallocatePrimitiveOnDevice()
{
    cudaFree(dr_V);
    dr_V = NULL;

    return;
}

__global__ void soln_kernel()
{ 
    int i,j,k,nVar;

    // Allocate tiled primitive variable array in shared memory
    __shared__ sm_V[gr_nx/gr_nbx + 2*gr_ngcx][gr_ny/gr_nby + 2*gr_ngcy][gr_nz/gr_nbz + 2*gr_ngcz][NUMB_VAR];

    /* Copy primitives from global memory to shared memory*/
    // First figure out where cells in full array begin and end
    int gr_ibegx_blk = blockIdx.x*(gr_nx/gr_nbx);
    int gr_ibegy_blk = blockIdx.y*(gr_ny/gr_nby);
    int gr_ibegz_blk = blockIdx.z*(gr_nz/gr_nbz);
    int gr_iendx_blk = gr_ngcx + (blockIdx.x + 1)*(gr_nx/gr_nbx);
    int gr_iendy_blk = gr_ngcy + (blockIdx.x + 1)*(gr_ny/gr_nby);
    int gr_iendz_blk = gr_ngcz + (blockIdx.x + 1)*(gr_nz/gr_nbz);

    // Copy from global to shared memory
    CLOOP(gr_ibegx_blk,gr_iendx_blk,gr_ibegy_blk,gr_iendy_blk,gr_iendz_blk,gr_iendz_blk){
        for(nVar=0;nVar<NUMB_VAR;nVar++){
            sm_V[i][j][k] = dv_V[index_3d(i+gr_ibegx_blk,j+gr_ibegy_blk,k+gr_ibegz_blk)][nVar];
            }
        }    

    /*
    NICK: I have not changed the rest of the kernel!
    */

    // Return timestep from CFL condition
    cfl(&dt);

    // Do data reconstruction and Riemann solvers
    // Dimensionally split method; updates dimensions independently
    for (int d = 0; d < NDIM; d++) { 
	soln_ReconEvolveAvg(dt,d);
	// Update solution across grid for this direction
	soln_update_split(dt,d);
    }

    // Apply boundary conditions
    bc_apply();
}
