#include "decs.h"

void io_writeOutput(int ioCounter, float t)
{
    int i,j,k;
    char filename[40]; // 17 to hold string like this: output_######.txt
    sprintf(filename, "output_%d.txt", 100000 + ioCounter);
    printf("Writing output file at ioCounter: %d and time t: %16.8f.\n", ioCounter, t);


    FILE* f_out = fopen(filename, "w");
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
}
