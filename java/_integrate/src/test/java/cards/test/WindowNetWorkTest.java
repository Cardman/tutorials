package cards.test;

import aiki.game.fight.BallNumberRate;
import aiki.game.fight.Fighter;
import aiki.main.AikiFactory;
import aiki.map.pokemon.UsablePokemon;
import cards.belote.enumerations.CardBelote;
import cards.consts.Suit;
import cards.gui.animations.PreparedPagesCards;
import cards.gui.containers.ContainerGame;
import cards.gui.containers.ContainerMulti;
import cards.gui.containers.ContainerMultiPresident;
import cards.gui.interfaces.ResultCardsServerInteractFree;
import cards.main.CardFactories;
import cards.main.LaunchingGame;
import cards.network.threads.Net;
import cards.president.enumerations.CardPresident;
import cards.tarot.enumerations.CardTarot;
import code.gui.AbsCustComponent;
import code.gui.AbsPanel;
import code.gui.initialize.AbstractSocket;
import code.maths.montecarlo.CustomSeedGene;
import code.mock.*;
import code.network.EquallableNetworkUtil;
import code.network.LoopClient;
import code.network.WindowNetWork;
import code.network.enums.IpType;
import code.scripts.imgs.cards.CardsInit;
import code.sml.Document;
import code.util.StringList;
import code.util.StringMap;
import code.util.consts.Constants;
import org.junit.Assert;
import org.junit.Test;

