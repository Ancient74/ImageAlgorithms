#pragma once
#include "BinaryImageBase.h"
#include<vector>
#include<memory>
#include"ibrightimage.h"
#include "ITreshHoldAlgorithm.h"
class BinaryImage :
	public BinaryImageBase
{
public:
	BinaryImage(int width, int height);
	BinaryImage(const std::vector<bool>&image, int width, int height);
    virtual ~BinaryImage() = default;
    BinaryImage(const BinaryImage&) = delete;
	BinaryImage& operator=(const BinaryImage&) = delete;

	bool GetPixel(int x, int y) const override;
	void SetPixel(int x, int y, bool pixel) override;
	int GetSize() const override;
	int GetWidth() const override;
	int GetHeight() const override;

    static std::unique_ptr<BinaryImage> FromBrightImage(const IBrightImage& image, IThreshHoldAlgorithm& alg);

protected:
	int GetIndex(int x, int y) const;

	std::vector<bool> m_image;
	int m_width;
	int m_height;
};

