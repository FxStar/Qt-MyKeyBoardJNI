# Makefile

# 设置变量
JAVA_DIR := ./java
BUILD_DIR :=  $(JAVA_DIR)/build/classes
CLASS_FILES := $(wildcard $(JAVA_DIR)/src/com/fx/qtkeyboard/*.java)
JNI_HEADER := $(BUILD_DIR)/QTKeyBoardJNI.h
JAR_FILE := $(BUILD_DIR)/QTKeyBoard.jar
BUILD_JAR_FILE := QTKeyBoard.jar
JNI_DIR := ./jni

# 默认目标
all: buildc buildh buildjar
	@echo "Build completed."

# 编译 Java 源代码
buildc:
	@echo "Compiling Java source code..."
	@javac -encoding utf8 -d  $(BUILD_DIR) $(CLASS_FILES)

# 生成 JNI 头文件
buildh: buildc
	@echo "Generating JNI header file..."
	@javah -o $(JNI_HEADER) -classpath $(BUILD_DIR) com.fx.qtkeyboard.QTKeyBoardJNI

# 打包成 JAR 文件
buildjar: buildc
	@echo "Creating JAR file..."
	@cd $(BUILD_DIR) && jar cf $(BUILD_JAR_FILE)  ./com/fx/qtkeyboard/*.class

# jni dll
builddll:
	@echo "Creating DLL file..."
	@cd $(JNI_DIR) && clang .\QTKeyBoardJNI.cpp -shared -O2 -o QTKeyBoardJNI.dll -ID:\Java8\include -ID:\Java8\include\win32 -I./include -ID:\Qt5.14.2\5.14.2\msvc2017_64\include\QtWidgets -ID:\Qt5.14.2\5.14.2\msvc2017_64\include\QtCore -ID:\Qt5.14.2\5.14.2\msvc2017_64\include\QtGui  -ID:\Qt5.14.2\5.14.2\msvc2017_64\include -L./lib -lMyKeyBoard -LD:\Qt5.14.2\5.14.2\msvc2017_64\lib -lQt5Gui -lQt5Core -lQt5Widgets -DWin_OS -lUser32 
buildso:
	@echo "Creating SO file..."
	@cd $ (JNI_DIR) && g++ ./QTKeyBoardJNI.cpp -shared -fPIC -g -O2 -o libQTKeyBoardJNI.so -I/usr/lib/jdk1.8.0_333/include -I/usr/lib/jdk1.8.0_333/include/linux  -I./include -I/home/lyz/Qt5.14.0/5.14.0/gcc_64/include/QtWidgets -I/home/lyz/Qt5.14.0/5.14.0/gcc_64/include/QtCore -I/home/lyz/Qt5.14.0/5.14.0/gcc_64/include/QtGui  -I/home/lyz/Qt5.14.0/5.14.0/gcc_64/include  -L/home/lyz/Qt5.14.0/5.14.0/gcc_64/lib -lQt5Gui -lQt5Core -lQt5Widgets -L/usr/lib/jdk1.8.0_333/lib/amd64 -ljawt -L./lib -lMyKeyBoard

# 清理操作
clean:
	@echo "Cleaning up..."
	@rm -rf $(BUILD_DIR)/*.class $(JNI_HEADER) $(JAR_FILE)
