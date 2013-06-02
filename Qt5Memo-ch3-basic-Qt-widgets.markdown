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

### 亲自试试 ###
　　在这份备忘录的开头，我们提过，这份备忘录是我们学习Qt并尝试编写IDE的过程中产生的。所以，我们现在来亲自试试创建一个IDE（或许目前的情况叫文本编辑器更合适）所需的菜单栏和状态栏。

	//version 0.0.0.1
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

　　这个例子是为了说明，QObject对象可以在不需要知道其它QObject对象任何信息的情况下和其一起工作。你只需要将它们连接在一起就可以实现让它们协同工作。想象一下，只需要调用几个connect函数就可以让许多强大的Qt部件协同工作，完成一个软件是多么惬意的一件事。

## 连接信号和槽 ##
　　我们接着回到我们之前的项目中。我们现在使用信号和槽机制为我们的编辑器增加退出功能。退出也就是当用户出发退出动作后，主窗口自动关闭。也即退出动作发出一个表明自己被触发了的信号后，主窗口自动关闭即可。

　　也就是说，我们只需要把退出动作被触发的信号连接到主窗口的`close()`槽上即可。

```cpp
//quit
act[quit]=new QAction(tr("quit"),this);
connect(act[quit],SIGNAL(triggered()),this,SLOT(close()));
```
	
　　只需要这样改写一下，再编译运行，即可实现退出功能。

### connect 函数 ###
　　如我们的例子中所见，连接信号和槽的函数叫connect。那么，这个函数具体有什么作用，又有那些用法。让我们来进入Qt5的文档一探究竟。

　　connect函数一共有五种形式：

	QMetaObject::Connection QObject::connect(
		const QObject * sender, const char * signal,
		const QObject * receiver, const char * method,
		Qt::ConnectionType type = Qt::AutoConnection) [static]
		
	QMetaObject::Connection QObject::connect(
		const QObject * sender,	const QMetaMethod & signal,
		const QObject * receiver, const QMetaMethod & method,
		Qt::ConnectionType type = Qt::AutoConnection) [static]
		
	QMetaObject::Connection QObject::connect(
		const QObject * sender,	const char * signal, const char * method,
		Qt::ConnectionType type = Qt::AutoConnection) const
		
	QMetaObject::Connection QObject::connect(
		const QObject * sender,	PointerToMemberFunction signal,
		const QObject * receiver, PointerToMemberFunction method,
		Qt::ConnectionType type) [static]
		
	QMetaObject::Connection QObject::connect(
		const QObject * sender,
		PointerToMemberFunction signal,
		Functor functor) [static]
		
　　下面让我们来一个一个的学习。

第一种：QMetaObject::Connection QObject::connect(
		const QObject * sender, const char * signal,
		const QObject * receiver, const char * method,
		Qt::ConnectionType type = Qt::AutoConnection) [static] 

　　创建一个从`sender`对象中的`signal`到`receiver`对象中的`method`的指定类型(type)的连接。返回一个指向连接的句柄。这个句柄可以用于以后中断连接(diconnect)。当你指定`signal`和`method`时必须使用`SIGNAL()`和`SLOT()`宏。这里有一个Qt5Doc中的例子：
	
```cpp
QLabel *label = new QLabel;
QScrollBar *scrollBar = new QScrollBar;
QObject::connect(scrollBar, SIGNAL(valueChanged(int)),
	　　　　　　label,  SLOT(setNum(int)));
```

　　这个样例建立了一个QScrollBar和一个QLabel。当用户操作QScrollBar时，QScrollBar的值会发生改变。此时，用于显示QScrollBar具体数值的QLabel的内容也必须随之改变。老式的框架会使用回调，也即把改变label内容的函数的地址传给scrollbar。当scrollbar改变时调用回调函数改变label的值。而Qt的设计使得这一工作要简单得多。我们只需要把scrollBar发出的`valueChanged(int)`信号和label的`setNum(int)`槽连接起来即可。信号中带有一个代表新的值的参数，这个参数会被自动传入槽中。而label的setNum槽在接到参数后会自动改变label显示的内容。

