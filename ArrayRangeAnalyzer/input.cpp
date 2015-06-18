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

}

void Input::readArrAttributes(Array &arr, QXmlStreamAttributes &atrs, int i) throw(QString&)
{

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
