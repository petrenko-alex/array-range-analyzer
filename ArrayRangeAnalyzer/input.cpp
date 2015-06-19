#include "input.h"

Input::Input()
{
}

Input::~Input()
{
}

bool Input::readData(const QStringList &inputFileNames, QVector <Index> &vars, QVector <Array> &arrs, QStringList &expr)
{
	bool isSuccess = true;
	Output out;

	/* Читаем информацию о переменных */
	try
	{
		readVarInfo(inputFileNames[0], vars);
	}
	catch (QString &errorString)
	{
		errorString.prepend("File containing the information about vars:\nFilename: " + inputFileNames[0] + "\nError: ");
		isSuccess = false;
		vars.clear();
		out.writeError(errorString);
	}

	/* Читаем информацию о массивах, если чтение переменных произошло успешно */
	if (isSuccess)
	{
		try
		{
			readArrInfo(inputFileNames[1], arrs);
		}
		catch (QString &errorString)
		{
			errorString.prepend("File containing the information about arrs:\nFilename: " + inputFileNames[1] + "\nError: ");
			isSuccess = false;
			arrs.clear();
			out.writeError(errorString);
		}
	}

	/* Читаем выражение, если чтение переменных и массивов произошло успешно */
	if (isSuccess)
	{
		try
		{
			readExpression(inputFileNames[2], expr, vars, arrs);
		}
		catch (QString &errorString)
		{
			errorString.prepend("File containing the expression:\nFilename: " + inputFileNames[2] + "\nError: ");
			isSuccess = false;
			expr.clear();
			out.writeError(errorString);
		}
	}
	
	/* Освобождаем вектора переменных и массивов от неиспользующихся в выражении переменных и массивов */
	if (isSuccess)
		removeUnusedVarsAndArrs(arrs, vars, expr);

	return isSuccess;
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

			/* Если встретился открывающий тег variable */
			if (token == QXmlStreamReader::StartElement && reader.name() == "variable")
			{	
				Index var;
				/* Нельзя задать более 3 переменных */
				if (i > 3)
				{
					QString errorString = "You can't use more than 3 variables in " + fileName + " file";
					throw errorString;
				}

				/* Получаем атрибуты тега variable */
				QXmlStreamAttributes atrs = reader.attributes();

				try
				{
					/* Читаем значения атрибутов тега variable */
					readVarAttributes(var, atrs, i);
				}
				catch (...)
				{
					file.close();
					throw;
				}
				/* Сохраняем считанную переменную в вектор */
				vars << var;
			}
			/* Если встретился закрывающий тег variable */
			else if (token == QXmlStreamReader::EndElement && reader.name() == "variable")
				++i;
			/* Если встретился неизвестный тег */
			else if (token == QXmlStreamReader::StartElement && reader.name() != "arrayRanges")
			{
				file.close();
				QString errorString = "Unknown tag \"" + reader.name().toString() + "\"";
				throw errorString;
			}
		}

		file.close();

		/* Ошибки в структуре xml файла */
		if (reader.hasError())
		{
			QString errorString = "File structure error in the file " + fileName + " containing the variable's info";
			throw errorString;
		}

		/* В файле не заданы переменные */
		if (vars.isEmpty())
		{
			QString errorString = "There is no variables info in " + fileName + " file";
			throw errorString;
		}
		/* Проверка на невыполняющиеся циклы */
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

	/* Чтение значения аттрибута name в теге variable */
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

	/* Чтение значения аттрибута from в теге variable */
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

	/* Чтение значения аттрибута to в теге variable */
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

	/* Чтение значения аттрибута step в теге variable */
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
			/* Если встретился открывающий тег array */
			if (token == QXmlStreamReader::StartElement && reader.name() == "array")
			{
				Array arr;
				/* Получаем атрибуты тега array */
				QXmlStreamAttributes atrs = reader.attributes();
				try
				{
					/* Читаем значения атрибутов тега array */
					readArrAttributes(arr, atrs, i);
				}
				catch (...)
				{
					file.close();
					throw;
				}
				/* Сохраняем считанный массив в вектор */
				arrs << arr;
			}
			/* Если встретился закрывающий тег array */
			else if (token == QXmlStreamReader::EndElement && reader.name() == "array")
				++i;
			/* Если встретился неизвестный тег */
			else if (token == QXmlStreamReader::StartElement && reader.name() != "arrayInfo")
			{
				QString errorString = "Unknown tag \"" + reader.name().toString() + "\"";
				throw errorString;
			}
		}

		file.close();

		/* Ошибки в структуре xml файла */
		if (reader.hasError())
		{
			QString errorString = "File structure error in the file " + fileName + " containing the array's info";
			throw errorString;
		}

		/* В файле не заданы массивы */
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

	/* Проверка наличия аттрибутов */
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

	/* Чтение значений атрибутов тега array */
	for (it; it != itEnd; ++it)
	{
		/* Чтение атрибута name */
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
		/* Чтение атрибута elements */
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
		/* Чтение атрибута dimSize */
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
	QFile file(fileName);

	if (file.open(QIODevice::ReadOnly))
	{
		int operandsCounter = 0;
		int operandsCount = 0;
		int operationsCount = 0;
		int arrCounter = 0;
		bool arrayUsed = false;
		bool varUsed = false;
		Operations ops;

		/* Читаем из файла выражение */
		QString exprString(file.readAll());
		if (!exprString.size())
		{
			QString errorString = "File " + fileName + " is empty";
			throw errorString;
		}
		/* Заносим выражение по-элементно в массив строк */
		expr = exprString.split(" ");
		int size = expr.size();

		/* Проверка корректности выражения(допустимые элементы,количество операндов для операции и т.п.) */
		for (int i = 0; i < size; ++i)
		{
			/* Если встретилось имя массива */
			if (ops.isDefiniteArray(expr[i], arrs))
			{
				arrayUsed = true;
				int arr = ops.findArr(expr[i], arrs);
				arrCounter += arrs[arr].size.size();
			}
			/* Если встретилось имя переменной */
			else if (ops.isDefiniteVariable(expr[i], vars))
				varUsed = true;

			/* Если встретился операнд, но не имя массива */
			if (ops.isOperand(expr[i], vars, arrs) && !ops.isDefiniteArray(expr[i], arrs))
			{
				++operandsCount;
				++operandsCounter;
			}
			/* Если встретилась операция и для нее достаточно операндов */
			else if (ops.isDefiniteOperation(expr[i]) && operandsCounter >= ops.getArity(expr[i]))
			{
				++operationsCount;
				operandsCounter -= (ops.getArity(expr[i]) - 1);
				if (expr[i] == QString("[]"))
				{
					--arrCounter;
				}
			}
			/* Если встретилась операция и для нее не достаточно операндов */
			else if (ops.isDefiniteOperation(expr[i]) && operandsCounter < ops.getArity(expr[i]))
			{
				QString errorString = "Wrong expression. Not enough operands to calculate \"" + expr[i] + "\" on the " + QString::number(i + 1) + " position";
				throw errorString;

			}
			/* Если встретился неизвестный элемент */
			else if (!ops.isDefiniteElement(expr[i], arrs, vars))
			{
				QString errorString = "Wrong expression. Undefined element \"" + expr[i] + "\" on the " + QString::number(i + 1) + " position";
				throw errorString;
			}
		}


		/* Проверка соответствия количества операндов и операций */
		int difference = operandsCount - operationsCount;
		if (difference > 1)
		{
			QString errorString = "Wrong expression. Not enough operations for all the operands. Please, check the expression";
			throw errorString;
		}
		if (arrCounter < 0)
		{
			QString errorString = "Wrong expression. Too much square brackets for arrs. Please, check the expression";
			throw errorString;
		}

		/* Проверка наличия заданных переменнных и массивов в выражении */
		if (!arrayUsed)
		{
			QString errorString = "Wrong expression. Definite arrays are not used in the expression. Please, check the expression";
			throw errorString;
		}
		else if (!varUsed)
		{
			QString errorString = "Wrong expression. Definite variables are not used in the expression. Please, check the expression";
			throw errorString;
		}
	}
	else
	{
		QString errorString = "Can't open the file " + fileName;
		throw errorString;
	}
}

