package code.mock;

public class MockProgramInfosSample extends MockAbsProgramInfos{
    public MockProgramInfosSample(String _h, String _t, double[] _se, long _initMillis, long[] _incrs, boolean _cust, String... _roots) {
        super(_h, _t, _se, _cust, new MockFileSet(_initMillis, _incrs,_roots));
    }

    @Override
    public MockAbsFrameFactory getMockFrameFactory() {
        return new MockFrameFactorySample(this);
    }
}
