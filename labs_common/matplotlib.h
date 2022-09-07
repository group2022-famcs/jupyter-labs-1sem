#pragma once

#pragma cling add_library_path("$CONDA_PREFIX/lib/")
#ifdef PYTHON_3_10
    #pragma cling add_include_path("$CONDA_PREFIX/include/python3.10")
    #pragma cling add_include_path("$CONDA_PREFIX/lib/python3.10/site-packages/numpy/core/include")
    #pragma cling load("python3.10")
#else
    #pragma cling add_include_path("$CONDA_PREFIX/include/python3.7m")
    #pragma cling add_include_path("$CONDA_PREFIX/lib/python3.7/site-packages/numpy/core/include")
    #pragma cling load("python3.7m")
#endif


#include "matplotlib-cpp/matplotlibcpp.h"
#include "images.h"


namespace plt = matplotlibcpp;

PngImage PltShow() {
    const auto PATH = "/tmp/image.png";
    matplotlibcpp::save(PATH);
    return LoadImage(PATH);
}
