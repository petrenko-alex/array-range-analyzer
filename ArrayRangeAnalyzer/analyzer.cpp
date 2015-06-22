#include "analyzer.h"

//#define TEST

Analyzer::Analyzer()
{
	iteration	= 1;
	exprPos		= 0;
	leftOpD		= rightOpD = resultD = 0;

	/* Инициализируем массив указателей на функции */
	operations.insert("+", &Analyzer::addition);
	operations.insert("-", &Analyzer::substraction);
	operations.insert("/", &Analyzer::division);
	operations.insert("*", &Analyzer::multiplication);
	operations.insert("%", &Analyzer::modulo);
	operations.insert("+\\", &Analyzer::incL);
	operations.insert("-\\", &Analyzer::decL);
	operations.insert("\\+", &Analyzer::incR);
	operations.insert("\\-", &Analyzer::decR);
	operations.insert("/-", &Analyzer::unaryMinus);
	operations.insert("abs()", &Analyzer::absF);
	operations.insert("ceil()", &Analyzer::ceilF);
	operations.insert("fabs()", &Analyzer::fabsF);
	operations.insert("floor()", &Analyzer::floorF);
	operations.insert("pow()", &Analyzer::powF);
	operations.insert("(int)", &Analyzer::typeConversionToInt);
}

Analyzer::~Analyzer()
{

}

void Analyzer::analyzeExpression(QVector<Index> &vars, QVector<Array> &arrs, const QStringList &expr, QVector<Exceeding> &exceedings) throw(QString&)
{
	int exprSize = expr.size();
	QStack<stackElement> operands;

	/* Проход по выражению слева на право */
	for (exprPos = 0; exprPos < exprSize; ++exprPos)
	{
		/* Если встретилась константа */
		if (ops.isFloatNumber(expr[exprPos]))						 
		{
			/* Помещаем в стек как константу */
			stackElement element(constant, expr[exprPos]);
			operands.push(element);
		}
		/* Если встеретилась переменная */
		else if (ops.isDefiniteVariable(expr[exprPos], vars))	 
		{
			/* Помещаем в стек как переменную и устанавливаем флаг usedInExpression */
			stackElement element(variable, expr[exprPos]);
			operands.push(element);
			int var = ops.findVar(expr[exprPos], vars);
			vars[var].usedInExpression = true;
		}
		/* Если встретился массив */
		else if (ops.isDefiniteArray(expr[exprPos], arrs))		
		{
			/* Устанавливаем как текущий в структуре curArr */
			curArr.name = expr[exprPos];
			curArr.dimension = 0;
		}
		/* Если встретилась операция*/
		else if (ops.isDefiniteOperation(expr[exprPos]))
		{
			/* Если встречается операция обращения по исндексу */
			if (expr[exprPos] == "[]")
			{
				subscript(operands, vars, arrs, exceedings);
			}
			/* Если встречается одна из операций присваивания */
			else if (expr[exprPos] == "=" || expr[exprPos] == "+=" || expr[exprPos] == "-=" || expr[exprPos] == "*=" || expr[exprPos] == "/=")
			{
				assignment(operands, vars, arrs, expr[exprPos]);
			}
			/* Если встречаются остальные операции */
			else
			{
				/* Определяем операцию по ее строковому представлению в выражении */
				operation myOp = operations.value(expr[exprPos]);
				/* Вызываем функцию соответствующей операции */
				(this->*myOp)(operands, vars, arrs);
			}
		}
	}
	++iteration;
}

void Analyzer::checkExpression(QVector<Index> &vars, QVector<Array> &arrs, const QStringList &expr, QVector<Exceeding> &exceedings) throw(QString&)
{
	Output out;
	bool resume = true;
	bool stop = false;
	auto curVar = vars.end() - 1;
	int loop[3] = {};

	/* Пока не установлен флаг окончания проверки */
	while (!stop)
	{
		/* Сохраняем текущие значения переменных как предыдущие */
		for (auto &var : vars)
		{
			var.prevValue = var.curValue;
		}

		/* Проверяем выражение при текущих значениях переменных */
		try
		{
			analyzeExpression(vars, arrs, expr, exceedings);
		}
		catch (QString &errorString)
		{
			stop = true;
			out.writeError(errorString);
		}


		/* Переходим к следующей итерации цикла */
		try
		{
			nextIteration(curVar, vars, loop, stop);
		}
		catch (QString &errorString)
		{
			stop = true;
			/* При тестировании бросаем исключение вверх тестирующей функции */
			#ifdef TEST
				throw errorString;
			#endif
			/* При обычном выполнении записываем в файл ошибок */
			out.writeError(errorString);
		}
	}
}

