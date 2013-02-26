#include <Python.h>
#include <cstdlib>
#include <string>
#include <iostream>

#include "sha1_checksum.hpp"

namespace {
    PyObject *sha1_sha1_file(PyObject *self, PyObject *args)
    {
        const char *filename;
        int sts;

        if (!PyArg_ParseTuple(args, "s", &filename))
            return NULL;
        
        std::string cs;
        sts = sha1_file(filename, cs, false);
        std::cout << cs << "  " << filename << std::endl;
        return Py_BuildValue("i", sts);
    }

    PyMethodDef Sha1Methods[] =
    {
         {"sha1_file", sha1_sha1_file, METH_VARARGS, "Calculate SHA1 checksum for a file."},
         {NULL, NULL, 0, NULL}
    };
}

PyMODINIT_FUNC initsha1()
{
     Py_InitModule("sha1", Sha1Methods);
}
