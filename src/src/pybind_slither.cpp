#include "logic.h"

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>
//#include <pybind11/eigen.h>

namespace py = pybind11;

PYBIND11_MODULE(slitherbots, m) {
    /*py::class_<Body>(m, "Body")
        //.def(py::init<vector<vector<int>>,int>(),py::arg("f2v"),py::arg("n_vertices"))
        .def_property("pos",&Body::get_pos,&Body::set_pos)
        .def("trunc",&Body::trunc,py::arg("order") = 0)
        .def("ambo",&Body::ambo)
        .def("dual",&Body::dual)
        .def("kis",&Body::kis,py::arg("order") = 0)
        .def("join",&Body::join)
        .def("optim",&Body::optim_step)
        .def("save_obj",&Body::save_obj);
    m.def("prism",&prism,py::arg("sides"));
    m.def("antiprism",&antiprism,py::arg("sides"));
    m.def("cone",&cone,py::arg("sides"));
    m.def("cube",&hexahedron);
    m.def("hexahedron",&hexahedron);
    m.def("tetrahedron",&tetrahedron);
    m.def("octahedron",&octahedron);
    m.def("dodecahedron",&dodecahedron);
    m.def("icosahedron",&icosahedron);*/
}
