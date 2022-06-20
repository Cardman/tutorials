package code.gui.images;

import code.gui.Interval;
import org.junit.Test;

import static org.junit.Assert.assertEquals;

public class MetaDimensionTest {
    @Test
    public void dim() {
        MetaDimension actual = new MetaDimension(new MetaDimension(5, 6));
        assertEquals(30, actual.getHeight()*actual.getWidth());
    }
}
