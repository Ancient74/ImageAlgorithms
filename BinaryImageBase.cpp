#include "BinaryImageBase.h"
#include <map>
#include <algorithm>
#include <functional>
#include "math.h"
int BinaryImageBase::Area()
{
	int sum = 0;
	for (int j = 0; j < GetHeight(); j++)
	{
		for (int i = 0; i < GetWidth(); i++)
		{
			sum += static_cast<int>(GetPixel(i, j));
		}
	}
	return sum;
}

int BinaryImageBase::AreaFromRegion(int x, int y, CheckType check_type)
{
	auto region = FindRegion(x, y, check_type);
	return AreaFromRegion(region);
}

int BinaryImageBase::AreaFromRegion(const Region& region)
{
    return static_cast<int>(region.size());
}

BinaryImageBase::Region BinaryImageBase::FindRegion(int x, int y, CheckType check_type)
{
	bool pixel = GetPixel(x, y);
	Region region;
	FindRegionRecursion(x, y, pixel, check_type, region);
	return region;
}

void BinaryImageBase::FindRegionRecursion(int x, int y, bool pixel_type, CheckType check_type, Region& region) 
{
	if (x < 0 || y < 0 || x >= GetWidth() || y >= GetHeight())
		return;

	bool current_pixel = GetPixel(x, y);
	if (current_pixel != pixel_type)
		return;

	auto find_result = std::find(region.begin(), region.end(), std::make_pair(x, y));
	if (find_result != region.end())
		return;

	region.push_back(std::make_pair(x, y));

	FindRegionRecursion(x - 1, y, pixel_type, check_type, region);
	FindRegionRecursion(x + 1, y, pixel_type, check_type, region);
	FindRegionRecursion(x, y - 1, pixel_type, check_type, region);
	FindRegionRecursion(x, y + 1, pixel_type, check_type, region);

	if (check_type == CheckType::DIAG)
	{
		FindRegionRecursion(x - 1, y - 1, pixel_type, check_type, region);
		FindRegionRecursion(x - 1, y + 1, pixel_type, check_type, region);
		FindRegionRecursion(x + 1, y - 1, pixel_type, check_type, region);
		FindRegionRecursion(x + 1, y + 1, pixel_type, check_type, region);
	}

}

std::pair<int, int> BinaryImageBase::Centroid()
{
	int area = Area();
	int sum_x = 0, sum_y = 0;
	int x_coord = 0;
	int y_coord = 0;
	for (int j = 0; j < GetHeight(); j++)
	{
		for (int i = 0; i < GetWidth(); i++)
		{
			if (GetPixel(i, j)) 
			{
				sum_x += i;
				sum_y += j;
			}
		}
	}
	if (sum_x != 0)
		x_coord = sum_x / area;
	if (sum_y != 0)
		y_coord = sum_y / area;

	return { x_coord, y_coord };
}

std::pair<int, int> BinaryImageBase::CentroidFromRegion(int x, int y, CheckType check_type)
{
	auto region = FindRegion(x, y, check_type);
	return CentroidFromRegion(region);
}

std::pair<int, int> BinaryImageBase::CentroidFromRegion(const Region& region)
{
	int area = AreaFromRegion(region);
	int sum_x = 0, sum_y = 0;
	int x_coord = 0;
	int y_coord = 0;

	for (auto index : region)
	{
		sum_x += index.first;
		sum_y += index.second;
	}

	if (sum_x != 0)
		x_coord = sum_x / area;
	if (sum_y != 0)
		y_coord = sum_y / area;

	return { x_coord, y_coord };
}