　　一定注意，连接信号和槽时值带参数类型即可，一定不要带参数名。例如下面这种就是错误的：
	
```cpp
// WRONG
QObject::connect(scrollBar, SIGNAL(valueChanged(int value)),
	             label, SLOT(setNum(int value)));
```
	
　　如之前所说，信号也是可以连接到信号的。Qt5Doc中接下来的例子展示了这一点。
	
```cpp
class MyWidget : public QWidget
{
    Q_OBJECT

public:
    MyWidget();

signals:
    void buttonClicked();

private:
    QPushButton *myButton;
};

MyWidget::MyWidget()
{
    myButton = new QPushButton(this);
    connect(myButton, SIGNAL(clicked()),
            this, SIGNAL(buttonClicked()));
}
```

　　在这个例子中，我们可以看到MyWidget的`clicked()`信号直接和它自己的`buttonClicked()`信号连接起来了。这样，当`clicked()`信号发出时，`buttonClicked()`信号也会被发出。

　　一个信号可以被连接到多个槽上，一个槽也可以和多个信号相连。在一个信号被连接到很多个槽上的情况下，如果该信号被发出，则会按照建立连接的先后顺序调用槽。

　　connect()函数会返回一个QMetaObject::connection类型的返回值，代表一个建立好的连接的句柄。如果连接失败，那么这个句柄将会是无效的。例如如果一个QObject无法核实signal或method是否存在，或者它们所携带的参数是不兼容的，那么连接就会失败。我们可以通过将QMetaObject::connection转换成bool来判断句柄是否是有效的。

　　接着我们来看看最后一个参数，type究竟是做什么用的。根据Qt的文档，它描述了建立的连接的类型。具体的说就是type决定了当信号发出时，槽是被立即触发，还是被加入一个队列中，稍后触发(queued for delivery at a later time)。如果信号被加入队列，那么其参数必须是Qt的meta-object系统知道的类型，因为Qt需要在后台拷贝以储存它们。你可以使用`qRegisterMetaType()`来在meta-object系统中注册你自定义的类型。

　　这个函数是线程安全的(thread-safe)。

	*QObject::connect: Cannot queue arguments of type 'MyType'错误* 这是因为你的类型(即样例中的`MyType`)没有被注册到Qt的Meta-Object系统中。你需要调用`qRegisterMetaType()`来注册它。
	
第二种：QMetaObject::Connection QObject::connect(
		const QObject * sender,	const QMetaMethod & signal,
		const QObject * receiver, const QMetaMethod & method,
		Qt::ConnectionType type = Qt::AutoConnection) [static]
		
　　这个函数和上面的那个作用完全相同，只不过是使用QMetaMethod来指定具体的信号(`signal`)和方法(`method`)。
	
第三种：QMetaObject::Connection QObject::connect(
		const QObject * sender,	const char * signal, const char * method,
		Qt::ConnectionType type = Qt::AutoConnection) const
	
　　这个形式估计是为大家少敲几个字母准备的，因为这个函数完全等价于`connect(sender,signal,this,method,type)`。同样，这个函数也是线程安全的。
	
第四种：QMetaObject::Connection QObject::connect(
		const QObject * sender,	PointerToMemberFunction signal,
		const QObject * receiver, PointerToMemberFunction method,
		Qt::ConnectionType type) [static]
		
　　这种形式是Qt5新增的，功能和之前第一种完全相同。

　　之前的例子，使用这个connect形式表示就是这样：

```cpp
QLabel *label = new QLabel;
QLineEdit *lineEdit = new QLineEdit;
QObject::connect(lineEdit, &QLineEdit::textChanged,
                 label,  &QLabel::setText);
```

