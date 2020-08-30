@echo off
rem *************************************************************************
rem Проверка операции постфиксной инкрементации, не приводящей к выходу
rem те же условия что и в тесте Left Inc - Exceeding но операция другая
rem Результат работы программы в файле "ArrayRangeAnalyzer-Results.txt"
rem *************************************************************************

rem Запуск программы...
"..\ArrayRangeAnalyzer.exe" ".\Sources for tests\Expr10.txt" ".\Sources for tests\Arrs5.xml" ".\Sources for tests\Vars4.xml"