#include <Python.h>
#include <stdio.h>

#include "c_library.h"

static PyObject* f_py(PyObject* self __attribute__((unused)),
                      PyObject* args __attribute__((unused)))
{
    printf("in f() Python wrapper. About to call C library\n");
    f();
    Py_RETURN_NONE;
}


static PyMethodDef methods[] =
    { {"f", (PyCFunction)f_py, METH_NOARGS, "Python bindings to f() in c_library\n"},
      {}
    };

#if PY_MAJOR_VERSION == 2

PyMODINIT_FUNC initc_library(void)
{

    PyImport_AddModule("c_library");
    Py_InitModule3("c_library", methods,
                   "Python bindings to c_library");
}

#else

static struct PyModuleDef module =
    {
     PyModuleDef_HEAD_INIT,
     "c_library",   /* name of module */
     "Python bindings to c_library",
     -1,
     methods
    };

PyMODINIT_FUNC PyInit_c_library(void)
{
    return PyModule_Create(&module);
}

#endif
