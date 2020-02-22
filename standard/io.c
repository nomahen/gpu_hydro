#include "decs.h"

void io_writeOutput(int ioCounter, float t)
{
    char filename[40]; // 17 to hold string like this: output_######.txt
    sprintf(filename, "output_%d.txt", 100000 + ioCounter);
    printf("Writing output file at ioCounter: %d and time t: %16.8f.\n", ioCounter, t);


    FILE* f_out = fopen(filename, "w");
    for (int i = gr_ibeg; i <= gr_iend; i++) {
        fprintf(f_out, "%16.8f", gr_xCoord[i]);
        for (int k = 0; k < NUMB_VAR; k++) {
            fprintf(f_out, "%32.16f", gr_V[i][k]);
        }
        fprintf(f_out, "\n");
    }
    fclose(f_out);
}
