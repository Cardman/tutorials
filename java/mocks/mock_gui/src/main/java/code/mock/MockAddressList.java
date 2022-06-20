package code.mock;

import code.gui.initialize.AbstractAddressList;
import code.util.CustList;

public class MockAddressList implements AbstractAddressList {
    private final CustList<MockAddress> hosts = new CustList<MockAddress>();
    @Override
    public int size() {
        return hosts.size();
    }

    public CustList<MockAddress> getHosts() {
        return hosts;
    }

    @Override
    public String getHost(int i) {
        return hosts.get(i).getHost();
    }

    @Override
    public boolean isLoopbackAddress(int i) {
        return hosts.get(i).isLoopbackAddress();
    }

    @Override
    public boolean isIpFour(int i) {
        return hosts.get(i).isIpFour();
    }

    @Override
    public boolean isIpSix(int i) {
        return hosts.get(i).isIpSix();
    }
}
