## Qt学习备忘录2：初试Qt##
　　在对Qt做完了基本的介绍之后（其实，你认为这是布道我也没太大意见），我们开始尝试一下Qt。先配置一下Qt的环境，然后用Qt写个简单的程序（对，你猜对了，就是hello，world）。感受一下用Qt写程序的感觉。

### 如何安装Qt开发环境 ###
　　本节将会说明如何安装Qt的开发环境，包括编译安装和二进制包安装。

#### 二进制包安装 ####
##### Ubuntu #####
　　Ubuntu环境下有两种不同的选择。

+  选择发行版打包好的Qt

	Ubuntu发行版的软件仓库中有一个打包好的Qt。你可以直接打开Ubuntu软件中心，然后搜索Qt Creator，点击安装。也可以使用命令行：
        
        sudo apt-get install qtcreator qt5-default
	
	安装Qt Creator及开发Qt5必要的环境
	
+  从官方网站下载最新的二进制包

	发行版中包含的Qt版本很可能不是最新的Qt版本，或者版本无法使你满意。这种情况下，你可以选择从官网下载Qt。官网下载地址为：http://qt-project.org/downloads
	
	根据你的具体情况下载Qt (版本号) for Linux 32-bit(或64-bit)。然后打开命令行，到你下载下的安装包所在的目录下，执行：
	
        chmod +x ./qt-linux-opensource-(你所下载的Qt的版本号)-x86_64-offline.run
        
	这条命令使我们下载的.run文件具有可执行权限。然后执行：
	
        sudo ./qt-linux-opensource-(你所下载的Qt的版本号)-x86_64-offline.run
        
	使用root权限安装Qt。之后会打开一个和Microsoft Windows下的安装程序相同的界面，一直点下一步即可，相信各位都没问题。
	
	（注意：笔者不使用sudo安装时会发生错误，但使用sudo后Qt Creator的配置文件的读写均需root权限，需手工修改权限为普通用户可读写，否则调Qt Creator设置的时候会报错。大牛们如果有更好的方法，还请赐教）
	
##### windows #####
FIXME：待补齐

#### 编译安装Qt5 #####
##### Ubuntu #####
首先，下载源代码，编译，安装。
FIXME：没实际经验，先不写了。

##### windows #####
FIXME：没实际经验，暂不写。

至此，Qt的开发环境就配置完毕了。接下来，我们开始完成一个简单的Hello World程序。

### Hello World ！ ###
#### 敲出第一段Qt代码 ####
步骤：

1. 「文件」->「新建文件或项目」
2. 选择「其他项目」中的「空Qt项目」

创建好项目后在项目中添加main.cpp，输入以下代码：

        #include <QApplication>
        #include <QLabel>
        
        int main(int argc, char *argv[])
        {
            QApplication a(argc, argv);

            QLabel label("Hello World!");
            label.show();
    
            return a.exec();
        }
		
　　编译，运行。然后一个Hello world程序就完成了，很简单，不是吗？

　　接下来，我们来具体分析一下这个Hello World程序。头两行引用头文件，这个自然不用多说。然后先实例化一个QApplication并将argc和argv参数传入。显然，我们大致猜到，QApplication类是用于处理Qt应用程序中最基本的功能的。比如处理外部传入的参数等等，是Qt应用程序中最基本的类。QLabel顾名思义，是一个标签控件，用于显示文字。那么，向构造函数传入的字符串，自然就是该标签的内容了。下一行`label.show()`的意思应该是显示该控件。最后，返回程序运行结果。

　　通过刚刚的目测，我们已经大致猜测了整段程序的含义，接下来，我们来细细地查阅Qt5的文档，来验证一下我们的想法。

#### QApplication类 ####
　　QApplication类管理着GUI程序的控制流和主要设置。QApplication继承了QGuiApplication类，并实现了一些基于QWidget的应用程序需要的功能。它负责处理关于widget的一些特定的初始化和终止化操作。注意！无论你的程序有几个窗口，你只能有**一个**QAppliaction对象。对于那些不基于QWidget的Qt程序，你应当使用QGuiApplication代替QApplication，因为它不必依赖于QtWidgets库。