public final class WindowNetWorkTest extends EquallableNetworkUtil {
    @Test
    public void initPresident() {
        long[] incrs_ = new long[]{1, 3, 5};
        MockProgramInfos pr_ = newMockProgramInfos(new CustomSeedGene(dbs(0.75)), new MockFileSet(123,incrs_,new String[]{"/"}));
        pr_.getSocketFactory().setOkServer(true);
        StringList lgs_ = Constants.getAvailableLanguages();
        StringMap<StringMap<PreparedPagesCards>> belote_ = LaunchingGame.generateAnalyzedBelote(lgs_);
        StringMap<StringMap<PreparedPagesCards>> president_ = LaunchingGame.generateAnalyzedPresident(lgs_);
        StringMap<StringMap<PreparedPagesCards>> tarot_ = LaunchingGame.generateAnalyzedTarot(lgs_);
        WindowNetWork toilettes_ = window(pr_, belote_, president_, tarot_, true);
        toilettes_.getConnection().run();
        WindowNetWork canard_ = window(pr_, belote_, president_, tarot_, false);
        toilettes_.getConnection().run();
        MockSocket chaussettes1_ = (MockSocket) toilettes_.getSockets().getSockets().getValue(0);
        MockSocket chaussettes2_ = (MockSocket) toilettes_.getSockets().getSockets().getValue(1);
        Assert.assertNotNull(chaussettes1_.getOutput().getList());
        Assert.assertNotNull(chaussettes2_.getOutput().getList());
        MockSocket chaussures1_ = (MockSocket) toilettes_.getBasicClient().getSocket();
        MockSocket chaussures2_ = (MockSocket) canard_.getBasicClient().getSocket();
        chaussures1_.getInstr().addAllElts(chaussettes1_.getOutput());
        chaussures2_.getInstr().addAllElts(chaussettes2_.getOutput());
        loopClient(toilettes_);
        loopClient(canard_);

//        chaussures1_.getInstr().addAllElts(chaussures1_.getOutput());
//        chaussures2_.getInstr().addAllElts(chaussures2_.getOutput());
        server(toilettes_, chaussures1_);
        loopClientBegin(toilettes_,toilettes_);
//        loopClient(toilettes_,toilettes_);
//        act(toilettes_, canard_, chaussettes1_, chaussettes2_, chaussures1_, chaussures2_);
        server(toilettes_, chaussures2_);
        loopClientBegin(toilettes_,toilettes_);
        loopClientBegin(toilettes_,canard_);
        ((ContainerMultiPresident)toilettes_.getNetg().getContainerGame()).getChoiceOfPlaceForPlayingGame().setSelectedItem(1);
//        chaussures1_.getInstr().clear();
        chaussures1_.getInstr().addAllElts(chaussures1_.getOutput());
        server(toilettes_, chaussures1_);
        loopClientBegin(toilettes_,toilettes_);
        loopClientBegin(toilettes_,canard_);
        ((ContainerMultiPresident)canard_.getNetg().getContainerGame()).getChoiceOfPlaceForPlayingGame().setSelectedItem(3);
//        chaussures2_.getInstr().clear();
        chaussures2_.getInstr().addAllElts(chaussures2_.getOutput());
        server(toilettes_, chaussures2_);
        loopClientBegin(toilettes_,toilettes_);
        loopClientBegin(toilettes_,canard_);
        ((ContainerMultiPresident)toilettes_.getNetg().getContainerGame()).getReady().setSelected(true);
//        chaussures1_.getInstr().clear();
        chaussures1_.getInstr().addAllElts(chaussures1_.getOutput());
        server(toilettes_, chaussures1_);
        loopClientBegin(toilettes_,toilettes_);
        loopClientBegin(toilettes_,canard_);
        ((ContainerMultiPresident)canard_.getNetg().getContainerGame()).getReady().setSelected(true);
//        chaussures2_.getInstr().clear();
        chaussures2_.getInstr().addAllElts(chaussures2_.getOutput());
        server(toilettes_, chaussures2_);
        loopClientBegin(toilettes_,toilettes_);
        loopClientBegin(toilettes_,canard_);
        AbsPanel pane = toilettes_.getCommonFrame().getPane();
        MockPlainButton button = (MockPlainButton) pane.getComponent(pane.getComponentCount() - 1);
        button.getActionListeners().get(0).action();
//        chaussures1_.getInstr().clear();
        chaussures1_.getInstr().addAllElts(chaussures1_.getOutput());
        server(toilettes_, chaussures1_);

        loopClient(toilettes_,toilettes_);
//        chaussures1_.getInstr().clear();
        chaussures1_.getInstr().addAllElts(chaussures1_.getOutput());
        loopClient(toilettes_,canard_);
//        chaussures2_.getInstr().clear();
        chaussures2_.getInstr().addAllElts(chaussures2_.getOutput());
        server2(toilettes_, chaussures1_);
        System.out.println(Net.getGames(toilettes_.getNet()).partiePresident().getProgressingTrick().total());
        server2(toilettes_, chaussures2_);
        System.out.println(Net.getGames(toilettes_.getNet()).partiePresident().getProgressingTrick().total());
        loopClient(toilettes_,toilettes_);
//        chaussures1_.getInstr().clear();
        chaussures1_.getInstr().addAllElts(chaussures1_.getOutput());
        loopClient(toilettes_,canard_);
//        chaussures2_.getInstr().clear();
        chaussures2_.getInstr().addAllElts(chaussures2_.getOutput());

        server2(toilettes_, chaussures1_);
        System.out.println(Net.getGames(toilettes_.getNet()).partiePresident().getProgressingTrick().total());
        server2(toilettes_, chaussures2_);
        System.out.println(Net.getGames(toilettes_.getNet()).partiePresident().getProgressingTrick().total());
        loopClient(toilettes_,toilettes_);
//        chaussures1_.getInstr().clear();
        chaussures1_.getInstr().addAllElts(chaussures1_.getOutput());
//        loopClient(toilettes_,canard_);
//        chaussures2_.getInstr().clear();
//        chaussures2_.getInstr().addAllElts(chaussures2_.getOutput());
//        server2(toilettes_, chaussures2_);
//        loopClient(toilettes_,toilettes_);
//        chaussures1_.getInstr().clear();
//        chaussures1_.getInstr().addAllElts(chaussures1_.getOutput());
//        loopClient(toilettes_,canard_);
//        chaussures2_.getInstr().clear();
//        chaussures2_.getInstr().addAllElts(chaussures2_.getOutput());



        AbsPanel cards_ = toilettes_.getNetg().getContainerGame().getPanelHand();
        System.out.println(((ContainerMultiPresident)toilettes_.getNetg().getContainerGame()).getPlayerHandPresident().getCards().getList());
        MockPaintableLabelAbs card_ = (MockPaintableLabelAbs) cards_.getComponent(cards_.getComponentCount()-2);
        card_.getMouseWithoutClickListeners().get(0).mousePressed(null,null,null);
//        chaussures1_.getInstr().clear();
        chaussures1_.getInstr().addAllElts(chaussures1_.getOutput());
        server2(toilettes_, chaussures1_);
//        chaussures1_.getInstr().clear();
//        chaussures1_.getInstr().addAllElts(chaussures1_.getOutput());
//        server(toilettes_, chaussures1_);
//        loopClientBegin(toilettes_,toilettes_);
//        loopClientBegin(toilettes_,canard_);
//        chaussures2_.getInstr().clear();
//        chaussures2_.getInstr().addAllElts(chaussures2_.getOutput());
//        server(toilettes_, chaussures2_);
//        loopClientBegin(toilettes_,toilettes_);
//        loopClientBegin(toilettes_,canard_);
        System.out.println(Net.getGames(toilettes_.getNet()).partiePresident().getDeal().getDealer());
        System.out.println(Net.getGames(toilettes_.getNet()).partiePresident().getProgressingTrick().getEntameur());
        System.out.println(Net.getGames(toilettes_.getNet()).partiePresident().getProgressingTrick().total());
        System.out.println(Net.getGames(toilettes_.getNet()).partiePresident().getProgressingTrick().getCards().getList().get(0).getCards().getList());
        System.out.println(Net.getGames(toilettes_.getNet()).partiePresident().getDeal().getDeal().get(1).getCards().getList());
        loopClient(toilettes_,toilettes_);
        chaussures1_.getInstr().addAllElts(chaussures1_.getOutput());
        server2(toilettes_, chaussures1_);

        loopClient(toilettes_,toilettes_);
//        chaussures1_.getInstr().clear();
        chaussures1_.getInstr().addAllElts(chaussures1_.getOutput());
        loopClient(toilettes_,canard_);
//        chaussures2_.getInstr().clear();
        chaussures2_.getInstr().addAllElts(chaussures2_.getOutput());
        server2(toilettes_, chaussures1_);
        System.out.println(Net.getGames(toilettes_.getNet()).partiePresident().getProgressingTrick().total());
        server2(toilettes_, chaussures2_);
        System.out.println(Net.getGames(toilettes_.getNet()).partiePresident().getProgressingTrick().total());
//        server2(toilettes_, chaussures2_);
        //
//        loopClient(toilettes_,canard_);
//        chaussures1_.getInstr().clear();
//        chaussures2_.getInstr().clear();
//        System.out.println(chaussettes1_.getInstr().getList());
//        System.out.println(chaussettes2_.getInstr().getList());
//        System.out.println(chaussures1_.getInstr().getList());
//        System.out.println(chaussures2_.getInstr().getList());
//        System.out.println(chaussettes1_.getOutput().getList());
//        System.out.println(chaussettes2_.getOutput().getList());
//        System.out.println(chaussures1_.getOutput().getList());
//        System.out.println(chaussures2_.getOutput().getList());
//        act2(toilettes_, canard_, chaussettes1_, chaussettes2_, chaussures1_, chaussures2_);
        /*System.out.println(((ContainerMultiPresident)toilettes_.getContainerGame()).get);
            ThreadInvoker.invokeNow(getNet().getThreadFactory(),new LoopClient(getNet(),doc_, getSocket()), getNet().getFrames());*/
    }

