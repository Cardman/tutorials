package code.gui.images;

import org.junit.Test;

import static org.junit.Assert.assertEquals;

public class MetaFontTest {
    @Test
    public void t() {
        MetaFont metaFont = new MetaFont("", 1, 1);
        assertEquals("",metaFont.getFontFamily());
        assertEquals(1, metaFont.getFont()* metaFont.getRealSize());
    }
}
