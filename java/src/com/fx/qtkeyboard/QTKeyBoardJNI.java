package com.fx.qtkeyboard;

import java.util.List;

import javax.swing.text.JTextComponent;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Iterator;

public class QTKeyBoardJNI {

    static {
        try {
            System.loadLibrary("QTKeyBoardJNI");
            // Thread keyBoardThread = new Thread(new Runnable() {

            // public void run() {
            // KeyBoardInit();
            // }
            // });

            // keyBoardThread.start();
        } catch (Exception e) {
            // TODO: handle exception
        }

    }

    // // 接口静态实例
    // private static final QTKeyBoardJNI m_qtKeyBoardJNI = new QTKeyBoardJNI();

    // // 获取接口静态实例
    // public static QTKeyBoardJNI getInstance() {
    // return m_qtKeyBoardJNI;
    // }

    // 获取侦听列表
    private final static List<KeyBoardListener> m_listeners = Collections
            .synchronizedList(new ArrayList<KeyBoardListener>());

    // 添加侦听
    public static void addListener(JTextComponent component) {
         
        m_listeners.clear();
        // if (!m_listeners.contains(listener)) {
        m_listeners.add(JText.getInstance(component));
        // }
    }

    // // 移除侦听列表
    // public static void romoveListener(KeyBoardListener listener) {
    // if (m_listeners.contains(listener)) {
    // m_listeners.remove(listener);
    // }
    // }

    // // 清空侦听列表
    // public static void clearListener() {
    // m_listeners.clear();
    // }

    // 键盘回调
    public static void onResponse(int key, String value) {

        KeyBoardListener obj;
        Iterator it = m_listeners.iterator();
        while (it != null && it.hasNext()) {
            obj = (KeyBoardListener) it.next();
            obj.onResponse(new KeyBoardListenerEvent(it, key, value));
        }
    }

    // public static void main(String[] args) {
    // int sum = QTKeyBoardJNI.Test();
    // System.out.println("Sum: " + sum);
    // }

    /* 打开键盘 */
    public static native void KeyBoardInit();

    public static native int KeyBoardOpen();

    // public static native int KeyBoardClose();

    public static native int Release();

    // public static native int Test();
}
