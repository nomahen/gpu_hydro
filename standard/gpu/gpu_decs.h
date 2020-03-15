/* For executing GPU Kernel */
extern float gr_nbx; // num blocks in x direction
extern float gr_nby; // num blocks in y direction
extern float gr_nbz; // num blocks in z direction
extern float gr_nt;  // num threads per block

/* GPU global memory arrays that are copied from CPU */
extern float	(*dv_V)[NUMB_VAR]; // primitive variables

///////////////////////////
/* FUNCTION DECLARATIONS */
///////////////////////////
void init_kernel(); // Prepares kernel for execution
void AllocatePrimitiveOnDevice(); // Allocate primitive variable array onto device memory
void CopyPrimitiveToDevice(); // Copy primitive variable array from CPU to device memory
void CopyPrimitiveToHost(); // Copy primitive variable array from device memory to CPU
void DeallocatePrimitiveOnDevice(); // Deallocate primitive variable array from device memory
__global__ void soln_kernel(); // Executes kernel to update solution 
__device__ int  index_3d(int i, int j, int k) ; // Get i,j,k index inside loop over all cell elements
__device__ float dot_product(float *a, float *b, int length) ; // Return dot product of arrays a and b of length length
