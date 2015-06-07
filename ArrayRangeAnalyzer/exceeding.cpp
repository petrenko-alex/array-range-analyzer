#include "exceeding.h"

exceeding::exceeding()
{
	arrayName		 = "";
	indexName;
	indexValue;
	requestedElement = 0;
	dimension		 = 0;
}

exceeding::exceeding(QString arrayName, QStringList indexName, QVector<double> indexValue, int requestedElement, int dimension)
{
	this->arrayName		   = arrayName;
	this->indexName		   = indexName;
	this->indexValue	   = indexValue;
	this->requestedElement = requestedElement;
	this->dimension		   = dimension;
}

bool exceeding::operator==(const exceeding &other)
{
	return this->arrayName		  == other.arrayName
		&& this->indexName		  == other.indexName
		&& this->indexValue		  == other.indexValue
		&& this->requestedElement == other.requestedElement
		&& this->dimension		  == other.dimension;
}

exceeding::~exceeding()
{

}
