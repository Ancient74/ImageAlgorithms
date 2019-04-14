#pragma once
#include"IBinaryImage.h"

class BinaryImageOperations
{
public:
	static void PerformDilation(const IBinaryImage& input, const IBinaryImage& struct_element, IBinaryImage& output);
	static void PerformConditionalDilation(const IBinaryImage& input, const IBinaryImage& struct_element, IBinaryImage& output);
	static void PerformErosion(const IBinaryImage& input, const IBinaryImage& struct_element, IBinaryImage& output);
	static void PerformClosing(const IBinaryImage& input, const IBinaryImage& struct_element, IBinaryImage& output);
	static void PerformOpening(const IBinaryImage& input, const IBinaryImage& struct_element, IBinaryImage& output);
};