void Analyzer::addition(QStack<stackElement> &operands, QVector<Index> &vars, QVector<Array> &arrs)
{
	/* Берем операнды из стека */
	stackElement rightElement = operands.pop();
	stackElement leftElement = operands.pop();

	/* Если они не являются неопределенными элементами */
	if (rightElement.type != undefined && leftElement.type != undefined)
	{
		/* Получаем численное значение правого операнда */
		rightOpS = rightElement.element;
		rightOpD = ops.stringOpToDoubleOp(rightOpS, vars);
		unaryMinusOrTypeConversion(rightElement, rightOpD);
		/* Получаем численное значение левого операнда */
		leftOpS = leftElement.element;
		leftOpD = ops.stringOpToDoubleOp(leftOpS, vars);
		unaryMinusOrTypeConversion(leftElement, leftOpD);
		/* Производим расчет */
		resultD = leftOpD + rightOpD;
		/* Результат в стек */
		stackElement element(constant, QString::number(resultD, 'f'));
		operands.push(element);
		/* Проверяем необходимость инкрем/декрем */
		postIncDec(rightElement, vars, arrs);
		postIncDec(leftElement, vars, arrs);
	}
	else
	{
		stackElement element(undefined);
		operands.push(element);
	}
}

void Analyzer::substraction(QStack<stackElement> &operands, QVector<Index> &vars, QVector<Array> &arrs)
{
	/* Берем операнды из стека */
	stackElement rightElement = operands.pop();
	stackElement leftElement = operands.pop();

	/* Если они не являются неопределенными элементами */
	if (rightElement.type != undefined && leftElement.type != undefined)
	{
		/* Получаем численное значение правого операнда */
		rightOpS = rightElement.element;
		rightOpD = ops.stringOpToDoubleOp(rightOpS, vars);
		unaryMinusOrTypeConversion(rightElement, rightOpD);
		/* Получаем численное значение левого операнда */
		leftOpS = leftElement.element;
		leftOpD = ops.stringOpToDoubleOp(leftOpS, vars);
		unaryMinusOrTypeConversion(leftElement, leftOpD);
		/* Производим расчет */
		resultD = leftOpD - rightOpD;
		/* Результат в стек */
		stackElement element(constant, QString::number(resultD, 'f'));
		operands.push(element);
		/* Проверяем необходимость инкрем/декрем */
		postIncDec(rightElement, vars, arrs);
		postIncDec(leftElement, vars, arrs);
	}
	else
	{
		stackElement element(undefined);
		operands.push(element);
	}
}

void Analyzer::division(QStack<stackElement> &operands, QVector<Index> &vars, QVector<Array> &arrs) throw(QString&)
{
	/* Берем операнды из стека */
	stackElement rightElement = operands.pop();
	stackElement leftElement = operands.pop();

	/* Если они не являются неопределенными элементами */
	if (rightElement.type != undefined && leftElement.type != undefined)
	{
		/* Получаем численное значение правого операнда */
		rightOpS = rightElement.element;
		rightOpD = ops.stringOpToDoubleOp(rightOpS, vars);
		unaryMinusOrTypeConversion(rightElement, rightOpD);
		/* Проверка ситуации деления на нуль*/
		if (rightOpD == 0)
		{ 
			QString errorString = "Division by zero is detected on the " + QString::number(exprPos + 1) + " position during the " + QString::number(iteration) + " iteration";
			throw errorString;
		}
		/* Получаем численное значение левого операнда */
		leftOpS = leftElement.element;
		leftOpD = ops.stringOpToDoubleOp(leftOpS, vars);
		unaryMinusOrTypeConversion(leftElement, leftOpD);
		/* Производим расчет */
		resultD = leftOpD / rightOpD;
		/* Результат в стек */
		stackElement element(constant, QString::number(resultD, 'f'));
		operands.push(element);
		/* Проверяем необходимость инкрем/декрем */
		postIncDec(rightElement, vars, arrs);
		postIncDec(leftElement, vars, arrs);
	}
	else
	{
		stackElement element(undefined);
		operands.push(element);
	}
}

