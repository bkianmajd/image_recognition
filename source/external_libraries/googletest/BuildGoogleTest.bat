set GTEST_DIR=%__CD__%
set BUILD_OUT_DIR=..\..\builds\common\googletest
cd %BUILD_OUT_DIR%
g++ --debug -isystem %GTEST_DIR%\include -I%GTEST_DIR% -pthread -c %GTEST_DIR%\src\gtest-all.cc
ar -rv libgtest.a gtest-all.o
cd %GTEST_DIR%
