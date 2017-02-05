#include<python2.7/Python.h>
#include<iostream>

using namespace std;

int main(){
	Py_Initialize();
	PyRun_SimpleString(
		"import sys\nsys.path.append('./')");
    PyObject *pName, *pModule, *pFunc, *pArgs;
    pName = PyString_FromString("approve");
    pModule = PyImport_Import(pName);
    Py_DECREF(pName);
    if(pModule!=NULL){
        pFunc = PyObject_GetAttrString(pModule, (char*)"approve");
        pArgs = PyTuple_New(1);
        PyTuple_SetItem(pArgs, 0, PyInt_FromLong(1));
        PyObject_CallObject(pFunc, pArgs);
    }
    else{
        PyErr_Print();
    }
    Py_Finalize();
    cout<<"exiting c"<<endl;
    return 0;
}

