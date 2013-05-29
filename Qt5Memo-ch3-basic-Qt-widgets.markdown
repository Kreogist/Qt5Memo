# Qt学习备忘录3：基本Qt部件、窗体、动作以及Qt的事件处理机制 #
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

## 建立主窗口——QMainWindow的使用 ##
　　之前我们已经说过，没有父部件的QWidget会成为一个独立的窗口。但一般情况下，很少有人直接使用QWidget类作为主窗口。因为主窗口往往需要菜单栏(Menu Bar)、状态栏(Status Bar)、工具栏(Toolbars)等等很多元素，QWidget显得太过简陋了。

　　幸运的是，Qt为我们准备好了一个功能强大的专门用于创建主窗口的框架。这个框架包含QMainWindow类以及很多相关的类(QToolBar、QDockWidget等等)。它们可以用于管理主窗口。其中，QMainWindow是主窗口的核心。

　　QMainWindow有它自己的布局，你可以向其中添加QToolBar,QDockWidget,QMenuBar和QStatusBar。布局中还有一个中央部件(Center Widget)，任何部件都可以成为中央部件。下面的图片展示了QMainWindow的布局。

![mainwindow layout](images/mainwindowlayout.png)

*注意：QT不支持创建一个不含中央部件(center widget)的主窗口。你必须有中央部件，即使那只是一个占位符。*

### 创建主窗口部件 ###
　　一个中央部件一般为标准Qt部件，如QTextEdit或QGraphicsView等。当然，自定义部件也是可以的。你可以使用`setCentralWidget()`函数设置中央部件。很好，那么我们来试一试。作为文本编辑器，最核心的部件当然是编辑器了。所以我们来把一个QTextEdit设置中央部件。

首先，我们知道，主窗口必然是需要自定义的，你见过有哪两个程序的的主窗口是完全一样的？所以，我们需要继承QMainWindow以实现自己的主窗口——一个有一个TextEdit的主窗口。

    #include <QMainWindow>
    #include <QTextEdit>
	
	class MainWindow : public QMainWindow
	{
		Q_OBJECT
	public:
		explicit MainWindow(QWidget *parent = 0);
		
	private:
		QTextEdit *editor;
	
	};

然后，我们在构造函数中设置我们的editor为主窗口。

    MainWindow::MainWindow(QWidget *parent) :
		QMainWindow(parent)
	{
		editor = new QTextEdit(this);
		setCentralWidget(editor);
	}

这样，我们就把一个TextEdit设置为中央部件了，很简单，不是吗？

### 创建菜单栏 ###
　　接下来，我们来试着创建一个菜单栏。

　　Qt通过QMenu实现菜单。QMainWindow会将菜单放置在菜单栏。菜单中的每一个QAction都会以菜单项的形式显示。Qt的文档读到这里，我们会产生一个疑问，什么是QAction呢？

+ 关于QAction

	QAction提供一个可以被插入到部件中的抽象用户界面动作（abstract user interface action）。在应用程序中，很多公共的命令可以通过菜单、工具栏和键盘快捷键调用。由于用户希望同一个命令执行相同的操作，无论是从菜单启动还是从工具栏调用，所以，将每个命令抽象成一个动作(action)是很有必要的。
	
	动作可以被添加到菜单中或者工具栏中，它会自动同步状态。例如，在一个字处理软件中，用户点击了加粗按钮，那么菜单中的加粗和工具栏中的加粗都会被自动设置为选中状态。
	
	动作可以作为一个独立的对象常见，也可以在创建菜单的时候创建。QMenu类包含一组方便的函数用于创建适用于菜单项的动作。
	
	一个QAction可以拥有图标，菜单文本(Menu Text)，快捷键，状态信息(status text)，"What's this?(这是什么)"文本和一个工具提示(tooltip)。这些大多可以通过构造函数设置。也可以通过`setIcon()`,`setText()`,`setIconText()`,`setShortcut()`,`setStatusTip()`,`setWhatsThis()`和`setToolTip()`这些函数单独设置。对于菜单项，可以通过调用`setFont()`设置单独的字体。
	
	动需可以通过`QWidget::addAction()`或`QGraphicsWidget::addAction()`函数添加到部件。注意，一个动作必须在添加到部件上之后才能使用，当添加全局快捷键是也是如此。
	
	一旦一个QAction被创建，它应当被添加到相关的菜单和工具栏中，然后和对应的槽相连接。信号和槽是Qt很特别的一个机制，我们会在稍后研究。这里有一个源自Qt5Doc的例子：
	
	openAct = new QAction(QIcon(":/images/open.png"), tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));
	
    fileMenu->addAction(openAct);
    fileToolBar->addAction(openAct);
	
	Qt建议将动作创建为使用它们的窗口的孩子(children of the window they are used in)。大多数情况下，动作会成为程序主窗口的孩子。

