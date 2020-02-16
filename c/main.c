#include "decs.h"
#include "defs.h"

int main()
{
	// Declarations
	float	t = 0.0; // Simulation time
	float	dt;  // timestep
	int	nStep = 0, ioCounter = 0, ioTimeFreqCounter = 0;
	float	ioCheckTime;
    
    // output data file
    FILE *f_out;

	// Call initializations
	grid_init();
	sim_init();

	/*
	Put initialization print statements here
	*/

	/*
	Call initialize output here
	*/

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

		/*
		Output statements here
		*/

		// Update time and step count
		t += dt;
		nStep += 1;

		// Output nstep,t,dt here
        f_out = fopen("output.txt", "w");
        for (int i = gr_ibeg; i < gr_iend; i++) {
            fprintf(f_out, "%16.8f", gr_xCoord[i]);
            for (int k = 0; k < NUMB_VAR; k++) {
                fprintf(f_out, "%32.16f", gr_V[i][k]);
            }
            fprintf(f_out, "\n");
        }
        fclose(f_out);
        
	} // end while loop

	/* Print finalize statements */

	// Finalize and deallocate memory
	// grid_finalize();

	return 0; // end!!!!!!!!!!
}