    private void server(WindowNetWork toilettes_, MockSocket _ch) {
        String s_ = _ch.getInstr().last();
//        String s_ = _ch.getInput().readLine();
        server(toilettes_, s_);
    }

    private void server(WindowNetWork toilettes_, String f_) {
        Document readObject1_ = toilettes_.getDoc(f_);
//        ((MockSocket)toilettes_.getSockets().getSockets().getValue(0)).getOutput().clear();
//        ((MockSocket)toilettes_.getSockets().getSockets().getValue(1)).getOutput().clear();
        toilettes_.getSockets().getConnectionsServer().firstValue().loopServer(f_,readObject1_);
    }

    private void server2(WindowNetWork toilettes_, MockSocket _ch) {
        String s_ = _ch.getInstr().last();
//        String s_ = _ch.getInput().readLine();
        server2(toilettes_, s_);
    }

    private void server2(WindowNetWork toilettes_, String f_) {
        Document readObject1_ = toilettes_.getDoc(f_);
        toilettes_.getSockets().getConnectionsServer().firstValue().loopServer(f_,readObject1_);
    }

    private void loopClient(WindowNetWork toilettes_) {
        ContainerMultiPresident c_ = (ContainerMultiPresident) toilettes_.getNetg().getContainerGame();
        MockSocket chaussures1_ = (MockSocket) toilettes_.getBasicClient().getSocket();
//        chaussures1_.getInstr().addAllElts(chaussures1_.getOutput());
//        chaussures1_.getOutput().clear();
        Document doc1_ = toilettes_.getDoc(chaussures1_.getInstr().last());
//        Document doc1_ = toilettes_.getDoc(chaussures1_.getInput().readLine());
//        chaussures1_.getInstr().clear();
        chaussures1_.getOutput().clear();
        toilettes_.getExiting(doc1_);
        new LoopClient(toilettes_,doc1_, chaussures1_).run();
        chaussures1_.getInstr().addAllElts(chaussures1_.getOutput());
    }

