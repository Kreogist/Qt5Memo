# Qt学习备忘录3：基本Qt部件、窗体、动作及其它 #
　　写出Hello World仅仅是我们学习之路的开始。它代表着我们已经出发了，带着对Qt的兴奋与好奇，让我们一起前行。那么我们从哪里开始呢？当然是最基础的东西。可什么东西是最基础的呢？Qt Core模块？Qt GUI模块？稍微有些不知所措了。重新回忆一下我们学习Qt的初衷：写跨平台GUI程序。很好。那么GUI程序都需要什么呢？窗体、菜单、工具栏、对话框······一堆我们熟悉的GUI元素浮现在我们脑海中。那么，我们就从这里开始吧。一点一点地探索如何创建并使用这些GUI元素。

　　针对桌面的Qt程序一般使用Qt Widgets编写。Qt Widgets是一组用于创建经典桌面样式用户界面的UI元素。每一种GUI组件都是一个放置在用户界面窗口内或显示在独立窗口中的部件(widget)。每一种部件都是QWidget的一个子类，而QWidget是QObject的一个子类。

　　QWidget并不是一个抽象类，它可以作为其它部件的容器。它还可以被继承以创建新的自定义部件，这只需要极小的努力就能完成。QWidget一般用于创建放置其他部件的窗体。

　　作为一个QObject，QWidget可以设置父对象（parent object），这样，它就可以在它不被使用的时候被自动删除。对于部件，这种父母和孩子的关系(parent-child relationships)有更多的意义：所有的子部件都被显示在父部件使用的屏幕区域内。这就意味着，如果你删除了一个窗口部件，所有的子部件都会被删除。

# 一种典型的main()函数写法 #
　　 Qt5的文档中提供了一种典型的Qt程序的主函数的写法，和我们之前的Hello World程序基本是一致的。

    #include <QtWidgets>
    
    // Include header files for application components.
    // ...
    
	int main(int argc, char *argv[])
	{
		QApplication app(argc, argv);
		
		// 设置并显示部件
		// ...
		
		return app.exec();
	}
	
　　具体的含义在我们解析Hello World程序时已经解说过了，相信大家现在都能看懂。

# 创建最简单的窗口 #
　　这里有一个创建窗口的例子，这个例子非常简单，可以使我们了解QWidget的最基本的使用。

    #include <QtWidgets>
	
	int main(int argc, char *argv[])
	{
		QApplication app(argc, argv);
		
		QWidget window;
		window.resize(320, 240);
		window.show();
		window.setWindowTitle(
			QApplication::translate("toplevel", "Top-level widget"));
			
		return app.exec();
	}

运行效果：

![show result](images/widgets-tutorial-toplevel.png "result")

## 一行一行地解释 ##
　　我们从创建QWidget这一行开始，前面的初始化过程之前已经解释过，以后就不再说明了。`QWidget window`一句用于创建一个QWidget对象。由于我们没有制定window的父对象是谁，所以默认为NULL，也就是没有父对象。所以，window被作为最顶级的窗口。

　　接下来的`window.resize(320,240)`设置窗口尺寸为320*240。

　　而后调用`window.show()`来显示窗口。

　　最后，调用`setWindowTitle()`函数设置窗口标题．`QApplication::translate()`函数与国际化有关，先不管它，以后再学。

# 关于QWidget类 #
　　QWidget可以说是Qt Widget模块的核心。这个类是所有用户界面对象的基类。

　　部件(widget)是用户界面的最基本元素（Qt5的文档中使用atom，也即原子这个词来描述它）：它从窗口系统接收鼠标、键盘以及其他事件，并把它自己绘制在屏幕上。所有的部件都是矩形的，按Z轴的顺序排列。一个部件的遮挡由其父对象和它前面的部件决定。

　　没有父部件的部件被称作窗口(window)。一般情况下，窗口有一个边框和一个标题栏。当然，使用适当的窗口标记(window flags)来创建一个没有这些东西的窗口也是可行的。在Qt中，最常见的窗口类型就是QMainWindow以及众多的QDialog的子类。

　　所有部件的构造函数可以接受一个或两个标准的参数：

1. `QWidget *parent = 0`代表新部件的父部件。如果它为0(默认值)，新部件会成为一个窗口。如果不为0,则它会成为`parent`的一个孩子，会受`parent`的设置影响。

2. `Qt::windowFlags f = 0`用于设置窗口标记。默认值适用于几乎所有窗口。但如果你想实现一些特殊的窗口，例如没有边框的窗口，你需要使用特殊的标记。

## 顶级窗口和子部件 ##
　　一个没有父部件的窗口会成为一个独立的窗口（顶级部件）。对于这些部件，你可以使用`setWindowTitle()`和`setWindowIcon()`独立地设置标题栏和图标。

　　子部件没有窗口。它们会在其父部件中被显示。Qt中的大部分都主要作为子部件使用。例如：你可以使用一个按钮作为顶级部件，但大多数人都使用它作为QDialog这样的部件的子部件（即把它放在一个对话框中）。之前我们的Hello World中的QLabel部件就是一个特殊的QLabel部件作为顶级部件使用的例子。

## 自定义部件及绘图 ##
　　由于QWidget是QPaintDevice类的一个子类，它可以使用一系列QPainter实例的绘图操作来显示自定义内容。所有的绘图操作会在`paintEvent()`函数中完成，这个函数会在部件需要重绘或应用程序发出重绘请求时被自动调用。

# 项目开工！从QMainWindow开始 #
　　在本备忘录的序中我们曾提及，我们准备开展一个IDE项目。从这节之后，我们将一步一步地按照我们学习Qt的顺序，将所学应用与项目中，并以此为例子，记录Qt中的一些概念和用法。

　　
