#include "DataBinaryImage.h"
#include "UnionFindDataStructure.h"
#include <algorithm>
DataBinaryImage::DataBinaryImage(BinaryImageBase* image):m_image(image)
{
	ResetImageData();
}

void DataBinaryImage::ResetImageData()
{
	m_image_data.clear();
	for (int j = 0; j < GetHeight(); j++)
	{
		for (int i = 0; i < GetWidth(); i++)
		{
			m_image_data.insert({ {i , j}, { 0 } });
		}
	}
	m_dirty = false;
}

int DataBinaryImage::GetSize() const
{
	return m_image->GetSize();
}

int DataBinaryImage::GetHeight() const
{
	return m_image->GetHeight();
}

int DataBinaryImage::GetWidth() const
{
	return m_image->GetWidth();
}

bool DataBinaryImage::GetPixel(int x, int y) const
{
	return m_image->GetPixel(x, y);
}

std::pair<int, int> DataBinaryImage::GetIndex(int x, int y) const
{
	return { x, y };
}

void DataBinaryImage::SetPixel(int x, int y, bool value)
{
	bool prev = GetPixel(x, y);
	if (prev == value)
		return;
	m_image->SetPixel(x, y, value);
	m_dirty = true;
}

void DataBinaryImage::SetData(int x, int y, PixelData data)
{
	m_image_data.at(GetIndex(x, y)).class_id = data.class_id;
}

PixelData DataBinaryImage::GetData(int x, int y) const
{
	return m_image_data.at(GetIndex(x, y));
}

void DataBinaryImage::DoMarking(CheckType check_type)
{
	if(m_dirty)
		ResetImageData();
	UnionFindDataStructure parent;
	int label = 1;
	for (int j = 0; j < GetHeight(); j++)
	{
		for (int i = 0; i < GetWidth(); i++)
		{
			if (!GetPixel(i, j))
				continue;
			int m;
			auto neighbors = PriorNeighbors(i, j, check_type);
			auto labels = Labels(neighbors);
			
			if (neighbors.empty())
			{
				m = label;
				label++;
			}
			else
			{
				m = *std::min(labels.begin(), labels.end());
			}
			SetData(i, j, { m });
			for (auto X : labels) 
			{
				if (X == m)
					continue;
				parent.Union(m, X);
			}
		}
	}
	for (int j = 0; j < GetHeight(); j++)
	{
		for (int i = 0; i < GetWidth(); i++)
		{
			if (GetPixel(i, j)) 
			{
				SetData(i, j, { { parent.Find(GetData(i, j).class_id) } });
			}
		}
	}
}

BinaryImageBase::Region DataBinaryImage::PriorNeighbors(int x, int y, CheckType check_type)
{
	BinaryImageBase::Region res;
	bool pixel = GetPixel(x, y);
	
	auto add_pixel = [&](int i, int j) {
		if (i < 0 || j < 0 || i >= GetWidth() || j >= GetHeight())
			return;
		if (GetPixel(i, j) == pixel)
			res.push_back({ i, j });
	};

	add_pixel(x - 1, y);
	add_pixel(x, y - 1);

	if (check_type == CheckType::DIAG)
	{
		add_pixel(x - 1, y - 1);
		add_pixel(x + 1, y - 1);
	}

	return res;
}

std::vector<int> DataBinaryImage::Labels(const BinaryImageBase::Region& region) 
{
	std::vector<int> res;
	for (auto index : region)
	{
		res.push_back(m_image_data.at(index).class_id);
	}
	return res;
}