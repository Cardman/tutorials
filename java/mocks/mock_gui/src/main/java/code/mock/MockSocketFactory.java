package code.mock;

import code.gui.initialize.*;

public class MockSocketFactory implements AbstractSocketFactory {
    @Override
    public AbstractSocket newSocket(int i, String s) {
        return new MockSocket(false);
    }

    @Override
    public AbstractServerSocket newServerSocket(String s, int i) {
        return new MockServerSocket();
    }

    @Override
    public AbstractNetworkInterfaceList newList() {
        return new MockNetworkInterfaceList();
    }

    @Override
    public AbstractAddressList newAddr(String s) {
        return new MockAddressList();
    }
}
