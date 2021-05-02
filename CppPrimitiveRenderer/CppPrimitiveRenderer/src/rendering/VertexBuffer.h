#pragma once
#include "VertexBufferLayout.h"
class VertexBuffer
{
public:
	VertexBuffer(VertexBufferLayout& layout);
	~VertexBuffer();
	void initDynamic(int initialByteSize);
	void resizeBuffer(int newByteSize);
	void updateData(const void* data, int size);
	void bind();
	const VertexBufferLayout getLayout() const { return layout; }
private:
	VertexBufferLayout layout;
	//cherno calls this renderer id but its more like buffer id.
	unsigned int bufferInt;
};