　　一些GUI程序会提供批处理模式（从命令行输入一些参数，然后自动执行任务而不需要人工操作）。在这类非GUI的模式下，初始化一些和图形用户界面相关的资源就显得有些浪费了。为了避免这个问题，Qt提供了QCoreApplication。下面这个例子（源自Qt5Doc）展示了如何动态选择创建QCoreApplication还是QApplication。

        QCoreApplication* createApplication(int &argc, char *argv[])
        {
            for (int i = 1; i < argc; ++i)
                if (!qstrcmp(argv[i], "-no-gui"))
                    return new QCoreApplication(argc, argv);
            return new QApplication(argc, argv);
        }
       
        int main(int argc, char* argv[])
        {
            QScopedPointer<QCoreApplication> app(createApplication(argc, argv));

            if (qobject_cast<QApplication *>(app.data())) {
               // 启动GUI版本...
            } else {
               // 启动非GUI版本...
            }
            
            return app->exec();
        }
		
　　这段代码运行时，首先检查是否传入-no-gui。如果传入了，则实例化QCoreApplication类，否则就创建QApplication类。QScopedPointer是Qt提供的智能指针类之一，可以自动进行回收内存等等工作，目前我们先不理它，把它当作普通指针就可以。`qobject_cast`可以将父类指针转化为子类指针，如果强制转型成功则返回子类指针。失败则返回NULL。通过判断其返回值，我们就可以知道我们创建的是否是QApplication类，从而启动对应的处理。这样就实现了动态选择创建QApplication或QCoreApplication的功能。

　　QApplication对象可以通过`instance()`函数访问。这是一个静态程序函数，返回QApplication对象的指针，这个指针和全局的qApp指针是相同的。函数原型及功能如下：

        QCoreApplication * QCoreApplication::instance() [static]
	　　//返回指向程序的QCoreApplication（或QApplication）对象的指针
		//如果没有QCoreApplication（或QApplication）被创建，则会返回NULL

　　QApplication主要负责这样一些工作：

+  它使用用户的桌面设置初始化应用程序，例如`palette()`, `font()` 和`doubleClickInterval()`。它会对这些属性进行跟踪，以应对用户修改桌面的全局设置（changes the desktop globally）。例如用户通过某种控制面板一类的东西修改某些设置。

+  它负责处理事件，也就是说，他从窗口系统接受事件消息并把他们分发到相应的部件。你可以通过调用`sendEvent()`和`postEvent()`发送你自己的事件给一些窗口部件(widgets)。

+  它解析命令行参数并且根据它们设置内部状态。所有的Qt应用程序都自动支持如下命令行选项：

        -style= style，设置程序的图形用户界面风格。可行的值取决于系统设定。如果你使用其它风格编译Qt或者有其他的风格插件，那么它们都可以被用作-style命令行选项。你可以通过设置QT_STYLE_OVERRIDE环境变量来为所有的Qt程序设置风格。
        -style style 和上面的一项功能相同。
        --stylesheet= stylesheet，设置应用程序的样式表。这个值必须是一个包含样式表的文件的路径。
        
		注意：样式表文件中的相对路径是相对于当前项目表文件的路径的。
        -stylesheet stylesheet，和上面的一项相同。
        -widgetcount，程序最后会输出调试信息，包括未销毁的部件数和同时存在的部件数的最大值。
        -reverse，将应用程序的层（layout）的方向设为Qt::RightToLeft
        -qmljsdebugger= ，有具体端口的活动的QML/JS调试器。这个值必须是这样的格式`端口:1234[,block]`， 其中block是可选的。这个参数会使程序等待直到一个调试器连接它。
		
+  它定义由QStyle对象封装的程序的外观。这个可以在运行时使用`setStyle()`修改。

+  它确定程序如何分配颜色。可以使用`setColorSpec()`函数设置。

    `void QApplication::setColorSpec(int spec) [static]`
	
	设置颜色规格（color specification）为spec。
	
	颜色规格控制当运行在有限的颜色数之下（例如：8位/256色）时，程序如何分配颜色。这个参数必须在你创建QApplication对象前设定好。
	
	更具体的内容可以参考Qt5的文档。

+  它提供通过`translate()`函数可见的本地化字符串。

+  它提供一些魔法般的对象，如`desktop()`和`clipboard()`。

+  它了解应用程序的所有窗口。你可以使用`widgetAt()`知道哪个窗口部件在当前位置上，通过`topLevelWidgets()`获得顶级窗口部件（或窗口）列表，以及调用`closeAllWindows()`关闭所有窗口等等。

+  它管理应用程序的鼠标光标处理，具体请参考`setOverrideCursor()`


*关于qApp宏*：qApp是一个全局指针，指向唯一的应用程序中的对象。它等于`QCoreApplication::instance()`函数返回的指针。在GUI程序里，它指向一个QApplication实例。只有一个应用程序对象可以被创建。

