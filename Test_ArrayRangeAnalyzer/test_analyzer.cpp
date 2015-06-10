#include "test_analyzer.h"


void Test_analyzer::analyzeExpression_data()
{
	QStringList		   indexNames;
	QVector<double>    indexValues;
	QStringList		   fileNames;
	Input			   inp;


	/*! ������� ������� */
	QTest::addColumn <QVector<Index> >("vars");
	QTest::addColumn <QVector<Array> >("arrs");
	QTest::addColumn <QStringList>("expr");
	QTest::addColumn <QVector<Exceeding> >("expectedExceedings");
	QTest::addColumn <QString>("expectedString");

	/*! ���� ������� - ����� */

/*! ���� ������ - ������ ��� */
		fileNames << "../../Tests/analyzeExpression/One Variable.xml"
				  << "../../Tests/analyzeExpression/One Array.xml"
				  << "../../Tests/analyzeExpression/1 and 2.txt";
		clearData();
		inp.readData(fileNames, vars, arrs, expr);
		vars[0].curValue = 0;
	QTest::newRow("1.One Array No Exceeding") << vars << arrs << expr << exceedings << "correct";

/*! ���� ������ - ����� */
		vars[0].curValue = 9;
		indexValues << 9;
		indexNames  << vars[0].name;
		exceedings  << Exceeding(arrs[0].name, indexNames, indexValues, 11, 1);
	QTest::newRow("2.One Array One Exceeding") << vars << arrs << expr << exceedings << "correct";

/*! ��������� �������� - ������ ��� */
		fileNames[1] = "../../Tests/analyzeExpression/Many Arrays.xml";
		fileNames[2] = "../../Tests/analyzeExpression/3,4,5.txt";
		clearData();
		inp.readData(fileNames, vars, arrs, expr);
		vars[0].curValue = 0;
	QTest::newRow("3.Many Arrays No Exceedings") << vars << arrs << expr << exceedings << "correct";

/*! ��������� �������� - ����� �� ������ */
		vars[0].curValue = 7;
		indexValues[0]	 = 7;
		indexNames[0]	 = vars[0].name;
		exceedings		 << Exceeding(arrs[1].name, indexNames, indexValues, 14, 1);
	QTest::newRow("4.Many Arrays One Exceeding") << vars << arrs << expr << exceedings << "correct";

/*! ����� ��� ���������� - ���������� ������������ �� ����� */
		arrs[1].isExceeding << true;
		vars[0].curValue	= 8;
		exceedings.clear();
	QTest::newRow("5.Already Has An Exceeding") << vars << arrs << expr << exceedings << "correct";

/*! ������� �� 0 - �������� ���������� */
		fileNames[2] = "../../Tests/analyzeExpression/6.txt";
		clearData();
		inp.readData(fileNames, vars, arrs, expr);
		vars[0].curValue = 0;
	QTest::newRow("6.Division By Zero") << vars << arrs << expr << exceedings << "Division by zero is detected on the 4 position during the 1 interation";

/*! �������� � ��������� �� ��������� ������� - �������� ���������� */
		fileNames[2] = "../../Tests/analyzeExpression/7.txt";
		clearData();
		inp.readData(fileNames, vars, arrs, expr);
		vars[0].curValue	= 5;
		arrs[0].isExceeding << true;
	QTest::newRow("7.Operation With Undefined Element") << vars << arrs << expr << exceedings << "Operation with undefined element is detected on the 9 position during the 1 iteration";

/*! ���������� �������������, ���������� � ������ */
		fileNames[2] = "../../Tests/analyzeExpression/8.txt";
		clearData();
		inp.readData(fileNames, vars, arrs, expr);
		vars[0].curValue = 9;
		indexValues[0]   = 10;
		indexNames[0]    = vars[0].name;
		exceedings		 << Exceeding(arrs[0].name, indexNames, indexValues, 10, 1);
	QTest::newRow("8.Left Inc Exceeding") << vars << arrs << expr << exceedings << "correct";

/*! ����������� �������������, �� ���������� � ������ */
		fileNames[2] = "../../Tests/analyzeExpression/9.txt";
		clearData();
		inp.readData(fileNames, vars, arrs, expr);
		vars[0].curValue = 9;
	QTest::newRow("9.Right Inc No Exceeding") << vars << arrs << expr << exceedings << "correct";

/*! ���������� �������������, ���������� � ������ */
		fileNames[2] = "../../Tests/analyzeExpression/10.txt";
		clearData();
		inp.readData(fileNames, vars, arrs, expr);
		vars[0].curValue = 0;
		indexValues[0]   = -1;
		indexNames[0]    = vars[0].name;
		exceedings		 << Exceeding(arrs[0].name, indexNames, indexValues, -1, 1);
	QTest::newRow("10.Left Dec Exceeding") << vars << arrs << expr << exceedings << "correct";

/*! ����������� �������������, �� ���������� � ������ */
		fileNames[2] = "../../Tests/analyzeExpression/11.txt";
		clearData();
		inp.readData(fileNames, vars, arrs, expr);
		vars[0].curValue = 0;
	QTest::newRow("11.Right Dec No Exceeding") << vars << arrs << expr << exceedings << "correct";

/*! ��������������� ��������� ���������� � ���������, ���������� � ������*/
		fileNames[2] = "../../Tests/analyzeExpression/12.txt";
		clearData();
		inp.readData(fileNames, vars, arrs, expr);
		vars[0].curValue = 0;
		indexValues[0]	 = 23;
		indexNames[0]	 = vars[0].name;
		exceedings		 << Exceeding(arrs[0].name, indexNames, indexValues, 27, 1);
	QTest::newRow("12.Pre-change Of Variable") << vars << arrs << expr << exceedings << "correct";

/*! ������������ ���������� �������� ��������������� ��������� */
		fileNames[2] = "../../Tests/analyzeExpression/13.txt";
		clearData();
		inp.readData(fileNames, vars, arrs, expr);
		vars[0].curValue = 1;
		indexValues[0]   = 12;
		indexNames[0]    = vars[0].name;
		exceedings		 << Exceeding(arrs[0].name, indexNames, indexValues, 12, 1);
	QTest::newRow("13.Arithmetic Assignment") << vars << arrs << expr << exceedings << "correct";

/*! ����� ��� ���������� ���������� ���������� � ������� */
		fileNames[0] = "../../Tests/analyzeExpression/Three Variables.xml";
		fileNames[2] = "../../Tests/analyzeExpression/14.txt";
		clearData();
		inp.readData(fileNames, vars, arrs, expr);
		vars[0].curValue = 3;
		vars[1].curValue = 1;
		vars[2].curValue = 5;
		indexValues[0]   = 3;
		indexValues		 << 1 << 5;
		indexNames[0]    = vars[0].name;
		indexNames		 << vars[1].name;
		indexNames		 << vars[2].name;
		exceedings		 << Exceeding(arrs[0].name, indexNames, indexValues, 18, 1);
	QTest::newRow("14.Many Variables in Index") << vars << arrs << expr << exceedings << "correct";

/*! ������� �����, ���������� � ������ */
		fileNames[2] = "../../Tests/analyzeExpression/15.txt";
		clearData();
		inp.readData(fileNames, vars, arrs, expr);
		indexNames.clear();
		indexValues.clear();
		vars[2].curValue = 5;
		indexValues		 << 5;
		indexNames		 << vars[2].name;
		exceedings		 << Exceeding(arrs[0].name, indexNames, indexValues, -5, 1);
	QTest::newRow("15.Unary Minus") << vars << arrs << expr << exceedings << "correct";

/*! ������� abs(), ���������� � ������ */
		fileNames[2] = "../../Tests/analyzeExpression/16.txt";
		clearData();
		inp.readData(fileNames, vars, arrs, expr);
		vars[0].curValue = -15;
		indexValues[0]   = -15;
		indexNames[0]    = vars[0].name;
		exceedings		 << Exceeding(arrs[0].name, indexNames, indexValues, 15, 1);
	QTest::newRow("16.Function abs") << vars << arrs << expr << exceedings << "correct";

/*! ������� ceil() � ������������� ������, ���������� � ������ */
		fileNames[2] = "../../Tests/analyzeExpression/17.txt";
		clearData();
		inp.readData(fileNames, vars, arrs, expr);
		vars[0].curValue = 10.5;
		indexValues[0]   = 10.5;
		indexNames[0]    = vars[0].name;
		exceedings		 << Exceeding(arrs[0].name, indexNames, indexValues, 11, 1);
	QTest::newRow("17.Function ceil(positive)") << vars << arrs << expr << exceedings << "correct";

/*! ������� ceil() � ������������� ������, ���������� � ������ */
		clearData();
		inp.readData(fileNames, vars, arrs, expr);
		vars[0].curValue = -10.5;
		indexValues[0]   = -10.5;
		indexNames[0]    = vars[0].name;
		exceedings		 << Exceeding(arrs[0].name, indexNames, indexValues, -10, 1);
	QTest::newRow("18.Function ceil(negative)") << vars << arrs << expr << exceedings << "correct";

/*! ������� fabs(), ���������� � ������ */
		fileNames[2] = "../../Tests/analyzeExpression/19.txt";
		clearData();
		inp.readData(fileNames, vars, arrs, expr);
		vars[0].curValue = -11.5;
		indexValues[0]   = -11.5;
		indexNames[0]    = vars[0].name;
		exceedings		 << Exceeding(arrs[0].name, indexNames, indexValues, 11, 1);
	QTest::newRow("19.Function fabs") << vars << arrs << expr << exceedings << "correct";

/*! ������� floor(), ���������� � ������ */
		fileNames[2] = "../../Tests/analyzeExpression/20.txt";
		clearData();
		inp.readData(fileNames, vars, arrs, expr);
		vars[0].curValue = 10.6;
		indexValues[0]   = 10.6;
		indexNames[0]    = vars[0].name;
		exceedings		 << Exceeding(arrs[0].name, indexNames, indexValues, 10, 1);
	QTest::newRow("20.Function floor") << vars << arrs << expr << exceedings << "correct";

/*! ������� pow(), ���������� � ������ */
		fileNames[2] = "../../Tests/analyzeExpression/21.txt";
		clearData();
		inp.readData(fileNames, vars, arrs, expr);
		vars[0].curValue = 2;
		indexValues[0]   = 2;
		indexNames[0]    = vars[0].name;
		exceedings		 << Exceeding(arrs[0].name, indexNames, indexValues, 32, 1);
	QTest::newRow("21.Function pow") << vars << arrs << expr << exceedings << "correct";

/*! �������� ������� �� �������, ���������� � ������ */
		fileNames[2] = "../../Tests/analyzeExpression/22.txt";
		clearData();
		inp.readData(fileNames, vars, arrs, expr);
		vars[0].curValue = 11;
		indexValues[0]   = 11;
		indexNames[0]    = vars[0].name;
		exceedings		 << Exceeding(arrs[0].name, indexNames, indexValues, 11, 1);
	QTest::newRow("22. Modulo operation") << vars << arrs << expr << exceedings << "correct";

/*! �������� ���������� ���� � int, ���������� � ������ */
		fileNames[2] = "../../Tests/analyzeExpression/23.txt";
		clearData();
		inp.readData(fileNames, vars, arrs, expr);
		vars[0].curValue = 13.21232;
		indexValues[0]   = 13.21232;
		indexNames[0]    = vars[0].name;
		exceedings		 << Exceeding(arrs[0].name, indexNames, indexValues, 13, 1);
	QTest::newRow("23.Type conversion To Int") << vars << arrs << expr << exceedings << "correct";

/*! ����� �� ������ �������(� ������ ��������� �����) */
		fileNames[2] = "../../Tests/analyzeExpression/24.txt";
		clearData();
		inp.readData(fileNames, vars, arrs, expr);
		arrs[0].isExceeding << true;
		vars[0].curValue    = 20;
		indexValues[0]	    = 20;
		indexNames[0]		= vars[0].name;
		exceedings			<< Exceeding(arrs[1].name, indexNames, indexValues, 40, 1);
	QTest::newRow("24.Exceeding In Second Array") << vars << arrs << expr << exceedings << "correct";

/*! ����� � ������� ��������� ������� */
		fileNames[1] = "../../Tests/analyzeExpression/Multiple Dimension Array.xml";
		fileNames[2] = "../../Tests/analyzeExpression/25.txt";
		clearData();
		inp.readData(fileNames, vars, arrs, expr);
		arrs[0].isExceeding << true << true;
		vars[0].curValue = 20;
		indexValues[0]   = 20;
		indexNames[0]    = vars[0].name;
		exceedings		 << Exceeding(arrs[0].name, indexNames, indexValues, 18, 3);
	QTest::newRow("25.Exceeding In Third Dimension") << vars << arrs << expr << exceedings << "correct";

/*! ��������� �������� - ����� ��� ������� */
		fileNames[0] = "../../Tests/analyzeExpression/26vars.xml";
		fileNames[1] = "../../Tests/analyzeExpression/Many Arrays.xml";
		fileNames[2] = "../../Tests/analyzeExpression/26.txt";
		clearData();
		inp.readData(fileNames, vars, arrs, expr);
		vars[0].curValue = 8;
		vars[2].curValue = 10;
		vars[1].curValue = 14;
		indexValues[0]   = 8;
		indexNames[0]    = vars[0].name;
		exceedings		 << Exceeding(arrs[0].name, indexNames, indexValues, 13, 1);
		indexValues[0]   = 10;
		indexNames[0]	 = vars[2].name;
		exceedings		 << Exceeding(arrs[0].name, indexNames, indexValues, 15, 2);
		indexValues[0]   = 14;
		indexNames[0]    = vars[1].name;
		exceedings		 << Exceeding(arrs[1].name, indexNames, indexValues, 14, 1);
	QTest::newRow("26.Many Arrays Many Exceedings") << vars << arrs << expr << exceedings << "correct";
}

