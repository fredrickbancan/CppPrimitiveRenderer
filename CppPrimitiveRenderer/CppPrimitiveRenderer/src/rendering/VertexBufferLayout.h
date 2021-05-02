#pragma once
#include <vector>
#include <GL/glew.h>
/*holds the layout elements*/
struct VertexBufferElement
{
	int type;
	int count;
	unsigned char normalized;

	static int getSizeOfType(int type)
	{
		switch (type)
		{
		case GL_FLOAT: return 4;

		case GL_UNSIGNED_INT: return 4;

		case GL_UNSIGNED_BYTE: return 1;
		}
		__debugbreak();
		return 0;
	}
};

class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> elements;
	/*stride holds the size in bytes of elements we push to the layout.*/
	int stride;
public:
	void add(int vertexAttribPtrType, int count, bool normalized)
	{
		elements.push_back({ vertexAttribPtrType, count, (unsigned char)normalized });
		stride += count * VertexBufferElement::getSizeOfType(vertexAttribPtrType);
	}
	const std::vector<VertexBufferElement> getElements() const
	{
		return elements;
	}
	unsigned int getStride() const
	{
		return stride;
	}
};

