package sample;

import javax.swing.*;
import java.awt.*;

public interface FrameGeneratorInt {
    JFrame frame();
    JDialog dialog();
    Cursor cursor(int _wCurs, int _hCurs, int[] _pixels);
    AbsCompo newCompo();
}