void Analyzer::multiplication(QStack<stackElement> &operands, QVector<Index> &vars, QVector<Array> &arrs)
{
	/* Берем операнды из стека */
	stackElement rightElement = operands.pop();
	stackElement leftElement = operands.pop();

	/* Если они не являются неопределенными элементами */
	if (rightElement.type != undefined && leftElement.type != undefined)
	{
		/* Получаем численное значение правого операнда */
		rightOpS = rightElement.element;
		rightOpD = ops.stringOpToDoubleOp(rightOpS, vars);
		unaryMinusOrTypeConversion(rightElement, rightOpD);
		/* Получаем численное значение левого операнда */
		leftOpS = leftElement.element;
		leftOpD = ops.stringOpToDoubleOp(leftOpS, vars);
		unaryMinusOrTypeConversion(leftElement, leftOpD);
		/* Производим расчет */
		resultD = leftOpD * rightOpD;
		/* Результат в стек */
		stackElement element(constant, QString::number(resultD, 'f'));
		operands.push(element);
		/* Проверяем необходимость инкрем/декрем */
		postIncDec(rightElement, vars, arrs);
		postIncDec(leftElement, vars, arrs);
	}
	else
	{
		stackElement element(undefined);
		operands.push(element);
	}
}

void Analyzer::modulo(QStack<stackElement> &operands, QVector<Index> &vars, QVector<Array> &arrs) throw(QString&)
{
	/* Берем операнды из стека */
	stackElement rightElement = operands.pop();
	stackElement leftElement = operands.pop();

	/* Если они не являются неопределенными элементами */
	if (rightElement.type != undefined && leftElement.type != undefined)
	{
		/* Получаем численное значение правого операнда */
		rightOpS = rightElement.element;
		rightOpD = ops.stringOpToDoubleOp(rightOpS, vars);
		unaryMinusOrTypeConversion(rightElement, rightOpD);
		/* Проверка ситуации деления на нуль */
		if (rightOpD == 0)
		{
			QString errorString = "Division by zero is detected on the " + QString::number(exprPos + 1) + " position during the " + QString::number(iteration) + " iteration";
			throw errorString;
		}
		/* Получаем численное значение левого операнда */
		leftOpS = leftElement.element;
		leftOpD = ops.stringOpToDoubleOp(leftOpS, vars);
		unaryMinusOrTypeConversion(leftElement, leftOpD);
		/* Производим расчет */
		resultD = (int)leftOpD % (int)rightOpD;
		/* Результат в стек */
		stackElement element(constant, QString::number(resultD, 'f'));
		operands.push(element);
		/* Проверяем необходимость инкрем/декрем */
		postIncDec(rightElement, vars, arrs);
		postIncDec(leftElement, vars, arrs);
	}
	else
	{
		stackElement element(undefined);
		operands.push(element);
	}
}

