#Qt5 教程#
　　仅以此文向所有为自由软件在中国的普及作出贡献的人们表示敬意
　　
##关于本文##
　　本文包含了原创内容和文档翻译，以及一些对别人文章的引用、整理，这些内容往往是混在一起的。这是我们的学习笔记（说是备忘录也可以），所以，并未严格区分这些内容。当然，必要的部分会按原作者的要求声明原文地址。

+   本文的目标读者

    所有希望了解Qt或者希望开发跨平台程序的学生、程序员等等

+   阅读本文需要什么技能？

    我们假定你掌握了足够的关于C++知识和计算机基础知识。


##Qt介绍##
　　随着时代的发展，你或许越来越多地发现，很多软件的身影都不只出现在装有Windows XP/Vista/7的机器上。它们开始出现在Mac上面，出现在Linux上面，甚至出现在朋友的手机里。软件的跨平台已成为时代的大趋势。你有没有过让你的程序也同时部署在多个平台上的愿望呢？如果有，Qt可以帮你轻松实现它。

###什么是Qt？###
　　Qt是一个功能强大的跨平台应用程序开发框架，且包含了很多用于开发应用程序的工具，以便于开发桌面、嵌入式及移动应用程序。

　　Qt包含了Qt Freamwork和Qt Creator IDE。Qt Framework提供了C++和CSS/Javascript的API，这些API基本都是跨平台的，你可以在不改变代码的情况下在多平台编译。你可以轻松地创建跨平台应用程序。Qt Creator IDE是一个功能强大的集成开发环境，集成了界面设计器、多种版本控制工具插件等工具，支持代码高亮、自动补齐等等的功能，使开发Qt应用程序变成一种享受。

###为什么使用Qt?###
　　最初的跨平台GUI程序都是把核心的平台无关的代码抽象出来，然后为每个平台单独开发对应的GUI。为每个平台分别维护代码图形化界面是个很烦人的工作。请设想这样一个场景：你刚刚在windows上实现一个复杂而繁琐的功能，然后为了保证各平台的一致，又得在Linux上再实现一遍，最后在Mac上又来一遍。万一你不行地发现这个功能的设计有些问题，又得分别修改三个平台上对应的代码。而且，这三个平台上开发应用程序的感觉有很大不同，你不但需要同时学会并适应在这三个平台上开发应用程序，还得及时切换。是不是感觉很累很麻烦呢？能不能不把宝贵的时间浪费在处理各个不同平台的差异上呢？

　　Qt开发的初衷正是希望为开发者开发跨平台程序提供便利。它提供了大量功能强大的类和API，为开发跨平台应用程序提供了极大的便利，就如它的标语所说的“Code less, Create more, Deploy everywhere”。你可以在一个你喜欢的平台上开发，然后轻松的部署到其他的许多平台上。

　　Qt5包含了如下模块，这些模块将极大地减轻你的工作量。

*基本模块*

+   Qt Core

    核心的被其他模块依赖的的图形无关的类；

+   Qt GUI

    GUI组件的基础类，包括OpenGL；

+   Qt Multimedia

    提供音频、视频、广播和相机功能的方式；

+   Qt Network

    用于进行更简单且可移动的网络开发的方式；

+   Qt QML

    提供QML和Javascript语言的支持；

+   Qt Quick

    一个用于构建含自定义用户界面的高动态应用程序的声明式框架；

+   Qt SQL

    提供SQL数据库整合的类；

+   Qt Test

    用于对Qt程序和库进行单元测试的类；

+   Qt WebKit

    提供对WebKit2和新的QML API的支持；

+   Qt WebKit Widgets

    WebKit1和源自Qt4的基于QWidget的类；

+   Qt Widgets

    C++的widgets类。

*附加模块*

+   Active Qt(Windows)

    提供对ActiveX和COM的支持的类；

+   Qt Concurrent(Windows)

    提供用于编写多线程程序的高层API的支持；

+   Qt D-Bus(Unix)

    提供使用D-Bus协议进行进程内通讯的支持的类；

+   Qt图形特效

    Qt Quick2图形特效支持；

+   Qt Image Formats

    提供额外的图形格式支持：包括 TIFF，MNG，TGA和WBMP。

+   Qt OpenGL

    OpenGL类支持；

    注意：此模块仅提供于Qt 4.x版本的移植。请在新的代码中使用QtGui类来代替QOpenGL。

+   Qt Print Support

    提供更加简易和可移动的打印方式。

+   Qt Declarative

    Qt Declarative 是一个提供 Qt 4 兼容的类。提供到Qt 4.8 Qt Quick documentation的文档支持；

+   Qt Script

    让QT应用支持脚本化，此功能用于Qt 4.x的兼容支持。请在新的代码中使用 QtQml 模块中的 QJS* 类来替代Qt Script。

+   Qt Script Tools

    为使用Qt Script的应用提供额外功能的支持。

+   Qt SVG

    提供用于显示SVG文件的功能类；

+   Qt XML

    提供C++对SAX和DOM的支持；

    注意：不建议使用此类, 请使用 QXmlStreamReader 和 QXmlStreamWriter 来启用新的功能；

+   Qt XML Patterns

    提供对 XPath，XQuery，XSLT 和 XML schema 语言的支持。

