/*!
 *\file
 *\brief ���� ���������� ������ ������ �� ������� �������.
 *\author ��������� �������� gafk555@gmail.com.
 *
 * ������ ���� �������� � ���� ����� ������ �� ������� �������.
 */

#ifndef EXCEEDING_H
#define EXCEEDING_H

#include <QObject>
#include <QVector>
#include <QStringList>

/*!
 *\brief ����� ������ �� ������� �������.
 *\author ��������� �������� gafk555@gmail.com.
 *
 * ������ ����� ��������� ����� �� ������� �������:
 * ��� �������, ����� ����������, ��� ������� ��������� �����,
 * �� ��������, ������� �������, �������� ������������ ���������
 * � ����� ��������� �������.
 */
class Exceeding
{
public:
	Exceeding();

	/*! ������� ������ ������ �� ������ ���� ����� ������� ������ */
	Exceeding(QString arrayName, QStringList indexName, QVector<double> indexValue, int requestedElement, int dimension);

	/*! ���������� ��� ������� ������ exceeding */
	bool operator==(const Exceeding &other);

	~Exceeding();

private:
	QString			 arrayName;				///< ��� �������, ��� �������� ��������� ����� �� �������
	QStringList		 indexName;				///< ����� ����������, ��� ������� ��������� �����
	QVector <double> indexValue;			///< �������� ���������� ��� ������ �� �������
	int				 requestedElement;		///< ������� �������, � �������� ������������ ���������
	int				 dimension;				///< ����� ��������� �������
};

#endif // EXCEEDING_H
