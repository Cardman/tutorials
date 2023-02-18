package code.network;

import code.maths.montecarlo.CustomSeedGene;
import code.mock.MockCustCheckBox;
import code.mock.MockFileSet;
import code.mock.MockPlainButton;
import code.mock.MockProgramInfos;
import code.util.core.StringUtil;
import org.junit.Test;

public class NetGroupFrameTest extends EquallableNetworkUtil {
    @Test
    public void t1() {
        MockProgramInfos pr_ = newMockProgramInfos(new CustomSeedGene(dbs(0.75)), new MockFileSet(0, new long[0], StringUtil.wrapStringArray("/")));
        pr_.getSocketFactory().setOkServer(true);
        ChatSample en_ = new ChatSample("en", pr_);
        MockCustCheckBox check_ = (MockCustCheckBox) en_.getCommonFrame().getPane().getComponent(0);
        check_.setSelected(true);
        MockPlainButton connect_ = (MockPlainButton) en_.getCommonFrame().getPane().getComponent(3);
        connect_.getActionListeners().first().action();
        en_.getConnection().run();
    }
}
