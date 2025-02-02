#include "test_input.h"


void Test_input::readVarInfo_data()
{
	QVector<Index> vars;

	/*! Колонки таблицы */
	QTest::addColumn <QString>("inputFileName");
	QTest::addColumn <QVector<Index> >("expectedVars");
	QTest::addColumn <QString>("expectedString");


	/*! Ряды таблицы - тесты */

/*! Входной файл отсутсвтует */
	QTest::newRow("1.No Input File") << "../UnitTests/readVarInfo/No Input File.xml"
									 << vars
									 << "Can't open the file ../UnitTests/readVarInfo/No Input File.xml";

/*! Входной файл пуст */
	QTest::newRow("2.Empty Input File") << "../UnitTests/readVarInfo/2.Empty Input File.xml"
										<< vars
										<< "File structure error in the file ../UnitTests/readVarInfo/2.Empty Input File.xml containing the variable's info";

/*! Ошибка в xml структуре входного файла */
	QTest::newRow("3.Wrong Input File Structure") << "../UnitTests/readVarInfo/3.Wrong Input File Structure.xml"
												  << vars
												  << "File structure error in the file ../UnitTests/readVarInfo/3.Wrong Input File Structure.xml containing the variable's info";

/*! Неизвестный тег во входном файле */
	QTest::newRow("4.Unknown Tag") << "../UnitTests/readVarInfo/4.Unknown Tag.xml"
								   << vars
							       << "Unknown tag \"variablesas\"";

/*! Отсутствует необходимый атрибут во входном файле */
	QTest::newRow("5.Missed Attribute") << "../UnitTests/readVarInfo/5.Missed Attribute.xml"
									    << vars
										<< "Missed attribute \"step\" in the 1 \"variable\" tag";

/*! Отсутствует значение неоходимого атрибута во входном файле */
	QTest::newRow("6.Missed Attribute Value") << "../UnitTests/readVarInfo/6.Missed Attribute Value.xml"
											  << vars
											  << "The value of attribute \"name\" in the 1 \"variable\" tag is not set";

/*! Неверно задано значение необходимого атрибута во входном файде */
	QTest::newRow("7.Wrong Attribute Value") << "../UnitTests/readVarInfo/7.Wrong Attribute Value.xml"
											 << vars
											 << "The value of attribute \"to\" in the 1 \"variable\" tag is not an integer value";

/*! Задана одна переменная во входном файле */
	vars << Index("i", 0, 2, 1);
	QTest::newRow("8.One Variable") << "../UnitTests/readVarInfo/8.One Variable.xml"
									<< vars
									<< "correct";

/*! Заданы две переменные во входном файле */
	vars << Index("jvar", 5, 123, 12);
	QTest::newRow("9.Two Variables") << "../UnitTests/readVarInfo/9.Two Variables.xml"
									 << vars
									 << "correct";

/*! Заданы три переменные во входном файле */
	vars << Index("iter", -5, 10, 3);
	QTest::newRow("10.Three Variables") << "../UnitTests/readVarInfo/10.Three Variables.xml"
										<< vars
										<< "correct";

/*! Задано больше трех переменных во входном файле */
	vars.clear();
	QTest::newRow("11.More Than Three Variables") << "../UnitTests/readVarInfo/11.More Than Three Variables.xml"
												  << vars
												  << "You can't use more than 3 variables in ../UnitTests/readVarInfo/11.More Than Three Variables.xml file";

/*! Не заданы переменные во входном файле */
	QTest::newRow("12.No Variables") << "../UnitTests/readVarInfo/12.No Variables.xml"
									 << vars
									 << "There is no variables info in ../UnitTests/readVarInfo/12.No Variables.xml file";

/*! Не выполняющийся цикл (возрастающий, но шаг < 0) */
	QTest::newRow("13.Non Executable(increasing loop)") << "../UnitTests/readVarInfo/13.Non Executable(increasing loop).xml"
														<< vars
														<< "Wrong cycle ranges for variable \"i\". Cycle wouldn't execute";

/*! Не выполняющийся цикл (убывающий, но шаг > 0) */
	QTest::newRow("14.Non Executable(decreasing loop)")	<< "../UnitTests/readVarInfo/14.Non Executable(decreasing loop).xml"
														<< vars
														<< "Wrong cycle ranges for variable \"i\". Cycle wouldn't execute";
}

