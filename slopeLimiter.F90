module slopeLimiter
  
#include "definition.h"
  
  !use grid_data


contains

  subroutine minmod(a,b,delta)
    implicit none
    real, intent(IN) :: a, b
    real, intent(OUT) :: delta

    delta = 0.5 * (sign(1.0,a) + sign(1.0,b))*min(abs(a),abs(b))

    return
  end subroutine minmod

  
  subroutine mc(a,b,delta)
    implicit none
    real, intent(IN) :: a, b
    real, intent(OUT) :: delta

    delta = (sign(1.0,a)+sign(1.0,b))*min(abs(a),0.25*abs(a+b),abs(b))

    return
  end subroutine mc

  
  subroutine vanLeer(a,b,delta)
    implicit none
    real, intent(IN) :: a, b
    real, intent(OUT) :: delta

    if (a*b <=0.) then
       delta = 0.0
    else
       delta=2.0*a*b/(a+b)
    endif

    return
  end subroutine vanLeer
  
end module slopeLimiter
