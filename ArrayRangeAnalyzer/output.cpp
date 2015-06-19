#include "output.h"

static bool isError = false;

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
	QString intro("*******************************************Array Range Analyzer*******************************************");
	isError = true;
	QFile file(errorFileName);
	/*! ���������� ���������� ������ � ���� */
	if (file.open(QIODevice::Append))
	{
		QTextStream out(&file);
		out << intro << endl << endl;
		out << errorString << endl << endl;
		file.close();
	}
}

void Output::makeOutputFile(QVector<Exceeding> &exceedings, const QVector<Array> &arrs, const QStringList &inputFileNames)
{
	QFile file(resultFileName);
	QString intro("*******************************************Array Range Analyzer*******************************************");
	QString leftSqBracket("[");
	QString rightSqBracket("]");
	QString arrName;
	QString mainInfo = "No exceedings are detected";
	bool exceedingForCurrentArray = false;
	int arrsNumber = arrs.size();
	int exceedingNumber = 0;

	if (file.open(QIODevice::WriteOnly))
	{
		/*! ������� � ���� ����� ������ ������� ������ */
		QTextStream out(&file);
		out << intro << endl << endl;
		out << "File with variables:  " << inputFileNames[0] << endl;
		out << "File with arrays:     " << inputFileNames[1] << endl;
		out << "File with expression: " << inputFileNames[2] << endl << endl;

		/*! ������������ � ����� ���������� � ������ */
		/*! �� ���� ������������ � ��������� �������� */
		for (int i = 0; i < arrsNumber; ++i)
		{
			/*! ������������ ����� ������� � �������� */
			arrName = "Array " + arrs[i].name;
			int dimensionsNumber = arrs[i].size.size();
			for (int j = 0; j < dimensionsNumber; ++j)
			{
				arrName += leftSqBracket + QString::number(arrs[i].size[j]) + rightSqBracket;
			}
			/*! ����� ����� ������� � ���� */
			out << arrName << endl;

			/*! �������� ������� ������ ��� ������� */
			int k = 0;
			for (auto &exc : exceedings)
			{
				if (arrs[i].name == exc.arrayName)
				{
					exceedingForCurrentArray = true;
					exceedingNumber = k;
					mainInfo = "Exceeding is detected in " + QString::number(exc.dimension) + QString(" dimension");
				}
				++k;
			}

			/*! ���� ��� �������� ������� ����� ��������� */
			if (exceedingForCurrentArray)
			{
				/*! ������������ ���������� � ������ */
				int indexNumber = exceedings[exceedingNumber].indexName.size();
				QString indexes("Variables ");
				for (int j = 0; j < indexNumber; ++j)
				{
					indexes += exceedings[exceedingNumber].indexName[j] + " = " + QString::number(exceedings[exceedingNumber].indexValue[j]) + "; ";
				}
				QString requestedElement("RequestedElement - ");
				requestedElement += QString::number(exceedings[exceedingNumber].requestedElement);
				exceedings.remove(exceedingNumber);
				exceedingNumber = 0;

				/*! ����� ���������� � ������ � ���� */
				out << mainInfo << endl;
				out << indexes << endl;
				out << requestedElement << endl << endl;
				exceedingForCurrentArray = false;
			}
			/*! ���� ����� �� ��������� ��� �������� ������� */
			else
			{
				/*! ������� ���������� �� ���� */
				mainInfo = "No exceedings are detected";
				out << mainInfo << endl << endl;
			}
		}
		out << intro << endl;
		file.close();
	}
}

bool Output::isErrorOccured()
{
	return false;
}
