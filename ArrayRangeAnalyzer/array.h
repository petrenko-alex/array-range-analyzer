/*!
 *\file
 *\brief ���� ���������� ������ �������.
 *\author ��������� �������� gafk555@gmail.com.
 *
 * ������ ���� �������� � ���� ����� �������.
 */

#ifndef ARRAY_H
#define ARRAY_H

#include <QObject>
#include <QVector>

/*!
*\brief ����� �������.
*\author ��������� �������� gafk555@gmail.com.
*
* ������ ����� ��������� ������ � ���������� � ���:
* ��� �������, ������� ��� ��������� � �������� �������.
*/
class Array
{
public:
	Array();
	~Array();

public:
	QString		   name;				///< ��� �������
	QVector <int>  size;				///< ������ � ��������� �������
	QVector <int>  elements;			///< ������ � ���������� �������
	QVector <bool> isExceeding;			///< ������, ���������� ���������� � ���, ��������� �� ����� �� ������� ��������� �������

};

#endif // ARRAY_H