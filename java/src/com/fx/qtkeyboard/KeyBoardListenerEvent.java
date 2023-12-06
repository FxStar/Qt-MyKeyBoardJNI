/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.fx.qtkeyboard;

import java.util.EventObject;

/**
 *
 * @author fx
 */
public class KeyBoardListenerEvent extends EventObject {
    public KeyBoardListenerEvent(Object source,int key, String value) {
        super(source);
        //TODO Auto-generated constructor stub
        this.onResponse(key, value);
    }

    int m_key = 0;
    String m_value = "";

    private void onResponse(int key, String value) {
        m_key = key;
        m_value = value;
    }

    public int getKey() {
        return m_key;
    }

    public String getValue() {
        return m_value;
    }

}