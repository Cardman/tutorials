package code.gui.images;

import org.junit.Test;

import static org.junit.Assert.assertEquals;

public class MetaPointTest {
    @Test
    public void dim() {
        MetaPoint actual = new MetaPoint(5, 6);
        assertEquals(30, actual.getXcoord()*actual.getYcoord());
    }
}
