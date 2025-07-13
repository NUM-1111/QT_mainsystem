@echo off
echo ========================================
echo 主系统与分系统1交互测试
echo ========================================

echo.
echo 1. 首先编译分系统1...
cd ..\system1
qmake system1.pro
mingw32-make

echo.
echo 2. 编译主系统...
cd ..\mainsystem
qmake mainsystem.pro
mingw32-make

echo.
echo 3. 启动测试...
echo 请手动运行主系统，然后点击"启动子系统1"按钮
echo 观察控制台输出，确认：
echo   - 分系统1是否成功启动
echo   - 主系统是否成功连接到分系统1
echo   - 发送"/show_ui"命令后分系统1是否显示界面

echo.
echo 测试完成！
pause 