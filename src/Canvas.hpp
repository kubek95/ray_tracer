#pragma once

#include <cstdint>
#include <vector>
#include <string>
#include <filesystem>

class Color;

class Canvas
{
    public:
        explicit Canvas(std::size_t width, std::size_t height);
        explicit Canvas(std::size_t width, std::size_t height, const Color& background);
        ~Canvas() = default;

        Canvas(const Canvas&) = default;
        auto operator=(const Canvas&) -> Canvas&;
        Canvas(Canvas&&) = default;
        auto operator=(Canvas&&) -> Canvas&;

        auto getPixel(std::size_t x, std::size_t y) const -> const Color&;
        auto setPixel(std::size_t x, std::size_t y, const Color& color) -> void;
        auto height() const -> std::size_t;
        auto width() const -> std::size_t;
        auto saveToFile(const std::filesystem::path& filePath) const -> void;
    private:
        auto coordToIndex(std::size_t x, std::size_t y) const -> std::size_t;
        auto writePpmHeader(std::ofstream& file) const -> void;
        auto writePpmContent(std::ofstream& file) const -> void;
        auto scaleColor(float color) const -> int;
        auto writePixelToFile(std::ofstream& file, const Color& pixel, std::uint8_t& lineLength) const -> void;

        const std::size_t _width;
        const std::size_t _height;
        std::vector<Color> _canvas;
};
