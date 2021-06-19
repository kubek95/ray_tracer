#include "Canvas.hpp"
#include "Color.hpp"

#include <stdexcept>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <sstream>

Canvas::Canvas(std::size_t width, std::size_t height):
    _width{width},
    _height{height},
    _canvas(width*height, Color{0.f, 0.f, 0.f})
{}

Canvas::Canvas(std::size_t width,
               std::size_t height,
               const Color& background):
    _width{width},
    _height{height},
    _canvas(_width*_height, background)
{}

auto Canvas::height() const -> std::size_t
{
    return _height;
}

auto Canvas::width() const -> std::size_t
{
    return _width;
}

auto Canvas::getPixel(std::size_t x, std::size_t y) const -> const Color&
{
    return _canvas[coordToIndex(x, y)];
}

auto Canvas::setPixel(std::size_t x, std::size_t y, const Color& color) -> void
{
    _canvas[coordToIndex(x, y)] = color;
}

auto Canvas::writePpmHeader(std::ofstream& file) const -> void
{
    file << "P3\n";
    file << _width << " " << _height << '\n';
    file << 255 << '\n';
}

auto Canvas::scaleColor(float color) const -> int
{
    if (color <= 0) {
         return 0;
    } else if (color >= 1) {
        return 255;
    } else {
        return static_cast<int>(std::ceil(255*color));
    }
}

auto Canvas::writePixelToFile(std::ostringstream& ss, const Color& pixel) const -> void
{
    ss << scaleColor(pixel.r()) << " ";
    ss << scaleColor(pixel.g()) << " ";
    ss << scaleColor(pixel.b()) << " ";
}

auto Canvas::splitLineIfNeeded(std::ostringstream& line) const -> void
{
    if (line.str().size() <= 70) {
        return;
    }
    auto tmp = line.str();
}

//TODO: remove trailing spaces and add spliting line to max 70 characters
auto Canvas::writePpmContent(std::ofstream& file) const -> void
{
    std::size_t lineNumberCount{0};
    std::ostringstream line;
    for(const auto& pixel: _canvas) {
        if (lineNumberCount ==_width-1) {
            lineNumberCount = 0;
            writePixelToFile(line, pixel);
            line << '\n';
            splitLineIfNeeded(line);
            file << line.str();
            line.str("");
            continue;
        }
        ++lineNumberCount;
        writePixelToFile(line, pixel);
    }
}

auto Canvas::saveToFile(const std::filesystem::path& filePath) const -> void
{
    std::ofstream file{filePath};
    if (!file) {
        throw std::runtime_error("Cannot open/create file");
    }
    writePpmHeader(file);
    writePpmContent(file);
}

auto Canvas::coordToIndex(std::size_t x, std::size_t y) const -> std::size_t
{
    if (x>=_width || y>=_height) {
        throw std::runtime_error("out of bounds");
    }
    return y*_width + x;
}
