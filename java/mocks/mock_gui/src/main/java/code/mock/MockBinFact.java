package code.mock;

import code.maths.montecarlo.AbstractGenerator;
import code.stream.core.AbstractBinFact;
import code.threads.FileStruct;

public class MockBinFact implements AbstractBinFact {
    private final MockRand mockRand;
    private final MockFileSet fileSet;

    public MockBinFact(AbstractGenerator _gen, MockFileSet _mfs) {
        mockRand = new MockRand(_gen);
        fileSet = _mfs;
    }

    @Override
    public byte[] loadFile(String _s) {
        return load(_s, fileSet).getContent();
    }

    public static FileStruct load(String _s, MockFileSet _files) {
        String abs_ = MockFile.absolute(_files, _s);
        FileStruct val_ = _files.getFiles().getVal(abs_);
        if (val_ == null) {
            return new FileStruct(null,0);
        }
        return val_;
    }


    @Override
    public boolean writeFile(String s, byte[] bytes) {
        String abs_ = MockFile.absolute(fileSet, s);
        String link_ = fileSet.linkedRoot(abs_);
        if (!fileSet.getValidating().okPath(abs_.substring(link_.length()),'/','\\')) {
            return false;
        }
        FileStruct val_ = fileSet.getFiles().getVal(abs_);
        if (val_ != null && val_.getContent() == null) {
            return false;
        }
        if (mockRand.edit()) {
            fileSet.getFiles().put(abs_,new FileStruct(bytes,fileSet.getMockMillis().millis()));
            return true;
        }
        return false;
    }

    public MockFileSet getFileSet() {
        return fileSet;
    }
}
