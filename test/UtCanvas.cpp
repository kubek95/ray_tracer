#include "Canvas.hpp"
#include "Color.hpp"

#include "gtest/gtest.h"
#include <cstdint>
#include <fstream>
#include <filesystem>
#include <iostream>

auto readTestFile(const std::filesystem::path& filePath) -> std::string
{
    std::ifstream file{filePath};
    if (!file) {
        return {};
    }
    std::string content;
    while(file) {
        auto ch = file.get();
        if (!file.eof()) {
            content.push_back(static_cast<char>(ch));
        }
    }
//    std::filesystem::remove(filePath);
    return content;
}

TEST(canvas, check_init_state)
{
    Canvas c{10, 20};
    ASSERT_EQ(c.width(), 10);
    ASSERT_EQ(c.height(), 20);
    Color defaultColor{0.f, 0.f, 0.f};
    for(std::size_t y{0}; y < c.height(); ++y) {
        for(std::size_t x{0}; x < c.width(); ++x) {
            ASSERT_EQ(c.getPixel(x, y), defaultColor);
        }
    }
}

TEST(canvas, should_throw_exception_when_getting_point_outside_of_range)
{
    Canvas c{10, 20};
    ASSERT_THROW(c.getPixel(10, 19), std::runtime_error);
    ASSERT_THROW(c.getPixel(9, 20), std::runtime_error);
    ASSERT_THROW(c.getPixel(10, 1), std::runtime_error);
    ASSERT_THROW(c.getPixel(1, 20), std::runtime_error);
}

TEST(canvas, should_allow_to_set_pixel_to_desired_color)
{
    Canvas canvas{10, 20};
    Color color{1.f, 0.f, 0.f};
    canvas.setPixel(2, 3, color);
    ASSERT_EQ(canvas.getPixel(2, 3), color);
}

TEST(canvas, DISABLED_should_create_file_with_correct_PPM_header)
{
    Canvas canvas{3, 2};
    const std::string expectedHeader {
        "P3\n"\
        "3 2\n"\
        "255\n"\
        "0 0 0 0 0 0 0 0 0\n"\
        "0 0 0 0 0 0 0 0 0\n"
    };
    std::filesystem::path ppmFile{"./test.ppm"};
    canvas.saveToFile(ppmFile);
    const auto header{readTestFile(ppmFile)};
    ASSERT_EQ(header, expectedHeader);
}

TEST(canvas, DISABLED_should_create_valid_ppm_file)
{
    Canvas canvas{5,3};
    canvas.setPixel(0,0, Color{1.5f, 0.f, 0.f});
    canvas.setPixel(2, 1, Color{0.f, 0.5f, 0.f});
    canvas.setPixel(4, 2, Color{-0.5f, 0.f, 1.f});
    const std::string expectedContent {
        "P3\n"\
        "5 3\n"\
        "255\n"\
        "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"\
        "0 0 0 0 0 0 0 128 0 0 0 0 0 0 0\n"\
        "0 0 0 0 0 0 0 0 0 0 0 0 0 0 255\n"
    };
    std::filesystem::path ppmFile{"./test.ppm"};
    canvas.saveToFile(ppmFile);
    const auto content{readTestFile(ppmFile)};
    ASSERT_EQ(content, expectedContent);
}

TEST(canvas, DISABLED_one_line_in_ppm_file_should_not_exceed_70_characters)
{
    Canvas canvas{10,2, Color{1.f, 0.8f, 0.6f}};
    const std::string expectedContent {
        "P3\n"\
        "10 2\n"\
        "255\n"\
        "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\n"\
        "153 255 204 153 255 204 153 255 204 153 255 204 153\n"\
        "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\n"\
        "153 255 204 153 255 204 153 255 204 153 255 204 153\n"\
    };
    std::filesystem::path ppmFile{"./test.ppm"};
    canvas.saveToFile(ppmFile);
    const auto content{readTestFile(ppmFile)};
    ASSERT_EQ(content, expectedContent);

}
