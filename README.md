##CosmologyFuncsPython
Cosmology functions for Python.

Some simple functions to calculate comoving distance as a function of redshift, for an input array of redshifts. The distances are calculated in C++ for speed and wrapped by a Python function dxx_mpch_arr_Py.

Use make to compile cosmology.cpp, to create a library file library.so which is called by cosmologycodes.py.