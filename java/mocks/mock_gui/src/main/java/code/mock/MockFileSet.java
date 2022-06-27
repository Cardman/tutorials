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

    public MockFileSet(long _initMillis, long[] _incrs, String[] _roots) {
        files = new StringMap<FileStruct>();
        validating = new DefaultNameValidating(new StringList());
        mockMillis = new MockMillis(_initMillis, _incrs);
        roots = new StringList(_roots);
        initRootsFolders();
    }
    public void initRootsFolders() {
        for (String s: roots) {
            files.addEntry(s, new FileStruct(null, mockMillis.millis()));
        }
        currentPath = roots.first();
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
        String abs_ = MockFile.absolute(this, _path);
        if (!files.contains(abs_)) {
            return;
        }
        this.currentPath = abs_;
    }

    public StringList getRoots() {
        return roots;
    }
}
