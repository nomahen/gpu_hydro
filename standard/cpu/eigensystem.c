#include "decs.h"

void eigenvalues(float *V, float *lambda, int d)
{
    float a, u;

    // sound speed and velocity
    a = sqrt(V[GAMC_VAR]*V[PRES_VAR]/V[DENS_VAR]);
    u = V[VELX_VAR+d];

    lambda[0] = u - a;
    lambda[1] = u;
    lambda[2] = u;
    lambda[3] = u;
    lambda[4] = u + a;

    return;
}


void right_eigenvectors(float *V, float (*reig)[NSYS_VAR], int d)
{
    float a,r;
    int nx=0,ny=0,nz=0;

    if(d==0)nx=1;
    if(d==1)ny=1;
    if(d==2)nz=1;

    a = sqrt(V[GAMC_VAR]*V[PRES_VAR]/V[DENS_VAR]);
    r = V[DENS_VAR];

    // First column of right eigenvector matrix
    reig[0][DENS_VAR] = 1.;
    reig[0][VELX_VAR] = (-a/r)*nx;
    reig[0][VELY_VAR] = (-a/r)*ny;
    reig[0][VELZ_VAR] = (-a/r)*nz;
    reig[0][PRES_VAR] = a*a;

    // Second column of right eigenvector matrix
    reig[1][DENS_VAR] = nx;
    reig[1][VELX_VAR] = 0.;
    reig[1][VELY_VAR] = nz;
    reig[1][VELZ_VAR] = ny;
    reig[1][PRES_VAR] = 0.;

    // Third column of right eigenvector matrix
    reig[2][DENS_VAR] = ny;
    reig[2][VELX_VAR] = nz;
    reig[2][VELY_VAR] = nx;
    reig[2][VELZ_VAR] = 0.;
    reig[2][PRES_VAR] = 0.;

    // Fourth column of right eigenvector matrix
    reig[3][DENS_VAR] = nz;
    reig[3][VELX_VAR] = ny;
    reig[3][VELY_VAR] = 0.;
    reig[3][VELZ_VAR] = nx;
    reig[3][PRES_VAR] = 0.;

    // Fifth column of right eigenvector matrix
    reig[4][DENS_VAR] = 1.;
    reig[4][VELX_VAR] = (a/r)*nx;
    reig[4][VELY_VAR] = (a/r)*ny;
    reig[4][VELZ_VAR] = (a/r)*nz;
    reig[4][PRES_VAR] = a*a;

    return;
}

void left_eigenvectors(float *V, float (*leig)[NSYS_VAR], int d)
{
    float a,r;
    int nx=0,ny=0,nz=0;

    if(d==0)nx=1;
    if(d==1)ny=1;
    if(d==2)nz=1;

    a = sqrt(V[GAMC_VAR]*V[PRES_VAR]/V[DENS_VAR]);
    r = V[DENS_VAR];

    // First row of left eigenvector matrix
    leig[0][DENS_VAR] = 0.;
    leig[0][VELX_VAR] = (-0.5*r/a)*nx;
    leig[0][VELY_VAR] = (-0.5*r/a)*ny;
    leig[0][VELZ_VAR] = (-0.5*r/a)*nz;
    leig[0][PRES_VAR] = 0.5/a/a;

    // Second row of left eigenvector matrix
    leig[1][DENS_VAR] = nx;
    leig[1][VELX_VAR] = 0.;
    leig[1][VELY_VAR] = nz;
    leig[1][VELZ_VAR] = ny;
    leig[1][PRES_VAR] = -nx/a/a;

    // Third row of left eigenvector matrix
    leig[2][DENS_VAR] = ny;
    leig[2][VELX_VAR] = nz;
    leig[2][VELY_VAR] = nx;
    leig[2][VELZ_VAR] = 0.;
    leig[2][PRES_VAR] = -ny/a/a;

    // Fourth row of left eigenvector matrix
    leig[3][DENS_VAR] = nz;
    leig[3][VELX_VAR] = ny;
    leig[3][VELY_VAR] = 0.;
    leig[3][VELZ_VAR] = nx;
    leig[3][PRES_VAR] = -nz/a/a;

    // Fifth row of left eigenvector matrix
    leig[4][DENS_VAR] = 0.;
    leig[4][VELX_VAR] = (0.5*r/a)*nx;
    leig[4][VELY_VAR] = (0.5*r/a)*ny;
    leig[4][VELZ_VAR] = (0.5*r/a)*nz;
    leig[4][PRES_VAR] = 0.5/a/a;


    return;
}
