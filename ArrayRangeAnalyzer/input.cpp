#include "input.h"

Input::Input()
{

}

Input::~Input()
{

}

bool Input::readData(const QStringList &inputFileNames, QVector <Index> &vars, QVector <Array> &arrs, QStringList &expr)
{
	return true;
}

void Input::readVarInfo(const QString fileName, QVector <Index> &vars) throw(QString&)
{
	QFile file(fileName);

	if (file.open(QIODevice::ReadOnly))
	{
		QXmlStreamReader reader(&file);
		int i = 1;

		while (!reader.atEnd() && !reader.hasError())
		{	
			QXmlStreamReader::TokenType token = reader.readNext();

			/*! ���� ���������� ����������� ��� variable */
			if (token == QXmlStreamReader::StartElement && reader.name() == "variable")
			{	
				Index var;
				/*! ������ ������ ����� 3 ���������� */
				if (i > 3)
				{
					QString errorString = "You can't use more than 3 variables in " + fileName + " file";
					throw errorString;
				}

				/*! �������� �������� ���� variable */
				QXmlStreamAttributes atrs = reader.attributes();

				try
				{
					/*! ������ �������� ��������� ���� variable */
					readVarAttributes(var, atrs, i);
				}
				catch (...)
				{
					file.close();
					throw;
				}
				/*! ��������� ��������� ���������� � ������ */
				vars << var;
			}
			/*! ���� ���������� ����������� ��� variable */
			else if (token == QXmlStreamReader::EndElement && reader.name() == "variable")
				++i;
			/*! ���� ���������� ����������� ��� */
			else if (token == QXmlStreamReader::StartElement && reader.name() != "arrayRanges")
			{
				file.close();
				QString errorString = "Unknown tag \"" + reader.name().toString() + "\"";
				throw errorString;
			}
		}

		file.close();

		/*! ������ � ��������� xml ����� */
		if (reader.hasError())
		{
			QString errorString = "File structure error in the file " + fileName + " containing the variable's info";
			throw errorString;
		}

		/*! � ����� �� ������ ���������� */
		if (vars.isEmpty())
		{
			QString errorString = "There is no variables info in " + fileName + " file";
			throw errorString;
		}
		/*! �������� �� ��������������� ����� */
		checkNonExecutableCycle(vars);
	}
	else
	{
		QString errorString = "Can't open the file " + fileName;
		throw errorString;
	}
}

void Input::readVarAttributes(Index &var, QXmlStreamAttributes &atrs, int i) throw(QString&)
{
	QString tmpString;
	Operations ops;

	/*! ������ �������� ��������� name � ���� variable */
	if (atrs.hasAttribute("name"))
	{
		tmpString = atrs.value("name").toString();
		if (tmpString == QString(""))
		{
			QString errorString = "The value of attribute \"name\" in the " + QString::number(i) + " \"variable\" tag is not set";
			throw errorString;
		}
		else
			var.name = tmpString;
	}
	else
	{
		QString errorString = "Missed attribute \"name\" in the " + QString::number(i) + " \"variable\" tag";
		throw errorString;
	}

	/*! ������ �������� ��������� from � ���� variable */
	if (atrs.hasAttribute("from"))
	{
		tmpString = atrs.value("from").toString();
		if (tmpString == QString(""))
		{
			QString errorString = "The value of attribute \"from\" in the " + QString::number(i) + " \"variable\" tag is not set";
			throw errorString;
		}
		else if (!ops.isIntNumber(tmpString))
		{
			QString errorString = "The value of attribute \"from\" in the " + QString::number(i) + " \"variable\" tag is not an integer value";
			throw errorString;
		}
		else
		{
			var.curValue = var.from = tmpString.toInt();

		}
	}
	else
	{
		QString errorString = "Missed attribute \"from\" in the " + QString::number(i) + " \"variable\" tag";
		throw errorString;
	}

	/*! ������ �������� ��������� to � ���� variable */
	if (atrs.hasAttribute("to"))
	{
		tmpString = atrs.value("to").toString();
		if (tmpString == QString(""))
		{
			QString errorString = "The value of attribute \"to\" in the " + QString::number(i) + " \"variable\" tag is not set";
			throw errorString;
		}
		else if (!ops.isIntNumber(tmpString))
		{
			QString errorString = "The value of attribute \"to\" in the " + QString::number(i) + " \"variable\" tag is not an integer value";
			throw errorString;
		}
		else
			var.to = tmpString.toInt();
	}
	else
	{
		QString errorString = "Missed attribute \"to\" in the " + QString::number(i) + " \"variable\" tag";
		throw errorString;
	}

	/*! ������ �������� ��������� step � ���� variable */
	if (atrs.hasAttribute("step"))
	{
		tmpString = atrs.value("step").toString();
		if (tmpString == QString(""))
		{
			QString errorString = "The value of attribute \"step\" in the " + QString::number(i) + " \"variable\" tag is not set";
			throw errorString;
		}
		else if (!ops.isIntNumber(tmpString))
		{
			QString errorString = "The value of attribute \"step\" in the " + QString::number(i) + " \"variable\" tag is not an integer value";
			throw errorString;
		}
		else if (tmpString.toInt() == 0)
		{
			QString errorString = "The value of attribute \"step\" in the " + QString::number(i) + " \"variable\" tag can't be 0";
			throw errorString;
		}
		else
			var.step = tmpString.toInt();
	}
	else
	{
		QString errorString = "Missed attribute \"step\" in the " + QString::number(i) + " \"variable\" tag";
		throw errorString;
	}
}

