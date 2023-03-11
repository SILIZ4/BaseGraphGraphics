#include <pybind11/detail/common.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "BaseGraph/extensions/graphics/svg.h"
#include "BaseGraph/extensions/graphics/vertex_layouts.h"


namespace py = pybind11;
using namespace BaseGraph;


PYBIND11_MODULE(_graphics, m) {
    py::module_::import("basegraph"); // required python import that allows the bindings to work

    py::class_<graphics::Coordinates>(m, "Coordinates")
        .def(py::init<double, double>())
        .def_readwrite("x", &graphics::Coordinates::x)
        .def_readwrite("y", &graphics::Coordinates::y);


    m.def("find_circle_layout", &graphics::findCircleLayout,
            py::arg("graph_size"), py::arg("radius")=10
    );

    m.def("find_force_directed_layout", &graphics::findForceDirectedLayout,
            py::arg("graph"), py::arg("iterations")=100, py::arg("k")=-1,
            py::arg("width")=10, py::arg("height")=10
    );
    m.def("create_svg", py::overload_cast<
            const DirectedGraph&, const std::vector<graphics::Coordinates>&, const std::string&
        >(&graphics::createSVG));
    m.def("create_svg", py::overload_cast<
            const UndirectedGraph&, const std::vector<graphics::Coordinates>&, const std::string&
        >(&graphics::createSVG));
}
