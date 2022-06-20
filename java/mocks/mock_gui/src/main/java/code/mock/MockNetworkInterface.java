package code.mock;

public class MockNetworkInterface {
    private final MockAddressList addressLists;
    private final String name;
    private final boolean virtual;

    public MockNetworkInterface(MockAddressList addressLists,String name, boolean virtual) {
        this.addressLists = addressLists;
        this.name = name;
        this.virtual = virtual;
    }

    public String getName() {
        return name;
    }

    public MockAddressList getAddressLists() {
        return addressLists;
    }

    public boolean isVirtual() {
        return virtual;
    }
}