void Input::readArrInfo(const QString fileName, QVector <Array> &arrs) throw(QString&)
{
	QFile file(fileName);

	if (file.open(QIODevice::ReadOnly))
	{
		QXmlStreamReader reader(&file);
		int i = 1;

		while (!reader.atEnd() && !reader.hasError())
		{
			QXmlStreamReader::TokenType token = reader.readNext();
			/*! ���� ���������� ����������� ��� array */
			if (token == QXmlStreamReader::StartElement && reader.name() == "array")
			{
				Array arr;
				/*! �������� �������� ���� array */
				QXmlStreamAttributes atrs = reader.attributes();
				try
				{
					/*! ������ �������� ��������� ���� array */
					readArrAttributes(arr, atrs, i);
				}
				catch (...)
				{
					file.close();
					throw;
				}
				/*! ��������� ��������� ������ � ������ */
				arrs << arr;
			}
			/*! ���� ���������� ����������� ��� array */
			else if (token == QXmlStreamReader::EndElement && reader.name() == "array")
				++i;
			/*! ���� ���������� ����������� ��� */
			else if (token == QXmlStreamReader::StartElement && reader.name() != "arrayInfo")
			{
				QString errorString = "Unknown tag \"" + reader.name().toString() + "\"";
				throw errorString;
			}
		}

		file.close();

		/*! ������ � ��������� xml ����� */
		if (reader.hasError())
		{
			QString errorString = "File structure error in the file " + fileName + " containing the array's info";
			throw errorString;
		}

		/*! � ����� �� ������ ������� */
		if (arrs.isEmpty())
		{
			QString errorString = "There no arrays info in " + fileName + " file";
			throw errorString;
		}

	}
	else
	{
		QString errorString = "Can't open the file " + fileName;
		throw errorString;
	}
}

void Input::readArrAttributes(Array &arr, QXmlStreamAttributes &atrs, int i) throw(QString&)
{
	auto it = atrs.begin();
	auto itEnd = atrs.end();
	QString tmpString;
	Operations ops;
	int dimNum = 1;
	QString dimSize = "dim" + QString::number(dimNum) + "size";

	/*! �������� ������� ���������� */
	if (!atrs.hasAttribute("name"))
	{
		QString errorString = "Missed attribute \"name\" in the " + QString::number(i) + " \"array\" tag";
		throw errorString;
	}
	if (!atrs.hasAttribute("dim1size"))
	{
		QString errorString = "Missed attribute \"dim1size\" in the " + QString::number(i) + " \"array\" tag";
		throw errorString;
	}
	if (!atrs.hasAttribute("elements"))
	{
		QString errorString = "Missed attribute \"elements\" in the " + QString::number(i) + " \"array\" tag";
		throw errorString;
	}

	/*! ������ �������� ��������� ���� array */
	for (it; it != itEnd; ++it)
	{
		/*! ������ �������� name */
		if ((*it).name() == "name")
		{
			tmpString = (*it).value().toString();
			if (tmpString == QString(""))
			{
				QString errorString = "The value of attribute \"name\" in the " + QString::number(i) + " \"array\" tag is not set";
				throw errorString;
			}
			else
				arr.name = tmpString;
		}
		/*! ������ �������� elements */
		else if ((*it).name() == "elements")
		{
			QString elementsString = (*it).value().toString();
			if (elementsString == QString(""))
			{
				QString errorString = "The value of attribute \"elements\" in the " + QString::number(i) + " \"array\" tag is not set";
				throw errorString;
			}
			else
			{
				int j = 0;
				QStringList elements = elementsString.split(" ");
				while (j < elements.size())
				{
					arr.elements << elements[j].toInt();
					++j;
				}
			}

		}
		/*! ������ �������� dimSize */
		else if ((*it).name() == dimSize)
		{
			tmpString = (*it).value().toString();
			if (tmpString == QString(""))
			{
				QString errorString = "The value of attribute \"" + dimSize + "\" in the " + QString::number(i) + " \"array\" tag is not set";
				throw errorString;
			}
			else if (!ops.isPositiveIntNumber(tmpString))
			{
				QString errorString = "The size of the " + QString::number(dimNum) + " dimension of \"" + arr.name + "\" array is not a positive integer value";
				throw errorString;
			}
			else if (tmpString.toInt() == 0)
			{
				QString errorString = "The value of attribute \"" + dimSize + "\" in the " + QString::number(i) + " \"array\" tag can't be 0";
				throw errorString;
			}
			else
			{
				arr.size << tmpString.toInt();
				arr.isExceeding << false;
				++dimNum;
				dimSize = "dim" + QString::number(dimNum) + "size";
			}
		}
	}
}

void Input::readExpression(const QString fileName, QStringList &expr, const QVector<Index> &vars, const QVector<Array> &arrs) throw(QString&)
{

}

void Input::checkNonExecutableCycle(QVector<Index> &vars) throw(QString&)
{

}

void Input::removeUnusedVarsAndArrs(QVector<Array> &arrs, QVector<Index> &vars, QStringList &expr)
{

}
