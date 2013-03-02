#include <Python.h>
#include "apr_helper_config.hpp"
#include "apr_helper_init.hpp"
#include "sha1_checksum.hpp"


namespace {
    PyObject *apr_helper_sha1_file(PyObject *self, PyObject *args)
    {
        const char *filename;

        if (!PyArg_ParseTuple(args, "s", &filename))
            return NULL;

        apr_helper_initialize();
        std::string cs;
        sha1_file(filename, cs, false);
        apr_helper_terminate();

        return Py_BuildValue("s", cs.c_str());
    }

    PyMethodDef AprHelperMethods[] =
        {
            {"sha1_file", apr_helper_sha1_file, METH_VARARGS, "Calculate SHA1 checksum for a file."},
            {NULL, NULL, 0, NULL}
        };
}

PyMODINIT_FUNC initapr_helper_py()
{
     Py_InitModule("apr-helper", AprHelperMethods);
}
