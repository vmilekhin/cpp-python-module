#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <stdexcept>
#include <cstddef>

namespace py = pybind11;

int add(int a, int b) { return a + b; }

py::array_t<double> batch_distance(
    py::array_t<double, py::array::c_style> matrix,
    py::array_t<double, py::array::c_style> query) {
  if (matrix.ndim() != 2 || query.ndim() != 1)
    throw std::invalid_argument("matrix must be 2D and query must be 1D");
  const py::ssize_t n = matrix.shape(0);
  const py::ssize_t d = matrix.shape(1);
  if (query.shape(0) != d)
    throw std::invalid_argument("dimension mismatch");

  py::array_t<double> output(n);
  const double* m = matrix.data();
  const double* q = query.data();
  double* out = output.mutable_data();
  {
    py::gil_scoped_release release;
    for (py::ssize_t i = 0; i < n; ++i) {
      double total = 0;
      for (py::ssize_t j = 0; j < d; ++j) {
        double diff = m[i*d+j] - q[j];
        total += diff * diff;
      }
      out[i] = total;
    }
  }
  return output;
}

PYBIND11_MODULE(sader_math, m) {
  m.doc() = "Educational C++ distance kernel";
  m.def("add", &add, "Add two integers");
  m.def("batch_distance", &batch_distance, "Squared L2 distances for N x D matrix");
}
