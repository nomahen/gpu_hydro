#include "decs.h"
#include "defs.h"
#include "sim_defs.h"
#include "gpu_decs.h"
#include "gpu_defs.h"

int main()
{
	// Declarations
	float	t = 0.0; // Simulation time
	float	dt;  // timestep
	int	nStep = 0; // number of iterations 
	int 	ioCounter = 1; // counter for output file
	float	ioCheckTime; // checking if to iterate output counter
	int i,j,k;

    // output data file
    FILE *f_out;

	// Call initializations
	grid_init();
	sim_init();

	printf("Finished initialization.\n");
	printf("Grid Initialization:\n");
	printf("gr_nx: %d", gr_nx);
	printf("gr_ny: %d", gr_ny);
	printf("gr_nz: %d", gr_nz);
	printf("\ngr_ngcx: %d", gr_ngcx);
	printf("\ngr_ngcy: %d", gr_ngcy);
	printf("\ngr_ngcz: %d", gr_ngcz);
	printf("\ngr_xbeg: %16.8f", gr_xbeg);
	printf("\ngr_xend: %16.8f", gr_xend);
	printf("\ngr_ybeg: %16.8f", gr_ybeg);
	printf("\ngr_yend: %16.8f", gr_yend);
	printf("\ngr_zbeg: %16.8f", gr_zbeg);
	printf("\ngr_zend: %16.8f", gr_zend);
	printf("\n\nSimulation initialization:\n");
	printf("sim_order: %d", sim_order);
	printf("\nsim_nStep: %d", sim_nStep);
	printf("\nsim_cfl: %16.8f", sim_cfl);
	printf("\nsim_tmax: %16.8f", sim_tmax);
	printf("\nsim_riemann: %d", sim_riemann);
	printf("\nsim_gamma: %16.8f", sim_gamma);
	printf("\nsim_smallPres: %16.8f", sim_smallPres);
	printf("\nsim_bcType: %d", sim_bcType);
	printf("\nsim_ioTfreq: %16.8f", sim_ioTfreq);
	printf("\nsim_ioNfreq: %d\n", sim_ioNfreq);
	printf("GPU Initialization:\n");
	printf("gr_nbx: %d", gr_nbx);
	printf("gr_nby: %d", gr_nby);
	printf("gr_nbz: %d", gr_nbz);
	printf("gr_nt: %d", gr_nt);

    // Output nstep,t,dt here
    f_out = fopen("output_init.txt", "w");
    CLOOP(gr_ibegx,gr_iendx,gr_ibegy,gr_iendy,gr_ibegz,gr_iendz){
	    fprintf(f_out, "%16.8f", gr_xCoord[i]);
	    fprintf(f_out, "%16.8f", gr_yCoord[j]);
	    fprintf(f_out, "%16.8f", gr_zCoord[k]);
	    for (int m = 0; m < NUMB_VAR; m++) {
	        fprintf(f_out, "%32.16f", gr_V[index_3d(i,j,k)][m]);
         	}
            fprintf(f_out, "\n");
    }
    fclose(f_out);
    // exit(0);

	while(t < sim_tmax && nStep < sim_nStep )
	{
		// Execute solution kernel
		init_kernel();

		// Update time and step count
		t += dt;
		nStep += 1;
		
		// if condition met, output new file
		ioCheckTime = sim_ioTfreq*ioCounter;
		if (t-dt < ioCheckTime && t > ioCheckTime) {
			io_writeOutput(ioCounter,t);
			ioCounter++;
		}

		// Output nstep,t,dt here
		printf("nstep: %d, t: %16.8f, dt: %16.8f\n", nStep, t, dt);
	} // end while loop
		
    f_out = fopen("output_final.txt", "w");
    CLOOP(gr_ibegx,gr_iendx,gr_ibegy,gr_iendy,gr_ibegz,gr_iendz){
	    fprintf(f_out, "%16.8f", gr_xCoord[i]);
	    fprintf(f_out, "%16.8f", gr_yCoord[j]);
	    fprintf(f_out, "%16.8f", gr_zCoord[k]);
	    for (int m = 0; m < NUMB_VAR; m++) {
	        fprintf(f_out, "%32.16f", gr_V[index_3d(i,j,k)][m]);
         	}
            fprintf(f_out, "\n");
    }
    fclose(f_out);

	
	printf("\n\n Simulation exiting!! Great job computer!! \n\n");


	// Finalize and deallocate memory
	// grid_finalize();

	return 0; // end!!!!!!!!!!
}