BinaryImageBase::BoundingBox BinaryImageBase::GetBoundingBox(const Region& region)
{
	BoundingBox res;

	res.right = *std::min_element(region.begin(), region.end(), [&](Index a, Index b) -> bool {
			return (a.first > b.first);
		});
	res.top = *std::min_element(region.begin(), region.end(), [&](Index a, Index b)  -> bool {
		return (a.second < b.second);
	});
	res.left = *std::min_element(region.begin(), region.end(), [&](Index a, Index b) -> bool {
		return (a.first < b.first);
	});
	res.bottom = *std::min_element(region.begin(), region.end(), [&](Index a, Index b)  -> bool {
		return (a.second > b.second);
	});

	res.rect_right_bottom = { res.right.first, res.bottom.second };
	res.rect_right_top = { res.right.first, res.top.second };

	res.rect_left_bottom = { res.left.first, res.bottom.second };
	res.rect_left_top = { res.left.first, res.top.second };

	std::vector<Index> tops, rights, lefts, bottoms;
	std::copy_if(region.begin(), region.end(), std::back_inserter(tops), [&](Index a) { return res.top.second == a.second;});

	res.top_left = *std::min_element(tops.begin(), tops.end(), [](Index a, Index b) { return a.first < b.first;});
	res.top_right = *std::max_element(tops.begin(), tops.end(), [](Index a, Index b) { return a.first < b.first;});

	std::copy_if(region.begin(), region.end(), std::back_inserter(rights), [&](Index a) { return res.right.first == a.first;});
	res.right_top = *std::min_element(rights.begin(), rights.end(), [](Index a, Index b) { return a.second < b.second;});
	res.right_bottom = *std::max_element(rights.begin(), rights.end(), [](Index a, Index b) { return a.second < b.second;});

	std::copy_if(region.begin(), region.end(), std::back_inserter(lefts), [&](Index a) { return res.left.first == a.first;});
	res.left_top = *std::min_element(lefts.begin(), lefts.end(), [](Index a, Index b) { return a.second < b.second;});
	res.left_bottom = *std::max_element(lefts.begin(), lefts.end(), [](Index a, Index b) { return a.second < b.second;});

	std::copy_if(region.begin(), region.end(), std::back_inserter(bottoms),[&](Index a) { return res.bottom.second == a.second;});
	res.bottom_left = *std::min_element(bottoms.begin(), bottoms.end(), [](Index a, Index b) { return a.first < b.first;});
	res.bottom_right = *std::max_element(bottoms.begin(), bottoms.end(), [](Index a, Index b) { return a.first < b.first;});

	return res;
}


double BinaryImageBase::SecondMoment(const Region &region, SecondMomentType type)
{
    int area = AreaFromRegion(region);
    int sum = 0;
    auto centroid = CentroidFromRegion(region);
    std::function<int(std::pair<int, int>)> formula;
    if(type == SecondMomentType::ROW)
        formula = [&](std::pair<int, int> index) { return (index.first - centroid.first)*(index.first - centroid.first); };
    else if (type == SecondMomentType::COLUMN)
        formula = [&](std::pair<int, int> index) { return (index.second - centroid.second)*(index.second - centroid.second); };
    else
        formula = [&](std::pair<int, int> index) { return (index.first - centroid.first)*(index.second - centroid.second); };

    for(auto index : region)
    {
        sum += formula(index);
    }
    return sum / static_cast<double>(area);
}

double BinaryImageBase::AxisMoment(const Region &region, Index first, Index second)
{
    int dot = first.first * second.first + first.second * second.second;
    double first_mag = std::sqrt( static_cast<double>(first.first*first.first +  first.second*first.second));
    double second_mag = std::sqrt( static_cast<double>(second.first*second.first +  second.second*second.second));
    double alpha = std::acos( dot / (first_mag * second_mag));
    double betta = alpha + 3.1415 / 2.0;

    double sum = 0;
    auto centriod = CentroidFromRegion(region);

    for(auto index : region)
    {
        double element = ((index.first - centriod.first)*std::cos(betta)) + ((index.second - centriod.second)*std::sin(betta));
        sum += element*element;
    }
    return sum / static_cast<double>(AreaFromRegion(region));
}




