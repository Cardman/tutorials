package code.mock;

import code.maths.montecarlo.AbstractGenerator;
import code.stream.core.AbstractBinFact;
import code.threads.FileStruct;
import code.util.StringMap;

public class MockBinFact implements AbstractBinFact {
    private final MockRand mockRand;
    private final MockFileSet fileSet;

    public MockBinFact(AbstractGenerator _gen, MockFileSet _mfs) {
        mockRand = new MockRand(_gen);
        fileSet = _mfs;
    }

    @Override
    public byte[] loadFile(String _s) {
        return load(_s, fileSet.getFiles());
    }

    public static byte[] load(String _s, StringMap<FileStruct> _files) {
        FileStruct val_ = _files.getVal(_s);
        if (val_ == null) {
            return null;
        }
        return val_.getContent();
    }


    @Override
    public boolean writeFile(String s, byte[] bytes) {
        if (!fileSet.getValidating().okPath(s,'/','\\')) {
            return false;
        }
        FileStruct val_ = fileSet.getFiles().getVal(s);
        if (val_ != null && val_.getContent() == null) {
            return false;
        }
        if (mockRand.edit()) {
            fileSet.getFiles().put(s,new FileStruct(bytes,fileSet.getMockMillis().millis()));
            return true;
        }
        return false;
    }

    public MockFileSet getFileSet() {
        return fileSet;
    }
}
