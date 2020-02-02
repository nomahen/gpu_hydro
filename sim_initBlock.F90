subroutine sim_initBlock()

#include "definition.h"
  
  use sim_data
  use grid_data, only : gr_V,gr_U,gr_i0,gr_imax,gr_xCoord,gr_dx,gr_ngc
  use primconsflux, only : prim2cons
  
  implicit none

  integer :: i
  real :: ekin, eint
  real :: arho,frho

  arho = 0.2
  frho = 5.0

  do i = gr_i0,gr_imax
     if (gr_xCoord(i) < sim_shockLocL) then
        gr_V(DENS_VAR,i) = sim_densL
        gr_V(VELX_VAR,i) = sim_velxL
        gr_V(PRES_VAR,i) = sim_presL
     else
        gr_V(DENS_VAR,i) = 1.0 + arho*sin(frho*gr_xCoord(i))
        gr_V(VELX_VAR,i) = sim_velxR
        gr_V(PRES_VAR,i) = sim_presR
     end if

     gr_V(GAMC_VAR,i) = sim_gamma
     gr_V(GAME_VAR,i) = sim_gamma
     gr_V(EINT_VAR,i) = gr_V(PRES_VAR,i)/(gr_V(GAME_VAR,i)-1.)
  end do

  ! also initialize conservative vars
  do i = gr_i0,gr_imax
     call prim2cons(gr_V(:,i), gr_U(DENS_VAR:ENER_VAR,i))
  end do

  
end subroutine sim_initBlock
