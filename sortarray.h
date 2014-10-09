/*
 *  SORT_ARARY
 *
 *	Needs <vector.h>
 */

void sort_arr(double* arr1, int num, int* indx1, int flag, bool replacearr);

using namespace std;

//********************************************************************************
// SORT ARRAY
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
	10... done in 0 s
	100... done in 0 s
	1000... done in 0 s
	10000... done in 0 s
	100000... done in 0 s
	1000000... done in 1 s
	5647390... done in 5 s
	9474168... done in 11 s
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