　　知道了什么是QAction，我们开始创建菜单。QMainWindow提供了`menuBar()`这个给力的函数。这个函数会返回当前程序的菜单栏的指针(QMenuBar*)，如果当前还没有创建菜单栏，它会自动创建一个。然后，我们就可以通过`QMenuBar::addMenu()`来添加菜单了。

　　QMainWindow有默认的菜单栏，但如果你想设置一个你自己的菜单栏，可以使用`setMenuBar()`如果你希望实现一个自定义的菜单栏(不使用QMenuBar部件)，你可以使用`setMenuWidget()`来设置它。这里有一个简单的例子(Qt5Doc)：

	void MainWindow::createMenus()
	{
		fileMenu = menuBar()->addMenu(tr("&File"));
		fileMenu->addAction(newAct);
		fileMenu->addAction(openAct);
		fileMenu->addAction(saveAct);
	}
	
### 创建工具栏 ###
　　工具栏通过QToolBar类实现。你可以通过`addToolBar()`函数向主窗口添加工具栏。工具栏的初始位置可以通过设置具体的Qt::ToolBaarArea来控制。通过`addToolBarBreak()`或`insertToolBarBreak()`,你可以插入一个工具栏分隔(就像文本编辑中的分隔行一样)来分隔区域。你还可以通过`QToolBar::setAllowedAreas()`和`QToolBar::setMovable()`函数限定工具栏的位置。

　　工具栏图标的大小可以通过`iconSize()`函数设定。尺寸是平台独立的。你可以调用`setIconSize()`设置一个固定的大小。你还可以使用`setToolButtonStyle()`函数修改所有工具栏按钮的外观(alter the appearance of all tool buttons)。

　　一个创建工具栏的例子如下(Qt5Doc)：

	void MainWindow::createToolBars()
	{
		fileToolBar = addToolBar(tr("File"));
		fileToolBar->addAction(newAct);
	}

### 创建状态栏 ###
　　创建状态栏和创建菜单栏类似，你可以使用`statusBar()`，它会返回当前的状态栏，如果没有则会创建一个。当然，也可以通过`setStatusBar()`设置一个。

　　我们现在来亲自试试创建一个文本编辑器的菜单栏和状态栏。

	//mainwindow.h
	class MainWindow : public QMainWindow
	{
		Q_OBJECT
	public:
		explicit MainWindow(QWidget *parent = 0);
	
	private:
		enum MainWindowActions
		{
			new_file,
			open,
			save,
			close_file,
			close_all,
			quit,
			about,
			act_count   //the number of actions.
		};
		
		QTextEdit *editor;
		QAction *act[act_count];
		
		void createActions();
		void createMenu();
		void createStatusbar();
	};

	
　　我们需要创建多个QAction．因此我们需要多个QAction指针变量，一个一个地创建过于麻烦，所以我们直接创建一个`QAction*`数组。为了方便以后增加新的action，我们使用一个枚举来实现。如你所见，这个枚举中包含了所有我们需要创建的动作。枚举的最后一项act_count是枚举中的最后一个值，所以正好等于我们所需要创建的`QAction*`数组的大小。这样做便于维护。