void Analyzer::subscript(QStack<stackElement> &operands, QVector<Index> &vars, QVector<Array> &arrs, QVector<Exceeding> &exceedings)
{
	int varsSize = vars.size();
	/* Извлекаем индекс элемента массива - операнд из стека*/
	stackElement rightElement = operands.pop();
	rightOpS = rightElement.element;
	rightOpD = ops.stringOpToDoubleOp(rightOpS, vars);
	unaryMinusOrTypeConversion(rightElement, rightOpD);
	/* Проверка наличия выхода для массива */
	int arr = ops.findArr(curArr.name, arrs);
	int exceedingsSize = arrs[arr].isExceeding.size();
	/* Если для текущего измерения массива еще нет выхода */
	if (!arrs[arr].isExceeding[curArr.dimension])
	{ 
		/* Если происходит выход - индекс больше размера или меньше 0 */
		if (rightOpD >= arrs[arr].size[curArr.dimension] || rightOpD < 0)
		{
			/* Создаем исключение */
			QStringList indexNames;
			QVector<double> indexValues;
			/* Заполнение векторов indexNames и indexValues */
			for (int i = 0; i < varsSize; ++i)
			{
				if (vars[i].usedInExpression)
				{
					indexNames << vars[i].name;
					indexValues << vars[i].curValue;
					vars[i].usedInExpression = false;
				}
			}
			exceedings << Exceeding(curArr.name, indexNames, indexValues, rightOpD, (curArr.dimension + 1));
			arrs[arr].isExceeding[curArr.dimension] = true;
			/* В стек помещаем неопределенный элемент */
			stackElement element(undefined);
			operands.push(element);
		}
		/* Если выхода не происходит*/
		else
		{ 
			/* Обращаемся к элементу массива по индексу и значение кладем в стек */
			int index = 0;
			if (arrs[arr].elements.size() - 1 < (int)rightOpD)
			{ 
				/* Вычисление индекса */
				for (int i = 0; i < (int)rightOpD; ++i)
				{
					if (++index == arrs[arr].elements.size())
					{
						index = 0;
					}
				}
				resultD = arrs[arr].elements[index];
			}
			else
				resultD = arrs[arr].elements[rightOpD];

			/* В стек помещаем элемент массива */
			stackElement element(arrayElement, QString::number(resultD, 'f'), arr, index);
			operands.push(element);
			/* Проверяем необходимость инкрем/декрем */
			postIncDec(rightElement, vars, arrs);
		}
	}
	else
	{
		stackElement element(undefined);
		operands.push(element);
	}
	disableUsedInExpressionFlags(vars);
	++curArr.dimension;
}

void Analyzer::incL(QStack<stackElement> &operands, QVector<Index> &vars, QVector<Array> &arrs) throw(QString&)
{
	/* Берем правый операнд */
	stackElement rightElement = operands.pop();
	/* Если операнд - переменная */
	if (rightElement.type == variable)
	{ 
		/* Инкрементируем значение переменной */
		rightOpS = rightElement.element;
		int var = ops.findVar(rightOpS, vars);
		rightOpD = vars[var].curValue;
		++rightOpD;
		unaryMinusOrTypeConversion(rightElement, rightOpD);
		vars[var].curValue = rightOpD;
		/* Результат в стек */
		stackElement element(variable, QString::number(vars[var].curValue, 'f'));
		operands.push(element);
	}
	/* Если операнд - элемент массива */
	else if (rightElement.type == arrayElement)
	{ 
		/* Инкрементируем элемент массива */
		rightOpD = arrs[rightElement.arrayIndex].elements[rightElement.elementIndex];
		++rightOpD;
		unaryMinusOrTypeConversion(rightElement, rightOpD);
		arrs[rightElement.arrayIndex].elements[rightElement.elementIndex] = rightOpD;
		/* Результат в стек */
		stackElement element(arrayElement, QString::number(resultD, 'f'), rightElement.arrayIndex, rightElement.elementIndex);
		operands.push(element);
	}
	/* Если операнд - неопределенный элемент */
	else if (rightElement.type == undefined)
	{
		QString errorString = "Critical operation with undefined element is detected on the " + QString::number(exprPos + 1) + " position during the " + QString::number(iteration) + " iteration";
		throw errorString;
	}
	/* Если операнд - не левостороннее значение */
	else if (rightElement.type == constant)
	{
		QString errorString = "L-value is required for \"++\" operation on the " + QString::number(exprPos + 1) + " position";
		throw errorString;
	}
}

