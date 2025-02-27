package code.mock;

import org.junit.Test;

import static org.junit.Assert.assertEquals;

public class MockImageTest {
    @Test
    public void draw1() {
        MockImage original_ = new MockImage(new int[4][4]);
        original_.setRGB(1,1,5);
        original_.setRGB(3,1,5);
        original_.setRGB(3,3,5);
        original_.setRGB(1,3,5);
        MockImage added_ = new MockImage(new int[4][4]);
        added_.setRGB(1,1,7);
        added_.setRGB(3,1,7);
        added_.setRGB(3,3,7);
        added_.setRGB(1,3,7);
        original_.drawImage(added_,2,2);
        assertEquals(0,original_.getRGB(0,0));
        assertEquals(0,original_.getRGB(0,1));
        assertEquals(0,original_.getRGB(0,2));
        assertEquals(0,original_.getRGB(0,3));
        assertEquals(0,original_.getRGB(1,0));
        assertEquals(5,original_.getRGB(1,1));
        assertEquals(0,original_.getRGB(1,2));
        assertEquals(5,original_.getRGB(1,3));
        assertEquals(0,original_.getRGB(2,0));
        assertEquals(0,original_.getRGB(2,1));
        assertEquals(0,original_.getRGB(2,2));
        assertEquals(0,original_.getRGB(2,3));
        assertEquals(0,original_.getRGB(3,0));
        assertEquals(5,original_.getRGB(3,1));
        assertEquals(0,original_.getRGB(3,2));
        assertEquals(7,original_.getRGB(3,3));
    }
    @Test
    public void draw2() {
        MockImage original_ = new MockImage(new int[4][4]);
        original_.setRGB(1,1,5);
        original_.setRGB(3,1,5);
        original_.setRGB(3,3,5);
        original_.setRGB(1,3,5);
        MockImage added_ = new MockImage(new int[4][4]);
        added_.setRGB(1,1,7);
        added_.setRGB(3,1,7);
        added_.setRGB(3,3,7);
        added_.setRGB(1,3,7);
        original_.drawImage(added_,-2,-2);
        assertEquals(0,original_.getRGB(0,0));
        assertEquals(0,original_.getRGB(0,1));
        assertEquals(0,original_.getRGB(0,2));
        assertEquals(0,original_.getRGB(0,3));
        assertEquals(0,original_.getRGB(1,0));
        assertEquals(7,original_.getRGB(1,1));
        assertEquals(0,original_.getRGB(1,2));
        assertEquals(5,original_.getRGB(1,3));
        assertEquals(0,original_.getRGB(2,0));
        assertEquals(0,original_.getRGB(2,1));
        assertEquals(0,original_.getRGB(2,2));
        assertEquals(0,original_.getRGB(2,3));
        assertEquals(0,original_.getRGB(3,0));
        assertEquals(5,original_.getRGB(3,1));
        assertEquals(0,original_.getRGB(3,2));
        assertEquals(5,original_.getRGB(3,3));
    }
    @Test
    public void draw3() {
        MockImage original_ = new MockImage(new int[4][4]);
        original_.setRGB(1,1,5);
        original_.setRGB(3,1,5);
        original_.setRGB(3,3,5);
        original_.setRGB(1,3,5);
        MockImage added_ = new MockImage(new int[4][4]);
        added_.setRGB(1,1,7);
        added_.setRGB(3,1,7);
        added_.setRGB(3,3,7);
        added_.setRGB(1,3,7);
        original_.drawImage(added_,1,3);
        assertEquals(0,original_.getRGB(0,0));
        assertEquals(0,original_.getRGB(0,1));
        assertEquals(0,original_.getRGB(0,2));
        assertEquals(0,original_.getRGB(0,3));
        assertEquals(0,original_.getRGB(1,0));
        assertEquals(5,original_.getRGB(1,1));
        assertEquals(0,original_.getRGB(1,2));
        assertEquals(0,original_.getRGB(1,3));
        assertEquals(0,original_.getRGB(2,0));
        assertEquals(0,original_.getRGB(2,1));
        assertEquals(0,original_.getRGB(2,2));
        assertEquals(0,original_.getRGB(2,3));
        assertEquals(0,original_.getRGB(3,0));
        assertEquals(5,original_.getRGB(3,1));
        assertEquals(0,original_.getRGB(3,2));
        assertEquals(0,original_.getRGB(3,3));
    }
    @Test
    public void draw4() {
        MockImage original_ = new MockImage(new int[4][4]);
        original_.setRGB(1,1,5);
        original_.setRGB(3,1,5);
        original_.setRGB(3,3,5);
        original_.setRGB(1,3,5);
        MockImage added_ = new MockImage(new int[4][4]);
        added_.setRGB(1,1,7);
        added_.setRGB(3,1,7);
        added_.setRGB(3,3,7);
        added_.setRGB(1,3,7);
        original_.drawImage(added_,3,1);
        assertEquals(0,original_.getRGB(0,0));
        assertEquals(0,original_.getRGB(0,1));
        assertEquals(0,original_.getRGB(0,2));
        assertEquals(0,original_.getRGB(0,3));
        assertEquals(0,original_.getRGB(1,0));
        assertEquals(5,original_.getRGB(1,1));
        assertEquals(0,original_.getRGB(1,2));
        assertEquals(5,original_.getRGB(1,3));
        assertEquals(0,original_.getRGB(2,0));
        assertEquals(0,original_.getRGB(2,1));
        assertEquals(0,original_.getRGB(2,2));
        assertEquals(0,original_.getRGB(2,3));
        assertEquals(0,original_.getRGB(3,0));
        assertEquals(0,original_.getRGB(3,1));
        assertEquals(0,original_.getRGB(3,2));
        assertEquals(0,original_.getRGB(3,3));
    }
    @Test
    public void draw5() {
        MockImage original_ = new MockImage(new int[4][4]);
        original_.setRGB(1,1,5);
        original_.setRGB(3,1,5);
        original_.setRGB(3,3,5);
        original_.setRGB(1,3,5);
        MockImage added_ = new MockImage(new int[4][4]);
        added_.setRGB(1,1,7);
        added_.setRGB(3,1,7);
        added_.setRGB(3,3,7);
        added_.setRGB(1,3,7);
        original_.drawImage(added_,-1,-3);
        assertEquals(7,original_.getRGB(0,0));
        assertEquals(0,original_.getRGB(0,1));
        assertEquals(0,original_.getRGB(0,2));
        assertEquals(0,original_.getRGB(0,3));
        assertEquals(0,original_.getRGB(1,0));
        assertEquals(5,original_.getRGB(1,1));
        assertEquals(0,original_.getRGB(1,2));
        assertEquals(5,original_.getRGB(1,3));
        assertEquals(7,original_.getRGB(2,0));
        assertEquals(0,original_.getRGB(2,1));
        assertEquals(0,original_.getRGB(2,2));
        assertEquals(0,original_.getRGB(2,3));
        assertEquals(0,original_.getRGB(3,0));
        assertEquals(5,original_.getRGB(3,1));
        assertEquals(0,original_.getRGB(3,2));
        assertEquals(5,original_.getRGB(3,3));
    }
    @Test
    public void draw6() {
        MockImage original_ = new MockImage(new int[4][4]);
        original_.setRGB(1,1,5);
        original_.setRGB(3,1,5);
        original_.setRGB(3,3,5);
        original_.setRGB(1,3,5);
        MockImage added_ = new MockImage(new int[4][4]);
        added_.setRGB(1,1,7);
        added_.setRGB(3,1,7);
        added_.setRGB(3,3,7);
        added_.setRGB(1,3,7);
        original_.drawImage(added_,-3,-1);
        assertEquals(7,original_.getRGB(0,0));
        assertEquals(0,original_.getRGB(0,1));
        assertEquals(7,original_.getRGB(0,2));
        assertEquals(0,original_.getRGB(0,3));
        assertEquals(0,original_.getRGB(1,0));
        assertEquals(5,original_.getRGB(1,1));
        assertEquals(0,original_.getRGB(1,2));
        assertEquals(5,original_.getRGB(1,3));
        assertEquals(0,original_.getRGB(2,0));
        assertEquals(0,original_.getRGB(2,1));
        assertEquals(0,original_.getRGB(2,2));
        assertEquals(0,original_.getRGB(2,3));
        assertEquals(0,original_.getRGB(3,0));
        assertEquals(5,original_.getRGB(3,1));
        assertEquals(0,original_.getRGB(3,2));
        assertEquals(5,original_.getRGB(3,3));
    }
    @Test
    public void draw7() {
        MockImage original_ = new MockImage(new int[4][4]);
        original_.setRGB(1,1,5);
        original_.setRGB(3,1,5);
        original_.setRGB(3,3,5);
        original_.setRGB(1,3,5);
        MockImage added_ = new MockImage(new int[4][4]);
        added_.setRGB(1,1,7);
        added_.setRGB(3,1,7);
        added_.setRGB(3,3,7);
        added_.setRGB(1,3,7);
        original_.drawImage(added_,2,-2);
        assertEquals(0,original_.getRGB(0,0));
        assertEquals(0,original_.getRGB(0,1));
        assertEquals(0,original_.getRGB(0,2));
        assertEquals(0,original_.getRGB(0,3));
        assertEquals(0,original_.getRGB(1,0));
        assertEquals(5,original_.getRGB(1,1));
        assertEquals(0,original_.getRGB(1,2));
        assertEquals(5,original_.getRGB(1,3));
        assertEquals(0,original_.getRGB(2,0));
        assertEquals(0,original_.getRGB(2,1));
        assertEquals(0,original_.getRGB(2,2));
        assertEquals(0,original_.getRGB(2,3));
        assertEquals(0,original_.getRGB(3,0));
        assertEquals(7,original_.getRGB(3,1));
        assertEquals(0,original_.getRGB(3,2));
        assertEquals(5,original_.getRGB(3,3));
    }
    @Test
    public void draw8() {
        MockImage original_ = new MockImage(new int[4][4]);
        original_.setRGB(1,1,5);
        original_.setRGB(3,1,5);
        original_.setRGB(3,3,5);
        original_.setRGB(1,3,5);
        MockImage added_ = new MockImage(new int[4][4]);
        added_.setRGB(1,1,7);
        added_.setRGB(3,1,7);
        added_.setRGB(3,3,7);
        added_.setRGB(1,3,7);
        original_.drawImage(added_,-2,2);
        assertEquals(0,original_.getRGB(0,0));
        assertEquals(0,original_.getRGB(0,1));
        assertEquals(0,original_.getRGB(0,2));
        assertEquals(0,original_.getRGB(0,3));
        assertEquals(0,original_.getRGB(1,0));
        assertEquals(5,original_.getRGB(1,1));
        assertEquals(0,original_.getRGB(1,2));
        assertEquals(7,original_.getRGB(1,3));
        assertEquals(0,original_.getRGB(2,0));
        assertEquals(0,original_.getRGB(2,1));
        assertEquals(0,original_.getRGB(2,2));
        assertEquals(0,original_.getRGB(2,3));
        assertEquals(0,original_.getRGB(3,0));
        assertEquals(5,original_.getRGB(3,1));
        assertEquals(0,original_.getRGB(3,2));
        assertEquals(5,original_.getRGB(3,3));
    }
    @Test
    public void draw9() {
        MockImage original_ = new MockImage(new int[4][4]);
        original_.setRGB(1,1,5);
        original_.setRGB(3,1,5);
        original_.setRGB(3,3,5);
        original_.setRGB(1,3,5);
        MockImage added_ = new MockImage(new int[4][4]);
        added_.setRGB(1,1,7);
        added_.setRGB(3,1,7);
        added_.setRGB(3,3,7);
        added_.setRGB(1,3,7);
        original_.drawImage(added_,1,-3);
        assertEquals(0,original_.getRGB(0,0));
        assertEquals(0,original_.getRGB(0,1));
        assertEquals(0,original_.getRGB(0,2));
        assertEquals(0,original_.getRGB(0,3));
        assertEquals(0,original_.getRGB(1,0));
        assertEquals(5,original_.getRGB(1,1));
        assertEquals(0,original_.getRGB(1,2));
        assertEquals(5,original_.getRGB(1,3));
        assertEquals(7,original_.getRGB(2,0));
        assertEquals(0,original_.getRGB(2,1));
        assertEquals(0,original_.getRGB(2,2));
        assertEquals(0,original_.getRGB(2,3));
        assertEquals(0,original_.getRGB(3,0));
        assertEquals(5,original_.getRGB(3,1));
        assertEquals(0,original_.getRGB(3,2));
        assertEquals(5,original_.getRGB(3,3));
    }
    @Test
    public void draw10() {
        MockImage original_ = new MockImage(new int[4][4]);
        original_.setRGB(1,1,5);
        original_.setRGB(3,1,5);
        original_.setRGB(3,3,5);
        original_.setRGB(1,3,5);
        MockImage added_ = new MockImage(new int[4][4]);
        added_.setRGB(1,1,7);
        added_.setRGB(3,1,7);
        added_.setRGB(3,3,7);
        added_.setRGB(1,3,7);
        original_.drawImage(added_,3,-1);
        assertEquals(0,original_.getRGB(0,0));
        assertEquals(0,original_.getRGB(0,1));
        assertEquals(0,original_.getRGB(0,2));
        assertEquals(0,original_.getRGB(0,3));
        assertEquals(0,original_.getRGB(1,0));
        assertEquals(5,original_.getRGB(1,1));
        assertEquals(0,original_.getRGB(1,2));
        assertEquals(5,original_.getRGB(1,3));
        assertEquals(0,original_.getRGB(2,0));
        assertEquals(0,original_.getRGB(2,1));
        assertEquals(0,original_.getRGB(2,2));
        assertEquals(0,original_.getRGB(2,3));
        assertEquals(0,original_.getRGB(3,0));
        assertEquals(0,original_.getRGB(3,1));
        assertEquals(0,original_.getRGB(3,2));
        assertEquals(5,original_.getRGB(3,3));
    }
    @Test
    public void draw11() {
        MockImage original_ = new MockImage(new int[4][4]);
        original_.setRGB(1,1,5);
        original_.setRGB(3,1,5);
        original_.setRGB(3,3,5);
        original_.setRGB(1,3,5);
        MockImage added_ = new MockImage(new int[4][4]);
        added_.setRGB(1,1,7);
        added_.setRGB(3,1,7);
        added_.setRGB(3,3,7);
        added_.setRGB(1,3,7);
        original_.drawImage(added_,-1,3);
        assertEquals(0,original_.getRGB(0,0));
        assertEquals(0,original_.getRGB(0,1));
        assertEquals(0,original_.getRGB(0,2));
        assertEquals(0,original_.getRGB(0,3));
        assertEquals(0,original_.getRGB(1,0));
        assertEquals(5,original_.getRGB(1,1));
        assertEquals(0,original_.getRGB(1,2));
        assertEquals(0,original_.getRGB(1,3));
        assertEquals(0,original_.getRGB(2,0));
        assertEquals(0,original_.getRGB(2,1));
        assertEquals(0,original_.getRGB(2,2));
        assertEquals(0,original_.getRGB(2,3));
        assertEquals(0,original_.getRGB(3,0));
        assertEquals(5,original_.getRGB(3,1));
        assertEquals(0,original_.getRGB(3,2));
        assertEquals(5,original_.getRGB(3,3));
    }
    @Test
    public void draw12() {
        MockImage original_ = new MockImage(new int[4][4]);
        original_.setRGB(1,1,5);
        original_.setRGB(3,1,5);
        original_.setRGB(3,3,5);
        original_.setRGB(1,3,5);
        MockImage added_ = new MockImage(new int[4][4]);
        added_.setRGB(1,1,7);
        added_.setRGB(3,1,7);
        added_.setRGB(3,3,7);
        added_.setRGB(1,3,7);
        original_.drawImage(added_,-3,1);
        assertEquals(0,original_.getRGB(0,0));
        assertEquals(0,original_.getRGB(0,1));
        assertEquals(7,original_.getRGB(0,2));
        assertEquals(0,original_.getRGB(0,3));
        assertEquals(0,original_.getRGB(1,0));
        assertEquals(5,original_.getRGB(1,1));
        assertEquals(0,original_.getRGB(1,2));
        assertEquals(5,original_.getRGB(1,3));
        assertEquals(0,original_.getRGB(2,0));
        assertEquals(0,original_.getRGB(2,1));
        assertEquals(0,original_.getRGB(2,2));
        assertEquals(0,original_.getRGB(2,3));
        assertEquals(0,original_.getRGB(3,0));
        assertEquals(5,original_.getRGB(3,1));
        assertEquals(0,original_.getRGB(3,2));
        assertEquals(5,original_.getRGB(3,3));
    }
}
