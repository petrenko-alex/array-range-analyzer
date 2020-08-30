@echo off
rem *************************************************************************
rem Ошибка считывания входных данных
rem Отсутствует один из необходимых атрибутов внутри xml файла с массивами
rem Сообщение об ошибке в консоли и файле "ArrayRangeAnalyzer-Errors.txt"
rem *************************************************************************

rem Запуск программы...
"..\ArrayRangeAnalyzer.exe" ".\Sources for tests\Expression.txt" ".\Sources for tests\Arrays - missed attribute.xml" ".\Sources for tests\Variables.xml"