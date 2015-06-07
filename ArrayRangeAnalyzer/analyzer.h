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
class analyzer
{
public:
	analyzer();
	~analyzer();

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
	void analyzeExpression(QVector<index> &vars, QVector<Array> &arrs, const QStringList &expr, QVector<exceeding> &exceedings) throw(QString&);


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
	void checkExpression(QVector<index> &vars, QVector<Array> &arrs, const QStringList &expr, QVector<exceeding> &exceedings) throw(QString&);


};

#endif // ANALYZER_H