　　接着，我们开始分别实现创建动作、菜单和状态栏的函数。

	void MainWindow::createActions()
    {
        //new file
        act[new_file]=new QAction(tr("new file"),this);

        //open
        act[open]=new QAction(tr("open"),this);

        //save
        act[save]=new QAction(tr("save"),this);

        //save_as
        act[save_as]=new QAction(tr("save as"),this);

        //save_all
        act[save_all]=new QAction(tr("save all"),this);

        //close
        act[close]=new QAction(tr("close"),this);

        //closs_all
        act[close_all]=new QAction(tr("close all"),this);

        //quit
        act[quit]=new QAction(tr("quit"),this);

        //redo
        act[redo]=new QAction(tr("redo"),this);

        //undo
        act[undo]=new QAction(tr("undo"),this);

        //cut
        act[cut]=new QAction(tr("cut"),this);

        //copy
        act[copy]=new QAction(tr("copy"),this);

        //paste
        act[paste]=new QAction(tr("paste"),this);

        //about
        act[about]=new QAction(tr("about"),this);

        //about_qt
        act[about_qt]=new QAction(tr("about Qt"),this);
    }

    void MainWindow::createMenu()
    {
        int i;
        QMenuBar *_menubar=menuBar();

        //file menu
        menu[file] = _menubar->addMenu(tr("file"));
        //from new_file to quit add into file menu
        for(i=new_file;i<=quit;i++)
            menu[file]->addAction(act[i]);

        //edit menu
        menu[edit]= _menubar->addMenu(tr("edit"));
        //from redo to paste add into edit menu
        for(i=redo;i<=paste;i++)
            menu[edit]->addAction(act[i]);

        //help menu
        menu[help]= _menubar->addMenu(tr("help"));
        //from about to about_qt add into help menu
        for(i=about;i<=about_qt;i++)
            menu[help]->addAction(act[i]);

    }

    void MainWindow::createStatusbar()
    {
        QStatusBar *statusbar=statusBar();

        //...
    }
	
　　然后，在MainWindow的构造函数中调用它们，这样当主窗口被创建时，它们也会被创建。

	MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent)
    {
        editor = new QTextEdit(this);
        setCentralWidget(editor);

        createActions();
        createMenu();
        createStatusbar();
    }
	
　　至此，我们的编辑器的第一个版本就完成了。它有一个独一无二的功能——有一组没有用的菜单和一个状态栏，开个玩笑，呵呵。运行结果：

![ch3-1result](images/Kreogist-Cute-Ide-ch3-v1.png)

　　Qt比我们想象得简单得多，不是吗？

# 给程序以生命之一：Qt的信号与槽机制 #
　　之前我们曾开玩笑，我们的文本编辑器有一个独一无二的功能，就是有一组无法响应用户操作的菜单。说笑归说笑，我们总得想办法让它响应用户操作。有了对用户操作的响应，GUI程序才具有了生命。Qt提供了两种机制用于处理事件。一种是Qt的事件系统。这是一个底层的以QObject为基类的对象间通信的机制。还有一种更常用的高层的机制叫做信号与槽。我们先从最常用的信号与槽机制介绍起。

## 什么是信号和槽？ ##
　　信号与槽用于对象间通信。信号和槽机制是Qt的一个核心特性，而且这是Qt最不同于其它的框架的部分，可以说是Qt的一个标志。

　　在GUI编程中,当我们改变一个部件时,我们总是想让其它部件得到通知。从更广义的角度讲，我们希望任意类型的对象间能够互相通讯。例如，如果用户点击关闭按钮,我们希望窗口的`close()`函数被调用。也即我们希望按钮和窗口这两个对象间可以通讯：关闭按钮被点击后，按钮通知窗口到了该关闭的时候了。然后窗口关掉自己。老式的工具包(toolkit)或框架使用回调(callback)来实现这个功能。一个回调是一个指向函数的指针。如果你希望一个处理函数通知你一些事件发生了，你需要传递一个指向另一个函数(回调)的指针给处理函数。然后，处理函数会在适当的时候调用回调函数。


