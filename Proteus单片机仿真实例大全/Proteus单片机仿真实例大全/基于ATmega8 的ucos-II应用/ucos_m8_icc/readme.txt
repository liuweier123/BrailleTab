           atmega 8  单片机   ucos  源代码


ucos-ii   编译器ICCAVR
CPU    atmega8     8M 晶振
对原作者的ucos进行了简化，去掉了 hook，保留了基本功能
代码精简，编译后代码占 mage8 的 49%
时钟使用timer2，中断时间为2 ms


任务1：刷新LED，检测按键，调整时间
任务2：计时，串口发送  9600 bps



////////////////////////////////////////////////////
作者：  YM
网站：  http://th123.nease.net
邮箱：  atmega@126.com