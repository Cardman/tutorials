package code.network;

import code.gui.AbsCustComponent;
import code.gui.AbsPanel;
import code.gui.AbsPlainButton;
import code.gui.initialize.AbsCompoFactory;
import code.gui.initialize.AbstractProgramInfos;
import code.gui.initialize.AbstractSocket;
import code.mock.*;
import code.network.enums.IpType;
import code.sml.Document;
import code.sml.DocumentBuilder;
import code.sml.Element;
import code.util.core.BoolVal;

public final class ChatSample extends NetGroupFrame implements MockWithAction {
    public ChatSample(String _lg, AbstractProgramInfos _list) {
        super(_lg, _list);
        AbsCompoFactory comp_ = _list.getCompoFactory();
        AbsPanel pan_ = comp_.newLineBox();
        pan_.add(comp_.newCustCheckBox());
        pan_.add(comp_.newTextField());
        pan_.add(comp_.newTextArea());
        AbsPlainButton connect_ = comp_.newPlainButton();
        connect_.addActionListener(new MockAction(0,this));
        pan_.add(connect_);
        AbsPlainButton send_ = comp_.newPlainButton();
        send_.addActionListener(new MockAction(1,this));
        pan_.add(send_);
        AbsPlainButton close_ = comp_.newPlainButton();
        close_.addActionListener(new MockAction(2,this));
        pan_.add(close_);
        getCommonFrame().setContentPane(pan_);
        pack();
        setVisible(true);
    }

    @Override
    public void action(int _nb) {
        if (_nb == 0) {
            MockCustCheckBox check_ = (MockCustCheckBox) getCommonFrame().getPane().getComponent(0);
            if (check_.isSelected()) {
                createServer("", IpType.IP_V4,0);
            }
        }
    }

    @Override
    public void quit() {
        setVisible(false);
    }

    @Override
    public String getApplicationName() {
        return "";
    }

    @Override
    public boolean canChangeLanguage() {
        return false;
    }

    @Override
    public void changeLanguage(String _language) {

    }

    @Override
    public Document getDoc(String _object) {
        if (_object.startsWith("C:")) {
            Document doc_ = DocumentBuilder.newXmlDocument();
            Element t_ = doc_.createElement("t");
            t_.appendChild(doc_.createTextNode(_object.substring(2)));
            doc_.appendChild(t_);
            return doc_;
        }
        return null;
    }

    @Override
    public Exiting getExiting(Document _doc) {
        return null;
    }

    @Override
    public AbstractSocket initIndexInGame(boolean _first, AbstractSocket _socket) {
        return _socket;
    }

    @Override
    public void gearClient(AbstractSocket _newSocket) {
        int nb_ = getSockets().getSockets().size();
        getSockets().getSockets().put(nb_, _newSocket);
        BasicServer serv_ = new BasicServerSample(_newSocket, this);
        MockSocket ms_ = (MockSocket) serv_.getSocket();
        ms_.getInstr().add("C:HELLO");
        MockSocket mc_ = (MockSocket) getBasicClient().getSocket();
        mc_.getInstr().add("C:HELLO");
        getThreadFactory().newStartedThread(getBasicClient(),true);
        getThreadFactory().newStartedThread(serv_,true);
        getSockets().getConnectionsServer().put(nb_ ,serv_);
//        IndexOfArrivingCards index_ = new IndexOfArrivingCards();
//        index_.setIndex(nb_);
        getSockets().getReadyPlayers().put(nb_ , BoolVal.FALSE);
        getSockets().getPlacesPlayers().put(nb_ ,(byte)(nb_));
//        Net.sendObject(_newSocket,index_);
        trySendString("C:HELLO",_newSocket);
        MockCompoFactory c_ = (MockCompoFactory) getFrames().getCompoFactory();
        c_.invoke();
    }

    @Override
    public void loop(Document _readObject, AbstractSocket _socket) {
        System.out.println(_readObject.export());
    }

    @Override
    public void quitNetwork(Exiting _exit, AbstractSocket _socket) {

    }
}
