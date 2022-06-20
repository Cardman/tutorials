package code.gui.images;

import org.junit.Test;

import static org.junit.Assert.assertEquals;

public class MetaRectTest {
    @Test
    public void t1() {
        MetaRect metaRect = new MetaRect(0, 0, 1, 1);
        assertEquals(1,metaRect.getHeight()* metaRect.getWidth());
    }
    @Test
    public void t2() {
        MetaRect metaRect = new MetaRect(0, 0, 1, 1);
        assertEquals(0,metaRect.getPoint().getXcoord()+ metaRect.getPoint().getYcoord());
        assertEquals(1,metaRect.move().getXcoord());
        assertEquals(1,metaRect.move().getYcoord());
    }
}
