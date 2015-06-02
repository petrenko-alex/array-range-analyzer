#include "array.h"

Array::Array()
{
	this->name = "";
	this->size;
	this->elements;
	this->isExceeding;
}

Array::Array(QString name, QVector<int> &size, QVector<int> &elements)
{
	this->name     = name;
	this->size     = size;
	this->elements = elements;
}

bool Array::operator==(const Array &other)
{
	return this->name        == other.name
		&& this->size        == other.size
		&& this->elements    == other.elements
		&& this->isExceeding == other.isExceeding;
}

Array::~Array()
{
}
