/*!
 *\file
 *\brief ���� ���������� ������ ������������� �����������.
 *\author ��������� �������� gafk555@gmail.com.
 *
 * ������ ���� �������� � ���� ����� ������������� �������� ������.
 */
#ifndef OUTPUT_H
#define OUTPUT_H

#include <QObject>
#include <QVector>
#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include "exceeding.h"
#include "array.h"

/*!
 *\brief ����� ������������� �������� ������.
 *\author ��������� �������� gafk555@gmail.com.
 *
 * ������ ����� �������� ����������� ������� ������ ����������� ������ ���������:
 * ����������� �������� ��������� �/��� ��������� ����������� ������.
 */

class Output
{
public:
	/*! ����������� ��-��������� */
	Output();
	/*! ���������� */
	~Output();

	/*!
	 * ���������� ���� � �������� � ��������� ��� ����������� �� �������
	 *\param[in] errorString ������ � ����������� �� ������
	 */
	void writeError(QString &errorString);

	/*!
	 * ���������� �������� ���� ��������� � ��������� ��� ����������� � �����������
	 * ������ ��������� - �������� ��������� �� ������ �� ������� �������
	 *\param[in] exceedings ���������� � ������� �� ������� �������
	 */
	void makeOutputFile(QVector<Exceeding> &exceedings, const QVector<Array> &arrs, const QStringList &inputFileNames);

	/*!
	 * ���������� ������� ����, ���� �� ������� ������ ��� ���������� ���������
	 *\return true, ���� ������ ��������� ��� false, ���� ���
	 */
	bool isErrorOccured();

private:
	QString resultFileName; ///< ��� ����� �����������
	QString errorFileName;  ///< ��� ����� ������
};

#endif // OUTPUT_H