void Analyzer::decL(QStack<stackElement> &operands, QVector<Index> &vars, QVector<Array> &arrs) throw(QString&)
{
	/* Берем правый операнд */
	stackElement rightElement = operands.pop();
	/* Если операнд - переменная */
	if (rightElement.type == variable)
	{ 
		/* Декрементируем значение переменной */
		rightOpS = rightElement.element;
		int var = ops.findVar(rightOpS, vars);
		rightOpD = vars[var].curValue;
		--rightOpD;
		unaryMinusOrTypeConversion(rightElement, rightOpD, 2);
		vars[var].curValue = rightOpD;
		/* Результат в стек */
		stackElement element(variable, QString::number(vars[var].curValue, 'f'));
		operands.push(element);
	}
	/* Если операнд - элемент массива */
	else if (rightElement.type == arrayElement)
	{ 
		/* Декрементируем элемент массива */
		rightOpD = arrs[rightElement.arrayIndex].elements[rightElement.elementIndex];
		--rightOpD;
		unaryMinusOrTypeConversion(rightElement, rightOpD, 2);
		arrs[rightElement.arrayIndex].elements[rightElement.elementIndex] = rightOpD;
		/* Результат в стек */
		stackElement element(arrayElement, QString::number(resultD, 'f'), rightElement.arrayIndex, rightElement.elementIndex);
		operands.push(element);
	}
	/* Если операнд - неопределенный элемент */
	else if (rightElement.type == undefined)
	{
		QString errorString = "Critical operation with undefined element is detected on the " + QString::number(exprPos + 1) + " position during the " + QString::number(iteration) + " iteration";
		throw errorString;
	}
	/* Если операнд - не левостороннее значение */
	else if (rightElement.type == constant)
	{
		QString errorString = "L-value is required for \"--\" operation on the " + QString::number(exprPos + 1) + " position";
		throw errorString;
	}
}

void Analyzer::incR(QStack<stackElement> &operands, QVector<Index> &vars, QVector<Array> &arrs) throw(QString&)
{
	/* Берем операнд из стека */
	stackElement rightElement = operands.pop();
	/* Если операнд - переменная или элемент массива */
	if (rightElement.type == variable || rightElement.type == arrayElement)
	{
		/* Устанавливаем флаг инкремента */
		rightElement.incNeeded = true;
		/* Результат в стек */
		operands.push(rightElement);
	}
	/* Если операнд - неопределенный элемент */
	else if (rightElement.type == undefined)
	{
		QString errorString = "Critical operation with undefined element is detected on the " + QString::number(exprPos + 1) + " position during the " + QString::number(iteration) + " iteration";
		throw errorString;
	}
	/* Если операнд - константа */
	else if (rightElement.type == constant)
	{
		QString errorString = "L-value is required for \"++\" operation on the " + QString::number(exprPos + 1) + " position";
		throw errorString;
	}
}

void Analyzer::decR(QStack<stackElement> &operands, QVector<Index> &vars, QVector<Array> &arrs) throw(QString&)
{
	/* Берем операнд из стека */
	stackElement rightElement = operands.pop();
	/* Если операнд - переменная или элемент массива */
	if (rightElement.type == variable || rightElement.type == arrayElement)
	{
		/* Устанавливаем флаг декремента */
		rightElement.decNeeded = true;
		/* Результат в стек */
		operands.push(rightElement);
	}
	/* Если операнд - неопределенный элемент */
	else if (rightElement.type == undefined)
	{
		QString errorString = "Critical operation with undefined element is detected on the " + QString::number(exprPos + 1) + " position during the " + QString::number(iteration) + " iteration";
		throw errorString;
	}
	/* Если операнд - константа */
	else if (rightElement.type == constant)
	{
		QString errorString = "L-value is required for \"--\" operation on the " + QString::number(exprPos + 1) + " position";
		throw errorString;
	}
}

void Analyzer::unaryMinus(QStack<stackElement> &operands, QVector<Index> &vars, QVector<Array> &arrs)
{
	/* Берем правый операнд */
	stackElement rightElement = operands.pop();
	/* Если операнд - неопределенный элемент */
	if (rightElement.type == undefined)
	{
		stackElement element(undefined);
		operands.push(element);
	}
	/* Если операнд - переменная, константа или элемент массива */
	else
	{
		/* Устанавливаем флагот отрицательного значения */
		rightElement.negative = true;
		/* Результат в стек */
		operands.push(rightElement);
	}
}

