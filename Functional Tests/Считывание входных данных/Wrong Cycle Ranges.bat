@echo off
rem *************************************************************************
rem Ошибка считывания входных данных
rem Неверно заданы границы и шаг переменной(цикл возрастающий, а шаг меньше 0)
rem Сообщение об ошибке в консоли и файле "ArrayRangeAnalyzer-Errors.txt"
rem *************************************************************************

rem Запуск программы...
"..\ArrayRangeAnalyzer.exe" ".\Sources for tests\Expression.txt" ".\Sources for tests\Arrays.xml" ".\Sources for tests\Variables - wrong cycle ranges.xml"