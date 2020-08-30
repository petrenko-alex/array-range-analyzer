@echo off
rem *************************************************************************
rem Ошибка считывания входных данных
rem Заданные массивы не используются в выражении
rem Сообщение об ошибке в консоли и файле "ArrayRangeAnalyzer-Errors.txt"
rem *************************************************************************

rem Запуск программы...
"..\ArrayRangeAnalyzer.exe" ".\Sources for tests\Expression without arrs.txt" ".\Sources for tests\Arrays.xml" ".\Sources for tests\Variables.xml"