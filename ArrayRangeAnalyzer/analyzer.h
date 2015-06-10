/*!
*\file
*\brief ���� ���������� ������ �������� ��������� �� ������� ������� �� ������� ��������.
*\author ��������� �������� gafk555@gmail.com.
*
* ������ ���� �������� � ���� ����� �������� ��������� �� ������� ������� �� ������� ��������.
*/

#ifndef ANALYZER_H
#define ANALYZER_H

#include <QObject>
#include "index.h"
#include "array.h"
#include "exceeding.h"

/*!
*\brief ����� �������� ��������� �� ������� ������� �� ������� �������.
*\author ��������� �������� gafk555@gmail.com.
*
* ������ ����� �������� �������� ������� ��� �������� ��������� �� ������� ������� �� ������� ��������.
*/
class Analyzer
{
public:
	Analyzer();
	~Analyzer();

	/*!
	 *\brief ��������� ������� ������� �� ������� �������� � ��������� ��� ������� ��������� ����������
	 *\details �������� �� ��������� ����� �� �����, �������� ���, � ���������� ������� �������� � �� ���������
	 *
	 *param[in]  vars		  ������ �������� ������ \ref index � ���������� � ����������
	 *param[in]  arrs		  ������ �������� ������ \ref Array - ���������� � ��������
	 *param[in]  expr		  ��������� � ���� ������ �����
	 *param[out] exceedings   ������ �������� ������ \ref exceeding - ���������� � ������� �� �������
	 *\exception errorString  ������ � ����������� � ��������� ����������
	 */
	void analyzeExpression(QVector<Index> &vars, QVector<Array> &arrs, const QStringList &expr, QVector<Exceeding> &exceedings) throw(QString&);


	/*!
	 *\brief ��������� ������� ������� �� ������� �������� � ��������� �� ���� ��������� �������� ����������
	 *\details ��� ���������� ���������� �����, ����� ���������� ���������� 
	 *
	 *param[in]  vars		  ������ �������� ������ \ref index � ���������� � ����������
	 *param[in]  arrs		  ������ �������� ������ \ref Array - ���������� � ��������
	 *param[in]  expr		  ��������� � ���� ������ �����
	 *param[out] exceedings   ������ �������� ������ \ref exceeding - ���������� � ������� �� �������
	 *\exception errorString  ������ � ����������� � ��������� ����������
	 */
	void checkExpression(QVector<Index> &vars, QVector<Array> &arrs, const QStringList &expr, QVector<Exceeding> &exceedings) throw(QString&);


};

#endif // ANALYZER_H

