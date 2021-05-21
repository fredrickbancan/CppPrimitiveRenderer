#pragma once
#include <vector>
#include "VertexBufferLayout.h"
#include "VertexBuffer.h"
class VertexArrayObject
{
public:
	VertexArrayObject();
	~VertexArrayObject();
	void beginBuilding();
	void addDynamicBuffer(int initialByteSize, VertexBufferLayout& layout);
	void addDynamicIndicesBuffer(int initialMaxCount);
	void finishBuilding();
	void bind();
	void resizeBuffer(int index, int newSizeBytes);
	void updateBuffer(int index, const void* data, int bytesToUpdate);
	void resizeIndicesBuffer(int newMaxCount);
	void updateIndicesBuffer(unsigned int* dataStart, int count);
	unsigned int getName() const { return vaoID; }
private:
	std::vector<VertexBuffer> vbos;
	unsigned int iboID = -1;
	unsigned int vaoID = -1;
};