#include "libyuv.h"
#include <iostream>
#include <opencv2/opencv.hpp>

static const char *image_path = "../color_checker.png";

void opencv_convert() {
  // 读取图片
  cv::Mat image = cv::imread(image_path);

  // 检查是否成功读取图片
  if (image.empty()) {
    std::cout << "无法读取图片，请检查路径或文件" << std::endl;
    return;
  }

  // 显示图片
  cv::Mat yuv;

  // 第二轮和第三轮没有区别了
  for (int i = 1; i <= 5; i++) {
    cv::cvtColor(image, yuv, cv::COLOR_BGR2YUV_I420);
    cv::cvtColor(yuv, image, cv::COLOR_YUV2BGR_I420);

    cv::imwrite(std::string("opencv-") + std::to_string(i) + ".png", image);
  }
}

void libyuv_convert() {
  // 读取图片
  cv::Mat image = cv::imread(image_path);

  // 检查是否成功读取图片
  if (image.empty()) {
    std::cout << "无法读取图片，请检查路径或文件" << std::endl;
    return;
  }

  cv::cvtColor(image, image, cv::COLOR_BGR2BGRA);
  int width = image.cols;
  int height = image.rows;

  std::vector<uint8_t> y(width * height);
  int uv_size = ((width + 1) / 2) * ((height + 1) / 2);
  std::vector<uint8_t> u(uv_size);
  std::vector<uint8_t> v(uv_size);
  int uv_stride = (width + 1) / 2;

  for (int i = 1; i <= 100; i++) {

    libyuv::ARGBToI420(image.data, image.step, y.data(), width, u.data(),
                       uv_stride, v.data(), uv_stride, width, height);

    libyuv::I420ToARGB(y.data(), width, u.data(), uv_stride, v.data(),
                       uv_stride, image.data, image.step, width, height);

    cv::imwrite(std::string("libyuv-") + std::to_string(i) + ".png", image);
  }
}

int main(int argc, const char *argv[]) {
  opencv_convert();
  libyuv_convert();
  return 0;
}
