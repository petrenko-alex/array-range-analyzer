/*!
 *\file
 *\brief ���� ���������� ������ ���������� ������� ������.
 *\author ��������� �������� gafk555@gmail.com.
 *
 * ������ ���� �������� � ���� ����� ���������� ������� ������.
 */

#ifndef INPUT_H
#define INPUT_H

#include <QObject>
#include <QVector>
#include <QStringList>
#include <QtXml >
#include "array.h"
#include "index.h"
//#include "operations.h"


/*!
 *\brief ����� ���������� ������� ������.
 *\author ��������� �������� gafk555@gmail.com.
 *
 * ������ ����� �������� ����������� ������� ��� ���������� ������� ������ ���������.
 */
class Input
{
public:
	Input();
	~Input();

	/*!
	 * ��������� ������� ������ ���������
	 *\param[in]  inputFileNames	����� ������� ������
	 *\param[out] vars				������ �������� ������ \ref index � ���������� � ����������
	 *\param[out] arrs				������ �������� ������ \ref Array - ���������� � ��������
	 *\param[out] expr				��������� � ���� ������ �����
	 *\return						������� ���������� ����������
	 */
	bool readData(const QStringList &inputFileNames, QVector <Index> &vars, QVector <Array> &arrs, QStringList &expr);


	/*!
	 * ��������� ������� ���� � ����������� �� �������������� � ��������� ����������
	 *\param[in]  fileName      ��� ����� ������� ������ � ����������� � ����������
	 *\param[out] vars          ������ �������� ������ \ref index � ���������� � ����������
	 *\exception  errorString   ������ � ����������� � ��������� ����������
	 */
	void readVarInfo(const QString fileName, QVector <Index> &vars) throw(QString&);

	/*!
	 * ��������� �������� ���������� ���� variable � ����� ������� ������ � ����������� � ����������
	 *\param[out] var          ������ ������ \ref index , � ������� ���������� ���������� ������
	 *\param[in]  atrs         ��������� ���� variable
	 *\param[in]  i            ����� ���� variable � �����
	 *\exception  errorString  ������ � ����������� � ��������� ����������
	 */
	void readVarAttributes(Index &var, QXmlStreamAttributes &atrs, int i) throw(QString&);

	/*!
	 * ��������� ������� ���� � ����������� �� �������������� � ��������� ��������
	 *\param[in]  fileName      ��� ����� ������� ������ � ����������� � ��������
	 *\param[out] arrs          ������ �������� ������ \ref Array � ���������� � ��������
	 *\exception  errorString   ������ � ����������� � ��������� ����������
	 */
	void readArrInfo(const QString fileName, QVector <Array> &arrs) throw(QString&);

	/*!
	 * ��������� �������� ���������� ���� array � ����� ������� ������ � ����������� � ��������
	 *\param[out] arr          ������ ������ \ref Array , � ������� ���������� ���������� ������
	 *\param[in]  atrs         ��������� ���� array
	 *\param[in]  i            ����� ���� array � �����
	 *\exception  errorString  ������ � ����������� � ��������� ����������
	 */
	void readArrAttributes(Array &arr, QXmlStreamAttributes &atrs, int i) throw(QString&);

	/*!
	 * ��������� ������� ���� � ����������
	 *\param[in]  fileName      ��� ����� ������� ������ � ����������
	 *\param[out] expr          ��������� � ���� ������ �����
	 *\param[in]  vars		    ������ �������� ������ \ref index � ���������� � ����������
	 *\param[in]  arrs		    ������ �������� ������ \ref Array - ���������� � ��������
	 *\exception  errorString   ������ � ����������� � ��������� ����������
	 */
	void readExpression(const QString fileName, QStringList  &expr, const QVector<Index> &vars, const QVector<Array> &arrs) throw(QString&);
};

#endif // INPUT_H
