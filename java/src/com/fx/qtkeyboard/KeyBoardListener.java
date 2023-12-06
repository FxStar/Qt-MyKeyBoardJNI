package com.fx.qtkeyboard;

import java.util.EventListener;

public interface KeyBoardListener extends EventListener {
    public void onResponse(KeyBoardListenerEvent event);
}