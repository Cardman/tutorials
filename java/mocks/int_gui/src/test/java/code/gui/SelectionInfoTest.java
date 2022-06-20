package code.gui;

import org.junit.Test;

import static org.junit.Assert.*;

public class SelectionInfoTest {
    @Test
    public void t() {
        SelectionInfo metaFont = new SelectionInfo(1, 1,true);
        assertTrue(metaFont.isMethodAction());
        assertEquals(1, metaFont.getFirstIndex()* metaFont.getLastIndex());
    }
}
