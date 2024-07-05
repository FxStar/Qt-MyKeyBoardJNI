package com.fx.qtkeyboard;

import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.SwingUtilities;

public class JMyTextArea extends BaseInputAbstract {

    private JTextArea textArea;

    // 私有静态变量，用于存储唯一的实例
    private static JMyTextArea instance;

    // 私有构造方法，防止外部实例化
    private JMyTextArea(JTextArea textArea) {
        // 在这里可以进行初始化操作
        this.textArea = textArea;
    }

    // 公有静态方法，提供全局访问点来获取唯一的实例
    public static JMyTextArea getInstance(JTextArea textArea) {
        // 使用双重检查锁定，确保只有一个线程可以创建实例
        if (instance == null) {
            instance = new JMyTextArea(textArea);

        }else{
            instance.textArea = textArea;
        }
        return instance;
    }

    @Override
    public void onResponse(KeyBoardListenerEvent event) {
        int caretPosition = textArea.getCaretPosition();

        switch (event.getKey()) {
            case 16777252: // 切换大小写
            case 17825792: // 切换中英
            case 16781694: // 切换数字
                // 切换类不用管
                break;
            case 16777219: // 删除单个操作
                SwingUtilities.invokeLater(new Runnable() {
                    public void run() {

                        try {
                            if (caretPosition - 1 >= 0) {
                                textArea.getDocument().remove(caretPosition - 1, 1);
                            }
                        } catch (Exception e) {
                            e.printStackTrace();
                        }
                    }
                });
                break;
            case 16777221: // 换行操作
                SwingUtilities.invokeLater(new Runnable() {
                    public void run() {

                        try {

                            textArea.getDocument().insertString(caretPosition, "\n", null);
                        } catch (Exception e) {
                            e.printStackTrace();
                        }
                    }
                });
                break;
            default: // 默认操作 追加字符串
                SwingUtilities.invokeLater(new Runnable() {
                    public void run() {

                        try {

                            textArea.getDocument().insertString(caretPosition, event.getValue(), null);
                        } catch (Exception e) {
                            e.printStackTrace();
                        }
                    }
                });
        }
    }
}