第五种：QMetaObject::Connection QObject::connect(
		const QObject * sender,
		PointerToMemberFunction signal,
		Functor functor) [static]

　　这也是Qt5中新增的语法。这个connect函数中的槽函数可以是任意函数(function)或者仿函数(functor)，只要是可以连接到该信号上的就可以。也就是说，只要这个函数所需要传入的参数不多于信号提供的参数即可作为槽函数使用。而对于仿函数，它的参数数量和信号提供的参数数量完全相等时才能作为槽函数使用。Qt5Doc提供的样例如下：

样例：
```cpp
void someFunction();
QPushButton *button = new QPushButton;
QObject::connect(button, &QPushButton::clicked, someFunction);
```

如果你的编译器支持C++11的lambda表达式，你也可以这样做：
```cpp
QByteArray page = ...;
QTcpSocket *socket = new QTcpSocket;
socket->connectToHost("qt-project.org", 80);
QObject::connect(socket, &QTcpSocket::connected, [=] () {
        socket->write("GET " + page + "\r\n");
    });
```

　　如果发送者被析构了，这个连接会自动断开。这个函数也是线程安全的。
	
### 关于Qt5中新的信号与槽语法的讨论 ###
　　Qt5中的一个给力的新功能就是它的信号与槽的新语法。这种语法充分发挥了C++11的优势，使得开发变得更安全而简单。

　　新的写法有这样几个优势：

+  编译期：检查信号与槽是否存在，参数类型检查，Q_OBJECT是否存在

+  信号可以和普通的函数、类的普通成员函数、lambda函数连接（而不再局限于信号函数和槽函数）

+  参数可以是 typedef 的或使用不同的namespace specifier

+  可以允许一些自动的类型转换（即信号和槽参数类型不必完全匹配）

　　其劣势是：

+  当出现重载时语法比较复杂

+  槽中的默认参数不再被支持

### 当新语法遇到重载 ###
　　新语法的一个问题是当遇到重组时会变得很复杂。例如下面这段代码：

```cpp
class ClassA : public QObject
{
    Q_OBJECT
...    
signals:
    void mySignal(double d);
	void mySignal(QString s);
...
};
```

　　假设我们想把mySignal(QString)和ClassB的mySlot连接起来，我们没法简单地这样写：

	connect(&a, &ClassA::mySignal, &b, &ClassB::mySlot);
	
　　因为mySignal实际上有两个，一个是double的，一个是QString的。这样写编译器无法知道你究竟调用的是哪一个。因此，当遇到重载时，会变得非常麻烦。我们需要显式调用static_cast来表明我们具体使用哪个重载。所以，正确的写法是：

    connect(&a, static_cast<void (ClassA::*)(QString)>(&ClassA::mySignal), &b, &ClassB::mySlot);

　　当遇到槽被重载时也是如此处理，就不赘述了。(笔者吐槽，这种情况下好像还是Qt4的老语法写着更简单一些)

### 用法：简洁的异步调用 ###
　　使用C++11使得很多操作都可以简单地完成。这里有一些源自qt-project.org的例子。

```cpp
void doYourStuff(const QByteArray &page)
{
    QTcpSocket *socket = new QTcpSocket;
	socket->connectToHost("qt.nokia.com", 80);
	QObject::connect(socket, &QTcpSocket::connected, [socket, page] () {
        socket->write(QByteArray("GET " + page + "\r\n"));
	});
	QObject::connect(socket, &QTcpSocket::readyRead, [socket] () {
		qDebug()<< "GOT DATA "<< socket->readAll();
	});
	QObject::connect(socket, &QTcpSocket::disconnected, [socket] () {
		qDebug()<< "DISCONNECTED ";
		socket->deleteLater();
	});
	
	QObject::connect(socket, static_cast<void (QTcpSocket::*)(QAbstractSocket::SocketError)>(&QAbstractSocket::error), [socket] (QAbstractSocket::SocketError) {
	qDebug()<< "ERROR " << socket->errorString();
	socket->deleteLater();
	});
}
```
　　这里还有一个打开对话框但不需要阻塞主事件循环的例子。
```cpp
void Doc::saveDocument() {
	QFileDialog *dlg = new QFileDialog();
	dlg->open();
	
	QObject::connect(dlg, &QDialog::finished, [dlg, this](int result) {
		if (result) {
			QFile file(dlg->selectedFiles().first());
			// ...
		}
		dlg->deleteLater();
	});

}
```

