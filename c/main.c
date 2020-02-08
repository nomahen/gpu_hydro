#include "decs.h"
#include "defs.h"

int main()
{
	// Declarations
	double	t=0.; // Simulation time
	double	dt ;  // timestep
	int	nStep=0,ioCounter=0,ioTimeFreqCounter=0 ;
	double	ioCheckTime

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
	} // end while loop

	/* Print finalize statements */

	// Finalize and deallocate memory
	grid_finalize();	

	return 1; // end!!!!!!!!!!
}
