package code;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.junit4.SpringRunner;
import org.springframework.beans.factory.annotation.Autowired;

import org.springframework.test.annotation.DirtiesContext;
import org.springframework.test.annotation.DirtiesContext.ClassMode;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertNull;

@RunWith(SpringRunner.class)
@SpringBootTest
@SpringBootApplication
public class UsageTest{

    @Autowired
    private UsageInt usageInt;

    @Test
    public void sum() {
        assertEquals(3, usageInt.oper(Config.SUM_INT,1,2));
    }
    @Test
    public void prod() {
        assertEquals(2, usageInt.oper(Config.MULT_INT,1,2));
    }

    @Test
    public void sumMap() {
        assertEquals(3, usageInt.oper(Config.SUM,1,2));
    }
    @Test
    public void prodMap() {
        assertEquals(2, usageInt.oper(Config.MULT,1,2));
    }

    @Test
    public void sum2() {
        assertEquals(5, usageInt.oper(Config.SUM_INT,3));
    }
    @Test
    public void prod2() {
        assertEquals(6, usageInt.oper(Config.MULT_INT,3));
    }

    @Test
    public void sumMap2() {
        assertEquals(5, usageInt.oper(Config.SUM,3));
    }
    @Test
    public void prodMap2() {
        assertEquals(6, usageInt.oper(Config.MULT,3));
    }
}