#include "test_input.h"


void Test_input::readVarInfo_data()
{
	QVector<Index> vars;

	/*! ������� ������� */
	QTest::addColumn <QString>("inputFileName");
	QTest::addColumn <QVector<Index> >("expectedVars");
	QTest::addColumn <QString>("expectedString");


	/*! ���� ������� - ����� */

/*! ������� ���� ����������� */
	QTest::newRow("1.No Input File") << "../../Tests/readVarInfo/No Input File.xml"
									 << vars
									 << "Can't open the file ../../Tests/readVarInfo/No Input File.xml";

/*! ������� ���� ���� */
	QTest::newRow("2.Empty Input File") << "../../Tests/readVarInfo/2.Empty Input File.xml"
										<< vars
										<< "File structure error in the file ../../Tests/readVarInfo/2.Empty Input File.xml containing the variable's info";

/*! ������ � xml ��������� �������� ����� */
	QTest::newRow("3.Wrong Input File Structure") << "../../Tests/readVarInfo/3.Wrong Input File Structure.xml"
												  << vars
												  << "File structure error in the file ../../Tests/readVarInfo/3.Wrong Input File Structure.xml containing the variable's info";

/*! ����������� ��� �� ������� ����� */
	QTest::newRow("4.Unknown Tag") << "../../Tests/readVarInfo/4.Unknown Tag.xml"
								   << vars
							       << "Unknown tag \"variablesas\"";

/*! ����������� ����������� ������� �� ������� ����� */
	QTest::newRow("5.Missed Attribute") << "../../Tests/readVarInfo/5.Missed Attribute.xml"
									    << vars
										<< "Missed attribute \"step\" in the 1 \"variable\" tag";

/*! ����������� �������� ����������� �������� �� ������� ����� */
	QTest::newRow("6.Missed Attribute Value") << "../../Tests/readVarInfo/6.Missed Attribute Value.xml"
											  << vars
											  << "The value of attribute \"name\" in the 1 \"variable\" tag is not set";

/*! ������� ������ �������� ������������ �������� �� ������� ����� */
	QTest::newRow("7.Wrong Attribute Value") << "../../Tests/readVarInfo/7.Wrong Attribute Value.xml"
											 << vars
											 << "The value of attribute \"to\" in the 1 \"variable\" tag is not an integer value";


/*! ������ ���� ���������� �� ������� ����� */
	vars << Index("i", 0, 2, -1);
	QTest::newRow("8.One Variable") << "../../Tests/readVarInfo/8.One Variable.xml"
									<< vars
									<< "correct";

/*! ������ ��� ���������� �� ������� ����� */
	vars << Index("jvar", 5, 123, 12);
	QTest::newRow("9.Two Variables") << "../../Tests/readVarInfo/9.Two Variables.xml"
									 << vars
									 << "correct";

/*! ������ ��� ���������� �� ������� ����� */
	vars << Index("iter", -5, 10, 3);
	QTest::newRow("10.Three Variables") << "../../Tests/readVarInfo/10.Three Variables.xml"
										<< vars
										<< "correct";

/*! ������ ������ ���� ���������� �� ������� ����� */
	vars.clear();
	QTest::newRow("11.More Than Three Variables") << "../../Tests/readVarInfo/11.More Than Three Variables.xml"
												  << vars
												  << "You can't use more than 3 variables in ../../Tests/readVarInfo/11.More Than Three Variables.xml file";

/*! �� ������ ���������� �� ������� ����� */
	QTest::newRow("12.No Variables") << "../../Tests/readVarInfo/12.No Variables.xml"
									 << vars
									 << "There no variables info in ../../Tests/readVarInfo/12.No Variables.xml file";
}

