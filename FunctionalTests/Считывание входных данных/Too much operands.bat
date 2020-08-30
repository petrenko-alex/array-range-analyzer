@echo off
rem *************************************************************************
rem Ошибка считывания входных данных
rem В выражении лишние операнды, для которых нет операции
rem Сообщение об ошибке в консоли и файле "ArrayRangeAnalyzer-Errors.txt"
rem *************************************************************************

rem Запуск программы...
"..\ArrayRangeAnalyzer.exe" ".\Sources for tests\Too much operands.txt" ".\Sources for tests\Arrays.xml" ".\Sources for tests\Variables.xml"