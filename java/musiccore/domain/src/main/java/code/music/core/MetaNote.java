package code.music.core;

import code.music.enums.Gamme;
import code.util.IdMap;
import code.util.core.StringUtil;

public final class MetaNote {

    private static final String SEPARATOR = "/";
    private static final String SEPARATOR_TIME = ",";
    private static final String EMPTY_STRING = "";
    private static final String SYMBOL_PAUSE = "_";
    private static final String SYMBOL_DIESE = "#";
    private static final int DELTA = 12;
    private Gamme value;
    private int level;
    private boolean diese;
    private boolean pause;
    private int durationNum;
    private int durationDen;
    private int dynamic = 85;
    public int pitch(IdMap<Gamme,Integer> _tr) {
        return _tr.getVal(value) + DELTA * level + diese(diese);
    }

    private static int diese(boolean _d) {
        if (_d) {
            return 1;
        }
        return 0;
    }

    private static double getDouble(int _n, int _d) {
        return (double)_n/(double)_d;
    }

    public double ratio() {
        return (double)durationNum/durationDen;
    }

    public Gamme getValue() {
        return value;
    }

    public int getLevel() {
        return level;
    }

    public boolean isDiese() {
        return diese;
    }

    public boolean isPause() {
        return pause;
    }

    public int getDurationNum() {
        return durationNum;
    }

    public int getDurationDen() {
        return durationDen;
    }

    public int getDynamic() {
        return dynamic;
    }

    public void setValue(Gamme _value) {
        value = _value;
    }

    public void setLevel(int _level) {
        level = _level;
    }

    public void setDiese(boolean _diese) {
        diese = _diese;
    }

    public void setPause(boolean _pause) {
        pause = _pause;
    }

    public void setDurationNum(int _durationNum) {
        durationNum = _durationNum;
    }

    public void setDurationDen(int _durationDen) {
        durationDen = _durationDen;
    }

    public void setDynamic(int _dynamic) {
        dynamic = _dynamic;
    }
    public boolean eq(MetaNote _obj) {
        if (durationDen != _obj.durationDen) {
            return false;
        }
        if (durationNum != _obj.durationNum) {
            return false;
        }
        if (dynamic != _obj.dynamic) {
            return false;
        }
        if (pause && _obj.pause || !pause && !_obj.pause) {
            return true;
        }
        if (!diese && _obj.diese || diese && !_obj.diese) {
            return false;
        }
        if (level != _obj.level) {
            return false;
        }
        return value == _obj.value;
    }
    public String display(boolean _db) {
        String time_;
        if (_db) {
            time_ = Double.toString(getDouble(durationNum, durationDen));
        } else {
            time_ = StringUtil.concat(Integer.toString(durationNum),SEPARATOR,Integer.toString(durationDen));
        }
        String dyn_ = Integer.toString(dynamic);
        if (pause) {
            return StringUtil.concat(SYMBOL_PAUSE,time_,SEPARATOR_TIME,dyn_);
        }
        String diese_;
        if (diese) {
            diese_ = SYMBOL_DIESE;
        } else {
            diese_ = EMPTY_STRING;
        }
        return StringUtil.concat(value.name(),diese_,Integer.toString(level),SEPARATOR_TIME,time_,SEPARATOR_TIME,dyn_);
    }
}
