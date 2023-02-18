package code.network;

import code.gui.initialize.AbstractSocket;
import code.sml.Document;

public class BasicServerSample extends BasicServer{
    public BasicServerSample(AbstractSocket _socket, NetGroupFrame _net) {
        super(_socket, _net);
    }

    @Override
    public void loopServer(String _input, Document _object) {
        System.out.println(_input);
    }
}
