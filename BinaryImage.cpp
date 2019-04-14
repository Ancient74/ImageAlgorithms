#include "BinaryImage.h"
#include<assert.h>
#include "OtsuTreshHoldAlgorithm.h"
BinaryImage::BinaryImage(int width, int height) : m_width(width), m_height(height)
{
	m_image.resize(GetSize());
}

BinaryImage::BinaryImage(const std::vector<bool>& image, int width, int height) : m_image(image), m_width(width), m_height(height)
{
	assert(GetSize() == m_image.size());
}

int BinaryImage::GetSize() const
{
	return GetWidth() * GetHeight();
}

int BinaryImage::GetHeight() const
{
	return m_height;
}

int BinaryImage::GetWidth() const
{
	return m_width;
}

int BinaryImage::GetIndex(int x, int y) const 
{
	return x + GetWidth()*y;
}

bool BinaryImage::GetPixel(int x, int y) const
{
	return m_image.at(GetIndex(x, y));
}

void BinaryImage::SetPixel(int x, int y, bool value)
{
	m_image[GetIndex(x, y)] = value;
}

std::unique_ptr<BinaryImage> BinaryImage::FromBrightImage(const IBrightImage& image, IThreshHoldAlgorithm& alg)
{
    auto res = std::make_unique<BinaryImage>(image.GetWidth(), image.GetHeight());
    int treshhold = alg.FindTreshHold(image);
    for (int j = 0; j < res->GetHeight(); j++)
    {
        for (int i = 0; i < res->GetWidth(); i++)
        {
            res->SetPixel(i, j, image.GetPixel(i, j) < treshhold);
        }
    }
    return res;
}

