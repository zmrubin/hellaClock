/*------------------------------------------------------------------------
  Python module to control Adafruit RGB Matrix HAT for Raspberry Pi.

  Very very simple at the moment...just a wrapper around the SetPixel,
  Fill, Clear and SetPWMBits functions of the librgbmatrix library.
  Any sort of graphics functions would need to be written into one's
  Python script.  Hope to make this connect neatly to the Python
  Imaging Library or something.
  ------------------------------------------------------------------------*/

#include <python2.7/Python.h>
#include "led-matrix.h"

using rgb_matrix::GPIO;
using rgb_matrix::RGBMatrix;

static GPIO io;

typedef struct { // Python object for matrix
	PyObject_HEAD
	RGBMatrix *matrix;
} RGBmatrixObject;

// Rows & chained display values are currently both required parameters.
// Might expand this to handle kwargs, etc.
static PyObject *RGBmatrix_new(
  PyTypeObject *type, PyObject *arg, PyObject *kw) {
        RGBmatrixObject *self = NULL;
	int              rows, chain;

	if((PyTuple_Size(arg) == 2) &&
	   PyArg_ParseTuple(arg, "II", &rows, &chain)) {
		if((self = (RGBmatrixObject *)type->tp_alloc(type, 0))) {
			self->matrix = new RGBMatrix(&io, rows, chain);
			Py_INCREF(self);
		}
	}

	return (PyObject *)self;
}

static int RGBmatrix_init(RGBmatrixObject *self, PyObject *arg) {
	self->matrix->Clear();
	return 0;
}

static void RGBmatrix_dealloc(RGBmatrixObject *self) {
	delete self->matrix;
	self->ob_type->tp_free((PyObject *)self);
}

static PyObject *Clear(RGBmatrixObject *self) {
	self->matrix->Clear();

        Py_INCREF(Py_None);
        return Py_None;
}

static PyObject *Fill(RGBmatrixObject *self, PyObject *arg) {
        uint32_t c;
	uint8_t  r, g, b;

	switch(PyTuple_Size(arg)) {
	   case 1: // Packed color
		if(!PyArg_ParseTuple(arg, "I", &c)) return Py_None;
		r = (c >> 16) & 0xFF;
		g = (c >>  8) & 0xFF;
		b =  c        & 0xFF;
		break;
	   case 3: // R, G, B
		if(!PyArg_ParseTuple(arg, "BBB", &r, &g, &b))
			return Py_None;
		break;
	   default:
		return Py_None;
	}

	self->matrix->Fill(r, g, b);

        Py_INCREF(Py_None);
        return Py_None;
}

static PyObject *SetPixel(RGBmatrixObject *self, PyObject *arg) {
        uint32_t x, y, c;
	uint8_t  r, g, b;

	switch(PyTuple_Size(arg)) {
	   case 3: // X, Y, packed color
		if(!PyArg_ParseTuple(arg, "IIBBB", &x, &y, &c))
			return Py_None;
		r = (c >> 16) & 0xFF;
		g = (c >>  8) & 0xFF;
		b =  c        & 0xFF;
		break;
	   case 5: // X, Y, R, G, B
		if(!PyArg_ParseTuple(arg, "IIBBB", &x, &y, &r, &g, &b))
			return Py_None;
		break;
	   default:
		return Py_None;
	}

	self->matrix->SetPixel(x, y, r, g, b);

        Py_INCREF(Py_None);
        return Py_None;
}

static PyObject *SetPWMBits(RGBmatrixObject *self, PyObject *arg) {
	uint8_t b;

	if((PyTuple_Size(arg) != 1) || (!PyArg_ParseTuple(arg, "B", &b)))
		return Py_None;

	self->matrix->SetPWMBits(b);

        Py_INCREF(Py_None);
        return Py_None;
}

static PyMethodDef methods[] = {
  { "Clear"     , (PyCFunction)Clear     , METH_NOARGS , NULL },
  { "Fill"      , (PyCFunction)Fill      , METH_VARARGS, NULL },
  { "SetPixel"  , (PyCFunction)SetPixel  , METH_VARARGS, NULL },
  { "SetPWMBits", (PyCFunction)SetPWMBits, METH_VARARGS, NULL },
  { NULL, NULL, 0, NULL }
};

static PyTypeObject RGBmatrixObjectType = {
	PyObject_HEAD_INIT(NULL)
	0,                              // ob_size (not used, always set to 0)
	"rgbmatrix.Adafruit_RGBmatrix", // tp_name (module name, object name)
	sizeof(RGBmatrixObject),        // tp_basicsize
	0,                              // tp_itemsize
	(destructor)RGBmatrix_dealloc,  // tp_dealloc
	0,                              // tp_print
	0,                              // tp_getattr
	0,                              // tp_setattr
	0,                              // tp_compare
	0,                              // tp_repr
	0,                              // tp_as_number
	0,                              // tp_as_sequence
	0,                              // tp_as_mapping
	0,                              // tp_hash
	0,                              // tp_call
	0,                              // tp_str
	0,                              // tp_getattro
	0,                              // tp_setattro
	0,                              // tp_as_buffer
	Py_TPFLAGS_DEFAULT,             // tp_flags
	0,                              // tp_doc
	0,                              // tp_traverse
	0,                              // tp_clear
	0,                              // tp_richcompare
	0,                              // tp_weaklistoffset
	0,                              // tp_iter
	0,                              // tp_iternext
	methods,                        // tp_methods
	0,                              // tp_members
	0,                              // tp_getset
	0,                              // tp_base
	0,                              // tp_dict
	0,                              // tp_descr_get
	0,                              // tp_descr_set
	0,                              // tp_dictoffset
	(initproc)RGBmatrix_init,       // tp_init
	0,                              // tp_alloc
	RGBmatrix_new,                  // tp_new
	0,                              // tp_free
};

PyMODINIT_FUNC initrgbmatrix(void) { // Module initialization function
        PyObject* m;

	if(io.Init() &&    // Set up GPIO pins.  MUST run as root.
          (m = Py_InitModule("rgbmatrix", methods)) &&
          (PyType_Ready(&RGBmatrixObjectType) >= 0)) {
                Py_INCREF(&RGBmatrixObjectType);
                PyModule_AddObject(m, "Adafruit_RGBmatrix",
                  (PyObject *)&RGBmatrixObjectType);
        }
}
