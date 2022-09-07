#pragma once

#include <fstream>
#include <vector>

#include <xcpp/xdisplay.hpp>

#include <xtensor-io/ximage.hpp>
#include <xtensor/xarray.hpp>
#include <xtensor/xio.hpp>

#include "assert.h"
#include "media.h"


xt::xarray<int> IntoXarray(const std::vector<std::vector<int>>& a) {
    ASSERT(!a.empty());
    const auto n = a.size();
    const auto m = a.front().size();

    xt::xarray<int> result = xt::zeros<int>({n, m});
    for (size_t i = 0; i < n; ++i) {
        ASSERT(a[i].size() == m);
        for (size_t j = 0; j < m; ++j) {
            result.at(i, j) = a[i][j];
        }
    }
    return result;
}

std::vector< std::vector<int> > IntoNestedVector(const xt::xarray<int>& a) {
    std::vector<size_t> shape(a.shape().begin(), a.shape().end());
    ASSERT(shape.size() == 2);
    const int n = shape[0];
    const int m = shape[1];

    std::vector<std::vector<int>> result(n, std::vector<int>(m, a.at(0, 0)));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            result[i][j] = a.at(i, j);
        }
    }
    return result;
}

std::string ReadFile(const char* filename)
{
    std::basic_ifstream<char> file(filename, std::ios::binary);
    return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}

PngImage LoadImage(const char* filename) {
    PngImage result{ReadFile(filename)};
    return result;
}

template <class E>
std::string ToPngBuffer(const xt::xexpression<E>& e) {
    const char* kTmpFilename = "/tmp/xio_image.png";
    xt::dump_image(kTmpFilename, e);
    return ReadFile(kTmpFilename);
}

template <class E>
PngImage IntoImage(const xt::xarray<E>& a) {
    PngImage result{ToPngBuffer(a)};
    return result;
}

PngImage IntoImage(const std::vector<std::vector<int>>& a) {
    return IntoImage(IntoXarray(a));
}

std::vector< std::vector<int> > LoadGrayscaleImage(const char* filename) {
    auto im = xt::load_image(filename);
    ASSERT(im.shape()[2] == 1);
    im.reshape({im.shape()[0], im.shape()[1]});
    return IntoNestedVector(im);
}
