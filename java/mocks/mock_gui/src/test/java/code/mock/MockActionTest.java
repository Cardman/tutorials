package code.mock;

import org.junit.Test;

import static org.junit.Assert.assertEquals;

public class MockActionTest {
    @Test
    public void action() {
        MockWithActionSample ac = new MockWithActionSample();
        new MockAction(1, ac).action();
        assertEquals(1,ac.getNb());
    }
}
