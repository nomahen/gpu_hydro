/* config.h defines all mnemonics. */

// slope limiters
#define MINMOD  0
#define MC      1
#define VANLEER 2

// Riemann solvers
#define HLL     0
#define ROE     1

// ndim never changes
#define NDIM	3

// memory allocation for each direction
#define NXM ((NX>1)?(NX+2*NGC):(1))
#define NYM ((NY>1)?(NY+2*NGC):(1))
#define NZM ((NZ>1)?(NZ+2*NGC):(1))

// primitive vars
#define DENS_VAR 0
#define VELX_VAR 1
#define VELY_VAR 2
#define VELZ_VAR 3
#define PRES_VAR 4
#define EINT_VAR 5
#define GAMC_VAR 6
#define GAME_VAR 7
#define NUMB_VAR 8

#define NSYS_VAR 5 /* total number of equations of the conservative system */

// conservative vars
#define MOMX_VAR 1
#define MOMY_VAR 2
#define MOMZ_VAR 3
#define ENER_VAR 4

// waves
#define NUMB_WAVE 5

// setup parameters
#define MAX_STRING_LENGTH 80

// BC
#define OUTFLOW  0
#define PERIODIC 1
#define REFLECT  2
#define USER     3

// loop abbreviations
// CLOOP: loop over all cells
#define CLOOP(istart,istop,jstart,jstop,kstart,kstop) \
for(i = istart; i <= istop; i++)\
for(j = jstart; j <= jstop; j++)\
for(k = kstart; k <= kstop; k++)

// extra stuff
// M_PI is not defined in math.h in C99; sometimes necessary to define it manually.
#ifndef M_PI
#define M_PI           3.14159265358979323846
#endif
