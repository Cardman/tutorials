package code.gui;

import code.util.CustList;
import org.junit.Test;

import static org.junit.Assert.assertEquals;

public class CustCellRenderTest {
    @Test
    public void t1() {
        CustCellRenderSample custCellRenderSample = new CustCellRenderSample();
        custCellRenderSample.setList(new CustList<String>(""));
        assertEquals("",custCellRenderSample.get(0));
    }
    @Test
    public void t2() {
        CustCellRenderSample custCellRenderSample = new CustCellRenderSample();
        custCellRenderSample.setCurrent(new GraphicListSample());
        custCellRenderSample.fwd();
        assertEquals("",custCellRenderSample.get(0));
    }
    @Test
    public void t3() {
        CustCellRenderSample custCellRenderSample = new CustCellRenderSample();
        custCellRenderSample.paintComponent(new ImageSample());
        custCellRenderSample.setList(new CustList<String>(""));
        assertEquals("",custCellRenderSample.get(0));
    }
    @Test
    public void t4() {
        CustCellRenderSample custCellRenderSample = new CustCellRenderSample();
        custCellRenderSample.paintComponent(new PreparedLabelSample());
        custCellRenderSample.setList(new CustList<String>(""));
        assertEquals("",custCellRenderSample.get(0));
    }
}