void Test_input::readArrInfo_data()
{
	QVector<Array> arrs;
	QVector<int>   size;
	QVector<int>   elements;


	/*! ������� ������� */
	QTest::addColumn <QString>("inputFileName");
	QTest::addColumn <QVector<Array> >("expectedArrs");
	QTest::addColumn <QString>("expectedString");

	/*! ���� ������� - ����� */

/*! ������� ���� ����������� */
	QTest::newRow("1.No Input File") << "../../Tests/readArrInfo/No Input File.xml"
									 << arrs
									 << "Can't open the file ../../Tests/readArrInfo/No Input File.xml";

/*! ������� ���� ���� */
	QTest::newRow("2.Empty Input File") << "../../Tests/readArrInfo/2.Empty Input File.xml"
										<< arrs
										<< "File structure error in the file ../../Tests/readArrInfo/2.Empty Input File.xml containing the array's info";

/*! ������ � xml ��������� �������� ����� */
	QTest::newRow("3.Wrong Input File Structure") << "../../Tests/readArrInfo/3.Wrong Input File Structure.xml"
												  << arrs
												  << "File structure error in the file ../../Tests/readArrInfo/3.Wrong Input File Structure.xml containing the array's info";

/*! ����������� ��� �� ������� ����� */
	QTest::newRow("4.Unknown Tag") << "../../Tests/readArrInfo/4.Unknown Tag.xml"
								   << arrs
								   << "Unknown tag \"aray\"";

/*! ����������� ����������� ������� �� ������� ����� */
	QTest::newRow("5.Missed Attribute") << "../../Tests/readArrInfo/5.Missed Attribute.xml"
										<< arrs
										<< "Missed attribute \"elements\" in the 1 \"array\" tag";

/*! ����������� �������� ����������� �������� �� ������� ����� */
	QTest::newRow("6.Missed Attribute Value") << "../../Tests/readArrInfo/6.Missed Attribute Value.xml"
											  << arrs
											  << "The value of attribute \"dim1size\" in the 1 \"array\" tag is not set";

/*! ������� ������ �������� ������������ �������� �� ������� ����� */
	QTest::newRow("7.Wrong Attribute Value") << "../../Tests/readArrInfo/7.Wrong Attribute Value.xml"
											 << arrs
											 << "The size of the 1 dimension of \"arr\" array is not an integer value";

/*! �� ������ ������� �� ������� ����� */
	QTest::newRow("8.No Arrays") << "../../Tests/readArrInfo/8.No Arrays.xml"
								 << arrs
								 << "There no arrays info in ../../Tests/readArrInfo/8.No Arrays.xml file";

/*! ����� ���� ������ �� ������� ����� */
		size << 10;
		elements << 2 << 8 << 9 << 7;
		Array arr1("arr", size, elements);
		arrs << arr1;
	QTest::newRow("9.One Array") << "../../Tests/readArrInfo/9.One Array.xml"
								 << arrs
								 << "correct";

/*! ������ ��������� �������� �� ������� ����� */
		size.clear();
		size << 12;
		elements.clear();
		elements << 2 << 9;
		Array arr2("mass", size, elements);
		arrs << arr2;
	QTest::newRow("10.Many Arrays") << "../../Tests/readArrInfo/10.Many Arrays.xml"
									<< arrs
									<< "correct";

/*! ����� ����������� ������ �� ������� ����� */
		size.clear();
		size << 10 << 29 << 3;
		elements.clear();
		elements << 1 << 9;
		Array arr3("arr", size, elements);
		arrs.clear();
		arrs << arr3;
	QTest::newRow("11.Multiple Dimension Array") << "../../Tests/readArrInfo/11.Multiple Dimension Array.xml"
												 << arrs
												 << "correct";

}

