#include "VertexArrayObject.h"

VertexArrayObject::VertexArrayObject()
{
	glGenVertexArrays(1, &vaoID);
}

VertexArrayObject::~VertexArrayObject()
{
	for (std::vector<VertexBuffer>::iterator i = vbos.begin(); i != vbos.end(); i++)
	{
		i->destroy();
	}
	glDeleteVertexArrays(1, &vaoID);
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
		i->bind();
		int offset = 0;
		int attribIterator = 0;
		for (std::vector<VertexBufferElement>::const_iterator j = i->getLayout().getElements().begin(); j != i->getLayout().getElements().end(); j++)
		{
			glEnableVertexAttribArray(attribIterator);
			glVertexAttribPointer(attribIterator, j->count, (GLenum)j->type, (GLboolean)j->normalized,  (GLsizei)i->getLayout().getStride(), (const void*)offset);
			attribIterator++;
			offset += j->count * VertexBufferElement::getSizeOfType(j->type);
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
