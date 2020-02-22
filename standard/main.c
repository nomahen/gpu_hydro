#include "decs.h"
#include "defs.h"
#include "sim_defs.h"

int main()
{
	// Declarations
	float	t = 0.0; // Simulation time
	float	dt;  // timestep
	int	nStep = 0; // number of iterations 
	int 	ioCounter = 1; // counter for output file
	float	ioCheckTime; // checking if to iterate output counter

    // output data file
    FILE *f_out;

	// Call initializations
	grid_init();
	sim_init();

	printf("Finished initialization.\n");
	printf("Grid Initialization:\n");
	printf("gr_nx: %d", gr_nx);
	printf("\ngr_ngc: %d", gr_ngc);
	printf("\ngr_xbeg: %16.8f", gr_xbeg);
	printf("\ngr_xend: %16.8f", gr_xend);
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

    // Output nstep,t,dt here
    f_out = fopen("output_init.txt", "w");
    for (int i = gr_ibeg; i <= gr_iend; i++) {
        fprintf(f_out, "%16.8f", gr_xCoord[i]);
        for (int k = 0; k < NUMB_VAR; k++) {
            fprintf(f_out, "%32.16f", gr_V[i][k]);
        }
        fprintf(f_out, "\n");
    }
    fclose(f_out);
    // exit(0);

	while(t < sim_tmax && nStep < sim_nStep )
	{
		// Return timestep from CFL condition
		cfl(&dt);

		// Do data reconstruction and Riemann solvers
		soln_ReconEvolveAvg(dt);

		// Update solution across grid
		soln_update(dt);

		// Apply boundary conditions
		bc_apply();

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
		
    f_out = fopen("output_final.txt", "w");
    for (int i = gr_ibeg; i <= gr_iend; i++) {
        fprintf(f_out, "%16.8f", gr_xCoord[i]);
        for (int k = 0; k < NUMB_VAR; k++) {
            fprintf(f_out, "%32.16f", gr_V[i][k]);
        }
        fprintf(f_out, "\n");
    }
    fclose(f_out);

	} // end while loop
	
	printf("\n\n Simulation exiting!! Great job computer!! \n\n");


	// Finalize and deallocate memory
	// grid_finalize();

	return 0; // end!!!!!!!!!!
}