void Analyzer::absF(QStack<stackElement> &operands, QVector<Index> &vars, QVector<Array> &arrs)
{
	/* Берем правый операнд */
	stackElement rightElement = operands.pop();

	/* Если он не является неопределенным элементом */
	if (rightElement.type != undefined)
	{
		/* Получаем численное значение операнда */
		rightOpS = rightElement.element;
		rightOpD = ops.stringOpToDoubleOp(rightOpS, vars);
		unaryMinusOrTypeConversion(rightElement, rightOpD);
		/* Производим расчет */
		resultD = abs(rightOpD);
		/* Результат в стек */
		stackElement element(constant, QString::number(resultD, 'f'));
		operands.push(element);
		/* Проверяем необходимость инкрем/декрем */
		postIncDec(rightElement, vars, arrs);
	}
	else
	{
		stackElement element(undefined);
		operands.push(element);
	}
}

void Analyzer::ceilF(QStack<stackElement> &operands, QVector<Index> &vars, QVector<Array> &arrs)
{
	/* Берем правый операнд */
	stackElement rightElement = operands.pop();

	/* Если он не является неопределенным элементом */
	if (rightElement.type != undefined)
	{
		/* Получаем численное значение операнда */
		rightOpS = rightElement.element;
		rightOpD = ops.stringOpToDoubleOp(rightOpS, vars);
		unaryMinusOrTypeConversion(rightElement, rightOpD);
		/* Производим расчет */
		resultD = ceil(rightOpD);
		/* Результат в стек */
		stackElement element(constant, QString::number(resultD, 'f'));
		operands.push(element);
		/* Проверяем необходимость инкрем/декрем */
		postIncDec(rightElement, vars, arrs);
	}
	else
	{
		stackElement element(undefined);
		operands.push(element);
	}
}

void Analyzer::fabsF(QStack<stackElement> &operands, QVector<Index> &vars, QVector<Array> &arrs)
{
	/* Берем правый операнд */
	stackElement rightElement = operands.pop();
	/* Если он не является неопределенным элементом */
	if (rightElement.type != undefined)
	{
		/* Получаем численное значение операнда */
		rightOpS = rightElement.element;
		rightOpD = ops.stringOpToDoubleOp(rightOpS, vars);
		unaryMinusOrTypeConversion(rightElement, rightOpD);
		/* Производим расчет */
		resultD = fabs(rightOpD);
		/* Результат в стек */
		stackElement element(constant, QString::number(resultD, 'f'));
		operands.push(element);
		/* Проверяем необходимость инкрем/декрем */
		postIncDec(rightElement, vars, arrs);
	}
	else
	{
		stackElement element(undefined);
		operands.push(element);
	}
}

void Analyzer::floorF(QStack<stackElement> &operands, QVector<Index> &vars, QVector<Array> &arrs)
{
	/* Берем правый операнд */
	stackElement rightElement = operands.pop();
	/* Если он не является неопределенным элементом */
	if (rightElement.type != undefined)
	{
		/* Получаем численное значение операнда */
		rightOpS = rightElement.element;
		rightOpD = ops.stringOpToDoubleOp(rightOpS, vars);
		unaryMinusOrTypeConversion(rightElement, rightOpD);
		/* Производим расчет */
		resultD = floor(rightOpD);
		/* Результат в стек */
		stackElement element(constant, QString::number(resultD, 'f'));
		operands.push(element);
		/* Проверяем необходимость инкрем/декрем */
		postIncDec(rightElement, vars, arrs);
	}
	else
	{
		stackElement element(undefined);
		operands.push(element);
	}
}

void Analyzer::powF(QStack<stackElement> &operands, QVector<Index> &vars, QVector<Array> &arrs)
{
	/* Берем операнды из стека */
	stackElement rightElement = operands.pop();
	stackElement leftElement = operands.pop();

	/* Если они не являются неопределенными элементами */
	if (rightElement.type != undefined && leftElement.type != undefined)
	{
		/* Получаем численное значение правого операнда */
		rightOpS = rightElement.element;
		rightOpD = ops.stringOpToDoubleOp(rightOpS, vars);
		unaryMinusOrTypeConversion(rightElement, rightOpD);
		/* Получаем численное значение левого операнда */
		leftOpS = leftElement.element;
		leftOpD = ops.stringOpToDoubleOp(leftOpS, vars);
		unaryMinusOrTypeConversion(leftElement, leftOpD);
		/* Производим расчет */
		resultD = pow(leftOpD, rightOpD);
		/* Результат в стек */
		stackElement element(constant, QString::number(resultD, 'f'));
		operands.push(element);
		/* Проверяем необходимость инкрем/декрем */
		postIncDec(rightElement, vars, arrs);
		postIncDec(leftElement, vars, arrs);
	}
	else
	{
		stackElement element(undefined);
		operands.push(element);
	}
}

