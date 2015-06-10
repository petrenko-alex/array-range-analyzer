/*!
 *\file
 *\brief Файл объявления класса выхода за пределы массива.
 *\author Александр Петренко gafk555@gmail.com.
 *
 * Данный файл содержит в себе класс выхода за пределы массива.
 */

#ifndef EXCEEDING_H
#define EXCEEDING_H

#include <QObject>
#include <QVector>
#include <QStringList>

/*!
 *\brief Класс выхода за пределы массива.
 *\author Александр Петренко gafk555@gmail.com.
 *
 * Данный класс описывает выход за пределы массива:
 * имя массива, имена переменных, при которых произошел выход,
 * их значения, элемент массива, которому производится обращение
 * и номер измерения массива.
 */
class Exceeding
{
public:
	Exceeding();

	/*! Создает объект класса на основе всех полей данного класса */
	Exceeding(QString arrayName, QStringList indexName, QVector<double> indexValue, int requestedElement, int dimension);

	/*! Сравнивает два объекта класса exceeding */
	bool operator==(const Exceeding &other);

	~Exceeding();

private:
	QString			 arrayName;				///< Имя массива, для которого произошел выход за пределы
	QStringList		 indexName;				///< Имена переменных, при которых произошёл выход
	QVector <double> indexValue;			///< Значения переменных при выходе за пределы
	int				 requestedElement;		///< Элемент массива, к которому производится обращение
	int				 dimension;				///< Номер измерения массива
};

#endif // EXCEEDING_H
