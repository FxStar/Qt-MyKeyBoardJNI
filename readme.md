```
javah -o QTKeyBoardJNI.h -classpath build\classes com.fx.qtkeyboard.QTKeyBoardJNI


```

```

javac -encoding utf8 -d ./build/classes .\src\com\fx\qtkeyboard\*.java

cd .\build\classes\
jar cf QTKeyBoard.jar .\com\fx\qtkeyboard\*.class 

```


```
clang .\QTKeyBoardJNI.cpp -shared -O2 -o QTKeyBoardJNI.dll -ID:\Java8\include -ID:\Java8\include\win32 -I./include -ID:\Qt5.14.2\5.14.2\msvc2017_64\include\QtWidgets -ID:\Qt5.14.2\5.14.2\msvc2017_64\include\QtCore -ID:\Qt5.14.2\5.14.2\msvc2017_64\include\QtGui  -ID:\Qt5.14.2\5.14.2\msvc2017_64\include -L./lib -lMyKeyBoard -LD:\Qt5.14.2\5.14.2\msvc2017_64\lib -lQt5Gui -lQt5Core -lQt5Widgets -DWin_OS -lUser32

    // windows 
 -DWin_OS -lUser32
```


# linux 可能用到的东西


```

g++ ./QTKeyBoardJNI.cpp -shared -fPIC -g -O2 -o libQTKeyBoardJNI.so -I/usr/lib/jdk1.8.0_333/include -I/usr/lib/jdk1.8.0_333/include/linux  -I./include -I/home/lyz/Qt5.14.0/5.14.0/gcc_64/include/QtWidgets -I/home/lyz/Qt5.14.0/5.14.0/gcc_64/include/QtCore -I/home/lyz/Qt5.14.0/5.14.0/gcc_64/include/QtGui  -I/home/lyz/Qt5.14.0/5.14.0/gcc_64/include  -L/home/lyz/Qt5.14.0/5.14.0/gcc_64/lib -lQt5Gui -lQt5Core -lQt5Widgets -L/usr/lib/jdk1.8.0_333/lib/amd64 -ljawt -L./lib -lMyKeyBoard




```