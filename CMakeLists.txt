cmake_minimum_required(VERSION 3.14)
project(projekt_3_sygnaly)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 14)

# Ścieżki do Python 3.10 z Minicondy
set(PYTHON_LIBRARY "C:/Users/marce/miniconda3/libs/python313.lib")
set(PYTHON_INCLUDE_DIR "C:/Users/marce/miniconda3/include")

# Zewnętrzne biblioteki
add_subdirectory(extern/matplotplusplus)
add_subdirectory(pybind11)

# Ścieżki nagłówków
include_directories(include)
include_directories(${PYTHON_INCLUDE_DIR})
link_directories(${PYTHON_LIBRARY})

# Budowanie modułu Pybind11
pybind11_add_module(signaltools python_bindings/bindings.cpp src/generators.cpp)
target_link_libraries(signaltools PRIVATE matplot ${PYTHON_LIBRARY})

# Aplikacje C++
add_executable(plot_test src/plot_test.cpp)
target_link_libraries(plot_test PRIVATE matplot)

add_executable(projekt_main src/main.cpp src/generators.cpp)
target_link_libraries(projekt_main PRIVATE matplot)
