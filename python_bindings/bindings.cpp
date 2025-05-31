#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/complex.h>
#include "generators.hpp"

namespace py = pybind11;

PYBIND11_MODULE(signaltools, m) {
    m.def("generate_sine", &generate_sine, "Generuje sygnał sinusoidalny");
    m.def("generate_cosine", &generate_cosine, "Generuje sygnał cosinusoidalny");
    m.def("generate_square", &generate_square, "Generuje sygnał prostokątny");
    m.def("generate_sawtooth", &generate_sawtooth, "Generuje sygnał piłokształtny");
    m.def("compute_dft", &compute_dft, "Oblicza transformatę Fouriera (DFT)");
    m.def("compute_idft", &compute_idft, "Oblicza transformatę odwrotną (IDFT)");
    m.def("low_pass_filter", &low_pass_filter, "Filtr średniej ruchomej 1D");

}
