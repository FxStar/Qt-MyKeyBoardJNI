package com.fx.qtkeyboard;

public abstract class BaseInputAbstract implements KeyBoardListener {
    protected BaseInputAbstract() {
        // 初始化操作
    }

    public void open() {
        QTKeyBoardJNI.addListener(this);
        QTKeyBoardJNI.KeyBoardOpen();
    }

    public void close() {
        QTKeyBoardJNI.romoveListener(this);
        QTKeyBoardJNI.KeyBoardClose();
    }

    public abstract void onResponse(KeyBoardListenerEvent event);
}
