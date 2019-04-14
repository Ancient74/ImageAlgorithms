#pragma once
class IBinaryImage
{
public:
	virtual bool GetPixel(int x, int y) const = 0;
	virtual void SetPixel(int x, int y, bool pixel) = 0;
	virtual int GetSize() const = 0;
	virtual int GetWidth() const = 0;
	virtual int GetHeight() const = 0;
};

