/*!
*\file
*\brief ���� ���������� ������ ��������������� ��������.
*\author ��������� �������� gafk555@gmail.com.
*
* ������ ���� �������� � ���� ����� ��������������� ��������.
*/

#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <QObject>
#include <QMap>
#include <QVector>
#include "index.h"
#include "array.h"
#include <QRegExp>

/*!
*\brief ����� ��������������� ��������.
*\author ��������� �������� gafk555@gmail.com.
*
* ������ ����� �������� ��������������� �������, �����������:
* - �������� ������� ��������
* - ����������, ��������� �� ������ �������������� ���������;
* - ����������, ��������� �� ������ ��������� ����������;
* - ����������, ��������� �� ������ ������������ ������;
* - ����������, ��������� �� ������ ����� ������;
* - ����������, ��������� �� ������ ������������� ����� ������;
* - ����������, ��������� �� ������ ������������ ������;
* - ����������, ��������� �� ������ ���������;
* - ����������, ��������� �� ������ ��������� ��������;
* - ����������, ��������� �� ������ ��������� ���������(��������, ����������, ��������� ��� ������).
*/
class operations
{
public:
	operations();
	~operations();

	/*!
	 * ���������� ������� ��������
	 *\param[in] op ������ ��������
	 *\return       ������� ��������
	 */
	int getArity(const QString &op);

	/*!
	 * ����������, �������� �� ������� �������������� ���������
	 *\param[in] op ����������� �������
	 *\retrun       ���������� �������� true - ���� ��������, false - ���� ��� 
	 */
	bool isDefiniteOperation(const QString &op);

	/*!
	 * ����������, �������� �� ������� �������� ����������
	 *\param[in] var  ����������� �������
	 *\param[in] vars ������ �������� ����������
	 *\retrun         ���������� �������� true - ���� ��������, false - ���� ���
	 */
	bool isDefiniteVariable(const QString &var, const QVector<index> &vars);

	/*!
	 * ����������, �������� �� ������ ������������ ������
	 *\param[in] number ����������� �������
	 *\retrun           ���������� �������� true - ���� ��������, false - ���� ���
	 */
	bool isFloatNumber(const QString &number);

	/*!
	 * ����������, �������� �� ������� ����� ������
	 *\param[in] number ����������� �������
	 *\retrun           ���������� �������� true - ���� ��������, false - ���� ���
	 */
	bool isIntNumber(const QString &number);

	/*!
	 * ����������, �������� �� ������� ������������� ����� ������
	 *\param[in] number ����������� �������
	 *\retrun           ���������� �������� true - ���� ��������, false - ���� ���
	 */
	bool isPositiveIntNumber(const QString &number);

	/*!
	 * ����������, �������� �� ������� ���������(������, ���������� ��� ��������)
	 *\param[in] number ����������� �������
	 *\param[in] vars   ������ �������� ����������
	 *\param[in] arrs   ������ �������� ��������
	 *\retrun           ���������� �������� true - ���� ��������, false - ���� ���
	 */
	bool isOperand(const QString &operand, const QVector<index> &vars, const QVector<Array> &arrs);

	/*!
	 * ����������, �������� �� ������� �������� ��������
	 *\param[in] arr  ����������� �������
	 *\param[in] arrs ������ �������� ��������
	 *\retrun         ���������� �������� true - ���� ��������, false - ���� ���
	 */
	bool isDefiniteArray(const QString &arr, const QVector<Array> &arrs);

	/*!
	 * ����������, �������� �� ������ ��������� (���������, ����������, ���������� ��� ��������)
	 *\param[in] element ����������� ������
	 *\param[in] arrs    ������ �������� ��������
	 *\param[in] vars    ������ �������� ����������
	 *\retrun            ���������� �������� true - ���� ��������, false - ���� ���
	 */
	bool isDefiniteElement(const QString &element, const QVector <Array> &arrs, const QVector<index> &vars);

private:
	QMap<QString, int> Operations;			///< �������������� � ��������� �������� � �� �������

};

#endif // OPERATIONS_H