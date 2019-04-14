#pragma once
#include "BinaryImageBase.h"

struct PixelData 
{
	int class_id;
};

//decorator for storing pixel data
class DataBinaryImage : public BinaryImageBase
{
public:
	typedef std::map<std::pair<int, int>, PixelData> ImageData;
	DataBinaryImage(BinaryImageBase* image);

	bool GetPixel(int x, int y) const override;
	void SetPixel(int x, int y, bool pixel) override;
	int GetSize() const override;
	int GetWidth() const override;
	int GetHeight() const override;

	void ResetImageData();

	bool IsDirty() { return m_dirty; }

	PixelData GetData(int x, int y) const;
	void SetData(int x, int y, PixelData data);

	virtual void DoMarking(CheckType check_type);

protected:
	std::pair<int, int> GetIndex(int x, int y) const;

	ImageData m_image_data;
	BinaryImageBase* m_image;
	bool m_dirty;

private:
	Region PriorNeighbors(int x, int y, CheckType check_type);
	std::vector<int> Labels(const Region& region);
};