+   什么是回调

	回调是指通过传递一个函数指针给另外一个函数，使得在特定的事件或条件发生时，可以由对方调用，以响应相应的事件或条件。
	
	我们在设计软件时常会遇到这样一种情况：某个模块检测到某个事件发生，然后，需要通知其它模块去处理。但设计这个模块时，我们并不知道具体是哪个模块去处理这个事件。例如：我们设计一个计时器，当时间到了的时候，需要通知其它模块处理。但具体哪个模块在使用计时器是不确定的，因为很多模块都可以使用它。这种情况下，就可以使用回调。一般在C语言中，使用函数指针实现回调。在前面的例子中，就是把一个处理函数的指针传给计时器。当计时器发现时间到了的时候，通过指针调用处理函数。这样，就降低了计时器和处理函数的耦合性。计时器不需要知道具体是哪个函数处理，处理函数也不必在意是哪个计时器调用它。双方都只需要关系自己的处理逻辑即可，这样他们间的关联性就降低了很多。
	
	最常见的例子是C语言标准库中的快排函数。它的函数原型如下：
	
	void qsort (void* base, size_t num, size_t size,
		int (*compar)(const void*,const void*));
	
    最后传入的compar函数的指针就是一个回调。这个函数会在qsort比较两个元素大小时被自动调用。这样，qsort就只需要关心排序逻辑，而不需要关心它排的数据的具体类型是int,double还是一个结构体。

　　Qt的开发者们认为，回调有两个根本缺陷：首先，它们不是类型安全的。我们不能保证处理函数会以正确的参数调用回调函数。其次，回调与处理函数是强耦合的，因为处理函数必须知道它需要调用的回调函数是哪个。

　　于是在Qt中,使用了另一种回调技术——信号和槽(signals and slots)。一个特定的事件(event)发生时，会发出一个信号(signal)。Qt的部件有许多预定义的信号，我们可以通过继承它们来添加我们自己的信号到这些部件上。一个槽是一个响应特定信号的函数。Qt的部件有许多预定义的槽。但如果我们希望自定义对一些信号的处理方法，我们可以继承这些窗口部件并添加自己的槽，这样就可以处理那些我们感兴趣的信号了。

![connections](images/abstract-connections.png)

　　信号和槽机制是类型安全的：一个信号的参数必须与接收信号槽的参数类型相匹配。 (事实上，一个槽的接受的参数数量可以比它接收的信号提供的参数量更少，因为它可以忽略额外的参数)。信号和槽是松耦合的：一个类发出一个信号后，它既不需要知道这个信号发给谁，也不必关心接收到信号的槽是什么。Qt的信号与槽机制确保了，当你连一个信号到一个槽时，槽将在正确的时机以信号发出的参数被调用。信号与槽可以包含任意类型、任意数量的变量。他们是完全类型安全。

　　所有继承自QObject的类(如。,QWidget)都可以包含信号和插槽。当一个对象改变它的状态且有其它对象对此感兴趣时，一个信号会被发出。这就是Qt中的对象进行通信的方式。它不知道也不关心谁会会接收它发出的信号。这是真正的对信息的封装。这确保了对象(objects)可以作为一个组成软件的组件来使用。

　　槽可以用来接收并处理信号。同时，它们也普通成员函数。就像对象不需要知道谁会接收它发出的信号一样，槽也不必知道是否有信号连接到它。这个机制保证了Qt可以创造出真正独立的组件。

　　只要你愿意，你可以连接任意多的信号到同一个槽。同样，只要你需要，一个信号也可以连接到任意多的槽上。甚至直接连接一个信号到另一个信号也是可行的。(这将使得第一个信号发出后，第二个信号立即被发出。)

