//-----------------------------------------------------------------------------
// Murmur Hash Library, by Bryan McLemore and Chris Heald
// Original Portions (c) 2008 Bryan McLemore and Chris Heald
// Released under The MIT License
// http://www.opensource.org/licenses/mit-license.php
//
// Portions of this code was based off of MurmurHash2, by Austin Appleby
// Info about that can be found at: http://murmurhash.googlepages.com/
// Is not quite as performant as the original since certain parts were broken
// up to make code more maintainable.
//
// WARNINGS: PLEASE NOTE!
// Including from the original code is a warning about assumptions and limits:
// 1. We can read a 4-byte value from any address without crashing
// 2. sizeof(int) == 4
// Also please note that:
// It will not produce the same results on little-endian and big-endian
//    machines.
//
// It would be fairly simple, I believe to swap out implementations based on 
// the alignment and if your machine is little or big endian.  However, those 
// are not in this implementation.

#include <Python.h>
#include <fstream>
#include <iostream>
#include <sys/stat.h>

using namespace std;

const unsigned int m = 0x5bd1e995;
const int r = 24;

static unsigned int murmur_initialize(unsigned int len, unsigned int seed) {
    return seed ^ len;
}

static unsigned int murmur_loop(const unsigned char * buffer, unsigned int len, unsigned int h) {
    
    while(len >= 4) {
		unsigned int k = *(unsigned int *)buffer;

		k *= m; 
		k ^= k >> r; 
		k *= m; 
		
		h *= m; 
		h ^= k;

		buffer += 4;
		len -= 4;
	}	
    
    switch(len) {
	case 3: h ^= buffer[2] << 16;
	case 2: h ^= buffer[1] << 8;
	case 1: h ^= buffer[0];
	        h *= m;
	};
	
	return h;
}

static unsigned int murmur_finalize(unsigned int h) {
    h ^= h >> 13;
	h *= m;
	h ^= h >> 15;

	return h;
}

static unsigned int MurmurHash2_String( const void * key, int len, unsigned int seed ) {
    
    unsigned int cur = murmur_initialize(len, seed);
	const unsigned char * data = (const unsigned char *)key;
    cur = murmur_loop(data, len, cur);
    return murmur_finalize(cur);
} 

static PyObject * murmur_string_hash(PyObject *self, PyObject *args) {
	const char *s;
	unsigned int len;
	unsigned int seed = 0;
	if (!PyArg_ParseTuple(args, "s#|I", &s, &len, &seed))
		return NULL;
	return Py_BuildValue("I", MurmurHash2_String(s, len, seed));
}

static PyMethodDef MurmurMethods[] = {
	{"string_hash", murmur_string_hash, METH_VARARGS, "Hash a string"},
	{NULL, NULL, 0, NULL}
};

static struct PyModuleDef murmurmodule = {
    PyModuleDef_HEAD_INIT,
    "spam",   /* name of module */
    NULL, /* module documentation, may be NULL */
    -1,       /* size of per-interpreter state of the module,
                 or -1 if the module keeps state in global variables. */
    MurmurMethods
};

PyMODINIT_FUNC
PyInit_murmur(void)
{
    return PyModule_Create(&murmurmodule);
}

int main(int argc, char *argv[]) {}
