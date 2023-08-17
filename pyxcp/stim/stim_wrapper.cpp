#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <mutex>

namespace py = pybind11;
using namespace py::literals;

#pragma warning(disable: 4251 4273)

#include "stim.hpp"

void print_dict(const py::dict& dict) {
/* Easily interact with Python types */
	for (auto item : dict) {
		std::cout << "key=" << std::string(py::str(item.first)) << ", " << "value=" << std::string(py::str(item.second)) << std::endl;
	}
}

PYBIND11_MODULE(stim, m) {
	//m.def("parse", &parse, "A2LParser");

	m.def("print_dict", &print_dict);
	
	m.attr("writer_lock") = &_writer_lock;
	
	py::class_<DaqEventInfo>(m, "DaqEventInfo")
		.def(py::init<std::string_view, std::int8_t, std::size_t, std::size_t, std::size_t, std::string_view, bool, bool, bool>())
	;

    py::class_<Stim>(m, "Stim")
        .def(py::init<>())
		.def("setDaqEventInfo", &Stim::setDaqEventInfo)
		.def("clear", &Stim::clear)
		.def("freeDaq", &Stim::freeDaq)
		.def("allocDaq", &Stim::allocDaq)
		.def("allocOdt", &Stim::allocOdt)
		.def("allocOdtEntry", &Stim::allocOdtEntry)
		.def("setDaqPtr", &Stim::setDaqPtr)
		.def("clearDaqList", &Stim::clearDaqList)
		.def("writeDaq", &Stim::writeDaq)
		.def("setDaqListMode", &Stim::setDaqListMode)
		.def("startStopDaqList", &Stim::startStopDaqList)
		
	;
	
	py::class_<Mutex> (m, "Mutex")
		.def("__enter__", [&] (Mutex& self) { 
			self.lock(); 
		})
		.def("__exit__",
		 [&] (Mutex& self, const std::optional<pybind11::type>& exc_type, const std::optional<pybind11::object>& exc_value, const std::optional<pybind11::object>& traceback) { 
			self.unlock(); 
		 })
    ;
}