void Input::checkNonExecutableCycle(QVector<Index> &vars) throw(QString&)
{
	for (auto &var : vars)
	{
		/* Если цикл возрастающий, а шаг меньше нуля - отрицательный */
		if (var.from < var.to && var.step < 0)
		{
			QString errorString = "Wrong cycle ranges for variable \"" + var.name + "\". Cycle wouldn't execute";
			throw errorString;
		}
		/* Если цикл убывающий, а шаг больше нуля - положительный */
		else if (var.from > var.to && var.step > 0)
		{
			QString errorString = "Wrong cycle ranges for variable \"" + var.name + "\". Cycle wouldn't execute";
			throw errorString;
		}
	}
}

void Input::removeUnusedVarsAndArrs(QVector<Array> &arrs, QVector<Index> &vars, QStringList &expr)
{
	Operations ops;
	int exprSize = expr.size();

	/* Анализируем, какие переменные и массивы используются в выражении */
	for (int i = 0; i < exprSize; ++i)
	{
		/* Если встретилось имя переменной */
		if (ops.isDefiniteVariable(expr[i], vars))
		{
			int var = ops.findVar(expr[i], vars);
			vars[var].usedInExpression = true;
		}
		/* Если встретилось имя массива */
		else if (ops.isDefiniteArray(expr[i], arrs))
		{
			int arr = ops.findArr(expr[i], arrs);
			arrs[arr].usedInExpression = true;
		}
	}

	/* Удаляем из vars неиспользующиеся переменные */
	for (auto &var : vars)
	{
		if (!var.usedInExpression)
		{
			int i = ops.findVar(var.name, vars);
			vars.remove(i);
		}
		else
			var.usedInExpression = false;
	}

	/* Удаляем из arrs неиспользующиеся массивы */
	for (auto &arr : arrs)
	{
		if (!arr.usedInExpression)
		{
			int i = ops.findArr(arr.name, arrs);
			arrs.remove(i);
		}
		else
			arr.usedInExpression = false;
	}
}
