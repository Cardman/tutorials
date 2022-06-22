package code.mock;

import org.junit.Test;

import static org.junit.Assert.assertEquals;

public class MockBinStreamInImplTest {
    @Test
    public void bytes1(){
        byte[] read = new byte[120];
        MockBinStreamInImpl mockBinStreamIn_ = new MockBinStreamInImpl(read, 1024);
        assertEquals(120,mockBinStreamIn_.read());
        assertEquals(120,mockBinStreamIn_.getBytes().length);
    }
    @Test
    public void bytes2(){
        byte[] read = new byte[1025];
        MockBinStreamInImpl mockBinStreamIn_ = new MockBinStreamInImpl(read, 1024);
        assertEquals(1024,mockBinStreamIn_.read());
        assertEquals(1024,mockBinStreamIn_.getBytes().length);
    }
    @Test
    public void bytes3(){
        byte[] read = new byte[1025];
        MockBinStreamInImpl mockBinStreamIn_ = new MockBinStreamInImpl(read, 1024);
        mockBinStreamIn_.read();
        assertEquals(1,mockBinStreamIn_.read());
        assertEquals(1025,mockBinStreamIn_.getBytes().length);
    }
    @Test
    public void bytes4(){
        byte[] read = new byte[1024];
        MockBinStreamInImpl mockBinStreamIn_ = new MockBinStreamInImpl(read, 1024);
        mockBinStreamIn_.read();
        assertEquals(0,mockBinStreamIn_.read());
        assertEquals(1024,mockBinStreamIn_.getBytes().length);
    }
    @Test
    public void bytes5(){
        byte[] read = new byte[1024];
        MockBinStreamInImpl mockBinStreamIn_ = new MockBinStreamInImpl(read, 1024);
        mockBinStreamIn_.read();
        mockBinStreamIn_.read();
        assertEquals(1024,mockBinStreamIn_.getBytes().length);
        mockBinStreamIn_.close();
        assertEquals(0,mockBinStreamIn_.getBytes().length);
    }
    @Test
    public void bytes6(){
        MockBinStreamInImpl mockBinStreamIn_ = new MockBinStreamInImpl(null, 1024);
        assertEquals(-2,mockBinStreamIn_.read());
    }
}
