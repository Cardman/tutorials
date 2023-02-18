package cards.test;

import aiki.game.fight.BallNumberRate;
import aiki.game.fight.Fighter;
import aiki.main.AikiFactory;
import aiki.map.pokemon.UsablePokemon;
import cards.belote.enumerations.CardBelote;
import cards.consts.Suit;
import cards.gui.WindowCards;
import cards.gui.animations.PreparedPagesCards;
import cards.gui.interfaces.ResultCardsServerInteractFree;
import cards.main.CardFactories;
import cards.main.LaunchingGame;
import cards.president.enumerations.CardPresident;
import cards.tarot.enumerations.CardTarot;
import code.gui.TextAnswerValue;
import code.maths.montecarlo.CustomSeedGene;
import code.mock.*;
import code.network.EquallableNetworkUtil;
import code.network.LoopClient;
import code.network.WindowNetWork;
import code.network.enums.IpType;
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
        WindowNetWork toilettes_ = new WindowNetWork("fr",pr_,belote_,president_,tarot_,new CardFactories(new MockAdvGraphicListGeneratorGene<CardBelote>(), new MockAdvGraphicListGeneratorGene<CardPresident>(), new MockAdvGraphicListGeneratorGene<CardTarot>(), new MockAdvGraphicListGeneratorGene<Suit>()),new AikiFactory(new MockAdvGraphicListGeneratorGene<BallNumberRate>(),new MockAdvGraphicListGeneratorGene<Fighter>(),new MockAdvGraphicListGeneratorGene<String>(),new MockAdvGraphicListGeneratorGene<String>(),new MockAdvGraphicListGeneratorGene<String>(),new MockAdvGraphicListGeneratorGene<UsablePokemon>()));
        toilettes_.setResultCardsServerInteract(new ResultCardsServerInteractFree(true,"__", IpType.IP_V4,4));
        toilettes_.pack();
        toilettes_.setVisible(true);
//        ((MockPlainButton)toilettes_.getSingleModeButton()).getActionListeners().get(0).action();
        ((MockPlainButton)toilettes_.getMultiModeButton()).getActionListeners().get(0).action();
        ((MockPlainButton)toilettes_.getCommonFrame().getPane().getComponent(2)).getActionListeners().get(0).action();
        toilettes_.getConnection().run();
        WindowNetWork canard_ = new WindowNetWork("fr",pr_,belote_,president_,tarot_,new CardFactories(new MockAdvGraphicListGeneratorGene<CardBelote>(), new MockAdvGraphicListGeneratorGene<CardPresident>(), new MockAdvGraphicListGeneratorGene<CardTarot>(), new MockAdvGraphicListGeneratorGene<Suit>()),new AikiFactory(new MockAdvGraphicListGeneratorGene<BallNumberRate>(),new MockAdvGraphicListGeneratorGene<Fighter>(),new MockAdvGraphicListGeneratorGene<String>(),new MockAdvGraphicListGeneratorGene<String>(),new MockAdvGraphicListGeneratorGene<String>(),new MockAdvGraphicListGeneratorGene<UsablePokemon>()));
        canard_.setResultCardsServerInteract(new ResultCardsServerInteractFree(false,"__", IpType.IP_V4,4));
        canard_.pack();
        canard_.setVisible(true);
//        ((MockPlainButton)canard_.getSingleModeButton()).getActionListeners().get(0).action();
        ((MockPlainButton)canard_.getMultiModeButton()).getActionListeners().get(0).action();
        ((MockPlainButton)canard_.getCommonFrame().getPane().getComponent(2)).getActionListeners().get(0).action();
        toilettes_.getConnection().run();
        MockSocket chaussettes1_ = (MockSocket) toilettes_.getSockets().getSockets().getValue(0);
        MockSocket chaussettes2_ = (MockSocket) toilettes_.getSockets().getSockets().getValue(1);
        Assert.assertNotNull(chaussettes1_.getOutput().getList());
        Assert.assertNotNull(chaussettes2_.getOutput().getList());
        MockSocket chaussures1_ = (MockSocket) toilettes_.getBasicClient().getSocket();
        MockSocket chaussures2_ = (MockSocket) canard_.getBasicClient().getSocket();
        chaussures1_.getInstr().addAllElts(chaussettes1_.getOutput());
        chaussures2_.getInstr().addAllElts(chaussettes2_.getOutput());
        Document doc1_ = toilettes_.getDoc(chaussures1_.getInput().readLine());
        chaussures1_.getInstr().clear();

        toilettes_.getExiting(doc1_);
        new LoopClient(toilettes_,doc1_, chaussures1_).run();
             Document doc_ = canard_.getDoc(chaussures2_.getInput().readLine());
             chaussures2_.getInstr().clear();
        canard_.getExiting(doc_);
        new LoopClient(canard_,doc_, chaussures2_).run();

        chaussures1_.getInstr().addAllElts(chaussures1_.getOutput());
        chaussures2_.getInstr().addAllElts(chaussures2_.getOutput());
        String f_ = chaussures1_.getInput().readLine();
        Document readObject1_ = toilettes_.getDoc(f_);
        toilettes_.getSockets().getConnectionsServer().firstValue().loopServer(f_,readObject1_);
        act(toilettes_, canard_, chaussettes1_, chaussettes2_, chaussures1_, chaussures2_);
        String s_ = chaussures2_.getInput().readLine();
        Document readObject_ = toilettes_.getDoc(s_);
        toilettes_.getSockets().getConnectionsServer().firstValue().loopServer(s_,readObject_);
        chaussures1_.getInstr().clear();
        chaussures2_.getInstr().clear();
        System.out.println(chaussettes1_.getInstr().getList());
        System.out.println(chaussettes2_.getInstr().getList());
        System.out.println(chaussures1_.getInstr().getList());
        System.out.println(chaussures2_.getInstr().getList());
        System.out.println(chaussettes1_.getOutput().getList());
        System.out.println(chaussettes2_.getOutput().getList());
        System.out.println(chaussures1_.getOutput().getList());
        System.out.println(chaussures2_.getOutput().getList());
        act2(toilettes_, canard_, chaussettes1_, chaussettes2_, chaussures1_, chaussures2_);
        /*System.out.println(((ContainerMultiPresident)toilettes_.getContainerGame()).get);
            ThreadInvoker.invokeNow(getNet().getThreadFactory(),new LoopClient(getNet(),doc_, getSocket()), getNet().getFrames());*/
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
