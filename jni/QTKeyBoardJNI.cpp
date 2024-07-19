#include <jni.h>

#include <QApplication>
#include <QDesktopWidget>
#include <QtCore>
#include "Keyboard.h"
#include "QTKeyBoardJNI.h"

#ifdef Win_OS
#include <Windows.h>
#endif
class CustomWindow : public QWidget
{
public:
    CustomWindow()
    {
        // 初始化窗口
        // ...
    }

protected:
    void closeEvent(QCloseEvent *event)
    {
        // 在窗口关闭时执行 window->hide()，而不是退出应用程序
        this->hide();
        event->ignore(); // 阻止默认的关闭事件处理
    }
};

JavaVM *m_vm;
jclass m_clz;
jmethodID onResponseMethod;

// 声明一个全局变量用于存储 QApplication 对象
QApplication *app = nullptr;

QWidget *window = nullptr;

// QThread *qtThread = nullptr;

void callbackOnKeyPressed(int key, QString value)
{

    // printf("Hello from native method key: %d;value: %s\n", key, value.toUtf8().constData());

    if (m_vm == NULL || m_clz == NULL || onResponseMethod == NULL)
    {
        return;
    }

    bool isAttacked = false;
    JNIEnv *g_env;
    int getEnvStat = m_vm->GetEnv((void **)&g_env, JNI_VERSION_1_6);
    if (getEnvStat < 0)
    {
        getEnvStat = m_vm->AttachCurrentThread((void **)&g_env, NULL);
        if (getEnvStat < 0)
        {
            return;
        }
        isAttacked = true;
    }
    // 将C++字符串转换为jstring
    jstring javaValue = g_env->NewStringUTF(value.toUtf8().constData());
    // printf("Hello from native method callbackOnKeyPressed: %d\n", 2); // 使用printf输出信息
    g_env->CallStaticVoidMethod(m_clz, onResponseMethod, (jint)key, javaValue);
    // printf("Hello from native method callbackOnKeyPressedend: %d\n", 2); // 使用printf输出信息
    g_env->DeleteLocalRef(javaValue);
    if (isAttacked)
    {
        m_vm->DetachCurrentThread();
    }
}

void runQtEventLoop()
{
    int argc = 0;                       // 在 JNI 函数中，通常你需要手动设置 argc
    char *argv[] = {NULL};              // 在 JNI 函数中，通常你需要手动设置 argv
    app = new QApplication(argc, argv); // 将 QApplication 对象存储为全局变量

    window = new CustomWindow();
    window->setWindowTitle(QStringLiteral("软键盘"));

    window->resize(850, 370);

    QIcon windowIcon("./keyboard.png"); // 替换为你的图标文件路径
    // QIcon windowIcon = QApplication::style()->standardIcon(QStyle::SP_DirLinkIcon);
    window->setWindowIcon(windowIcon);

    Qt::WindowFlags flags = window->windowFlags();
    flags &= ~Qt::WindowMinMaxButtonsHint; // 移除缩小按钮 和放大
    flags |= Qt::WindowStaysOnTopHint;     // 窗口始终位于顶部
    // flags |= Qt::X11BypassWindowManagerHint; // 只有x11 下需要
    flags |= Qt::WindowDoesNotAcceptFocus; // linux 用到（不会获取焦点）
    window->setWindowFlags(flags);
#ifdef Win_OS
    // 具体来说，WS_EX_NOACTIVATE 表示窗口不会激活，即不会成为焦点窗口，不会接收键盘输入等。而 WS_EX_COMPOSITED 表示窗口使用了复合（compositing）特性，这通常与视觉效果和渲染性能有关。
    HWND wid = (HWND)(window->winId());
    SetWindowLong(wid, GWL_EXSTYLE, GetWindowLong(wid, GWL_EXSTYLE) | WS_EX_NOACTIVATE); // 导致点击按钮效果丢失 |WS_EX_COMPOSITED
#endif
    // Set the focus policy to prevent getting focus
    window->setFocusPolicy(Qt::NoFocus);
    window->setAttribute(Qt::WA_ShowWithoutActivating);

    AeaQt::Keyboard keyboard;
    keyboard.show();

    keyboard.registerCallback(callbackOnKeyPressed);

    QVBoxLayout *v = new QVBoxLayout;
    v->addWidget(&keyboard, 5);

    window->setLayout(v);
    // window->hide();
    window->setStyleSheet("QWidget { background-color: #4e5052; }"); // 设置背景色

    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width() - window->width()) / 2;
    int y = (screenGeometry.height() - window->height()) / 2;
    window->move(x, y);

    // 启动 Qt 事件循环
    app->exec();
}

/*
 * Class:     com_fx_qtkeyboard_QTKeyBoardJNI
 * Method:    KeyBoardInit
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_fx_qtkeyboard_QTKeyBoardJNI_KeyBoardInit(JNIEnv *env, jclass clz)
{

    env->GetJavaVM(&m_vm);

    m_clz = (jclass)env->NewGlobalRef(clz);

    onResponseMethod = env->GetStaticMethodID(clz, "onResponse", "(ILjava/lang/String;)V");
    // 只在首次调用时创建 Qt 的事件循环线程和相关数据
    // printf("Hello from native method init: %d\n", 2); // 使用printf输出信息
    // 启动 Qt 的事件循环线程
    // if (!qtThread)
    // {
    //     qtThread = new QThread;
    //     QObject::connect(qtThread, &QThread::started, runQtEventLoop);
    //     qtThread->start();
    // }
    runQtEventLoop();

    // printf("Hello from native method init: %d\n", 2666); // 使用printf输出信息
}

/*
 * Class:     com_fx_qtkeyboard_QTKeyBoardJNI
 * Method:    KeyBoardOpen
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_fx_qtkeyboard_QTKeyBoardJNI_KeyBoardOpen(JNIEnv *env, jclass clz)
{
    if (window)
    {
        window->show();
        window->raise();
        return 1;
    }
    return 0;
}

/*
 * Class:     com_fx_qtkeyboard_QTKeyBoardJNI
 * Method:    KeyBoardClose
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_fx_qtkeyboard_QTKeyBoardJNI_KeyBoardClose(JNIEnv *env, jclass clz)
{
    if (window)
    {
        window->hide();
        return 1;
    }
    return 0;
}

/*
 * Class:     com_fx_qtkeyboard_QTKeyBoardJNI
 * Method:    Release
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_fx_qtkeyboard_QTKeyBoardJNI_Release(JNIEnv *env, jclass clz)
{
    // app->quit();
    if (window)
    {
        window->hide(); // 隐藏窗口
        delete window;  // 删除窗口对象
        window = nullptr;
    }

    if (app)
    {
        delete app; // 删除 QApplication 对象
        app = nullptr;
    }
    // if (qtThread && qtThread->isRunning())
    // {
    //     qtThread->quit();
    // }
    // delete qtThread;
    return 1;
}

/*
 * Class:     com_fx_qtkeyboard_QTKeyBoardJNI
 * Method:    Test
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_fx_qtkeyboard_QTKeyBoardJNI_Test(JNIEnv *env, jclass clz)
{
    printf("Hello from native method: %d\n", 111); // 使用printf输出信息
    return 1;
}
