#pragma once
#include "IBinaryImage.h"
#include <vector>
#include <map>

enum CheckType {
	CROSS, // top, left, right, bottom search
	DIAG // CROSS & diagonal elements included
};

enum SecondMomentType {
    ROW,
    COLUMN,
    MIXED
};

class BinaryImageBase :
	public IBinaryImage
{
public:
	typedef std::pair<int, int> Index;
	typedef std::vector<Index> Region;

	struct BoundingBox
	{
		Index rect_right_top;
		Index rect_right_bottom;
		Index rect_left_top;
		Index rect_left_bottom;

		Index top_left;
		Index top_right;

		Index right_top;
		Index right_bottom;

		Index bottom_left;
		Index bottom_right;

		Index left_top;
		Index left_bottom;

		Index top;
		Index left;
		Index right;
		Index bottom;
	};

	virtual int Area();
	virtual Index Centroid();

	//Calculate area for the region that contains pixel[x][y]
	virtual int AreaFromRegion(int x, int y, CheckType check_type);
	virtual int AreaFromRegion(const Region& region);

	virtual Index CentroidFromRegion(int x, int y, CheckType check_type);
	virtual Index CentroidFromRegion(const Region& region);

	virtual BoundingBox GetBoundingBox(const Region& region);

    virtual double SecondMoment(const Region& region, SecondMomentType type);
    virtual double AxisMoment(const Region& region, Index first, Index second);

	virtual Region FindRegion(int x, int y, CheckType check_type);

private:
	void FindRegionRecursion(int x, int y, bool pixel_type, CheckType check_type, Region& region);
};