　　展开想象的翅膀，还有更多应用方法等待你发觉。

### 小插曲：lambda表达式 ###

## 高级信号与槽用法 ##

### sender()和receivers() ###
　　有些情况下，我们需要知道究竟是哪个对象发出信号。这时，我们可以调用`sender()`函数。函数原型如下：

	QObject * QObject::sender() const [protected]
	
　　在一个被信号激活的槽中调用该函数，该函数会返回一个指向发送信号的QObject的指针。否则，会返回0。The pointer is valid only during the execution of the slot that calls this function from this object's thread context.



这里我们写了个例子，以更清楚地说明这种情况。
	
```cpp
//Qt5Memo/src/signals-with-several-slots/example.h
//我们建立一个类来展示多个槽连接到同一个信号的情况。
//slot1,slot2,slot3这三个槽分别会输出slot1,slot2,slot3
//这样，我们就可以通过输出知道他们被调用的顺序。
#include <QObject>
#include <iostream>

using namespace std;

class Example : public QObject
{
    Q_OBJECT
public:
    explicit Example(QObject *parent = 0);

    void emit_signal(){emit signal_emited();}
    void connect123();
    void connect132();
    void break_connection();

public slots:
    void slot1(){cout<<"slot1"<<endl;}
    void slot2(){cout<<"slot2"<<endl;}
    void slot3(){cout<<"slot3"<<endl;}

signals:
    void signal_emited();

private:
    QMetaObject::Connection connection_handle[3];
    
};

#endif // EXAMPLE_H
```

```cpp
//Qt5Memo/src/signals-with-several-slots/example.cpp
//一些具体的实现。
//connect123和connect132分别按不同顺序连接信号和槽。
#include "example.h"

Example::Example(QObject *parent) :
    QObject(parent)
{
}

void Example::connect123()
{
    connection_handle[0]=connect(this,SIGNAL(signal_emited()),this,SLOT(slot1()));
    connection_handle[1]=connect(this,SIGNAL(signal_emited()),this,SLOT(slot2()));
    connection_handle[2]=connect(this,SIGNAL(signal_emited()),this,SLOT(slot3()));
}

void Example::connect132()
{
    connection_handle[0]=connect(this,SIGNAL(signal_emited()),this,SLOT(slot1()));
    connection_handle[1]=connect(this,SIGNAL(signal_emited()),this,SLOT(slot3()));
    connection_handle[2]=connect(this,SIGNAL(signal_emited()),this,SLOT(slot2()));
}

void Example::break_connection()
{
    for(int i=0;i<3;i++)
        disconnect(connection_handle[i]);
}
```
接着，我们开始我们的实验。

```cpp
//Qt5Memo/src/signals-with-several-slots/main.cpp
#include <QCoreApplication>
#include <QObject>

#include "example.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Example e;
    //首先，我们按slot1,slot2,slot3的顺序把槽连到同一个信号上
    //然后，发出信号。
    e.connect123();
    e.emit_signal();

    e.break_connection();

    //接着，我们重新按slot1,slot3,slot2的顺序把槽连到同一个信号上
    //然后，再发出信号。
    e.connect132();
    e.emit_signal();

    e.break_connection();
    
    return a.exec();
}
```

运行结果：

    slot1
    slot2
    slot3
    slot1
    slot3
    slot2

可以清晰的看出，槽的调用顺序和我们连接他们的顺序是一致的。

