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
import code.maths.montecarlo.CustomSeedGene;
import code.mock.MockAdvGraphicListGeneratorGene;
import code.mock.MockFileSet;
import code.mock.MockPlainButton;
import code.mock.MockProgramInfos;
import code.network.EquallableNetworkUtil;
import code.network.WindowNetWork;
import code.network.enums.IpType;
import code.util.StringList;
import code.util.StringMap;
import code.util.consts.Constants;
import org.junit.Test;

public final class WindowCardsTest extends EquallableNetworkUtil {
    @Test
    public void initPresident() {
        long[] incrs_ = new long[]{1, 3, 5};
        MockProgramInfos pr_ = newMockProgramInfos(new CustomSeedGene(dbs(0.75)), new MockFileSet(123,incrs_,new String[]{"/"}));
        pr_.getSocketFactory().setOkServer(true);
        StringList lgs_ = Constants.getAvailableLanguages();
        StringMap<StringMap<PreparedPagesCards>> belote_ = LaunchingGame.generateAnalyzedBelote(lgs_);
        StringMap<StringMap<PreparedPagesCards>> president_ = LaunchingGame.generateAnalyzedPresident(lgs_);
        StringMap<StringMap<PreparedPagesCards>> tarot_ = LaunchingGame.generateAnalyzedTarot(lgs_);
        WindowCards toilettes_ = new WindowCards("fr",pr_,belote_,president_,tarot_,new CardFactories(new MockAdvGraphicListGeneratorGene<CardBelote>(), new MockAdvGraphicListGeneratorGene<CardPresident>(), new MockAdvGraphicListGeneratorGene<CardTarot>(), new MockAdvGraphicListGeneratorGene<Suit>()));
        toilettes_.pack();
        toilettes_.setVisible(true);
        ((MockPlainButton)toilettes_.getSingleModeButton()).getActionListeners().get(0).action();
//        ((MockPlainButton)toilettes_.getMultiModeButton()).getActionListeners().get(0).action();
    }
}