void Analyzer::assignment(QStack<stackElement> &operands, QVector<Index> &vars, QVector<Array> &arrs, QString type) throw(QString&)
{
	/* Берем операнды из стека */
	stackElement rightElement = operands.pop();
	stackElement leftElement = operands.pop();

	/* Если они не являются неопределенными элементами */
	if (rightElement.type != undefined && leftElement.type != undefined)
	{
		/* Получаем численное значение правого операнда */
		rightOpS = rightElement.element;
		rightOpD = ops.stringOpToDoubleOp(rightOpS, vars);
		unaryMinusOrTypeConversion(rightElement, rightOpD);
		/* Если операнд - переменная - присвоение переменной */
		if (leftElement.type == variable)
		{ 
			/* Получаем численное значение левого операнда */
			leftOpS = leftElement.element;
			int var = ops.findVar(leftOpS, vars);

			/* Выполняем присваивание переменной в зависимости от значения type */
			if (type == "=")
				vars[var].curValue = rightOpD;
			else if (type == "+=")
				vars[var].curValue += rightOpD;
			else if (type == "-=")
				vars[var].curValue -= rightOpD;
			else if (type == "*=")
				vars[var].curValue *= rightOpD;
			else if (type == "/=")
				vars[var].curValue /= rightOpD;

			/* Результат в стек */
			stackElement element(variable, vars[var].name);
			operands.push(element);
		}
		else if (leftElement.type == arrayElement)
		{
			/* Выполняем присваивание элементу массива в зависимости от значения type */
			if (type == "=")
				arrs[leftElement.arrayIndex].elements[leftElement.elementIndex] = rightOpD;
			else if (type == "+=")
				arrs[leftElement.arrayIndex].elements[leftElement.elementIndex] += rightOpD;
			else if (type == "-=")
				arrs[leftElement.arrayIndex].elements[leftElement.elementIndex] -= rightOpD;
			else if (type == "*=")
				arrs[leftElement.arrayIndex].elements[leftElement.elementIndex] *= rightOpD;
			else if (type == "/=")
				arrs[leftElement.arrayIndex].elements[leftElement.elementIndex] /= rightOpD;

			/* Результат в стек */
			stackElement element(arrayElement, QString::number(rightOpD, 'f'), leftElement.arrayIndex, leftElement.elementIndex);
			operands.push(element);
		}
		/* Если операнд - константа */
		else if (leftElement.type == constant)
		{
			QString errorString = "L-value is required for \"" + type + "\" operation on the " + QString::number(exprPos + 1) + " position";
			throw errorString;
		}
		/* Проверяем необходимость инкрем/декрем */
		postIncDec(rightElement, vars, arrs);
		postIncDec(leftElement, vars, arrs);
	}
	/* Если операнд - неопределенный элемент */
	else
	{
		QString errorString = "Critical operation with undefined element is detected on the " + QString::number(exprPos + 1) + " position during the " + QString::number(iteration) + " iteration";
		throw errorString;
	}
}

void Analyzer::typeConversionToInt(QStack<stackElement> &operands, QVector<Index> &vars, QVector<Array> &arrs)
{
	/* Берем правый операнд */
	stackElement rightElement = operands.pop();

	/* Если операнд - неопределенный элемент */
	if (rightElement.type == undefined)
	{

		stackElement element(undefined);
		operands.push(element);
	}
	/* Если он не является неопределенным элементом */
	else
	{
		/* Устанавливаем флаг intNeeded */
		rightElement.intNeeded = true;
		/* Результат в стек */
		operands.push(rightElement);
		/* Проверяем необходимость инкрем/декрем */
		postIncDec(rightElement, vars, arrs);
	}
}

