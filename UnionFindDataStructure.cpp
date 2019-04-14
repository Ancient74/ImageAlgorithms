#include "UnionFindDataStructure.h"

int UnionFindDataStructure::Find(int label)
{
	if (m_data.find(label) == m_data.end())
		m_data[label] = 0;

	int j = label;
	while (m_data[j] != 0)
	{
		j = m_data[j];
	}
	return j;
}

void UnionFindDataStructure::Union(int label1, int label2)
{
	int j = Find(label1);
	int k = Find(label2);
	
	if (j != k)
	{
		m_data[k] = j;
	}
}
