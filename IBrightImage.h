#pragma once
#include <vector>
class IBrightImage
{
public:
    virtual int GetPixel(int x, int y) const = 0;
    virtual void SetPixel(int x, int y, int value) = 0;
    virtual int GetSize() const = 0;
    virtual int GetWidth() const = 0;
    virtual int GetHeight() const = 0;

    static std::vector<int> GetBrightnessHistogram(const IBrightImage& image)
    {
        std::vector<int> histogram(256);
        for (int j = 0; j < image.GetHeight(); j++)
        {
            for (int i = 0; i < image.GetWidth(); i++)
            {
                size_t grey = static_cast<size_t>(image.GetPixel(i, j));
                histogram[grey]++;
            }
        }
        return histogram;
    }
};
