package sample;

import org.junit.Assert;
import org.junit.Test;

public class MockedTest {
    @Test
    public void getSet() {
        Mocked mocked = new Mocked();
        mocked.setValue("");
        Assert.assertEquals("",mocked.getValue());
    }
}
