#Qt5 教程#
仅以此文向所有为自由软件在中国的普及作出贡献的人们表示敬意

##Qt介绍##
　　随着时代的发展，你或许越来越多地发现，很多软件的身影都不只出现在装有Windows XP/Vista/7的机器上。它们开始出现在Mac上面，出现在Linux上面，甚至出现在朋友的手机里。软件的跨平台已成为时代的大趋势。你有没有过让你的程序也同时部署在多个平台上的愿望呢？如果有，Qt可以帮你轻松实现它。

###什么是Qt？###
　　Qt是一个功能强大的跨平台应用程序开发框架，且包含了很多用于开发应用程序的工具，以便于开发桌面、嵌入式及移动应用程序。
　　Qt包含了Qt Freamwork和Qt Creator IDE。Qt Framework提供了C++和CSS/Javascript的API，这些API基本都是跨平台的，你可以在不改变代码的情况下在多平台编译。你可以轻松地创建跨平台应用程序。Qt Creator IDE是一个功能强大的集成开发环境，集成了界面设计器、多种版本控制工具插件等工具，支持代码高亮、自动补齐等等的功能，使开发Qt应用程序变成一种享受。

###为什么使用Qt?###
　　最初的跨平台GUI程序都是把核心的平台无关的代码抽象出来，然后为每个平台单独开发对应的GUI。为每个平台分别维护代码图形化界面是个很烦人的工作。请设想这样一个场景：你刚刚在windows上实现一个复杂而繁琐的功能，然后为了保证各平台的一致，又得在Linux上再实现一遍，最后在Mac上又来一遍。万一你不行地发现这个功能的设计有些问题，又得分别修改三个平台上对应的代码。而且，这三个平台上开发应用程序的感觉有很大不同，你不但需要同时学会并适应在这三个平台上开发应用程序，还得及时切换。是不是感觉很累很麻烦呢？能不能不把宝贵的时间浪费在处理各个不同平台的差异上呢？
　　Qt开发的初衷正是希望为开发者开发跨平台程序提供便利。它提供了大量功能强大的类和API，为开发跨平台应用程序提供了极大的便利，就如它的标语所说的“Code less, Create more, Deploy everywhere”。你可以在一个你喜欢的平台上开发，然后轻松的部署到其他的许多平台上。
　　Qt5包含了如下模块
*基本模块*

+   Qt Core
　　核心的被其他模块依赖的的图形无关的类
+   Qt GUI
　　GUI组件的基础类，包括OpenGL
+   Qt Multimedia
　　提供音频、视频、广播和相机功能的类
+   Qt Network
　　用于进行更简单且可移植的网络开发的类
+   Qt QML
　　提供QML和Javascript语言
+   Qt Quick
　　一个用于构建含自定义用户界面的高动态应用程序的声明式框架
+   Qt SQL
　　提供SQL数据库整合的类
+   Qt Test	
　　用于对Qt程序和库进行单元测试的类
+   Qt WebKit
　　提供对WebKit2和新的QML API的支持
+   Qt WebKit Widgets
　　WebKit1和源自Qt4的基于QWidget的类。
+   Qt Widgets
　　C++的widgets类

*附加模块*

+   Active Qt(Windows)
　　提供对ActiveX和COM的支持的类
+   Qt Concurrent(windows)
　　提供用于编写多线程程序的高层API
+   Qt D-Bus(Unix)
　　提供使用D-Bus协议进行进程内通讯的支持的类
+   Qt图形特效
　　Qt Quick2图形特效
+   Qt Image Formats	All		Plugins for additional image formats: TIFF, MNG, TGA, WBMP.
+   Qt OpenGL			OpenGL support classes.

Note: Provided to ease porting from Qt 4.x. Please use the QOpenGL classes in QtGui for new code.
+   Qt Print Support	All		Classes to make printing easier and more portable.
+   Qt Declarative	All		Qt Declarative is provided for Qt 4 compatibility. The documentation is available through the Qt 4.8 Qt Quick documentation.
+   Qt Script	All		Classes for making Qt applications scriptable. Provided for Qt 4.x compatibility. Please use the QJS* classes in the QtQml module for new code.
+   Qt Script Tools	All		Additional components for applications that use Qt Script.
+   Qt SVG	All		Classes for displaying the contents of SVG files.
+   Qt XML			C++ implementations of SAX and DOM.

Note: Deprecated, please use QXmlStreamReader and QXmlStreamWriter for new functionality.
Qt XML Patterns			Support for XPath, XQuery, XSLT and XML schema validation.

###Qt5的多平台支持###

Qt5使用QPA（Qt Platform Abstraction，Qt平台抽象）将各个不同的平台的具体处理抽象化，以提供平台独立性，且可以通过插件的方式进行扩展。Qt原本在很多类的实现中都针对不同平台分别进行了特殊处理，提高了支持更多平台的难度。QPA把这些都抽象了出来，并以插件的形式实现对各平台的支持。只要实现一个新的插件就可以支持新的平台。这使得支持新的平台变成了一件轻而易举的事。Qt5支持如下平台


+   youo