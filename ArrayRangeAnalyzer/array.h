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

	/*! ������� ������ ������ Array �� ������ �����, �������� ��������� � ��������� ������� */
	Array(QString name, QVector<int> &size, QVector<int> &elements);

	/*! ���������� ��� ������� ������ Array */
	bool operator==(const Array &other);

	QString		   name;				///< ��� �������
	QVector <int>  size;				///< ������ � ��������� �������
	QVector <int>  elements;			///< ������ � ���������� �������
	QVector <bool> isExceeding;			///< ������, ���������� ���������� � ���, ��������� �� ����� �� ������� ��������� �������

};

#endif // ARRAY_H