package code.mock;

import code.threads.FileStruct;
import code.util.StringMap;

public class MockConcurrentMapStringFileStruct extends MockConcurrentMap<String, FileStruct> {
    public MockConcurrentMapStringFileStruct() {
        super(new StringMap<FileStruct>());
    }
}
