package code.mock;

import code.stream.AbstractListRoot;

public class MockListRoot implements AbstractListRoot {
    @Override
    public int length() {
        return 1;
    }

    @Override
    public String path(int _i) {
        return "/";
    }
}
