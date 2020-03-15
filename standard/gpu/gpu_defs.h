/* For executing GPU Kernel */
float gr_nbx; // num blocks in x direction
float gr_nby; // num blocks in y direction
float gr_nbz; // num blocks in z direction
float gr_nt;  // num threads per block

/* GPU global memory arrays that are copied from CPU */
float	(*dv_V)[NUMB_VAR]; // primitive variables
