#ifndef TEST_INPUT_H
#define TEST_INPUT_H

#include <QObject>
#include <QtTest>
#include "../ArrayRangeAnalyzer/input.h"
#include "declarations.h"

class input;
class Test_input : public QObject
{
	Q_OBJECT

private slots:
	/*! Подготавливает данные для тестирования readVarInfo */
	void readVarInfo_data();

	/*! Подготавливает данные для тестирования readArrInfo */
	//void readArrInfo_data();

	/*! Подготавливает данные для тестирования readExpression */
	//void readExpression_data();

	/*! Подготавливает данные для тестирования readData */
	//void readData_data();

	/*! Тестирует функцию readVarInfo */
	void readVarInfo();

	/*! Тестирует функцию readArrInfo*/
	//void readArrInfo();

	/*! Тестирует функцию readExpression*/
	//void readExpression();

	/*! Тестирует функцию readData*/
 	//void readData();
};

#endif // TEST_INPUT_H
