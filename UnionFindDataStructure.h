#pragma once
#include <map>
class UnionFindDataStructure
{
public:
	int Find(int label);
	void Union(int label1, int label2);
private:
	std::map<int, int> m_data;
};

