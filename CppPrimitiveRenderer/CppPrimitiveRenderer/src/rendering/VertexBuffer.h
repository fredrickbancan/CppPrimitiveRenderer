#pragma once
#include "VertexBufferLayout.h"
class VertexBuffer
{
public:
	VertexBuffer(VertexBufferLayout& layout);
	void initDynamic(int initialByteSize);
	void resizeBuffer(int newByteSize);
	void updateData(const void* data, int size);
	void bind();
	void destroy();
    VertexBufferLayout& getLayout()  { return layout; }
private:
	VertexBufferLayout layout;
	//cherno calls this renderer id but its more like buffer id.
	unsigned int bufferInt;
};