　　信号和槽组合在一起，构成了Qt强大的组件编程机制。（ **Together, signals and slots make up a powerful component programming mechanism.** ）

## 一个源自Qt5Doc的简单例子 ##
　　一个简单的C++版本计数器如下：

	class Counter
    {
    public:
        Counter() { m_value = 0; }

        int value() const { return m_value; }
        void setValue(int value);

    private:
        int m_value;
    };
	
　　而这段代码基于QObject技术实现的版本如下：

    #include <QObject>
	
    class Counter : public QObject
    {
        Q_OBJECT
	
    public:
        Counter() { m_value = 0; }
	
        int value() const { return m_value; }
	
	public slots:
        void setValue(int value);
	
    signals:
        void valueChanged(int newValue);
	
    private:
        int m_value;
    };
	
　　这个使用QObject的版本有同样的内部状态，并提供公共方法来访问状态，但它同时也支持使用信号和槽进行组件编程。这个类可以通过发射一个`valueChanged()`信号告诉其它模块，它的值已经改变了。它有一个槽，其他对象可以发送信号到这个槽。

　　**注意：所有需要定义信号或槽的类都必须在类的声明的顶部包含Q_OBJECT宏。同时，它们也必须直接或间接继承QObject类**

　　通过对比以上两个Counter类的设计，我们可以发现使用QObject实现的Counter类更像一个独立的组件。它更容易和别的组件协同工作。打个比方，QObject版本就像一个独立的具有计数技能的人，他会高声宣布自己的计数改变了，也可以在听到他所关心的人高声宣布的信息是改变自己的计数。但至于是吼出信息的人是男的女的老的少的，他好不关心，他只关心信号本身所携带的信息。同时，他也不关系到底谁关注他吼的信息，他只需吼出来就可以。因而他可以和任何人一起工作。

　　组件的槽由程序员实现。例如，我们可以这样实现`setValue(int value)`槽：
	
	void Counter::setValue(int value)
    {
        if (value != m_value) {
            m_value = value;
            emit valueChanged(value);
        }
    }
	
　　`emit valueChanged(value)`这一行以value的值为参数发出`valueChanged()`信号。在下面这段代码中，我们建立两个Counter对象，然后把第一个对象的`valueChanged()`信号连接到另一个对象的`setValue()`槽上。

    Counter a, b;
    QObject::connect(&a, &Counter::valueChanged,
                     &b, &Counter::setValue);

    a.setValue(12);     // a.value() == 12, b.value() == 12
    b.setValue(48);     // a.value() == 12, b.value() == 48
	
　　调用`a.setValue(12)`会发射一个`valueChanged(12)`信号。然后b的`setValue()`槽会接收到它。换句话说，`b.setValue(12)`会在此时被调用。接着，b也会发射`valueChanged()`信号，但由于没有槽和b的信号相连，b的信号会被自动无视掉。

　　需要注意的是，`setValue()`设置value后，只有当value不等于m_value时才会发射信号。这是为了避免循环连接导致的无限循环。(例如：b.valueChanged()再被连接到a.setValue())。也就是说， **Qt会自动处理循环连接的问题**。

　　默认情况下，你每形成一个连接，就会发出一个信号。重复的连接会发出两个信号。你可以通过调用`disconnect()`函数断开连接。如果你向`connect()`传入Qt::UniqueConnection参数，那么只有当以前没有建立过连接时，连接才会被建立。如果连接已经重复了(同一个信号连到了同一个对象的同一个槽上多次)，连接会失败，然后返回false。

　　这个例子是为了说明，QObject对象可以在不需要知道其它QObject对象任何信息的情况下和其一起工作。你只需要将它们连接在一起就可以实现让它们协同工作。想象一下，只需要调用几个connect函数就可以让许多强大的Qt部件协同工作，构成一个软件是多么惬意的一件事。
