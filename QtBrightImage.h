#pragma once
#include <QImage>
#include "ibrightimage.h"

class QtBrightImage : public IBrightImage
{
public:
    static std::unique_ptr<QtBrightImage> FromQtImage(const QImage& image);

    int GetPixel(int x, int y) const override;
    void SetPixel(int x, int y, int value) override;
    int GetSize() const override;
    int GetWidth() const override;
    int GetHeight() const override;

protected:
    int GetIndex(int x, int y) const {return x + GetWidth()*y;}

private:
    std::vector<int> m_image;
    int m_width;
    int m_height;
};

