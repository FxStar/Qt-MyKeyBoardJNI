```
javah -o QTKeyBoardJNI.h -classpath build\classes com.fx.qtkeyboard.QTKeyBoardJNI


```

```

javac -encoding utf8 -d ./build/classes .\src\com\fx\qtkeyboard\*.java

cd .\build\classes\
jar cf QTKeyBoard.jar .\com\fx\qtkeyboard\*.class 

```


```
clang .\QTKeyBoardJNI.cpp -shared -O2 -o QTKeyBoardJNI.dll -ID:\Java8\include -ID:\Java8\include\win32 -I./include -ID:\Qt5.14.2\5.14.2\msvc2017_64\include\QtWidgets -ID:\Qt5.14.2\5.14.2\msvc2017_64\include\QtCore -ID:\Qt5.14.2\5.14.2\msvc2017_64\include\QtGui  -ID:\Qt5.14.2\5.14.2\msvc2017_64\include -L./lib -lMyKeyBoard -LD:\Qt5.14.2\5.14.2\msvc2017_64\lib -lQt5Gui -lQt5Core -lQt5Widgets

    // windows 
 -DWin_OS -lUser32
```


# linux 可能用到的东西

```
#include <X11/Xlib.h>

// 获取当前窗口的 Display
Display *display = XOpenDisplay(NULL);

// 获取当前窗口的 XID
Window xid = DefaultRootWindow(display);

// 设置窗口属性
XWindowAttributes windowAttrs;
XGetWindowAttributes(display, xid, &windowAttrs);

XSetWindowAttributes newAttrs;
newAttrs.override_redirect = True;  // 设置为True，窗口将不获取焦点

XChangeWindowAttributes(display, xid, CWOverrideRedirect, &newAttrs);

// 如果需要刷新窗口
XFlush(display);

XCloseDisplay(display);

```


```
#include <QX11Info>
#include <X11/Xlib.h>

// 获取当前窗口的 XID
Window xid = QX11Info::appRootWindow();

// 获取当前窗口的 Display
Display *display = QX11Info::display();

// 设置窗口属性
XWindowAttributes windowAttrs;
XGetWindowAttributes(display, xid, &windowAttrs);

XSetWindowAttributes newAttrs;
newAttrs.override_redirect = False;  // 可根据需要设置其他属性

XChangeWindowAttributes(display, xid, CWOverrideRedirect, &newAttrs);

// 如果需要刷新窗口
XFlush(display);

```