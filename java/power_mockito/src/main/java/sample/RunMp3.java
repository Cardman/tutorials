package sample;

import javazoom.jl.player.advanced.*;

public final class RunMp3 implements Runnable {
    private final AdvancedPlayer player;
    private final int frames;
    private boolean finished;

    public RunMp3(AdvancedPlayer _pl, int _frames) {
        this.player = _pl;
        this.frames = _frames;
    }

    @Override
    public void run() {
        finished = ClMp3Impl.play(player, frames);
    }

    public boolean isFinished() {
        return finished;
    }
}
