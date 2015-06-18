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

			/*! Если встретился открывающий тег variable */
			if (token == QXmlStreamReader::StartElement && reader.name() == "variable")
			{	
				Index var;
				/*! Нельзя задать более 3 переменных */
				if (i > 3)
				{
					QString errorString = "You can't use more than 3 variables in " + fileName + " file";
					throw errorString;
				}

				/*! Получаем атрибуты тега variable */
				QXmlStreamAttributes atrs = reader.attributes();

				try
				{
					/*! Читаем значения атрибутов тега variable */
					readVarAttributes(var, atrs, i);
				}
				catch (...)
				{
					file.close();
					throw;
				}
				/*! Сохраняем считанную переменную в вектор */
				vars << var;
			}
			/*! Если встретился закрывающий тег variable */
			else if (token == QXmlStreamReader::EndElement && reader.name() == "variable")
				++i;
			/*! Если встретился неизвестный тег */
			else if (token == QXmlStreamReader::StartElement && reader.name() != "arrayRanges")
			{
				file.close();
				QString errorString = "Unknown tag \"" + reader.name().toString() + "\"";
				throw errorString;
			}
		}

		file.close();

		/*! Ошибки в структуре xml файла */
		if (reader.hasError())
		{
			QString errorString = "File structure error in the file " + fileName + " containing the variable's info";
			throw errorString;
		}

		/*! В файле не заданы переменные */
		if (vars.isEmpty())
		{
			QString errorString = "There is no variables info in " + fileName + " file";
			throw errorString;
		}
		/*! Проверка на невыполняющиеся циклы */
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
