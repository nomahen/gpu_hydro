#include "decs.h"

int index_3d(int i,int j,int k){
	return i*(2*gr_ngcy + gr_ny)*(2*gr_ngcz + gr_nz) + j*(2*gr_ngcz + gr_nz) + k;
}
