package code.gui.events;

import code.gui.AbsCtrlKeyState;
import code.gui.AbsMouseButtons;
import code.gui.AbsMouseLocation;

public interface AbsMouseListenerCl {

    void mouseClicked(AbsMouseLocation _location, AbsCtrlKeyState _keyState, AbsMouseButtons _buttons);
}
