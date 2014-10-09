/*
 *  COSMOLOGY FUNCTIONS FOR PYTHON
 */

#define pi 3.141592653589793238
#include <math.h>
#include <iostream>
#include <vector>
#include <sortarray.h>

using namespace std;

//********************************************************************************
// Function DXX_MPCH_ARR - returns comoving distance dxx(z) in Mpc/h for an 
// array of redshifts (saves a huge amount of time).
extern "C" double* dxx_mpch_arr_Py(int num, double* z_arr, double OM)
{
	double h,OL,OK,ORR,w0,wa,H0,H0y,c_MpcGyr,xx;
	double redshift,a,ezinv;
	double dz = 1e-8;
	double zshift, zlast;
	double* dxx = new double[num];
	
	h = 1;
	OL = 1.-OM;
	OK = 1.-OM-OL;
	H0 = h*100.; // km/s/Mpc
	H0y = H0 * 1.0225e-3; // Gyr^-1 3.24e-20 * 3.156e16
	c_MpcGyr = 3e8 / 3.09e22 * 3.1536e16; // [m/s] / [m/Gpc] * [s/Gyr]
	
	// Sort zz
	int* zindx = new int[num];
	sort_arr(z_arr, num, zindx, 1, 0);  // Doesn't reorder zz
	
	zlast = 0.;
	xx=0.;
	for (int i=0; i<num; i++){
		redshift=zlast;
		zshift = z_arr[zindx[i]];
		// Do integration
		while (redshift <= zshift){
			a = 1./(1.+redshift);
			ezinv = 1./sqrt(OM/(a*a*a) + OK/(a*a) + OL);
			
			xx += ezinv*dz;
			
			redshift += dz;
		}
		dxx[zindx[i]] = xx * c_MpcGyr / H0y;
		zlast = redshift - dz;
	}
	
	return dxx;
}
