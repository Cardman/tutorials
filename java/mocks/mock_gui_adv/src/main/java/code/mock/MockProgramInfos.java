package code.mock;

public final class MockProgramInfos extends MockAbsProgramInfos {

    private final MockFrameFactory mockFrameFactory = new MockFrameFactory(this);

    public MockProgramInfos(String _h, String _t, double[] _se, long _initMillis, long[] _incrs, boolean _cust) {
        super(_h, _t, _se, _initMillis, _incrs, _cust);
    }

    public MockFrameFactory getMockFrameFactory() {
        return mockFrameFactory;
    }
}