    private void loopClient(WindowNetWork _server,WindowNetWork toilettes_) {
        AbstractSocket server_ = Net.getSocketByPlace(((ContainerMulti) toilettes_.getNetg().getContainerGame()).getIndexInGame(), _server.getSockets());
        MockSocket chaussures1_ = (MockSocket) toilettes_.getBasicClient().getSocket();
//        chaussures1_.getInstr().clear();
//        chaussures1_.getInstr().add(((MockSocket)server_).getOutput().last());
//        chaussures1_.getInstr().addAllElts(((MockSocket)server_).getOutput());
//        _server.getSockets().getSockets().getValue();
//        ContainerMultiPresident c_ = (ContainerMultiPresident) toilettes_.getNetg().getContainerGame();
//        chaussures1_.getInstr().addAllElts(chaussures1_.getOutput());
//        chaussures1_.getOutput().clear();
        Document doc1_ = toilettes_.getDoc(((MockSocket)server_).getOutput().last());
//        Document doc1_ = toilettes_.getDoc(chaussures1_.getInput().readLine());
//        chaussures1_.getInstr().clear();
//        chaussures1_.getOutput().clear();
        toilettes_.getExiting(doc1_);
        new LoopClient(toilettes_,doc1_, chaussures1_).run();
//        chaussures1_.getInstr().addAllElts(chaussures1_.getOutput());
    }

    private void loopClientBegin(WindowNetWork _server,WindowNetWork toilettes_) {
        AbstractSocket server_ = _server.getSockets().getSockets().getVal(((ContainerMulti) toilettes_.getNetg().getContainerGame()).getNoClient());
        MockSocket chaussures1_ = (MockSocket) toilettes_.getBasicClient().getSocket();
//        chaussures1_.getInstr().clear();
//        chaussures1_.getInstr().add(((MockSocket)server_).getOutput().last());
//        chaussures1_.getInstr().addAllElts(((MockSocket)server_).getOutput());
//        _server.getSockets().getSockets().getValue();
//        ContainerMultiPresident c_ = (ContainerMultiPresident) toilettes_.getNetg().getContainerGame();
//        chaussures1_.getInstr().addAllElts(chaussures1_.getOutput());
//        chaussures1_.getOutput().clear();
        Document doc1_ = toilettes_.getDoc(((MockSocket)server_).getOutput().last());
//        Document doc1_ = toilettes_.getDoc(chaussures1_.getInput().readLine());
//        chaussures1_.getInstr().clear();
//        chaussures1_.getOutput().clear();
        toilettes_.getExiting(doc1_);
        new LoopClient(toilettes_,doc1_, chaussures1_).run();
//        chaussures1_.getInstr().addAllElts(chaussures1_.getOutput());
    }
    private WindowNetWork window(MockProgramInfos pr_, StringMap<StringMap<PreparedPagesCards>> belote_, StringMap<StringMap<PreparedPagesCards>> president_, StringMap<StringMap<PreparedPagesCards>> tarot_, boolean _create) {
        WindowNetWork canard_ = new WindowNetWork("fr", pr_, belote_, president_, tarot_,new CardFactories(new MockAdvGraphicListGeneratorGene<CardBelote>(), new MockAdvGraphicListGeneratorGene<CardPresident>(), new MockAdvGraphicListGeneratorGene<CardTarot>(), new MockAdvGraphicListGeneratorGene<Suit>()),new AikiFactory(new MockAdvGraphicListGeneratorGene<BallNumberRate>(),new MockAdvGraphicListGeneratorGene<Fighter>(),new MockAdvGraphicListGeneratorGene<String>(),new MockAdvGraphicListGeneratorGene<String>(),new MockAdvGraphicListGeneratorGene<String>(),new MockAdvGraphicListGeneratorGene<UsablePokemon>()));
        canard_.setResultCardsServerInteract(new ResultCardsServerInteractFree(_create,"__", IpType.IP_V4,4));
        canard_.pack();
        canard_.setVisible(true);
//        ((MockPlainButton)canard_.getSingleModeButton()).getActionListeners().get(0).action();
        ((MockPlainButton)canard_.getMultiModeButton()).getActionListeners().get(0).action();
        ((MockPlainButton)canard_.getCommonFrame().getPane().getComponent(2)).getActionListeners().get(0).action();
        canard_.setImages(CardsInit.ms());
        return canard_;
    }

    private void act(WindowNetWork _toilettes, WindowNetWork _canard, MockSocket _chaussettes1, MockSocket _chaussettes2, MockSocket _chaussures1, MockSocket _chaussures2) {
        Document doc11_ = _toilettes.getDoc(_chaussettes1.getOutput().last());
        _toilettes.getExiting(doc11_);
        new LoopClient(_toilettes,doc11_, _chaussures1).run();
    }
    private void act2(WindowNetWork _toilettes, WindowNetWork _canard, MockSocket _chaussettes1, MockSocket _chaussettes2, MockSocket _chaussures1, MockSocket _chaussures2) {
        Document doc11_ = _toilettes.getDoc(_chaussettes1.getOutput().last());
        Document doc12_ = _canard.getDoc(_chaussettes2.getOutput().last());
        _toilettes.getExiting(doc11_);
        new LoopClient(_toilettes,doc11_, _chaussures1).run();
        _chaussures2.getInstr().clear();
        _canard.getExiting(doc12_);
        new LoopClient(_canard,doc12_, _chaussures2).run();
    }
}
