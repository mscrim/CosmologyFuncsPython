/*
 *  COSMOLOGY FUNCTIONS FOR PYTHON
 *
 *  Morag Scrimgeour
 */

#define pi 3.141592653589793238
#include <math.h>
#include <iostream>
#include <vector>

using namespace std;

//********************************************************************************
// Function SORT ARRAY - sorts an array and returns the indices of the sorted array
typedef std::pair<double,int> indxpair;
// Set up comparator to use in std::sort
bool comparator_asc( const indxpair& l, const indxpair& r)
{
	return l.first < r.first;
}
bool comparator_desc( const indxpair& l, const indxpair& r)
{
	return l.first > r.first;
}
void sort_arr(double* arr1, int num, int* indx1, int flag, bool replacearr)
/*
 * arr1 : array to sort
 * num : size of array
 * indx1: array to hold sorted indexes
 * Flag = 2: Sort descending
 * Flag = 1: Sort ascending
 *
 * Takes ~ 11s for an array of 9.5 million elements
 */
{
	vector<indxpair> pairArr (num);
	
	for (int i=0; i<num; i++){
		pairArr[i] = make_pair(arr1[i],i);
	}
	
	// Sort pairArr
	if (flag == 1) std::sort (pairArr.begin(), pairArr.end(), comparator_asc);
	if (flag == 2) std::sort (pairArr.begin(), pairArr.end(), comparator_desc);
	
	for (int i=0; i<num; i++){
		if (replacearr) arr1[i] = pairArr[i].first;
		indx1[i] = pairArr[i].second;
	}
	
	return;		
}

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
