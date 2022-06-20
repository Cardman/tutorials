package code.mock;

import code.gui.initialize.AbstractAddressList;
import code.gui.initialize.AbstractNetworkInterfaceList;
import code.util.CustList;

public class MockNetworkInterfaceList implements AbstractNetworkInterfaceList {
    private final CustList<MockNetworkInterface> list = new CustList<MockNetworkInterface>();

    public CustList<MockNetworkInterface> getList() {
        return list;
    }

    @Override
    public int size() {
        return list.size();
    }

    @Override
    public AbstractAddressList list(int i) {
        return list.get(i).getAddressLists();
    }

    @Override
    public int size(int i) {
        return list.get(i).getAddressLists().size();
    }

    @Override
    public String getName(int i) {
        return list.get(i).getName();
    }

    @Override
    public boolean isVirtual(int i) {
        return list.get(i).isVirtual();
    }
}
