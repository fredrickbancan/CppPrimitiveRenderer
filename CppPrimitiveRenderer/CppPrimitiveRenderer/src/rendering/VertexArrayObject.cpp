#include "VertexArrayObject.h"

VertexArrayObject::VertexArrayObject()
{
	glGenVertexArrays(1, &vaoID);
}

VertexArrayObject::~VertexArrayObject()
{
}

void VertexArrayObject::beginBuilding()
{
	glBindVertexArray(vaoID);
}

void VertexArrayObject::addDynamicBuffer(int initialByteSize, VertexBufferLayout& layout)
{
	VertexBuffer vbo(layout);
	vbo.initDynamic(initialByteSize);
	vbos.push_back(vbo);
}

void VertexArrayObject::finishBuilding()
{
	for (std::vector<VertexBuffer>::iterator i = vbos.begin(); i != vbos.end(); i++)
	{
		VertexBuffer vboAt = *i;
		vboAt.bind();
		int offset = 0;
		int attribIterator = 0;
		for (std::vector<VertexBufferElement>::const_iterator j = vboAt.getLayout().getElements().begin(); j != vboAt.getLayout().getElements().end(); j++)
		{
			VertexBufferElement vboEAt = *j;
			glEnableVertexAttribArray(attribIterator);
			glVertexAttribPointer(attribIterator, vboEAt.count, (GLenum)vboEAt.type, (GLboolean)vboEAt.normalized,  (GLsizei)vboAt.getLayout().getStride(), (const void*)offset);
			attribIterator++;
			offset += vboEAt.count * VertexBufferElement::getSizeOfType(vboEAt.type);
		}
	}
}

void VertexArrayObject::bind()
{
	glBindVertexArray(vaoID);
	for (std::vector<VertexBuffer>::iterator i = vbos.begin(); i != vbos.end(); i++)
	{
		i->bind();
	}
}

void VertexArrayObject::resizeBuffer(int index, int newSizeBytes)
{
	vbos[index].resizeBuffer(newSizeBytes);
}

void VertexArrayObject::updateBuffer(int index, const void* data, int bytesToUpdate)
{
	vbos[index].updateData(data, bytesToUpdate);
}