void Analyzer::postIncDec(stackElement &element, QVector<Index> &vars, QVector<Array> &arrs)
{
	/* Если установлен флаг постфиксного инкремента */
	if (element.incNeeded)
	{
		/* Если элемент - переменная */
		if (element.type == variable)
		{
			/* Инкрементируем ее значение и обнуляем флаг incNeeded */
			int varIndex = ops.findVar(element.element, vars);
			++vars[varIndex].curValue;
			element.incNeeded = false;
		}
		/* Если элемент - элемент массива */
		else if (element.type == arrayElement)
		{
			/* Инкрементируем его значение и обнуляем флаг incNeeded */
			++arrs[element.arrayIndex].elements[element.elementIndex];
			element.incNeeded = false;
		}
	}

	/* Если установлен флаг постфиксного декремента */
	if (element.decNeeded)
	{
		/* Если элемент - переменная */
		if (element.type == variable)
		{
			/* Декрементируем ее значение и обнуляем флаг decNeeded */
			int varIndex = ops.findVar(element.element, vars);
			--vars[varIndex].curValue;
			element.decNeeded = false;
		}
		/* Если элемент - элемент массива */
		else if (element.type == arrayElement)
		{
			/* Декрементируем его значение и обнуляем флаг decNeeded */
			--arrs[element.arrayIndex].elements[element.elementIndex];
			element.decNeeded = false;
		}
	}
}

void Analyzer::disableUsedInExpressionFlags(QVector<Index> &vars)
{
	/* Проходим по вектору vars */
	for (auto &var : vars)
	{
		/* Сбрасываем значение флага usedInExpression */
		var.usedInExpression = false;
	}
}

void Analyzer::unaryMinusOrTypeConversion(stackElement &element, double &value, int op /*= 0*/)
{
	/* Если установлен флаг negative */
	if (element.negative && (op == 0 || op == 1))
	{
		/* Делаем значение value отрицательным и обнуляем флаг negative */
		value = -value;
		element.negative = false;
	}

	/* Если установлен флаг intNeeded */
	if (element.intNeeded && (op == 0 || op == 2))
	{
		/* Приводим value к int и обнуляем флаг intNeeded */
		value = (int)value;
		element.intNeeded = false;
	}
}

void Analyzer::nextIteration(QVector<Index>::iterator &varIt, QVector<Index> &vars, int *loop, bool &stopCheck)
{
	bool resume = true;
	/* Пока установлен флаг продолжения */
	while (resume)
	{
		/* Условия, при которых можно увеличивать текущую переменную на шаг - правая граница не достигнута */
		bool positiveStepResume = (*varIt).step > 0 && (*varIt).curValue + (*varIt).step <= (*varIt).to;
		bool negativeStepResume = (*varIt).step < 0 && (*varIt).curValue + (*varIt).step >= (*varIt).to;

		/* Если условия выполняются */
		if (positiveStepResume || negativeStepResume)
		{
			/* Увеличиваем значение текущей переменной */
			(*varIt).curValue += (*varIt).step;
			/* Проверяем на зацикленность */
			checkEndlessLoop(varIt, vars, loop);
			varIt = vars.end() - 1;
			/* Переход на следующую итерацию выполнен */
			resume = false;
		}
		/* Если текущая переменная достигла своего максимального значения */
		else
		{
			/* Переходим к предыдущей переменной */
			(*varIt).curValue = (*varIt).from;
			--varIt;
			/* Продолжаем переход к следующей итерации */
			resume = true;

			/* Если достигли конца */
			if (varIt < vars.begin())
			{
				/* Устанавливаем флаг окончания проверки выражения */
				resume = false;
				stopCheck = true;
			}
		}
	}
}

void Analyzer::checkEndlessLoop(QVector<Index>::iterator &var, QVector<Index> &vars, int *loop) throw(QString&)
{
	int index = ops.findVar((*var).name, vars);

	/* Если текущее значение переменной(после перехода на новую итерацию) равно предыдущему */
	if ((*var).curValue == (*var).prevValue)
	{
		/* Увеличиваем счетчик повторных значений для данной переменной */
		++loop[index];
	}

	/* Если счетчик повторных значений достиг максимального значения */
	if (loop[index] > (*var).looped)
	{
		QString errorString = "Variable \"" + (*var).name + "\" is got caught in an endless loop";
		throw errorString;
	}
}

