#pragma once
#include"IBinaryImage.h"

class IBinaryImageRenderer {
public:
	virtual void Draw(const IBinaryImage& image) const = 0;
};