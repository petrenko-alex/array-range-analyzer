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
