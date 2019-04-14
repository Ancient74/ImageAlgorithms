#include"BinaryImageOperations.h"
#include<assert.h>
#include"BinaryImage.h"

void BinaryImageOperations::PerformDilation(const IBinaryImage& input, const IBinaryImage& struct_element, IBinaryImage& output)
{
	assert(struct_element.GetSize() > 0);
	assert(input.GetSize() > 0);
	assert(output.GetSize() == input.GetSize());

	auto apply_struct_element = [&](int x, int y) {
		for (int j = 0; j < struct_element.GetHeight(); j++)
		{
			for (int i = 0; i < struct_element.GetWidth(); i++)
			{
				int offset_x = x + i;
				int offset_y = y + j;

				if (offset_x >= input.GetWidth() || offset_y >= input.GetHeight())
					continue;

				output.SetPixel(offset_x, offset_y, output.GetPixel(offset_x, offset_y) || input.GetPixel(offset_x, offset_y) || struct_element.GetPixel(i, j));
			}
		}
	};

	for (int j = 0; j < input.GetHeight(); j++)
	{
		for (int i = 0; i < input.GetWidth(); i++)
		{
			bool is_applicable = input.GetPixel(i, j);
			if (!is_applicable) continue;

			apply_struct_element(i, j);
		}
	}
}

void BinaryImageOperations::PerformErosion(const IBinaryImage& input, const IBinaryImage& struct_element, IBinaryImage& output)
{
	assert(struct_element.GetSize() > 0);
	assert(input.GetSize() > 0);
	assert(output.GetSize() == input.GetSize());

	auto apply_struct_element = [&](int x, int y) {
		for (int j = 0; j < struct_element.GetHeight(); j++)
		{
			for (int i = 0; i < struct_element.GetWidth(); i++)
			{
				int offset_x = x + i;
				int offset_y = y + j;

				if (offset_x >= input.GetWidth() || offset_y >= input.GetHeight())
					continue;

				output.SetPixel(offset_x, offset_y, ((i == 0) && (j == 0)));
			}
		}
	};

	auto check_struct_element = [&](int x, int y)->bool {
		for (int j = 0; j < struct_element.GetHeight(); j++)
		{
			for (int i = 0; i < struct_element.GetWidth(); i++)
			{
				int offset_x = x + i;
				int offset_y = y + j;

				if (offset_x >= input.GetWidth() || offset_y >= input.GetHeight())
					return false;

				if (input.GetPixel(offset_x, offset_y) != struct_element.GetPixel(i, j))
					return false;
			}
		}
		return true;
	};

	for (int j = 0; j < input.GetHeight(); j++)
	{
		for (int i = 0; i < input.GetWidth(); i++)
		{
			bool is_applicable = check_struct_element(i, j);
			if (!is_applicable) continue;

			apply_struct_element(i, j);
		}
	}
}

void BinaryImageOperations::PerformClosing(const IBinaryImage& input, const IBinaryImage& struct_element, IBinaryImage& output)
{
	BinaryImage temp(input.GetWidth(), input.GetHeight());
	PerformDilation(input, struct_element, temp);
	PerformErosion(temp, struct_element, output);
}

void BinaryImageOperations::PerformOpening(const IBinaryImage& input, const IBinaryImage& struct_element, IBinaryImage& output)
{
	BinaryImage temp(input.GetWidth(), input.GetHeight());
	PerformErosion(input, struct_element, temp);
	PerformDilation(temp, struct_element, output);
}

void BinaryImageOperations::PerformConditionalDilation(const IBinaryImage& input, const IBinaryImage& struct_element, IBinaryImage& output)
{
	BinaryImage temp(input.GetWidth(), input.GetHeight());
	PerformDilation(input, struct_element, temp);
	for (int j = 0; j < input.GetHeight(); j++)
	{
		for (int i = 0; i < input.GetWidth(); i++)
		{
			output.SetPixel(i, j, temp.GetPixel(i, j) == input.GetPixel(i, j));
		}
	}
}

