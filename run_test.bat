@echo off
echo 正在编译数据库测试程序...

REM 设置Qt环境变量（根据你的Qt安装路径调整）
set QTDIR=C:\Qt\5.15.2\mingw81_64
set PATH=%QTDIR%\bin;%PATH%

REM 编译测试程序
qmake test_database.pro
mingw32-make

REM 运行测试程序
if exist test_database.exe (
    echo 运行测试程序...
    test_database.exe
) else (
    echo 编译失败，请检查错误信息
)

pause 