void Test_analyzer::checkExpression_data()
{
	QStringList		   indexNames;
	QVector<double>    indexValues;
	QStringList		   fileNames;
	Input			   inp;


	/*! ������� ������� */
	QTest::addColumn <QVector<Index> >("vars");
	QTest::addColumn <QVector<Array> >("arrs");
	QTest::addColumn <QStringList>("expr");
	QTest::addColumn <QVector<Exceeding> >("expectedExceedings");
	QTest::addColumn <QString>("expectedString");

/*! ������������ ���������� */
		fileNames << "../../Tests/checkExpression/1var.xml"
				  << "../../Tests/checkExpression/1arr.xml"
				  << "../../Tests/checkExpression/1expr.txt";
		clearData();
		inp.readData(fileNames, vars, arrs, expr);
	QTest::newRow("1.Infinite Loop") << vars << arrs << expr << exceedings << "Variable \"i\" is got caught in an endless loop";

/*! ���� ���������� - ������ ���� ��� ����� */
		fileNames[0] = "../../Tests/checkExpression/2var.xml";
		fileNames[2] = "../../Tests/checkExpression/2expr.txt";
		clearData();
		inp.readData(fileNames, vars, arrs, expr);
		indexValues << 0;
		indexNames  << vars[0].name;
		exceedings  << Exceeding(arrs[0].name, indexNames, indexValues, 15, 1);
	QTest::newRow("2.One Variable One Step") << vars << arrs << expr << exceedings << "correct";

/*! ���� ���������� - ��������� ����� ����� */
		fileNames[0] = "../../Tests/checkExpression/3var.xml";
		fileNames[2] = "../../Tests/checkExpression/3expr.txt";
		clearData();
		inp.readData(fileNames, vars, arrs, expr);
		indexValues[0] = 6;
		indexNames[0]  = vars[0].name;
		exceedings	   << Exceeding(arrs[0].name, indexNames, indexValues, 12, 1);
	QTest::newRow("3.One Variable Many Steps") << vars << arrs << expr << exceedings << "correct";

/*! ��������� ���������� - ������ ���� ��� ����� � ������ */
		fileNames[0] = "../../Tests/checkExpression/4var.xml";
		fileNames[1] = "../../Tests/checkExpression/4arr.xml";
		fileNames[2] = "../../Tests/checkExpression/4expr.txt";
		clearData();
		inp.readData(fileNames, vars, arrs, expr);
		indexValues[0] = 5;
		indexNames[0]  = vars[1].name;
		exceedings     << Exceeding(arrs[1].name, indexNames, indexValues, 7, 1);
		indexValues[0] = -5;
		indexNames[0]  = vars[2].name;
		exceedings     << Exceeding(arrs[2].name, indexNames, indexValues, -5, 1);
	QTest::newRow("4.Many Variables One Step Each") << vars << arrs << expr << exceedings << "correct";

/*! ��������� ���������� -  ������ ���������� ����� ����� � ������ */
		fileNames[0] = "../../Tests/checkExpression/5var.xml";
		fileNames[1] = "../../Tests/checkExpression/5arr.xml";
		fileNames[2] = "../../Tests/checkExpression/5expr.txt";
		clearData();
		inp.readData(fileNames, vars, arrs, expr);
		indexValues[0] = 5;
		indexNames[0]  = vars[0].name;
		exceedings	   << Exceeding(arrs[0].name, indexNames, indexValues, 7, 1);
		indexValues[0] = 8;
		indexNames[0]  = vars[2].name;
		exceedings	   << Exceeding(arrs[2].name, indexNames, indexValues, 9, 1);
		indexValues[0] = 6;
		indexNames[0]  = vars[1].name;
		exceedings	   << Exceeding(arrs[1].name, indexNames, indexValues, 13, 1);
	QTest::newRow("5.Many Variables Different Step�s Number For Each") << vars << arrs << expr << exceedings << "correct";

/*! ����������� ���� */
		fileNames[0] = "../../Tests/checkExpression/6var.xml";
		fileNames[1] = "../../Tests/checkExpression/6arr.xml";
		fileNames[2] = "../../Tests/checkExpression/6expr.txt";
		clearData();
		inp.readData(fileNames, vars, arrs, expr);
		indexValues[0] = 15;
		indexNames[0]  = vars[0].name;
		exceedings	   << Exceeding(arrs[0].name, indexNames, indexValues, 15, 1);
	QTest::newRow("6.Increasing Loop") << vars << arrs << expr << exceedings << "correct";

/*! ��������� ���� */
		fileNames[0] = "../../Tests/checkExpression/7var.xml";
		clearData();
		inp.readData(fileNames, vars, arrs, expr);
		indexValues[0] = -1;
		indexNames[0]  = vars[0].name;
		exceedings     << Exceeding(arrs[0].name, indexNames, indexValues, -1, 1);
	QTest::newRow("7.Decreasing Loop") << vars << arrs << expr << exceedings << "correct";

	/*! ���������� ������������ � ���������� ����� */
		fileNames[0] = "../../Tests/checkExpression/8var.xml";
		fileNames[1] = "../../Tests/checkExpression/8arr.xml";
		fileNames[2] = "../../Tests/checkExpression/8expr.txt";
		clearData();
		inp.readData(fileNames, vars, arrs, expr);
		indexValues[0] = 10;
		indexNames[0]  = vars[0].name;
		exceedings     << Exceeding(arrs[0].name, indexNames, indexValues, 10, 1);
		indexValues[0] = -1;
		indexNames[0]  = vars[1].name;
		exceedings     << Exceeding(arrs[0].name, indexNames, indexValues, -1, 2);
	QTest::newRow("8.Various Loop") << vars << arrs << expr << exceedings << "correct";
}

