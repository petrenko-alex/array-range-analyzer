#include "analyzer.h"

Analyzer::Analyzer()
{

}

Analyzer::~Analyzer()
{

}

void Analyzer::analyzeExpression(QVector<Index> &vars, QVector<Array> &arrs, const QStringList &expr, QVector<Exceeding> &exceedings) throw(QString&)
{

}

void Analyzer::checkExpression(QVector<Index> &vars, QVector<Array> &arrs, const QStringList &expr, QVector<Exceeding> &exceedings) throw(QString&)
{

}

void Analyzer::addition(QStack<stackElement> &operands, QVector<Index> &vars, QVector<Array> &arrs)
{
	/*! Берем операнды из стека */
	stackElement rightElement = operands.pop();
	stackElement leftElement = operands.pop();

	/*! Если они не являются неопределенными элементами */
	if (rightElement.type != undefined && leftElement.type != undefined)
	{
		/*! Получаем численное значение правого операнда */
		rightOpS = rightElement.element;
		rightOpD = ops.stringOpToDoubleOp(rightOpS, vars);
		unaryMinusOrTypeConversion(rightElement, rightOpD);
		/*! Получаем численное значение левого операнда */
		leftOpS = leftElement.element;
		leftOpD = ops.stringOpToDoubleOp(leftOpS, vars);
		unaryMinusOrTypeConversion(leftElement, leftOpD);
		/*! Производим расчет */
		resultD = leftOpD + rightOpD;
		/*! Результат в стек */
		stackElement element(constant, QString::number(resultD, 'f'));
		operands.push(element);
		/*! Проверяем необходимость инкрем/декрем */
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
	/*! Берем операнды из стека */
	stackElement rightElement = operands.pop();
	stackElement leftElement = operands.pop();

	/*! Если они не являются неопределенными элементами */
	if (rightElement.type != undefined && leftElement.type != undefined)
	{
		/*! Получаем численное значение правого операнда */
		rightOpS = rightElement.element;
		rightOpD = ops.stringOpToDoubleOp(rightOpS, vars);
		unaryMinusOrTypeConversion(rightElement, rightOpD);
		/*! Получаем численное значение левого операнда */
		leftOpS = leftElement.element;
		leftOpD = ops.stringOpToDoubleOp(leftOpS, vars);
		unaryMinusOrTypeConversion(leftElement, leftOpD);
		/*! Производим расчет */
		resultD = leftOpD - rightOpD;
		/*! Результат в стек */
		stackElement element(constant, QString::number(resultD, 'f'));
		operands.push(element);
		/*! Проверяем необходимость инкрем/декрем */
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
	/*! Берем операнды из стека */
	stackElement rightElement = operands.pop();
	stackElement leftElement = operands.pop();

	/*! Если они не являются неопределенными элементами */
	if (rightElement.type != undefined && leftElement.type != undefined)
	{
		/*! Получаем численное значение правого операнда */
		rightOpS = rightElement.element;
		rightOpD = ops.stringOpToDoubleOp(rightOpS, vars);
		unaryMinusOrTypeConversion(rightElement, rightOpD);
		/*! Проверка ситуации деления на нуль*/
		if (rightOpD == 0)
		{ 
			QString errorString = "Division by zero is detected on the " + QString::number(exprPos + 1) + " position during the " + QString::number(iteration) + " iteration";
			throw errorString;
		}
		/*! Получаем численное значение левого операнда */
		leftOpS = leftElement.element;
		leftOpD = ops.stringOpToDoubleOp(leftOpS, vars);
		unaryMinusOrTypeConversion(leftElement, leftOpD);
		/*! Производим расчет */
		resultD = leftOpD / rightOpD;
		/*! Результат в стек */
		stackElement element(constant, QString::number(resultD, 'f'));
		operands.push(element);
		/*! Проверяем необходимость инкрем/декрем */
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
	/*! Берем операнды из стека */
	stackElement rightElement = operands.pop();
	stackElement leftElement = operands.pop();

	/*! Если они не являются неопределенными элементами */
	if (rightElement.type != undefined && leftElement.type != undefined)
	{
		/*! Получаем численное значение правого операнда */
		rightOpS = rightElement.element;
		rightOpD = ops.stringOpToDoubleOp(rightOpS, vars);
		unaryMinusOrTypeConversion(rightElement, rightOpD);
		/*! Получаем численное значение левого операнда */
		leftOpS = leftElement.element;
		leftOpD = ops.stringOpToDoubleOp(leftOpS, vars);
		unaryMinusOrTypeConversion(leftElement, leftOpD);
		/*! Производим расчет */
		resultD = leftOpD * rightOpD;
		/*! Результат в стек */
		stackElement element(constant, QString::number(resultD, 'f'));
		operands.push(element);
		/*! Проверяем необходимость инкрем/декрем */
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
	/*! Берем операнды из стека */
	stackElement rightElement = operands.pop();
	stackElement leftElement = operands.pop();

	/*! Если они не являются неопределенными элементами */
	if (rightElement.type != undefined && leftElement.type != undefined)
	{
		/*! Получаем численное значение правого операнда */
		rightOpS = rightElement.element;
		rightOpD = ops.stringOpToDoubleOp(rightOpS, vars);
		unaryMinusOrTypeConversion(rightElement, rightOpD);
		/*! Проверка ситуации деления на нуль */
		if (rightOpD == 0)
		{
			QString errorString = "Division by zero is detected on the " + QString::number(exprPos + 1) + " position during the " + QString::number(iteration) + " iteration";
			throw errorString;
		}
		/*! Получаем численное значение левого операнда */
		leftOpS = leftElement.element;
		leftOpD = ops.stringOpToDoubleOp(leftOpS, vars);
		unaryMinusOrTypeConversion(leftElement, leftOpD);
		/*! Производим расчет */
		resultD = (int)leftOpD % (int)rightOpD;
		/*! Результат в стек */
		stackElement element(constant, QString::number(resultD, 'f'));
		operands.push(element);
		/*! Проверяем необходимость инкрем/декрем */
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
	/*! Извлекаем индекс элемента массива - операнд из стека*/
	stackElement rightElement = operands.pop();
	rightOpS = rightElement.element;
	rightOpD = ops.stringOpToDoubleOp(rightOpS, vars);
	unaryMinusOrTypeConversion(rightElement, rightOpD);
	/*! Проверка наличия выхода для массива */
	int arr = ops.findArr(curArr.name, arrs);
	int exceedingsSize = arrs[arr].isExceeding.size();
	/*! Если для текущего измерения массива еще нет выхода */
	if (!arrs[arr].isExceeding[curArr.dimension])
	{ 
		/*! Если происходит выход - индекс больше размера или меньше 0 */
		if (rightOpD >= arrs[arr].size[curArr.dimension] || rightOpD < 0)
		{
			/*! Создаем исключение */
			QStringList indexNames;
			QVector<double> indexValues;
			/*! Заполнение векторов indexNames и indexValues */
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
			/*! В стек помещаем неопределенный элемент */
			stackElement element(undefined);
			operands.push(element);
		}
		/*! Если выхода не происходит*/
		else
		{ 
			/*! Обращаемся к элементу массива по индексу и значение кладем в стек */
			int index = 0;
			if (arrs[arr].elements.size() - 1 < (int)rightOpD)
			{ 
				/*! Вычисление индекса */
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

			/*! В стек помещаем элемент массива */
			stackElement element(arrayElement, QString::number(resultD, 'f'), arr, index);
			operands.push(element);
			/*! Проверяем необходимость инкрем/декрем */
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

void Analyzer::postIncDec(stackElement &element, QVector<Index> &vars, QVector<Array> &arrs)
{

}

void Analyzer::disableUsedInExpressionFlags(QVector<Index> &vars)
{

}

void Analyzer::unaryMinusOrTypeConversion(stackElement &element, double &value, int op /*= 0*/)
{

}
