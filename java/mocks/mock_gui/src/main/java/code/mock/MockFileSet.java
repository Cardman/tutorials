package code.mock;

import code.expressionlanguage.filenames.DefaultNameValidating;
import code.threads.FileStruct;
import code.util.StringList;
import code.util.StringMap;

public class MockFileSet {
    private final DefaultNameValidating validating;
    private final StringMap<FileStruct> files;
    private final MockMillis mockMillis;
    private final StringList roots;
    private String currentPath = "/";

    public MockFileSet(StringMap<FileStruct> _f, DefaultNameValidating _validator, MockMillis _mm) {
        files = _f;
        validating = _validator;
        mockMillis = _mm;
        roots = new StringList("/");
    }
    public StringMap<FileStruct> getFiles() {
        return files;
    }

    public DefaultNameValidating getValidating() {
        return validating;
    }

    public MockMillis getMockMillis() {
        return mockMillis;
    }

    public String getCurrentPath() {
        return currentPath;
    }

    public void setCurrentPath(String _path) {
        this.currentPath = _path;
    }

    public StringList getRoots() {
        return roots;
    }
}
