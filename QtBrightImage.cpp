#include "QtBrightImage.h"
#include <QRgb>

std::unique_ptr<QtBrightImage> QtBrightImage::FromQtImage(const QImage& image)
{
    std::unique_ptr<QtBrightImage> res = std::make_unique<QtBrightImage>();
    res->m_width = image.size().width();
    res->m_height = image.size().height();
    res->m_image.resize(static_cast<size_t>(res->GetSize()));
    for (int j = 0; j < res->GetHeight(); j++)
    {
        for (int i = 0; i < res->GetWidth(); i++)
        {
            res->SetPixel(i, j, qGray(image.pixel(i, j)));
        }
    }
    return res;
}

int QtBrightImage::GetPixel(int x, int y) const
{
    return m_image[static_cast<size_t>(GetIndex(x, y))];
}

void QtBrightImage::SetPixel(int x, int y, int value)
{
    m_image[static_cast<size_t>(GetIndex(x, y))] = value;
}

int QtBrightImage::GetSize() const
{
    return GetWidth()*GetHeight();
}
int QtBrightImage::GetWidth() const
{
    return m_width;
}
int QtBrightImage::GetHeight() const
{
    return m_height;
}
