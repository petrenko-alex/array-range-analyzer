/*!
 *\file
 *\brief ���� ���������� ������ ���������� �����.
 *\author ��������� �������� gafk555@gmail.com.
 *
 * ������ ���� �������� � ���� ����� ���������� �����.
 */

#ifndef INDEX_H
#define INDEX_H

#include <QObject>

/*!
 *\brief ����� ���������� �����.
 *\author ��������� �������� gafk555@gmail.com.
 *
 * ������ ����� ��������� ����������, ������������ � ���������� ������� �������:
 * �������� � ��� �� ���������, �� ������������� �������� �� ������ ���� ����������,
 * �������� �� ���������� ���� � ������� ������������.
 */
class Index
{
public:
	Index();
	~Index();

	/*! ������� ������ ������ index �� ������ �����, ������, ���� � �������� ��������� �������� */
	Index(QString name, int from, int to, int step, int looped = 10);

	/*! ���������� ��� ������� ������ index */
	bool operator==(const Index &other);


	QString name;				///< ��� ����������
	int     from;				///< ����� ������� ���������
	int     to;					///< ������ ������� ���������
	int     step;				///< ��� ��������� ����������
	double  curValue;			///< ������������� �������� ����������
	double  prevValue;			///< �������� ���������� �� ���������� ����
	int     looped;				///< ������� ��������� �������� ��� �������� ������������
};

#endif // INDEX_H
