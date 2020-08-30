@echo off
rem *************************************************************************
rem Ошибка считывания входных данных
rem Неверное значение атрибута в теге variable внутри xml файла с переменными
rem Сообщение об ошибке в консоли и файле "ArrayRangeAnalyzer-Errors.txt"
rem *************************************************************************

rem Запуск программы...
"..\ArrayRangeAnalyzer.exe" ".\Sources for tests\Expression.txt" ".\Sources for tests\Arrays.xml" ".\Sources for tests\Variables - Wrong attr value.xml"