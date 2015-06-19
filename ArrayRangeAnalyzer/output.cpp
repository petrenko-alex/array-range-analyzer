#include "output.h"

Output::Output()
{
	this->errorFileName = "ArrayRangeAnalyzer-Errors.txt";
	this->resultFileName = "ArrayRangeAnalyzer-Results.txt";
}

Output::~Output()
{

}

void Output::writeError(QString &errorString)
{

}

void Output::makeOutputFile(QVector<Exceeding> &exceedings, const QVector<Array> &arrs, const QStringList &inputFileNames)
{

}

bool Output::isErrorOccured()
{
	return false;
}
