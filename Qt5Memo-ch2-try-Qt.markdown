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
