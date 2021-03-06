# uTiny
简单的3D游戏引擎，类似Unity3D的 API

## 前言
这是我一时冲动玩起来的编程项目，如果你需要它，记住它并不完善。

它比较小（tiny），又有点像 Unity3D，所以就这样命名了。

平时偶尔会想做一个3D效果演示或者做一个小型3D游戏，总觉得Unity3D这样的游戏引擎尽管好用，但用起来却是杀鸡用牛刀。而如果用OpenGL或者Direct3D这些底层图形API来实现，渲染系统本身的复杂性就远远超过了初始想法的复杂性。

设计的中引擎是能够屏蔽掉OpenGL跟DirectX的，使用时无需考虑它们，只要写好自己的交互逻辑就好了。目前底层由GLUT实现，未来会考虑加入DirectX或者Vulkan的底层实现。


## 功能
### 场景管理
3D场景为若干节点构成的场景图。每个节点可以包含若干附加数据，如网格，摄像机，脚本等


### 模型加载
可以从FBX文件加载模型


### 脚本系统
引擎没有实现脚本语言解释器，但实现了C++的脚本类，通过实现Script子类并绑定到节点来实现脚本控制


## 特性
### 具有与Unity3D相似的API
尽管C++与C#有着诸多区别，但 Unity3D 提供的 C# API 一定程度上可以使用C++来实现。

这里借鉴了 Unity3D 中的GameObject、 Component、 Transform、 Material、 Renderer等API， 提供了同名的 C++ 类。
