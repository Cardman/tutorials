package code.mock;

import code.stream.core.AbstractZipFact;
import code.stream.core.ContentTime;
import code.util.StringMap;

public class MockZipFact implements AbstractZipFact {
    // sgn'\r'nbf/d/f'\r'nb/d/f'\r'nb'\r'...contents
    @Override
    public StringMap<ContentTime> zippedBinaryFiles(byte[] bytes) {
        return new StringMap<ContentTime>();
    }

    @Override
    public byte[] zipBinFiles(StringMap<ContentTime> stringMap) {
        return new byte[0];
    }
}