　　这些功能涵盖了开发应用程序时的所需的绝大部分功能。这就意味着，我们可以专注于开发我们项目中的特色部分，而不必为很多常规的细枝末节的功能而耗费宝贵的时间和精力，更不必每次都重造那些别人已经造过无数遍的轮子。同时，你也不必担心Qt的稳定性、易用性等等。Qt有大量的成功案例，例如著名的桌面环境KDE（K Desktop Environment）,VirtualBox虚拟机软件，国产办公软件的金山WPS等等，它绝不会让你失望。

　　如果上述文字仍无法打动你的话，我们再来随便看几个Qt提供的类，看看能否给你点震撼呢？
　　
+   QRegularExpression

    这个类提供了对Perl兼容的正则表达式的支持，且完全支持Unicode。

+   QJsonArray、QJsonDocument、QJsonObject、QJsonParseError、QJsonValue

    这些类提供了对解析和生成JSON的支持（JSON(JavaScript Object Notation) 是一种轻量级的数据交换格式，广泛用于网络中）。

+   QSystemTrayIcon

    这个类提供对系统托盘(System Tray)的支持，可以在托盘上显示图标，显示消息，支持托盘菜单等等。且这是跨平台的。支持所有Qt支持的windows版本、所有符合freedesktop.org关于系统托盘的规定的X11窗口管理器（包括最近的GNOME和KDE版本），以及所有Qt支持的Mac OS X版本。

+   QCompleter

    QCompleter类为任意Qt Widget提供自动补齐功能，例如QLineEdit和QComboBox。

　　当然这些仅仅是Qt提供的大量功能中的少数几个，你是否动心了呢？动心了就请继续阅读本文，踏上Qt的学习和使用之旅吧。

###关于Qt5的多平台支持###
在开始之前，我们先来看看Qt5的多平台支持能力。

Qt5使用QPA（Qt Platform Abstraction，Qt平台抽象）将各个不同的平台的具体处理抽象化，以提供平台独立性，且可以通过插件的方式进行扩展。Qt原本在很多类的实现中都针对不同平台分别进行了特殊处理，提高了支持更多平台的难度。QPA把这些都抽象了出来，并以插件的形式实现对各平台的支持。只要实现一个新的插件就可以支持新的平台。这使得支持新的平台变成了一件轻而易举的事。

Qt5支持如下平台：

Qt5支持的桌面平台有Windows、Linux/X11和Mac OS X，嵌入式系统支持嵌入式Linux(DirectFB, EGLFS, KMS, and Wayland)、嵌入式Windows(精简版和标准版)以及实时操作系统，例如：QNX, VxWorks和INTEGRITY。
Qt5在以后的版本中将会提供对主流移动操作系统的支持（包括Android、iOS、Windows 8 (WinRT)、BlackBerry 10），这些支持正在开发中，将在未来的版本中提供（据最新消息，Qt 5.1将提供Android和iOS）。

Qt项目对如下配置进行过测试：

+   Ubuntu Linux 11.10, X11 (64-bit)	Ubuntu提供的编译器版本
+   Ubuntu Linux 12.04, X11 (64-bit)	Ubuntu提供的编译器版本
+   Microsoft Windows 7 (32-bit)	MSVC 2010 SP1
+   Microsoft Windows 7 (32-bit)	MinGW-builds gcc 4.7.2 (32-bit)
+   Microsoft Windows 8 (64-bit)	MSVC 2012
+   Apple Mac OS X 10.7 "Lion", Cocoa (64-bit)	苹果提供的Clang版本
+   Apple Mac OS X 10.8 "Mountain Lion", Cocoa (64-bit)	苹果提供的Clang版本

###Qt提供的安装包###
Qt项目为所有上述平台提供二进制安装包。如果想在其他Qt支持的平台上开发，你需要自己从源代码编译。如果想知道更多关于Qt在不同平台和编译器上的信息，请看[平台和信息注意事项页面](http://qt-project.org/doc/qt-5.0/qtdoc/platform-notes.html)

###Qt工具###
　　工具是QT套件正式的一部分。正式的工具在所有的开发平台上都可运行。

　　下面是QT的工具列表：

+    Qt Designer

    拓展Qt Designer功能的类；
+    Qt Help

    在线帮助的类；
+    Qt UI Tools

    UI工具的类；

###Qt许可协议###
看了这么多，你或许会问：这么强大的开发工具，得要多少钱啊？看看自己的钱包，不免有些紧张。其实不必那么紧张，Qt可以使用三种不同的协议以适应不同的用户需求：

+   Qt商业许可协议（付费）

    如果你准备开发一个专有或商业软件且不希望向第三方开放任何源代码，或者你无法遵守GNU LGPL version 2.1 or GNU GPL version 3.0协议，你可以选择这个协议

+   GNU LGPL version 2.1（免费）

    这个协议很著名，大家应该都很了解了。只要你采用动态链接的形式使用Qt，你就可以随意发布你的应用程序。

+   GNU GPL version 3.0 （免费）

    GPL开源协议大家更了解，不必多说了。如果你想使用GPLv3发布你的程序，或者代码中需要使用其他的一些使用GPLv3协议授权的代码，那么你可以使用GPLv3版本的Qt。
    
这三个协议的Qt库的源代码是完全一致的，也就是说功能上没有任何差异。只是收费版本提供很多支持、售后服务而已。如果想更多地了解LGPL的内容，可以参考FinderCheng的[这篇博客](http://devbean.blog.51cto.com/448512/313477)
    