void Test_input::readExpression_data()
{
	QVector<Array> arrs;
	QVector<Index> vars;
	QStringList    expr;
	QVector<int>   size;
	QVector<int>   elements;

	/*! ������� ������� */
	QTest::addColumn <QString>("inputFileName");
	QTest::addColumn <QVector<Index> >("inputVars");
	QTest::addColumn <QVector<Array> >("inputArrs");
	QTest::addColumn <QStringList>("expectedExpr");
	QTest::addColumn <QString>("expectedString");

	/*! ���� ������� - ����� */

/*! ������� ���� ����������� */
	QTest::newRow("1.No Input File") << "../../Tests/readExpression/No Input File.txt"
									 << vars
									 << arrs
									 << expr
									 << "Can't open the file ../../Tests/readExpression/No Input File.txt";

/*! ������� ���� ���� */
	QTest::newRow("2.Empty Input File") << "../../Tests/readExpression/2.Empty Input File.txt"
										<< vars
										<< arrs
										<< expr
										<< "File ../../Tests/readExpression/2.Empty Input File.txt is empty";

/*! ����������� ������� �� ������� ����� */
		vars << Index("i", 0, 0, 0);
		arrs << Array("arr", size, elements);
	QTest::newRow("3.Undefined Element") << "../../Tests/readExpression/3.Undefined Element.txt"
										 << vars
										 << arrs
										 << expr
										 << "Wrong expression. Undefined element \"j\" on the 3 position";

/*! ������������ ��������� ��� �������� */
	QTest::newRow("4.Not Enough Operands For Operation") << "../../Tests/readExpression/4.Not Enough Operands For Operation.txt"
														 << vars
														 << arrs
														 << expr
														 << "Wrong expression. Not enough operands to calculate \"+\" on the 2 position";

/*! ������� �� ������������ */
	QTest::newRow("5.Arrays Are Not Used") << "../../Tests/readExpression/5.Arrays Are Not Used.txt"
										   << vars
										   << arrs
										   << expr
										   << "Wrong expression. Definite arrays are not used in the expression. Please, check the expression";

/*! ���������� �� ������������ */
	QTest::newRow("6.Variables Are Not Used") << "../../Tests/readExpression/6.Variables Are Not Used.txt"
											  << vars
											  << arrs
											  << expr
											  << "Wrong expression. Definite variables are not used in the expression. Please, check the expression";

/*! ��������� ������ ���  �������� - ������ �������� */
	QTest::newRow("7.Too much operands") << "../../Tests/readExpression/7.Too much operands.txt"
										 << vars
										 << arrs
										 << expr
										 << "Wrong expression. Not enough operations for all the operands. Please, check the expression";

/*! �������� ������ ��� ��������� - ������ �������� */
	QTest::newRow("8.Excess of operations") << "../../Tests/readExpression/8.Excess of operations.txt"
											<< vars
											<< arrs
											<< expr
											<< "Wrong expression. Excess of operations for the present set of operands. Please, check the expression";

/*! ���������� ��������� */
		vars << Index("j", 0, 0, 0);
		expr << "i" << "2" << "j" << "+" << "=" << "j" << "2" << "3" << "+"
			<< "=" << "arr" << "i" << "j" << "*" << "[]" << "+" << "+";
	QTest::newRow("9.Normal Expression") << "../../Tests/readExpression/9.Normal Expression.txt"
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

	/*! ������� ������� */
	QTest::addColumn <QStringList>("inputFileNames");
	QTest::addColumn <QVector<Index> >("expectedVars");
	QTest::addColumn <QVector<Array> >("expectedArrs");
	QTest::addColumn <QStringList>("expectedExpr");
	QTest::addColumn <bool>("expectedSuccess");


	/*! ���� ������� - ����� */

/*!  ������� ������ ���������� � ���������� ����������� ��������� */
		fileNames << "../../Tests/readVarInfo/No Input File.xml";
	QTest::newRow("1.ReadVarInfo Failed") << fileNames
										  << vars
										  << arrs
										  << expr
										  << false;

/*! ������� ������ ���������� � �������� ����������� ��������� */
		vars << Index("i", 0, 2, -1);
		fileNames[0] = "../../Tests/readVarInfo/8.One Variable.xml";
		fileNames << "../../Tests/readArrInfo/No Input File.xml";
	QTest::newRow("2.ReadArrInfo Failed") << fileNames
										  << vars
										  << arrs
										  << expr
										  << false;

/*! ������� ������ ��������� ����������� ��������� */
		size << 10;
		elements << 2 << 8 << 9 << 7;
		arrs << Array("arr", size, elements);
		fileNames[1] = "../../Tests/readArrInfo/9.One Array.xml";
		fileNames << "../../Tests/readExpression/No Input File.txt";
	QTest::newRow("3.ReadExpression Failed") << fileNames
											 << vars
											 << arrs
											 << expr
											 << false;

/*! �������� ���������� ������� ������ */
		fileNames[2] = "../../Tests/readData/Correct Expression.txt";
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

	/*! ������� ������ �� ������� */
	QFETCH(QString,			inputFileName);
	QFETCH(QVector<Index>,	expectedVars);
	QFETCH(QString,			expectedString);

	/*! ������� ����������� ������� */
	try
	{
		inp.readVarInfo(inputFileName, vars);
	}
	catch (QString& errorString)
	{
		exception = errorString;
	}

	/*! ��������� ��������� */
	QVERIFY2(exception == expectedString
		&& vars		   == expectedVars, "Test failed!");
}

void Test_input::readArrInfo()
{
	Input inp;
	QVector<Array> arrs;
	QString exception("correct");

	/*! ������� ������ �� ������� */
	QFETCH(QString,			inputFileName);
	QFETCH(QVector<Array>,	expectedArrs);
	QFETCH(QString,			expectedString);

	/*! ������� ����������� ������� */
	try
	{
		inp.readArrInfo(inputFileName, arrs);
	}
	catch (QString &errorString)
	{
		exception = errorString;
	}

	/*! ��������� ��������� */
	QVERIFY2(exception == expectedString
		&& arrs		   == expectedArrs, "Test failed!");
}

void Test_input::readExpression()
{
	Input inp;
	QStringList expr;
	QString exception("correct");


	/*! ������� ������ �� ������� */
	QFETCH(QString,		   inputFileName);
	QFETCH(QVector<Index>, inputVars);
	QFETCH(QVector<Array>, inputArrs);
	QFETCH(QStringList,    expectedExpr);
	QFETCH(QString,		   expectedString);

	/*! ������� ����������� ������� */
	try
	{
		inp.readExpression(inputFileName, expr, inputVars, inputArrs);
	}
	catch (QString &errorString)
	{
		exception = errorString;
	}

	/*! ��������� ��������� */
	QVERIFY2(exception == expectedString
		&& expr		   == expectedExpr,   "Test failed!");
}

void Test_input::readData()
{
	Input inp;
	bool success = false;
	QVector<Array> arrs;
	QVector<Index> vars;
	QStringList    expr;
	QStringList    fileNames;

	/*! ������� ������� */
	QFETCH(QStringList,    inputFileNames);
	QFETCH(QVector<Index>, expectedVars);
	QFETCH(QVector<Array>, expectedArrs);
	QFETCH(QStringList,    expectedExpr);
	QFETCH(bool,		   expectedSuccess);

	/*! ������� ����������� ������� */
	success = inp.readData(inputFileNames, vars, arrs, expr);

	/*! ��������� ��������� */
	QVERIFY2(vars  == expectedVars
		&& arrs    == expectedArrs
		&& expr    == expectedExpr
		&& success == expectedSuccess, "Test failed!");

}
