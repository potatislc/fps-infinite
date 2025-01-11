#pragma once

#include <cstdint>
#include "glm/glm.hpp"

template <typename T>
class PixelArray
{
public:
    T* pixels = nullptr;
    int width = 0;
    int height = 0;
    PixelArray() = default;
    PixelArray(T* pixels, int width, int height) : pixels(pixels), width(width), height(height) {};
    ~PixelArray()
    {
        delete[] pixels;
    }

    static void rippleize(const PixelArray<T>& src, T* dstPixels, float freq, float amp)
    {
        int w = src.width;

        for (int y = 0; y < w; y++)
        {
            float tempY = (float)y / 4 + freq;
            for (int x = 0; x < w; x++)
            {
                float tempX = (float)x / 4 + freq;
                int rippleX = (int)(x + glm::sin(tempY) * glm::cos(tempX) * amp) % w;
                int rippleY = (int)(y + glm::sin(tempX) * glm::cos(tempY) * amp) % w;
                if (rippleX < 0) rippleX += w;
                if (rippleY < 0) rippleY += w;
                dstPixels[x + y * w] = src.pixels[rippleX + rippleY * w];
            }
        }
    }

    // Move constructor
    PixelArray(PixelArray&& other) noexcept
            : pixels(other.pixels), width(other.width), height(other.height)
    {
        other.pixels = nullptr; // Ensure the source no longer owns the data
        other.width = 0;
        other.height = 0;
    }

    // Move assignment operator
    PixelArray& operator=(PixelArray&& other) noexcept
    {
        if (this != &other) // Guard against self-assignment
        {
            delete[] pixels; // Clean up current resources
            pixels = other.pixels;
            width = other.width;
            height = other.height;

            other.pixels = nullptr; // Ensure the source no longer owns the data
            other.width = 0;
            other.height = 0;
        }
        return *this;
    }

    // Delete copy constructor and copy assignment operator to avoid accidental deep copying
    PixelArray(const PixelArray&) = delete;
    PixelArray& operator=(const PixelArray&) = delete;
};