void Test_input::readArrInfo_data()
{
	QVector<Array> arrs;
	QVector<int>   size;
	QVector<int>   elements;


	/*! Колонки таблицы */
	QTest::addColumn <QString>("inputFileName");
	QTest::addColumn <QVector<Array> >("expectedArrs");
	QTest::addColumn <QString>("expectedString");

	/*! Ряды таблицы - тесты */

/*! Входной файл отсутсвтует */
	QTest::newRow("1.No Input File") << "../UnitTests/readArrInfo/No Input File.xml"
									 << arrs
									 << "Can't open the file ../UnitTests/readArrInfo/No Input File.xml";

/*! Входной файл пуст */
	QTest::newRow("2.Empty Input File") << "../UnitTests/readArrInfo/2.Empty Input File.xml"
										<< arrs
										<< "File structure error in the file ../UnitTests/readArrInfo/2.Empty Input File.xml containing the array's info";

/*! Ошибка в xml структуре входного файла */
	QTest::newRow("3.Wrong Input File Structure") << "../UnitTests/readArrInfo/3.Wrong Input File Structure.xml"
												  << arrs
												  << "File structure error in the file ../UnitTests/readArrInfo/3.Wrong Input File Structure.xml containing the array's info";

/*! Неизвестный тег во входном файле */
	QTest::newRow("4.Unknown Tag") << "../UnitTests/readArrInfo/4.Unknown Tag.xml"
								   << arrs
								   << "Unknown tag \"aray\"";

/*! Отсутствует необходимый атрибут во входном файле */
	QTest::newRow("5.Missed Attribute") << "../UnitTests/readArrInfo/5.Missed Attribute.xml"
										<< arrs
										<< "Missed attribute \"elements\" in the 1 \"array\" tag";

/*! Отсутствует значение неоходимого атрибута во входном файле */
	QTest::newRow("6.Missed Attribute Value") << "../UnitTests/readArrInfo/6.Missed Attribute Value.xml"
											  << arrs
											  << "The value of attribute \"dim1size\" in the 1 \"array\" tag is not set";

/*! Неверно задано значение необходимого атрибута во входном файде */
	QTest::newRow("7.Wrong Attribute Value") << "../UnitTests/readArrInfo/7.Wrong Attribute Value.xml"
											 << arrs
											 << "The size of the 1 dimension of \"arr\" array is not a positive integer value";

/*! Не заданы массивы во входном файле */
	QTest::newRow("8.No Arrays") << "../UnitTests/readArrInfo/8.No Arrays.xml"
								 << arrs
								 << "There no arrays info in ../UnitTests/readArrInfo/8.No Arrays.xml file";

/*! Задан один массив во входном файле */
		size << 10;
		elements << 2 << 8 << 9 << 7;
		Array arr1("arr", size, elements);
		arrs << arr1;
	QTest::newRow("9.One Array") << "../UnitTests/readArrInfo/9.One Array.xml"
								 << arrs
								 << "correct";

/*! Задано несколько массивов во входном файле */
		size.clear();
		size << 12;
		elements.clear();
		elements << 2 << 9;
		Array arr2("mass", size, elements);
		arrs << arr2;
	QTest::newRow("10.Many Arrays") << "../UnitTests/readArrInfo/10.Many Arrays.xml"
									<< arrs
									<< "correct";

/*! Задан многомерный массив во входном файле */
		size.clear();
		size << 10 << 29 << 3;
		elements.clear();
		elements << 1 << 9;
		Array arr3("arr", size, elements);
		arrs.clear();
		arrs << arr3;
	QTest::newRow("11.Multiple Dimension Array") << "../UnitTests/readArrInfo/11.Multiple Dimension Array.xml"
												 << arrs
												 << "correct";

}

