#include "decs.h"

void init_kernel(float *dr_V, float *dr_VL, float *dr_VR, float *dr_flux)
{
    dim3 dimGrid(gr_nbx,gr_nby,gr_nbz);
    dim3 dimBlock(gr_nt,1,1);

    // DANAT: already done before
    // AllocatePrimitiveOnDevice();
    // CopyPrimitiveToDevice();

    cfl_kernel

    soln_kernel <<< dimGrid, dimBlock >>> (dr_V, dr_VL, dr_VR, dr_flux);

    bc_apply_kernel

    // CopyPrimitiveToHost();
    // DeallocatePrimitiveOnDevice();

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

__global__ void soln_kernel(float *dr_V, float *dr_VL, float *dr_VR, float *dr_flux)
{
    int i,j,k,nVar;
    uint n = blockIdx.x * (blockDim.y * blockDim.z) + blockIdx.y * blockDim.z + blockIdx.z;

    // Allocate tiled primitive variable array in shared memory
    // DANAT: GPU version 1: not using shared memory; load everything from global
    // __shared__ sm_V[gr_nx/gr_nbx + 2*gr_ngcx][gr_ny/gr_nby + 2*gr_ngcy][gr_nz/gr_nbz + 2*gr_ngcz][NUMB_VAR];

    /* Copy primitives from global memory to shared memory*/
    // First figure out where cells in full array begin and end
    int gr_ibegx_blk = blockIdx.x * (gr_nx/gr_nbx);
    int gr_ibegy_blk = blockIdx.y * (gr_ny/gr_nby);
    int gr_ibegz_blk = blockIdx.z * (gr_nz/gr_nbz);
    int gr_iendx_blk = gr_ngcx + (blockIdx.x + 1) * (gr_nx/gr_nbx) - 1;
    int gr_iendy_blk = gr_ngcy + (blockIdx.x + 1) * (gr_ny/gr_nby) - 1;
    int gr_iendz_blk = gr_ngcz + (blockIdx.x + 1) * (gr_nz/gr_nbz) - 1;

    // Copy from global to shared memory
    // DANAT: don't forget about filling the guard cells too!
    // CLOOP(gr_ibegx_blk,gr_iendx_blk,gr_ibegy_blk,gr_iendy_blk,gr_iendz_blk,gr_iendz_blk){
    //     for(nVar=0;nVar<NUMB_VAR;nVar++){
    //             sm_V[i][j][k] = dv_V[index_3d(i+gr_ibegx_blk,j+gr_ibegy_blk,k+gr_ibegz_blk)][nVar];
    //         }
    // }

    // Return timestep from CFL condition
    // DANAT: for now I'll assume that dt is supplied externally; will fix it later
    // cfl(&dt);

    // Do data reconstruction and Riemann solvers
    // Dimensionally split method; updates dimensions independently
    for (int d = 0; d < NDIM; d++) {
    	soln_ReconEvolveAvg(dt, d, dr_V[n], dr_VL[n], dr_VR[n], dr_flux[n]);
    	// Update solution across grid for this direction
    	soln_update_split(dt, d, dr_V[n], dr_flux[n]);
    }

    // Apply boundary conditions
    // DANAT: Can we do it on CPU?
    // bc_apply(dr_V[n]);
}
