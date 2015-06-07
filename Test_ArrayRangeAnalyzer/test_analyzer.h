#ifndef TEST_ANALYZER_H
#define TEST_ANALYZER_H

#include <QObject>
#include <QtTest>
#include "../ArrayRangeAnalyzer/analyzer.h"
#include "declarations.h"

class Test_analyzer : public QObject
{
	Q_OBJECT

public:
	/*! Подготавливает данные для тестирования analyzeExpression */
	void analyzeExpression_data();

	/*! Подготавливает данные для тестирования checkExpression */
	void checkExpression_data();

	/*! Тестирует функцию analyzeExpression */
	void analyzeExpression();

	/*! Тестирует функцию checkExpression */
	void checkExpression();

private:
	/*! Очищает содержимое контейнеров класса */
	void clearData();

	QVector<index>     vars;
	QVector<Array>	   arrs;
	QVector<exceeding> exceedings;
	QStringList        expr;
};

#endif // TEST_ANALYZER_H
