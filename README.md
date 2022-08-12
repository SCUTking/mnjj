# 模拟家居——C++实训

使用QT creater打开
在联网的情况下，运行软件。

下面是实训要求：
请你设计一个家居环境模拟系统，根据用户设置提供的墙体、窗体布局和空调、新风、地暖、加湿、除湿等设备的运行和能耗参数，
模拟空间中温度、湿度、空气质量的变化情况，给出随时间变化的数值或图形化展示。更进一步，假定所有设备都能智能控制，
根据随外界温湿度数据变化的设备运行控制指令。系统功能可以包括但不限于：
1、	空间的表示：
a)	空间大小固定或让用户设置
b)	是否考虑墙体门窗等能耗影响，如果有可进行参数设置
2、	设备管理
a)	包含的设备种类可自选，建议逐一添加，设备的参数自行调研，可以到品牌官网进行了解，比如远大科技集团
b)	设备参数可设置，可分型号管理，可比较不同设置下的设备运行对环境的影响及能耗需求
3、	数据生成和表示
a)	除了一些必要的设置，外界温湿度随时间变化的数据可利用曲线生成，可分四季模型，南北方模型等
b)	可用表格的方式显示数据，也可以图形化的方式
4、	空间、设备的联动
a)	多空间需求和多设备联动（比如中央空调、中央新风）
b)	功率的合理分配