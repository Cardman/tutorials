package code.mock;

import code.stream.core.AbstractTextFact;
import code.util.core.StringUtil;
import code.util.ints.UniformingString;

public class MockTextFact implements AbstractTextFact {

    private final MockBinFact mockBinFact;

    public MockTextFact(MockBinFact _bin) {
        this.mockBinFact = _bin;
    }

    @Override
    public String contentsOfFile(String _s, UniformingString _uni, long l) {
        return _uni.apply(StringUtil.decode(mockBinFact.loadFile(_s)));
    }

    @Override
    public boolean write(String _file, String _cont, boolean _append) {
        if (_append) {
            byte[] bytes_ = mockBinFact.loadFile(_file);
            if (bytes_ != null) {
                byte[] encode_ = StringUtil.encode(_cont);
                byte[] joined_ = new byte[bytes_.length+encode_.length];
                int len_ = joined_.length;
                for (int i = 0; i < len_; i++) {
                    if (i < bytes_.length) {
                        joined_[i] = bytes_[i];
                    } else {
                        joined_[i] = encode_[i-bytes_.length];
                    }
                }
                return mockBinFact.writeFile(_file,joined_);
            }
        }
        return mockBinFact.writeFile(_file,StringUtil.encode(_cont));
    }
}
