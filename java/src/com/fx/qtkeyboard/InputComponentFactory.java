package com.fx.qtkeyboard;

import javax.swing.JComponent;
import javax.swing.JTextField;
import javax.swing.JTextArea;

public class InputComponentFactory {

    public static BaseInputAbstract createInputComponent(JComponent component) {
        if (component instanceof JTextField) {
            return JText.getInstance((JTextField) component);
        } else if (component instanceof JTextArea) {
            return JMyTextArea.getInstance((JTextArea) component);
        }
        // else if (component instanceof JSpinner) {
        // return new JSpinnerInput((JSpinner) component);
        // }
        return null; // 如果不支持的组件类型，可以根据需求返回适当的默认值
    }
}
