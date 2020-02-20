subroutine soln_PLM(dt)

#include "definition.h"  

  use grid_data
  use sim_data
  use slopeLimiter
  use eigensystem

  implicit none
  real, intent(IN) :: dt
  integer :: i

  real, dimension(NUMB_WAVE) :: lambda
  real, dimension(NSYS_VAR,NUMB_WAVE) :: reig, leig
  logical :: conservative
  real, dimension(NSYS_VAR) :: vecL,vecR,sigL,sigR
  integer :: kWaveNum
  real :: lambdaDtDx
  real, dimension(NUMB_VAR)  :: delV,delL,delR
  real, dimension(NUMB_WAVE) :: delW
  integer :: nVar
  

  
  ! we need conservative eigenvectors
  conservative = .false.

  do i = gr_ibeg-1, gr_iend+1

     call eigenvalues(gr_V(DENS_VAR:GAME_VAR,i),lambda)
     call left_eigenvectors (gr_V(DENS_VAR:GAME_VAR,i),conservative,leig)
     call right_eigenvectors(gr_V(DENS_VAR:GAME_VAR,i),conservative,reig)

     ! primitive limiting
     if (.not. sim_charLimiting) then
        ! slope limiting
        ! deltas in primitive vars
        delL(DENS_VAR:PRES_VAR) = gr_V(DENS_VAR:PRES_VAR,i  )-gr_V(DENS_VAR:PRES_VAR,i-1)
        delR(DENS_VAR:PRES_VAR) = gr_V(DENS_VAR:PRES_VAR,i+1)-gr_V(DENS_VAR:PRES_VAR,i  )

       
        do nVar = DENS_VAR,PRES_VAR
           if (sim_limiter == 'minmod') then
              call minmod(delL(nVar),delR(nVar),delV(nVar))
           elseif (sim_limiter == 'vanLeer') then
              call vanLeer(delL(nVar),delR(nVar),delV(nVar))
           elseif (sim_limiter == 'mc') then
              call mc(delL(nVar),delR(nVar),delV(nVar))
           endif
        enddo
        do kWaveNum = 1, NUMB_WAVE
           ! project primitive delta to characteristic vars
           delW(kWaveNum) = dot_product(leig(DENS_VAR:PRES_VAR,kWaveNum),delV(DENS_VAR:PRES_VAR))
        enddo
     else
        ! characteristic limiting
        do kWaveNum = 1, NUMB_WAVE
           ! slope limiting
           ! deltas in characteristic vars
           delL(kWaveNum) = dot_product(leig(DENS_VAR:PRES_VAR,kWaveNum),gr_V(DENS_VAR:PRES_VAR,i  )-gr_V(DENS_VAR:PRES_VAR,i-1))
           delR(kWaveNum) = dot_product(leig(DENS_VAR:PRES_VAR,kWaveNum),gr_V(DENS_VAR:PRES_VAR,i+1)-gr_V(DENS_VAR:PRES_VAR,i  ))
              
           if (sim_limiter == 'minmod') then
              call minmod(delL(kWaveNum),delR(kWaveNum),delW(kWaveNum))
           elseif (sim_limiter == 'vanLeer') then
              call vanLeer(delL(kWaveNum),delR(kWaveNum),delW(kWaveNum))
           elseif (sim_limiter == 'mc') then
              call mc(delL(kWaveNum),delR(kWaveNum),delW(kWaveNum))
           endif
        enddo
     endif



     ! set the initial sum to be zero
     sigL(DENS_VAR:ENER_VAR) = 0.
     sigR(DENS_VAR:ENER_VAR) = 0.
     vecL(DENS_VAR:ENER_VAR) = 0.
     vecR(DENS_VAR:ENER_VAR) = 0.
     
     do kWaveNum = 1, NUMB_WAVE
        ! lambdaDtDx = lambda*dt/dx
        lambdaDtDx = lambda(kWaveNum)*dt/gr_dx

        
        if (sim_riemann == 'roe') then
           if (lambda(kWaveNum) > 0.0) then
              vecR(DENS_VAR:PRES_VAR) = 0.5*(1.0 - lambdaDtDx)*reig(DENS_VAR:PRES_VAR,kWaveNum)*delW(kWaveNum)
              sigR(DENS_VAR:PRES_VAR) = sigR(DENS_VAR:PRES_VAR) + vecR(DENS_VAR:PRES_VAR)
           else
              vecL(DENS_VAR:PRES_VAR) = 0.5*(-1.0 - lambdaDtDx)*reig(DENS_VAR:PRES_VAR,kWaveNum)*delW(kWaveNum)
              sigL(DENS_VAR:PRES_VAR) = sigL(DENS_VAR:PRES_VAR) + vecL(DENS_VAR:PRES_VAR)
           endif
        else
              vecR(DENS_VAR:PRES_VAR) = 0.5*(1.0 - lambdaDtDx)*reig(DENS_VAR:PRES_VAR,kWaveNum)*delW(kWaveNum)
              sigR(DENS_VAR:PRES_VAR) = sigR(DENS_VAR:PRES_VAR) + vecR(DENS_VAR:PRES_VAR)

              vecL(DENS_VAR:PRES_VAR) = 0.5*(-1.0 - lambdaDtDx)*reig(DENS_VAR:PRES_VAR,kWaveNum)*delW(kWaveNum)
              sigL(DENS_VAR:PRES_VAR) = sigL(DENS_VAR:PRES_VAR) + vecL(DENS_VAR:PRES_VAR)
        endif

        ! Let's make sure we copy all the cell-centered values to left and right states
        ! this will be just FOG
        gr_vL(DENS_VAR:NUMB_VAR,i) = gr_V(DENS_VAR:NUMB_VAR,i)
        gr_vR(DENS_VAR:NUMB_VAR,i) = gr_V(DENS_VAR:NUMB_VAR,i)
        
        ! Now PLM reconstruction for dens, velx, and pres
        gr_vL(DENS_VAR:PRES_VAR,i) = gr_V(DENS_VAR:PRES_VAR,i) + sigL(DENS_VAR:PRES_VAR)
        gr_vR(DENS_VAR:PRES_VAR,i) = gr_V(DENS_VAR:PRES_VAR,i) + sigR(DENS_VAR:PRES_VAR)      
     end do
  end do
  


  return
end subroutine soln_PLM
