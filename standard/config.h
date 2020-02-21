/* config.h defines all mnemonics. */

// slope limiters
#define MINMOD  0
#define MC      1
#define VANLEER 2

// Riemann solvers
#define HLL     0
#define ROE     1

// primitive vars
#define DENS_VAR 0
#define VELX_VAR 1
#define PRES_VAR 2
#define EINT_VAR 3
#define GAMC_VAR 4
#define GAME_VAR 5
#define NUMB_VAR 6

#define NSYS_VAR 3 /* total number of equations of the conservative system */

// conservative vars
#define MOMX_VAR 1
#define ENER_VAR 2

// waves
#define SHOCKLEFT 0
#define CTENTROPY 1
#define SHOCKRGHT 2
#define NUMB_WAVE 3

// setup parameters
#define MAX_STRING_LENGTH 80

// BC
#define OUTFLOW  0
#define PERIODIC 1
#define REFLECT  2
#define USER     3
