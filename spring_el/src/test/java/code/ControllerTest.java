package code;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.junit4.SpringRunner;

import static org.junit.Assert.*;

@RunWith(SpringRunner.class)
@SpringBootTest
public class ControllerTest {
    @Autowired
    private Controller controller;
    @Test
    public void sample() {
        assertEquals(0, controller.oper(Config.SUM_INT,0,0));
    }
}
