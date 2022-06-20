package code.gui;

import org.junit.Test;

import static org.junit.Assert.assertEquals;

public class IntervalTest {
    @Test
    public void inter() {
        Interval actual = new Interval(5, 6);
        assertEquals(30, actual.getMax()*actual.getMin());
    }

}
