package code.player.gui;

import code.gui.TextAnswerValue;
import code.maths.montecarlo.CustomSeedGene;
import code.mock.*;
import code.network.EquallableNetworkUtil;
import code.player.main.LaunchingPlayer;
import org.junit.Test;

public final class WindowPlayerTest extends EquallableNetworkUtil {
    @Test
    public void test() {
        long[] incrs_ = new long[]{1, 3, 5};
        MockProgramInfos pr_ = newMockProgramInfos(new CustomSeedGene(dbs(0.75)), new MockFileSet(123,new long[]{1, 3, 5},new String[]{"/"}));
        pr_.getFileCoreStream().newFile("tmp").mkdirs();
        pr_.setCurrentPath("tmp");
        MockFileCoreStream fc_ = (MockFileCoreStream)pr_.getFileCoreStream();
//        fc_.
        MockBinFact bin_ = (MockBinFact) pr_.getStreams().getBinFact();
        byte[] bytes_ = new byte[15];
        bytes_[0] = (byte)'R';
        bytes_[1] = (byte)'I';
        bytes_[2] = (byte)'F';
        bytes_[3] = (byte)'F';
        bytes_[8] = (byte)'W';
        bytes_[9] = (byte)'A';
        bytes_[10] = (byte)'V';
        bytes_[11] = (byte)'E';
        bytes_[12] = 2;
        bytes_[13] =5;
        bytes_[14] = 6;
        bin_.writeFile("/song.wav", bytes_);
//        new CreateMainWindowPlayer("fr",new StringList(),pr_).run();
//        new CreateMainWindowPlayer("fr",new StringList("song.wav"),pr_).run();
//        System.out.println(pr_.openClip(bytes));
        LaunchingPlayer l_;
        WindowPlayer window_ = new WindowPlayer("fr", pr_);
        window_.loadList("/song.wav");
        window_.playOrPause(true);
        ((MockClipStream)window_.getClipStream()).setPosition(256);
    }
}
