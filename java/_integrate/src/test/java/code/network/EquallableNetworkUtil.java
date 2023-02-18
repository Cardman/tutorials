package code.network;

import code.gui.TextAnswerValue;
import code.maths.montecarlo.CustomSeedGene;
import code.mock.MockEventListIncr;
import code.mock.MockFileSet;
import code.mock.MockProgramInfos;

public abstract class EquallableNetworkUtil {
    public static MockProgramInfos newMockProgramInfos(CustomSeedGene _s, MockFileSet _set) {
        return new MockProgramInfos("", "", new MockEventListIncr(_s,new int[0],new String[0],new TextAnswerValue[0]), _set);
    }

    public static double[] dbs(double... _args) {
        return _args;
    }

}
