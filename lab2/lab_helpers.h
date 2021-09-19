//
// Created by Dmitriy V. Baranov on 17.09.2021.
//

#ifndef LAB2__LAB_HELPERS_H_
#define LAB2__LAB_HELPERS_H_

#include <vector>
#include <string>
#include <cassert>

#define assertm(exp, msg) assert(((void)msg, exp))
#define STB_IMAGE_IMPLEMENTATION
#include "lab2_files/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "lab2_files/stb_image_write.h"

std::vector<std::vector<int>> LoadGrayscaleImage(const std::string &filename) {
  int width, height, bpp;
  uint8_t *image = stbi_load(filename.c_str(), &width, &height, &bpp, 1);
  assertm(image, "Can not read image. May be it is corrupted, invalid or simply not found");
  assertm(width > 0, "Image width should be positive");
  assertm(height > 0, "Image height should be positive");
  assertm(static_cast<long long>(width) * height <= 1e9,"Image total pixels number should not exceed 1 billion");

  std::vector<std::vector<int>> image_vector(height, std::vector<int>(width));
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      image_vector[i][j] = image[i * width + j];
    }
  }
  stbi_image_free(image);
  return image_vector;
}

void WriteGrayscaleImage(const std::vector<std::vector<int>> &image, const std::string &filename) {
  auto height = image.size();
  assertm(height > 0, "Image should have positive height");
  auto width = image.front().size();
  assertm(width > 0, "Image should have positive width");
  assertm(static_cast<long long>(width) * height <= 1e9,"Image total pixels number should not exceed 1 billion");
  std::vector<uint8_t> image_vector(height * width);
  for (size_t i = 0; i < image_vector.size(); ++i) {
    image_vector[i] = image[i / width][i % width];
  }
  stbi_write_jpg(filename.c_str(), static_cast<int>(width), static_cast<int>(height), 1, image_vector.data(), 100);
}

std::vector<std::vector<std::vector<int>>> LoadRGBImage(const std::string &filename) {
  int width, height, bpp;
  uint8_t *image = stbi_load(filename.c_str(), &width, &height, &bpp, 3);
  assertm(image, "Can not read image. May be it is corrupted, invalid or simply not found");
  assertm(width > 0, "Image width should be positive");
  assertm(height > 0, "Image height should be positive");
  assertm(bpp == 3, "Image should have exactly 3 channels");
  assertm(static_cast<long long>(width) * height <= 1e9,"Image total pixels number should not exceed 1 billion");

  std::vector<std::vector<std::vector<int>>> image_vector(
      height, std::vector<std::vector<int>>(width, std::vector<int>(3)));
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      for (int k = 0; k < 3; ++k) {
        image_vector[i][j][k] = image[width * 3 * i + 3 * j + k];
      }
    }
  }
  stbi_image_free(image);
  return image_vector;
}

void WriteRGBImage(const std::vector<std::vector<std::vector<int>>> &image, const std::string &filename) {
  auto height = image.size();
  assertm(height, "Image should have non-zero height");
  auto width = image.front().size();
  assertm(width, "Image should have non-zero width");
  assertm(image.front().front().size(), "Image should have exactly 3 channels");

  std::vector<uint8_t> image_vector(height * width * 3, 0);
  for (size_t i = 0; i < image_vector.size(); ++i) {
    auto z = i / 3 / width;
    auto x = i - z * 3 * width;
    image_vector[i] += image[z][x / 3][x % 3];
  }
  stbi_write_jpg(filename.c_str(), static_cast<int>(width), static_cast<int>(height), 3, image_vector.data(), 100);
}

#endif //LAB2__LAB_HELPERS_H_
