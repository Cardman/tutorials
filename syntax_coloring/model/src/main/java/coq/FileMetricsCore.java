package coq;

import java.util.List;
import java.util.*;
public final class FileMetricsCore {
    private static final char LINE_RETURN = '\n';
    private static final char TAB = '\t';

    private final List<Integer> lineReturns;
    private final List<Integer> tabulations;


    public FileMetricsCore(List<Integer> _liRet, List<Integer> _tabs) {
        this.lineReturns = _liRet;
        this.tabulations = _tabs;
    }

    public static FileMetrics processLinesTabs(String _file, int _width) {
        int i_ = 0;
        int len_ = _file.length();
		List<Integer> rets_ = new ArrayList<Integer>();
		List<Integer> tabs_ = new ArrayList<Integer>();
        rets_.add(-1);
        while (i_ < len_) {
            char ch_ = _file.charAt(i_);
            if (ch_ < ' ') {
                if (ch_ == TAB) {
                    tabs_.add(i_);
                } else {
                    rets_.add(i_);
                }
            }
            i_++;
        }
		return new FileMetrics(new FileMetricsCore(rets_,tabs_),_width);
    }

    public List<Integer> getLineReturns() {
        return lineReturns;
    }

    public List<Integer> getTabulations() {
        return tabulations;
    }
}