void Test_analyzer::analyzeExpression()
{
	Analyzer analyze;
	QVector<Exceeding> testExceedings;
	QString exception("correct");

	/*! ������� ������ �� ������� */
	QFETCH(QVector<Index>,		vars);
	QFETCH(QVector<Array>,		arrs);
	QFETCH(QStringList,			expr);
	QFETCH(QVector<Exceeding>,	expectedExceedings);
	QFETCH(QString,				expectedString);

	/*! ������� ����������� ������� */
	try
	{
		analyze.analyzeExpression(vars, arrs, expr, testExceedings);
	}
	catch (QString& errorString)
	{
		exception = errorString;
	}

	/*! ��������� ��������� */
	QVERIFY2(exception    == expectedString
		&& testExceedings == expectedExceedings, "Test failed!");

}

void Test_analyzer::checkExpression()
{
	Analyzer analyze;
	QVector<Exceeding> testExceedings;
	QString exception("correct");

	/*! ������� ������ �� ������� */
	QFETCH(QVector<Index>,		vars);
	QFETCH(QVector<Array>,		arrs);
	QFETCH(QStringList,			expr);
	QFETCH(QVector<Exceeding>,	expectedExceedings);
	QFETCH(QString,				expectedString);

	/*! ������� ����������� ������� */
	try
	{
		analyze.checkExpression(vars, arrs, expr, testExceedings);
	}
	catch (QString& errorString)
	{
		exception = errorString;
	}

	/*! ��������� ��������� */
	QVERIFY2(exception    == expectedString
		&& testExceedings == expectedExceedings, "Test failed!");
}

void Test_analyzer::clearData()
{
	vars.clear();
	arrs.clear();
	exceedings.clear();
	expr.clear();
}