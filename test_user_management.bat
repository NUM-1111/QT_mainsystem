@echo off
echo 正在编译用户管理界面测试程序...

REM 设置Qt环境变量（根据你的Qt安装路径调整）
set QTDIR=C:\Qt\5.15.2\mingw81_64
set PATH=%QTDIR%\bin;%PATH%

REM 编译测试程序
qmake test_user_management.pro
mingw32-make

REM 运行测试程序
if exist test_user_management.exe (
    echo 运行用户管理界面测试程序...
    test_user_management.exe
) else (
    echo 编译失败，请检查错误信息
)

pause 