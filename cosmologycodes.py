'''
Cosmology functions
'''

import ctypes
import numpy as np

speedlight = 299792.458
lib = ctypes.CDLL('library.so')

def dxx_mpch_arr(num, z_arr, OM):
    '''
    Calls the C++ function "dxx_mpch_arr_py" from cosmology.cpp. First the 
    shared library "library.so" is created by typing Make.
       z_arr: array of redshifts to convert
       num: number of elements in z_arr
    '''
    cz_arr = (ctypes.c_double * len(z_arr))(*z_arr)
    lib.dxx_mpch_arr_Py.restype = ctypes.POINTER(ctypes.c_double * num)
    
    result = lib.dxx_mpch_arr_Py(ctypes.c_int(num),cz_arr,ctypes.c_double(OM)) 
    dxx_mpch = [i for i in result.contents]
    dxx_mpch = np.array(dxx_mpch)
    return dxx_mpch
    
# Test of dxx_mpch_arr
#print 'Test of dxx_mpch_arr:'
#z_arr1 = [0.02,0.03,0.01]
#print dxx_mpch_arr(3,z_arr1,0.3175)

