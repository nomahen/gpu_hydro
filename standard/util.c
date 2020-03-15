#include "decs.h"

int index_3d(int i,int j,int k){
	return i*(2*gr_ngcy + gr_ny)*(2*gr_ngcz + gr_nz) + j*(2*gr_ngcz + gr_nz) + k;
}

float dot_product(float *a, float *b, int length){
	float val = 0;
	for(int i = 0; i < length; i++){
	    val += a[i]*b[i];
	}
	return val;

}
