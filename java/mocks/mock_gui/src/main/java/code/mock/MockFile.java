package code.mock;

import code.stream.AbstractFile;
import code.threads.FileStruct;
import code.util.CustList;
import code.util.StringList;
import code.util.core.StringUtil;

public class MockFile implements AbstractFile {
    private final MockFileSet fileSet;
    private String abs;
    public MockFile(MockFileSet _mfs, String _s) {
        fileSet = _mfs;
        abs = absolute(_mfs, _s);
    }
    public static String absolute(MockFileSet _mfs, String _s) {
        for (String r: _mfs.getRoots()) {
            if (_s.startsWith(r)) {
                return _s;
            }
        }
        return _mfs.getCurrentPath()+_s;
    }
    @Override
    public String getName() {
        return StringUtil.splitChars(abs,'/','\\').last();
    }

    @Override
    public String getAbsolutePath() {
        return abs;
    }

    @Override
    public String[] list() {
        if (!isDirectory()) {
            return new MockFileListInfoName(null).getSimples();
        }
        StringList files_ = new StringList();
        for (String p: fileSet.getFiles().getKeys()) {
            if (!StringUtil.quickEq(p,abs)&&(p.startsWith(abs+"/")||p.startsWith(abs+"\\"))) {
                String sub_ = p.substring(abs.length()+1).replace('\\','/');
                int sep_ = sub_.indexOf('/');
                if (sep_ < 0) {
                    files_.add(sub_);
                } else {
                    files_.add(sub_.substring(0,sep_));
                }
            }
        }
        int len_ = files_.size();
        String[] l_ = new String[len_];
        for (int i = 0; i < len_; i++) {
            l_[i] = files_.get(i);
        }
        return l_;
    }

    @Override
    public boolean isDirectory() {
        FileStruct val_ = fileSet.getFiles().getVal(abs);
        if (val_ == null) {
            return false;
        }
        return val_.getContent() == null;
    }

    @Override
    public boolean exists() {
        return fileSet.getFiles().getVal(abs) != null;
    }

    @Override
    public long length() {
        FileStruct val_ = fileSet.getFiles().getVal(abs);
        if (val_ == null) {
            return 0;
        }
        return val_.getContent().length;
    }

    @Override
    public long lastModified() {
        FileStruct val_ = fileSet.getFiles().getVal(abs);
        if (val_ == null) {
            return 0;
        }
        return val_.getLastDate();
    }

    @Override
    public boolean renameTo(AbstractFile _abstractFile) {
        if (_abstractFile.exists()) {
            return false;
        }
        String otherAbs_ = _abstractFile.getAbsolutePath();
        if (StringUtil.quickEq(abs, otherAbs_)) {
            return false;
        }
        String r_ = fileSet.linkedRoot(otherAbs_);
        if (!fileSet.getValidating().okPath(otherAbs_.substring(r_.length()), '/', '\\')) {
            return false;
        }
        FileStruct old_ = fileSet.getFiles().getVal(abs);
        fileSet.getFiles().removeKey(abs);
        abs = otherAbs_;
        fileSet.getFiles().put(abs,old_);
        return true;
    }

    @Override
    public boolean delete() {
        for (String p: fileSet.getFiles().getKeys()) {
            if (!StringUtil.quickEq(p,abs)&&(p.startsWith(abs+"/")||p.startsWith(abs+"\\"))) {
                return false;
            }
        }
        FileStruct old_ = fileSet.getFiles().getVal(abs);
        fileSet.getFiles().removeKey(abs);
        return old_ != null;
    }

    @Override
    public String getParent() {
        CustList<String> parts_ = parentParts();
        return StringUtil.join(parts_,'/');
    }

    private CustList<String> parentParts() {
        StringList list_ = StringUtil.splitChars(abs, '/', '\\');
        return list_.mid(0, list_.size() - 1);
    }

    @Override
    public boolean mkdirs() {
        String r_ = fileSet.linkedRoot(abs);
        if (!fileSet.getValidating().okPath(abs.substring(r_.length()), '/', '\\')) {
            return false;
        }
        StringList list_ = StringUtil.splitChars(abs, '/', '\\');
        StringList pars_ = new StringList();
        for (String p: list_) {
            if (MockBinFact.load(StringUtil.join(pars_, '/'),fileSet).getContent() != null) {
                return false;
            }
            pars_.add(p);
        }
        if (fileSet.getFiles().contains(abs)) {
            return false;
        }
        fileSet.getFiles().put(abs,new FileStruct(null,fileSet.getMockMillis().millis()));
        return true;
    }
}