void Test_input::readExpression_data()
{
	Input inp;
	QVector<Array> arrs;
	QVector<Index> vars;
	QStringList    expr;
	QVector<int>   size;
	QVector<int>   elements;

	/*! Колонки таблицы */
	QTest::addColumn <QString>("inputFileName");
	QTest::addColumn <QVector<Index> >("inputVars");
	QTest::addColumn <QVector<Array> >("inputArrs");
	QTest::addColumn <QStringList>("expectedExpr");
	QTest::addColumn <QString>("expectedString");

	/*! Требуемые для проверки циклов данные */
	inp.readArrInfo(QString("../UnitTests/readArrInfo/10.Many Arrays.xml"), arrs);
	inp.readVarInfo(QString("../UnitTests/readVarInfo/10.Three Variables.xml"), vars);

	/*! Ряды таблицы - тесты */

/*! Входной файл отсутсвтует */
	QTest::newRow("1.No Input File") << "../UnitTests/readExpression/No Input File.txt"
									 << vars
									 << arrs
									 << expr
									 << "Can't open the file ../UnitTests/readExpression/No Input File.txt";

/*! Входной файл пуст */
	QTest::newRow("2.Empty Input File") << "../UnitTests/readExpression/2.Empty Input File.txt"
										<< vars
										<< arrs
										<< expr
										<< "File ../UnitTests/readExpression/2.Empty Input File.txt is empty";

/*! Неизвестный элемент во входном файле */
		vars << Index("i", 0, 0, 0);
		arrs << Array("arr", size, elements);
	QTest::newRow("3.Undefined Element") << "../UnitTests/readExpression/3.Undefined Element.txt"
										 << vars
										 << arrs
										 << expr
										 << "Wrong expression. Undefined element \"j\" on the 3 position";

/*! Недостаточно операндов для операции */
	QTest::newRow("4.Not Enough Operands For Operation") << "../UnitTests/readExpression/4.Not Enough Operands For Operation.txt"
														 << vars
														 << arrs
														 << expr
														 << "Wrong expression. Not enough operands to calculate \"+\" on the 2 position";

/*! Массивы не используются */
	QTest::newRow("5.Arrays Are Not Used") << "../UnitTests/readExpression/5.Arrays Are Not Used.txt"
										   << vars
										   << arrs
										   << expr
										   << "Wrong expression. Definite arrays are not used in the expression. Please, check the expression";

/*! Переменные не используются */
	QTest::newRow("6.Variables Are Not Used") << "../UnitTests/readExpression/6.Variables Are Not Used.txt"
											  << vars
											  << arrs
											  << expr
											  << "Wrong expression. Definite variables are not used in the expression. Please, check the expression";

/*! Операндов больше чем  операций - лишние операнды */
	QTest::newRow("7.Too much operands") << "../UnitTests/readExpression/7.Too much operands.txt"
										 << vars
										 << arrs
										 << expr
										 << "Wrong expression. Not enough operations for all the operands. Please, check the expression";

/*! Избыток квадратных скобок в выражении */
	QTest::newRow("8.Excess of square brackets")	<< "../UnitTests/readExpression/8.Excess of square brackets.txt"
													<< vars
													<< arrs
													<< expr
													<< "Wrong expression. Too much square brackets for arrs. Please, check the expression";

/*! Корректное выражение */
		vars << Index("j", 0, 0, 0);
		expr << "i" << "2" << "j" << "+" << "=" << "j" << "2" << "3" << "+"
			<< "=" << "arr" << "i" << "j" << "*" << "[]" << "+" << "+";
	QTest::newRow("9.Normal Expression") << "../UnitTests/readExpression/9.Normal Expression.txt"
										 << vars
										 << arrs
										 << expr
										 << "correct";
}

