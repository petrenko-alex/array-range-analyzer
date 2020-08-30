@echo off
rem *************************************************************************
rem Ошибка считывания входных данных
rem Неизвестный тег внутир xml файла с массивами
rem Сообщение об ошибке в консоли и файле "ArrayRangeAnalyzer-Errors.txt"
rem *************************************************************************

rem Запуск программы...
"..\ArrayRangeAnalyzer.exe" ".\Sources for tests\Expression.txt" ".\Sources for tests\Arrays - unknown tags.xml" ".\Sources for tests\Variables.xml"