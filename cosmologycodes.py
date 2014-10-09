'''
Cosmology functions
'''

import ctypes

lib = ctypes.CDLL('library.so')

def dxx_mpch_arr(z_arr, OM):
    '''
    Calculates a list of comoving distances in units of h^{-1}Mpc (dxx_mpch),
    given an input list of redshifts (z_arr) and a value of Omega_m (OM).
    Calls the C++ function "dxx_mpch_arr_py" from cosmology.cpp. First the 
    shared library "library.so" is created by typing Make.
       z_arr: array of redshifts to convert
       num: number of elements in z_arr
    '''
    num = len(z_arr)
    cz_arr = (ctypes.c_double * num)(*z_arr)
    lib.dxx_mpch_arr_Py.restype = ctypes.POINTER(ctypes.c_double * num)
    
    result = lib.dxx_mpch_arr_Py(ctypes.c_int(num),cz_arr,ctypes.c_double(OM)) 
    dxx_mpch = [i for i in result.contents]
    return dxx_mpch