void Test_input::readData_data()
{
	QVector<Array> arrs;
	QVector<Index> vars;
	QVector<int>   size;
	QVector<int>   elements;
	QStringList    expr;
	QStringList    fileNames;

	/*! Колонки таблицы */
	QTest::addColumn <QStringList>("inputFileNames");
	QTest::addColumn <QVector<Index> >("expectedVars");
	QTest::addColumn <QVector<Array> >("expectedArrs");
	QTest::addColumn <QStringList>("expectedExpr");
	QTest::addColumn <bool>("expectedSuccess");


	/*! Ряды таблицы - тесты */

/*!  Функция чтения информации о переменных завершиться неуспешно */
		fileNames << "../UnitTests/readVarInfo/No Input File.xml";
	QTest::newRow("1.ReadVarInfo Failed") << fileNames
										  << vars
										  << arrs
										  << expr
										  << false;

/*! Функция чтения информации о массивах завершиться неуспешно */
		vars << Index("i", 0, 2, 1);
		fileNames[0] = "../UnitTests/readVarInfo/8.One Variable.xml";
		fileNames << "../UnitTests/readArrInfo/No Input File.xml";
	QTest::newRow("2.ReadArrInfo Failed") << fileNames
										  << vars
										  << arrs
										  << expr
										  << false;

/*! Функция чтения выражения завершиться неуспешно */
		size << 10;
		elements << 2 << 8 << 9 << 7;
		arrs << Array("arr", size, elements);
		fileNames[1] = "../UnitTests/readArrInfo/9.One Array.xml";
		fileNames << "../UnitTests/readExpression/No Input File.txt";
	QTest::newRow("3.ReadExpression Failed") << fileNames
											 << vars
											 << arrs
											 << expr
											 << false;

/*! Успешное считывание входных данных */
		fileNames[2] = "../UnitTests/readData/Correct Expression.txt";
		expr << "arr" << "i" << "2.25" << "+" << "[]";
	QTest::newRow("4.Successful Reading") << fileNames
										  << vars
										  << arrs
										  << expr
										  << true;
}

void Test_input::readVarInfo()
{
	Input inp;
	QVector<Index> vars;
	QString exception("correct");

	/*! Извлечь данные из таблицы */
	QFETCH(QString,			inputFileName);
	QFETCH(QVector<Index>,	expectedVars);
	QFETCH(QString,			expectedString);

	/*! Вызвать тестируемую функцию */
	try
	{
		inp.readVarInfo(inputFileName, vars);
	}
	catch (QString& errorString)
	{
		vars.clear();
		exception = errorString;
	}

	/*! Проверить результат */
	QVERIFY2(exception == expectedString, "Returned string is not correct");
	QVERIFY2(vars	   == expectedVars, "Returned vars are not correct");
}

void Test_input::readArrInfo()
{
	Input inp;
	QVector<Array> arrs;
	QString exception("correct");

	/*! Извлечь данные из таблицы */
	QFETCH(QString,			inputFileName);
	QFETCH(QVector<Array>,	expectedArrs);
	QFETCH(QString,			expectedString);

	/*! Вызвать тестируемую функцию */
	try
	{
		inp.readArrInfo(inputFileName, arrs);
	}
	catch (QString &errorString)
	{
		arrs.clear();
		exception = errorString;
	}

	/*! Проверить результат */
	QVERIFY2(exception == expectedString, "Returned string is not correct");
	QVERIFY2(arrs	   == expectedArrs, "Returned arrs are not correct");
}

void Test_input::readExpression()
{
	Input inp;
	QStringList expr;
	QString exception("correct");


	/*! Извлечь данные из таблицы */
	QFETCH(QString,		   inputFileName);
	QFETCH(QVector<Index>, inputVars);
	QFETCH(QVector<Array>, inputArrs);
	QFETCH(QStringList,    expectedExpr);
	QFETCH(QString,		   expectedString);

	/*! Вызвать тестируемую функцию */
	try
	{
		inp.readExpression(inputFileName, expr, inputVars, inputArrs);
	}
	catch (QString &errorString)
	{
		expr.clear();
		exception = errorString;
	}

	/*! Проверить результат */
	QVERIFY2(exception == expectedString, "Returned string is not correct");
	QVERIFY2(expr	   == expectedExpr, "Returned expression is not correct");
}

void Test_input::readData()
{
	Input inp;
	bool success = false;
	QVector<Array> arrs;
	QVector<Index> vars;
	QStringList    expr;
	QStringList    fileNames;

	/*! Колонки таблицы */
	QFETCH(QStringList,    inputFileNames);
	QFETCH(QVector<Index>, expectedVars);
	QFETCH(QVector<Array>, expectedArrs);
	QFETCH(QStringList,    expectedExpr);
	QFETCH(bool,		   expectedSuccess);

	/*! Вызвать тестируемую функцию */
	success = inp.readData(inputFileNames, vars, arrs, expr);

	/*! Проверить результат */
	QVERIFY2(vars	 == expectedVars, "Returned vars are not correct");
	QVERIFY2(arrs	 == expectedArrs, "Returned arrs are not correct");
	QVERIFY2(expr	 == expectedExpr, "Returned expression is not correct");
	QVERIFY2(success == expectedSuccess, "Returned success is not correct");
}
