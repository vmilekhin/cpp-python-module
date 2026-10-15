import time
import statistics
import numpy as np
import sader_math

N = 5000
D = 128
rng = np.random.default_rng(42)
matrix = np.ascontiguousarray(rng.random((N, D)), dtype=np.float64)
query = np.ascontiguousarray(rng.random(D), dtype=np.float64)

def python_loop():
    result = []
    for row in matrix:
        total = 0.0
        for j in range(D):
            diff = float(row[j]) - float(query[j])
            total += diff * diff
        result.append(total)
    return np.array(result)

def numpy_version():
    return np.sum((matrix - query) ** 2, axis=1)

def cpp_version():
    return sader_math.batch_distance(matrix, query)

def measure(fn, repeats=5):
    fn()
    times = []
    for _ in range(repeats):
        t0 = time.perf_counter()
        result = fn()
        times.append((time.perf_counter() - t0) * 1000)
    return statistics.median(times), result

assert sader_math.add(2, 3) == 5
baseline, a = measure(python_loop)
num, b = measure(numpy_version)
cpp, c = measure(cpp_version)
np.testing.assert_allclose(a, b, rtol=1e-12, atol=1e-12)
np.testing.assert_allclose(b, c, rtol=1e-12, atol=1e-12)
print(f"Python loops: {baseline:.2f} ms")
print(f"NumPy:        {num:.2f} ms")
print(f"C++ pybind11: {cpp:.2f} ms")
print("Input is C-contiguous float64:", matrix.flags.c_contiguous, matrix.dtype)
