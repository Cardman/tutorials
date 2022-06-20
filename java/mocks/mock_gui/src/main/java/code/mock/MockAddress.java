package code.mock;

public class MockAddress {
    private final String host;
    private final boolean loopbackAddress;
    private final boolean ipFour;
    private final boolean ipSix;

    public MockAddress(String host, boolean loopbackAddress, boolean ipFour, boolean ipSix) {
        this.host = host;
        this.loopbackAddress = loopbackAddress;
        this.ipFour = ipFour;
        this.ipSix = ipSix;
    }

    public String getHost() {
        return host;
    }

    public boolean isIpFour() {
        return ipFour;
    }

    public boolean isIpSix() {
        return ipSix;
    }

    public boolean isLoopbackAddress() {
        return loopbackAddress;
    }
}
