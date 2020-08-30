@echo off
rem *************************************************************************
rem Ошибка считывания входных данных
rem Неизвестный символ в выражении
rem Сообщение об ошибке в консоли и файле "ArrayRangeAnalyzer-Errors.txt"
rem *************************************************************************

rem Запуск программы...
"..\ArrayRangeAnalyzer.exe" ".\Sources for tests\Expr with undef el.txt" ".\Sources for tests\Arrays.xml" ".\Sources for tests\Variables.xml"