package code.vm.applications.main.other;

import aiki.db.DataBase;
import aiki.db.ImageHeroKey;
import aiki.facade.FacadeGame;
import aiki.facade.enums.SelectedBoolean;
import aiki.fight.enums.Statistic;
import aiki.fight.moves.DamagingMoveData;
import aiki.fight.moves.effects.EffectDamage;
import aiki.fight.moves.enums.TargetChoice;
import aiki.fight.pokemon.NameLevel;
import aiki.fight.pokemon.PokemonData;
import aiki.fight.pokemon.enums.ExpType;
import aiki.fight.util.LevelMove;
import aiki.fight.util.StatBaseEv;
import aiki.fight.util.TypesDuo;
import aiki.game.Game;
import aiki.game.params.enums.DifficultyModelLaw;
import aiki.game.params.enums.DifficultyWinPointsFight;
import aiki.game.player.enums.Sex;
import aiki.gui.WindowAiki;
import aiki.instances.Instances;
import aiki.main.AikiFactory;
import aiki.map.Condition;
import aiki.map.DataMap;
import aiki.map.buildings.Gym;
import aiki.map.buildings.PokemonCenter;
import aiki.map.characters.*;
import aiki.map.characters.enums.GeranceType;
import aiki.map.characters.enums.SellType;
import aiki.map.enums.Direction;
import aiki.map.levels.*;
import aiki.map.levels.enums.EnvironmentType;
import aiki.map.places.City;
import aiki.map.places.League;
import aiki.map.places.Road;
import aiki.map.pokemon.PkTrainer;
import aiki.map.pokemon.PokemonTeam;
import aiki.map.pokemon.WildPk;
import aiki.map.pokemon.enums.Gender;
import aiki.map.util.MiniMapCoords;
import aiki.map.util.MiniMapCoordsList;
import aiki.map.util.TileMiniMap;
import aiki.sml.DefDataBaseStream;
import aiki.sml.DocumentWriterAikiCoreUtil;
import aiki.sml.GamesPk;
import aiki.sml.LoadingGame;
import aiki.util.*;
import applications.gui.WindowApps;
import applications.main.LaunchingApplications;
import cards.belote.*;
import cards.belote.enumerations.BidBelote;
import cards.belote.enumerations.CardBelote;
import cards.belote.enumerations.DealingBelote;
import cards.belote.sml.DocumentWriterBeloteUtil;
import cards.consts.CouleurValeur;
import cards.consts.GameType;
import cards.consts.MixCardsChoice;
import cards.consts.Suit;
import cards.facade.Games;
import cards.main.CardFactories;
import cards.president.DealPresident;
import cards.president.GamePresident;
import cards.president.HandPresident;
import cards.president.RulesPresident;
import cards.president.enumerations.CardPresident;
import cards.president.sml.DocumentWriterPresidentUtil;
import cards.tarot.DealTarot;
import cards.tarot.GameTarot;
import cards.tarot.HandTarot;
import cards.tarot.RulesTarot;
import cards.tarot.enumerations.CardTarot;
import cards.tarot.sml.DocumentWriterTarotUtil;
import code.converterimages.gui.DocumentImagesUtil;
import code.expressionlanguage.gui.unit.WindowUnit;
import code.expressionlanguage.utilcompo.FileInfos;
import code.gui.AppFactories;
import code.gui.CdmFactory;
import code.gui.WithAppFactories;
import code.gui.files.*;
import code.gui.images.AbstractImage;
import code.gui.initialize.AbstractLightProgramInfos;
import code.maths.LgInt;
import code.maths.Rate;
import code.maths.litteral.EvolvedMathFactory;
import code.maths.montecarlo.CustomSeedGene;
import code.maths.montecarlo.DefaultGenerator;
import code.maths.montecarlo.MonteCarloNumber;
import code.mock.*;
import code.netw.NetWork;
import code.player.gui.WindowPlayer;
import code.sml.DocumentBuilder;
import code.sml.Element;
import code.sml.FullDocument;
import code.sml.util.TranslationsFile;
import code.sml.util.TranslationsLg;
import code.stream.StreamBinaryFile;
import code.stream.StreamTextFile;
import code.stream.core.ContentTime;
import code.threads.AbstractBaseExecutorServiceParam;
import code.threads.AbstractThread;
import code.util.*;
import code.util.core.StringUtil;
import org.junit.Test;

public class ApplicationsTest {

    public static final String EN = "en";
    public static final String TEMP_FOLDER = "/coucou";
    public static final String ARG = "/anti_aerien";
    public static final String LOCALE = "locale";
    public static final String LANGUAGE = "/coucou/langue.xml";
    public static final String EXPORT = "/anti_aerien_2";
    public static final String SAVED_GAME = "/anti_aerien_3";

    @Test
    public void rts1() {
        MockProgramInfos p = build();
        p.setLanguages(new StringList(EN));
        p.getFileCoreStream().newFile(TEMP_FOLDER).mkdirs();
        FullDocument fullDocument = DocumentBuilder.newDocumentBuilder().newDocument();
        fullDocument.appendChild(fullDocument.createElement("_"));
        StreamTextFile.saveTextFile(ARG, fullDocument.export(),p.getStreams());
        FullDocument lg = DocumentBuilder.newDocumentBuilder().newDocument();
        Element elt_ = lg.createElement("_");
        Element locale = lg.createElement(LOCALE);
        locale.setAttribute(LOCALE, EN);
        elt_.appendChild(locale);
        lg.appendChild(elt_);
        StreamTextFile.saveTextFile(LANGUAGE, lg.export(),p.getStreams());
        LaunchingApplications la = new LaunchingApplications(new WithAppFactories(p,new AppFactories(new AikiFactory(p, executor(), executor()),new CardFactories(p, executor(), executor()),new CdmFactory(p,new MockInterceptor()))));
        la.loadLanguage(TEMP_FOLDER,new String[]{ARG});
        System.out.println(p.getFrames().size());
    }
    @Test
    public void rts2() {
        MockProgramInfos p = build();
        p.setLanguages(new StringList(EN));
        p.getFileCoreStream().newFile(TEMP_FOLDER).mkdirs();
        FullDocument fullDocument = DocumentBuilder.newDocumentBuilder().newDocument();
        fullDocument.appendChild(fullDocument.createElement("_"));
        StreamTextFile.saveTextFile(ARG, fullDocument.export(),p.getStreams());
        LaunchingApplications la = new LaunchingApplications(new WithAppFactories(p,new AppFactories(new AikiFactory(p, executor(), executor()),new CardFactories(p, executor(), executor()),new CdmFactory(p,new MockInterceptor()))));
        la.loadLanguage(TEMP_FOLDER,new String[]{ARG});
        System.out.println(p.getFrames().size());
//        ((MockCompoFactory)p.getCompoFactory()).invoke();
    }
    @Test
    public void noFile1() {
        MockProgramInfos p = build();
        p.setLanguages(new StringList(EN));
        p.getFileCoreStream().newFile(TEMP_FOLDER).mkdirs();
        StreamTextFile.saveTextFile(ARG, "",p.getStreams());
        LaunchingApplications la = new LaunchingApplications(new WithAppFactories(p,new AppFactories(new AikiFactory(p, executor(), executor()),new CardFactories(p, executor(), executor()),new CdmFactory(p,new MockInterceptor()))));
        la.loadLanguage(TEMP_FOLDER,new String[]{ARG});
        System.out.println(p.getFrames().size());
//        ((MockCompoFactory)p.getCompoFactory()).invoke();
    }
    @Test
    public void noFile2() {
        MockProgramInfos p = build();
        p.setLanguages(new StringList(EN));
        p.getFileCoreStream().newFile(TEMP_FOLDER).mkdirs();
        StreamTextFile.saveTextFile(ARG, "",p.getStreams());
        FullDocument lg = DocumentBuilder.newDocumentBuilder().newDocument();
        Element elt_ = lg.createElement("_");
        Element locale = lg.createElement(LOCALE);
        locale.setAttribute(LOCALE, EN);
        elt_.appendChild(locale);
        lg.appendChild(elt_);
        StreamTextFile.saveTextFile(LANGUAGE, lg.export(),p.getStreams());
        LaunchingApplications la = new LaunchingApplications(new WithAppFactories(p,new AppFactories(new AikiFactory(p, executor(), executor()),new CardFactories(p, executor(), executor()),new CdmFactory(p,new MockInterceptor()))));
        la.loadLanguage(TEMP_FOLDER,new String[]{ARG});
        System.out.println(p.getFrames().size());
//        ((MockCompoFactory)p.getCompoFactory()).invoke();
    }
    @Test
    public void pk() {
        MockProgramInfos p = build();
        TranslationsLg en_ = p.lg(EN);
        p.setLanguage(EN);
        GamesPk.enTr(GamesPk.initAppliTr(en_));
        p.setLanguages(new StringList(EN));
        p.getFileCoreStream().newFile(TEMP_FOLDER).mkdirs();
        DataBase res_ = InitDbValid2.initDb();
        res_.getMap().initializeLinks();
        res_.getMap().initInteractiveElements();
        res_.getMap().initializeTree();
        res_.getMap().initializeAccessibility();
        FacadeGame f_ = new FacadeGame();
        f_.setData(res_);
        f_.setLanguages(new StringList(EN));
        f_.setSimplyLanguage(EN);
        f_.setSexList(new MockLSexList());
        DefDataBaseStream ins_ = new DefDataBaseStream();
        LoadingGame loadingGame_ = new LoadingGame();
        loadingGame_.setExport(EXPORT);
        ins_.exportRom(p,f_, loadingGame_);

        Game g_ = new Game(res_);
        g_.initUserInteract("_", Sex.NO, g_.getDifficulty(), res_);
        g_.setZippedRom(EXPORT);
        StreamTextFile.saveTextFile(ARG, DocumentWriterAikiCoreUtil.setGame(g_),p.getStreams());



        FullDocument lg = DocumentBuilder.newDocumentBuilder().newDocument();
        Element elt_ = lg.createElement("_");
        Element locale = lg.createElement(LOCALE);
        locale.setAttribute(LOCALE, EN);
        elt_.appendChild(locale);
        lg.appendChild(elt_);
        StreamTextFile.saveTextFile(LANGUAGE, lg.export(),p.getStreams());
        LaunchingApplications la = new LaunchingApplications(new WithAppFactories(p,new AppFactories(new AikiFactory(p, executor(), executor()),new CardFactories(p, executor(), executor()),new CdmFactory(p,new MockInterceptor()))));
        la.loadLanguage(TEMP_FOLDER,new String[]{ARG});
        ((WindowAiki)p.getFrames().get(1)).getFacade().setSexList(f_.getSexList());
        ((MockThreadFactory)p.getThreadFactory()).getAllThreads().get(0).join();
    }
    @Test
    public void pk2() {
        MockProgramInfos p = build();
        TranslationsLg en_ = p.lg(EN);
        p.setLanguage(EN);
        GamesPk.enTr(GamesPk.initAppliTr(en_));
        p.setLanguages(new StringList(EN));
        p.getFileCoreStream().newFile(TEMP_FOLDER).mkdirs();
        DataBase res_ = InitDbValid2.initDb();
        res_.getMap().initializeLinks();
        res_.getMap().initInteractiveElements();
        res_.getMap().initializeTree();
        res_.getMap().initializeAccessibility();
        FacadeGame f_ = new FacadeGame();
        f_.setData(res_);
        f_.setLanguages(new StringList(EN));
        f_.setSimplyLanguage(EN);
        f_.setSexList(new MockLSexList());
        DefDataBaseStream ins_ = new DefDataBaseStream();
        LoadingGame loadingGame_ = new LoadingGame();
        loadingGame_.setExport(EXPORT);
        loadingGame_.setLastRom(EXPORT);
        loadingGame_.setLastSavedGame(SAVED_GAME);
        ins_.exportRom(p,f_, loadingGame_);

        Game g_ = new Game(res_);
        g_.initUserInteract("_", Sex.NO, g_.getDifficulty(), res_);
        g_.setZippedRom(EXPORT);
        StreamTextFile.saveTextFile(SAVED_GAME, DocumentWriterAikiCoreUtil.setGame(g_),p.getStreams());

        StreamTextFile.saveTextFile(ARG, DocumentWriterAikiCoreUtil.setLoadingGame(loadingGame_),p.getStreams());

        FullDocument lg = DocumentBuilder.newDocumentBuilder().newDocument();
        Element elt_ = lg.createElement("_");
        Element locale = lg.createElement(LOCALE);
        locale.setAttribute(LOCALE, EN);
        elt_.appendChild(locale);
        lg.appendChild(elt_);
        StreamTextFile.saveTextFile(LANGUAGE, lg.export(),p.getStreams());
        LaunchingApplications la = new LaunchingApplications(new WithAppFactories(p,new AppFactories(new AikiFactory(p, executor(), executor()),new CardFactories(p, executor(), executor()),new CdmFactory(p,new MockInterceptor()))));
        la.loadLanguage(TEMP_FOLDER,new String[]{ARG});
        ((WindowAiki)p.getFrames().get(1)).getFacade().setSexList(f_.getSexList());
        ((MockThreadFactory)p.getThreadFactory()).getAllThreads().get(0).join();
    }
    @Test
    public void rend() {
        MockProgramInfos p = build();
        TranslationsLg en_ = p.lg(EN);
        FileInfos.enTr(FileInfos.initComments(en_));
        p.setLanguages(new StringList(EN));
        p.setLanguage(EN);
        String xmlConf_ = "<cfg>\n" +
                "\t<java.lang.String field='firstUrl' value='page.html'/>\n" +
                "\t<java.lang.String field='prefix' value='c'/>\n" +
                "\t<sm field='navigation'>\n" +
                "\t\t<java.lang.String key='' value='bean_one.method'/>\n" +
                "\t\t<sm>\n" +
                "\t\t\t<java.lang.String key='' value='res'/>\n" +
                "\t\t\t<java.lang.String value='page2.html'/>\n" +
                "\t\t</sm>\n" +
                "\t</sm>\n" +
                "\t<n field=\"context\">\n" +
                "\t<java.lang.Integer field='tabWidth' value='4'/>\n" +
                "\t<sm field='styleValues' value='StyleValueRgb=___'/>\n" +
                "\t</n>\n" +
                "\t<java.lang.Integer field='tabWidth' value='4'/>\n" +
                "\t<java.lang.String field='messagesFolder' value='messages'/>\n" +
                "\t<java.lang.String field='filesConfName' value='conf_cl.txt'/>\n" +
                "\t<sm field='beans'>\n" +
                "\t\t<java.lang.String key='' value='bean_one'/>\n" +
                "\t\t<b>\n" +
                "\t\t\t<java.lang.String field='scope' value='session'/>\n" +
                "\t\t\t<java.lang.String field='className' value='pkg.BeanOne'/>\n" +
                "\t\t</b>\n" +
                "\t</sm>\n" +
                "\t<sm field='properties'>\n" +
                "\t\t<java.lang.String key='' value='msg_cust'/>\n" +
                "\t\t<java.lang.String value='sample/file'/>\n" +
                "\t</sm>\n" +
                "\t<sl field='addedFiles'>\n" +
                "\t\t<str value='page.html'/>\n" +
                "\t</sl>\n" +
                "\t<sl field='renderFiles'>\n" +
                "\t\t<str value='page.html'/>\n" +
                "\t</sl>\n" +
                "\t<sm field='lateValidators'>\n" +
                "\t\t<str key='' value='my_val'/>\n" +
                "\t\t<str value='pkg.MyVal'/>\n" +
                "\t</sm>\n" +
                "</cfg>";
        StringMap<ContentTime> cont_ = with(p, with(p, with(p, init(), "conf.txt", "content"), "src/"), "src/folder/");
        StringMap<ContentTime> contConf_ = with(p,cont_,"conf_cl.txt","src/folder/file.txt");
        StringMap<ContentTime> contRend_ = with(p,contConf_,"page.html","<html><body>_</body></html>");
        StringMap<ContentTime> content_ = with(p, contRend_, "src/folder/file.txt", "public class cl.Init{public static Object init(String[] names, String[] contents){return new String[0];}}");
        StringMap<ContentTime> contents_ = with(p, content_, "conf.xml", xmlConf_);
        byte[] zipped_ = p.getZipFact().zipBinFiles(contents_);
        StreamBinaryFile.writeFile("/_.zip",zipped_,p.getStreams());
        StreamTextFile.saveTextFile(ARG,"/_.zip\nconf.xml\ninitDb=cl.Init.init\nen", p.getStreams());
        FullDocument lg = DocumentBuilder.newDocumentBuilder().newDocument();
        Element elt_ = lg.createElement("_");
        Element locale = lg.createElement(LOCALE);
        locale.setAttribute(LOCALE, EN);
        elt_.appendChild(locale);
        lg.appendChild(elt_);
        p.getFileCoreStream().newFile(TEMP_FOLDER).mkdirs();
        StreamTextFile.saveTextFile(LANGUAGE, lg.export(),p.getStreams());
        LaunchingApplications la = new LaunchingApplications(new WithAppFactories(p,new AppFactories(new AikiFactory(p, executor(), executor()),new CardFactories(p, executor(), executor()),new CdmFactory(p,new MockInterceptor()))));
        la.loadLanguage(TEMP_FOLDER,new String[]{ARG});
        ((MockThreadFactory)p.getThreadFactory()).getAllThreads().get(0).join();
    }

    @Test
    public void wu1() {
        MockProgramInfos p = build();
        TranslationsLg en_ = p.lg(EN);
        FileInfos.enTr(FileInfos.initComments(en_));
        p.setLanguages(new StringList(EN));
        p.setLanguage(EN);
        byte[] zipped_ = p.getZipFact().zipBinFiles(with(p,  with(p,with(p,with(p, init(), "conf.txt", "content"),"src/"),"src/folder/"),"src/folder/file.txt","public class pkg.Sample{@Test public void err(){Assert.assert(0,1);}@Test public void success(){Assert.assert(1,1);}}"));
        StreamBinaryFile.writeFile("/_.zip",zipped_,p.getStreams());
        StreamTextFile.saveTextFile(ARG,"/_.zip\nen\ntabWidth=4", p.getStreams());
        FullDocument lg = DocumentBuilder.newDocumentBuilder().newDocument();
        Element elt_ = lg.createElement("_");
        Element locale = lg.createElement(LOCALE);
        locale.setAttribute(LOCALE, EN);
        elt_.appendChild(locale);
        lg.appendChild(elt_);
        p.getFileCoreStream().newFile(TEMP_FOLDER).mkdirs();
        StreamTextFile.saveTextFile(LANGUAGE, lg.export(),p.getStreams());
        LaunchingApplications la = new LaunchingApplications(new WithAppFactories(p,new AppFactories(new AikiFactory(p, executor(), executor()),new CardFactories(p, executor(), executor()),new CdmFactory(p,new MockInterceptor()))));
        la.loadLanguage(TEMP_FOLDER,new String[]{ARG});
        ((MockBaseExecutorService)((WindowUnit)p.getFrames().last()).getExec()).getTasks().lastValue().attendre();
    }

    @Test
    public void wu2() {
        MockProgramInfos p = build();
        TranslationsLg en_ = p.lg(EN);
        FileInfos.enTr(FileInfos.initComments(en_));
        p.setLanguages(new StringList(EN));
        p.setLanguage(EN);
        byte[] zipped_ = p.getZipFact().zipBinFiles(with(p,  with(p,with(p,with(p, init(), "conf.txt", "content"),"src/"),"src/folder/"),"src/folder/file.txt","public class pkg.Sample{@Test public void err(){Assert.assert(0,1);}@Test public void success(){Assert.assert(1,1);}}"));
        StreamBinaryFile.writeFile("/_.zip",zipped_,p.getStreams());
        StreamTextFile.saveTextFile(ARG,"/_.zip\nen", p.getStreams());
        FullDocument lg = DocumentBuilder.newDocumentBuilder().newDocument();
        Element elt_ = lg.createElement("_");
        Element locale = lg.createElement(LOCALE);
        locale.setAttribute(LOCALE, EN);
        elt_.appendChild(locale);
        lg.appendChild(elt_);
        p.getFileCoreStream().newFile(TEMP_FOLDER).mkdirs();
        StreamTextFile.saveTextFile(LANGUAGE, lg.export(),p.getStreams());
        LaunchingApplications la = new LaunchingApplications(new WithAppFactories(p,new AppFactories(new AikiFactory(p, executor(), executor()),new CardFactories(p, executor(), executor()),new CdmFactory(p,new MockInterceptor()))));
        la.loadLanguage(TEMP_FOLDER,new String[]{ARG});
        ((MockBaseExecutorService)((WindowUnit)p.getFrames().last()).getExec()).getTasks().lastValue().attendre();
    }
    @Test
    public void wf() {
        MockProgramInfos p = build();
        TranslationsLg en_ = p.lg(EN);
        FileInfos.enTr(FileInfos.initComments(en_));
        p.setLanguages(new StringList(EN));
        p.setLanguage(EN);
        byte[] zipped_ = p.getZipFact().zipBinFiles(with(p,  with(p,with(p,with(p, init(), "conf.txt", "content"),"src/"),"src/folder/"),"src/folder/file.txt","public class pkg.Sample{public static void m(){}@Test public void err(){Assert.assert(0,1);}@Test public void success(){Assert.assert(1,1);}}"));
        StreamBinaryFile.writeFile("/_.zip",zipped_,p.getStreams());
        StreamTextFile.saveTextFile(ARG,"/_.zip\nen\nmain=pkg.Sample.m\ncover=\nargs=", p.getStreams());
        FullDocument lg = DocumentBuilder.newDocumentBuilder().newDocument();
        Element elt_ = lg.createElement("_");
        Element locale = lg.createElement(LOCALE);
        locale.setAttribute(LOCALE, EN);
        elt_.appendChild(locale);
        lg.appendChild(elt_);
        p.getFileCoreStream().newFile(TEMP_FOLDER).mkdirs();
        StreamTextFile.saveTextFile(LANGUAGE, lg.export(),p.getStreams());
        LaunchingApplications la = new LaunchingApplications(new WithAppFactories(p,new AppFactories(new AikiFactory(p, executor(), executor()),new CardFactories(p, executor(), executor()),new CdmFactory(p,new MockInterceptor()))));
        la.loadLanguage(TEMP_FOLDER,new String[]{ARG});
    }
    @Test
    public void c1() {
        MockProgramInfos p = build();
        TranslationsLg en_ = p.lg(EN);
        Games.enTr(Games.initAppliTr(en_));
        maxiImgs(p);
        p.setLanguages(new StringList(EN));
        p.setLanguage(EN);
        RulesBelote rules_ = rulesThreePlayers();
        DealBelote deal_ = dealThreePlayersIa();
//        MockGameBelote mock_ = new MockGameBelote();
//        nextDiscardIa(mock_, CardBelote.DIAMOND_7, CardBelote.DIAMOND_8,CardBelote.SPADE_KING,CardBelote.SPADE_QUEEN,CardBelote.CLUB_KING,CardBelote.CLUB_QUEEN,CardBelote.CLUB_9,CardBelote.CLUB_8);
//        nextSlam(mock_, BoolVal.TRUE);
//        nextCard(mock_, CardBelote.HEART_JACK);
        GameBelote gb_ = edited(deal_, rules_);
        gb_.ajouterContrat(bidSuit(Suit.UNDEFINED,0, BidBelote.FOLD));
//        gb_.ajouterContrat(bidSuit(Suit.UNDEFINED,0,BidBelote.FOLD));
//        gb_.ajouterContrat(bidSuit(Suit.UNDEFINED,0,BidBelote.FOLD));
//        gb_.ajouterContrat(bidSuit(Suit.HEART,0,BidBelote.OTHER_SUIT));
//        gb_.ecarter(mock_);
        StreamTextFile.saveTextFile(ARG, DocumentWriterBeloteUtil.setGameBelote(gb_), p.getStreams());
        FullDocument lg = DocumentBuilder.newDocumentBuilder().newDocument();
        Element elt_ = lg.createElement("_");
        Element locale = lg.createElement(LOCALE);
        locale.setAttribute(LOCALE, EN);
        elt_.appendChild(locale);
        lg.appendChild(elt_);
        p.getFileCoreStream().newFile(TEMP_FOLDER).mkdirs();
        StreamTextFile.saveTextFile(LANGUAGE, lg.export(),p.getStreams());
        LaunchingApplications la = new LaunchingApplications(new WithAppFactories(p,new AppFactories(new AikiFactory(p, executor(), executor()),new CardFactories(p, executor(), executor()),new CdmFactory(p,new MockInterceptor()))));
        la.loadLanguage(TEMP_FOLDER,new String[]{ARG});
    }
    @Test
    public void c2() {
        MockProgramInfos p = build();
        TranslationsLg en_ = p.lg(EN);
        Games.enTr(Games.initAppliTr(en_));
        maxiImgs(p);
        p.setLanguages(new StringList(EN));
        p.setLanguage(EN);
        RulesPresident r_ = new RulesPresident(4);
        r_.getCommon().setNbDeals(1);
        DealPresident deal_ = mix(3);
        GamePresident gp_ = edited(deal_, r_);
        StreamTextFile.saveTextFile(ARG, DocumentWriterPresidentUtil.setGamePresident(gp_), p.getStreams());
        FullDocument lg = DocumentBuilder.newDocumentBuilder().newDocument();
        Element elt_ = lg.createElement("_");
        Element locale = lg.createElement(LOCALE);
        locale.setAttribute(LOCALE, EN);
        elt_.appendChild(locale);
        lg.appendChild(elt_);
        p.getFileCoreStream().newFile(TEMP_FOLDER).mkdirs();
        StreamTextFile.saveTextFile(LANGUAGE, lg.export(),p.getStreams());
        LaunchingApplications la = new LaunchingApplications(new WithAppFactories(p,new AppFactories(new AikiFactory(p, executor(), executor()),new CardFactories(p, executor(), executor()),new CdmFactory(p,new MockInterceptor()))));
        la.loadLanguage(TEMP_FOLDER,new String[]{ARG});
        tryAn((MockThreadFactory) p.getThreadFactory());
    }
    @Test
    public void c3() {
        MockProgramInfos p = build();
        TranslationsLg en_ = p.lg(EN);
        Games.enTr(Games.initAppliTr(en_));
        maxiImgs(p);
        p.setLanguages(new StringList(EN));
        p.setLanguage(EN);
        RulesTarot rules_ = rules();
        DealTarot deal_ = deal1(4);
//        MockGameBelote mock_ = new MockGameBelote();
//        nextDiscardIa(mock_, CardBelote.DIAMOND_7, CardBelote.DIAMOND_8,CardBelote.SPADE_KING,CardBelote.SPADE_QUEEN,CardBelote.CLUB_KING,CardBelote.CLUB_QUEEN,CardBelote.CLUB_9,CardBelote.CLUB_8);
//        nextSlam(mock_, BoolVal.TRUE);
//        nextCard(mock_, CardBelote.HEART_JACK);
        GameTarot gb_ = edited(deal_, rules_);
//        gb_.ajouterContrat(bidSuit(Suit.UNDEFINED,0, BidBelote.FOLD));
//        gb_.ajouterContrat(bidSuit(Suit.UNDEFINED,0,BidBelote.FOLD));
//        gb_.ajouterContrat(bidSuit(Suit.UNDEFINED,0,BidBelote.FOLD));
//        gb_.ajouterContrat(bidSuit(Suit.HEART,0,BidBelote.OTHER_SUIT));
//        gb_.ecarter(mock_);
        StreamTextFile.saveTextFile(ARG, DocumentWriterTarotUtil.setGameTarot(gb_), p.getStreams());
        FullDocument lg = DocumentBuilder.newDocumentBuilder().newDocument();
        Element elt_ = lg.createElement("_");
        Element locale = lg.createElement(LOCALE);
        locale.setAttribute(LOCALE, EN);
        elt_.appendChild(locale);
        lg.appendChild(elt_);
        p.getFileCoreStream().newFile(TEMP_FOLDER).mkdirs();
        StreamTextFile.saveTextFile(LANGUAGE, lg.export(),p.getStreams());
        LaunchingApplications la = new LaunchingApplications(new WithAppFactories(p,new AppFactories(new AikiFactory(p, executor(), executor()),new CardFactories(p, executor(), executor()),new CdmFactory(p,new MockInterceptor()))));
        la.loadLanguage(TEMP_FOLDER,new String[]{ARG});
    }
    @Test
    public void imgs() {
        MockProgramInfos p = build();
        TranslationsLg en_ = p.lg(EN);
        p.setLanguages(new StringList(EN));
        p.setLanguage(EN);
        updateBase(p.currentLg());
        p.getFileCoreStream().newFile("/from/one").mkdirs();
        p.getFileCoreStream().newFile("/from/one/sub1").mkdirs();
        p.getFileCoreStream().newFile("/from/one/sub2").mkdirs();
        p.getFileCoreStream().newFile("/from/two").mkdirs();
        p.getFileCoreStream().newFile("/from/two/sub1").mkdirs();
        p.getFileCoreStream().newFile("/from/two/sub2").mkdirs();
        StreamBinaryFile.writeFile("/from/one/sub1/1",new byte[0],p.getStreams());
        StreamBinaryFile.writeFile("/from/one/sub1/2",toBinary(new int[][]{new int[]{1,2},new int[]{3,4}}),p.getStreams());
        StreamBinaryFile.writeFile("/from/one/sub2/1",new byte[0],p.getStreams());
        StreamBinaryFile.writeFile("/from/one/sub2/2",toBinary(new int[][]{new int[]{1,2},new int[]{3,4},new int[]{5,6}}),p.getStreams());
        StreamBinaryFile.writeFile("/from/two/sub1/1",new byte[0],p.getStreams());
        StreamBinaryFile.writeFile("/from/two/sub1/2",toBinary(new int[][]{new int[]{1,2,3},new int[]{4,5,6}}),p.getStreams());
        StreamBinaryFile.writeFile("/from/two/sub2/1",new byte[0],p.getStreams());
        StreamBinaryFile.writeFile("/from/two/sub2/2",toBinary(new int[][]{new int[]{1,2,3},new int[]{4,5,6},new int[]{7,8,9}}),p.getStreams());
        FullDocument d_ = DocumentBuilder.newDocumentBuilder().newDocument();
        Element eltExp_ = d_.createElement(DocumentImagesUtil.ROOT_CONF);
        eltExp_.setAttribute(DocumentImagesUtil.INFO_IMP,"/from");
        eltExp_.setAttribute(DocumentImagesUtil.INFO_EXP,"/to");
        d_.appendChild(eltExp_);
        StreamTextFile.saveTextFile(ARG,d_.export(),p.getStreams());
        FullDocument lg = DocumentBuilder.newDocumentBuilder().newDocument();
        Element elt_ = lg.createElement("_");
        Element locale = lg.createElement(LOCALE);
        locale.setAttribute(LOCALE, EN);
        elt_.appendChild(locale);
        lg.appendChild(elt_);
        p.getFileCoreStream().newFile(TEMP_FOLDER).mkdirs();
        StreamTextFile.saveTextFile(LANGUAGE, lg.export(),p.getStreams());
        LaunchingApplications la = new LaunchingApplications(new WithAppFactories(p,new AppFactories(new AikiFactory(p, executor(), executor()),new CardFactories(p, executor(), executor()),new CdmFactory(p,new MockInterceptor()))));
        la.loadLanguage(TEMP_FOLDER,new String[]{ARG});
    }
    @Test
    public void sound() {
        MockProgramInfos p = build();
        p.setLanguages(new StringList(EN));
        p.setLanguage(EN);
        FullDocument d_ = DocumentBuilder.newDocumentBuilder().newDocument();
        Element r_ = d_.createElement(WindowPlayer.SMIL);
        Element s1_ = d_.createElement(WindowPlayer.CST_MEDIA);
        s1_.setAttribute(WindowPlayer.CST_SRC,"file1");
        r_.appendChild(s1_);
        Element s2_ = d_.createElement(WindowPlayer.CST_MEDIA);
        s2_.setAttribute(WindowPlayer.CST_SRC,"file2");
        r_.appendChild(s2_);
        d_.appendChild(r_);
        StreamBinaryFile.writeFile(ARG, StringUtil.encode(d_.export()),p.getStreams());
        StreamBinaryFile.writeFile("file1",wrapInts('R', 'I', 'F', 'F', 0, 0, 0, 0, 'W', 'A', 'V', 'e', 1),p.getStreams());
        StreamBinaryFile.writeFile("file2",wrapInts('R', 'I', 'F', 'F', 0, 0, 0, 0, 'W', 'A', 'V', 'E', 2),p.getStreams());
        FullDocument lg = DocumentBuilder.newDocumentBuilder().newDocument();
        Element elt_ = lg.createElement("_");
        Element locale = lg.createElement(LOCALE);
        locale.setAttribute(LOCALE, EN);
        elt_.appendChild(locale);
        lg.appendChild(elt_);
        p.getFileCoreStream().newFile(TEMP_FOLDER).mkdirs();
        StreamTextFile.saveTextFile(LANGUAGE, lg.export(),p.getStreams());
        LaunchingApplications la = new LaunchingApplications(new WithAppFactories(p,new AppFactories(new AikiFactory(p, executor(), executor()),new CardFactories(p, executor(), executor()),new CdmFactory(p,new MockInterceptor()))));
        la.loadLanguage(TEMP_FOLDER,new String[]{ARG});

    }

    @Test
    public void rtsBut() {
        MockProgramInfos p = build();
        p.setLanguages(new StringList(EN));
        p.getFileCoreStream().newFile(TEMP_FOLDER).mkdirs();
        FullDocument fullDocument = DocumentBuilder.newDocumentBuilder().newDocument();
        fullDocument.appendChild(fullDocument.createElement("_"));
        StreamTextFile.saveTextFile(ARG, fullDocument.export(),p.getStreams());
        FullDocument lg = DocumentBuilder.newDocumentBuilder().newDocument();
        Element elt_ = lg.createElement("_");
        Element locale = lg.createElement(LOCALE);
        locale.setAttribute(LOCALE, EN);
        elt_.appendChild(locale);
        lg.appendChild(elt_);
        StreamTextFile.saveTextFile(LANGUAGE, lg.export(),p.getStreams());
        LaunchingApplications la = new LaunchingApplications(new WithAppFactories(p,new AppFactories(new AikiFactory(p, executor(), executor()),new CardFactories(p, executor(), executor()),new CdmFactory(p,new MockInterceptor()))));
        la.loadLanguage(TEMP_FOLDER,new String[]{});
        ((WindowApps)p.getFrames().get(0)).getButtonDemo().getActionListeners().get(0).action();
        p.getFrames().get(1).getCommonFrame().getWindowListenersDef().get(0).windowClosing();
        ((WindowApps)p.getFrames().get(0)).getButtonDemo().getActionListeners().get(0).action();
        System.out.println(p.getFrames().size());
    }
    @Test
    public void pkBut() {
        MockProgramInfos p = build();
        TranslationsLg en_ = p.lg(EN);
        p.setLanguage(EN);
        GamesPk.enTr(GamesPk.initAppliTr(en_));
        p.setLanguages(new StringList(EN));
        p.getFileCoreStream().newFile(TEMP_FOLDER).mkdirs();
        DataBase res_ = InitDbValid2.initDb();
        res_.getMap().initializeLinks();
        res_.getMap().initInteractiveElements();
        res_.getMap().initializeTree();
        res_.getMap().initializeAccessibility();
        FacadeGame f_ = new FacadeGame();
        f_.setData(res_);
        f_.setLanguages(new StringList(EN));
        f_.setSimplyLanguage(EN);
        f_.setSexList(new MockLSexList());
        DefDataBaseStream ins_ = new DefDataBaseStream();
        LoadingGame loadingGame_ = new LoadingGame();
        loadingGame_.setExport(EXPORT);
        ins_.exportRom(p,f_, loadingGame_);

        Game g_ = new Game(res_);
        g_.initUserInteract("_", Sex.NO, g_.getDifficulty(), res_);
        g_.setZippedRom(EXPORT);
        StreamTextFile.saveTextFile(ARG, DocumentWriterAikiCoreUtil.setGame(g_),p.getStreams());



        FullDocument lg = DocumentBuilder.newDocumentBuilder().newDocument();
        Element elt_ = lg.createElement("_");
        Element locale = lg.createElement(LOCALE);
        locale.setAttribute(LOCALE, EN);
        elt_.appendChild(locale);
        lg.appendChild(elt_);
        StreamTextFile.saveTextFile(LANGUAGE, lg.export(),p.getStreams());
        LaunchingApplications la = new LaunchingApplications(new WithAppFactories(p,new AppFactories(new AikiFactory(p, executor(), executor()),new CardFactories(p, executor(), executor()),new CdmFactory(p,new MockInterceptor()))));
        la.loadLanguage(TEMP_FOLDER,new String[]{});
        ((WindowApps)p.getFrames().get(0)).getButtonPokemon().getActionListeners().get(0).action();
        ((WindowAiki)p.getFrames().get(1)).getFacade().setSexList(f_.getSexList());
        ((MockThreadFactory)p.getThreadFactory()).getAllThreads().get(0).join();
    }
    @Test
    public void rendBut() {
        MockProgramInfos p = build();
        TranslationsLg en_ = p.lg(EN);
        FileInfos.enTr(FileInfos.initComments(en_));
        p.setLanguages(new StringList(EN));
        p.setLanguage(EN);
        String xmlConf_ = "<cfg>\n" +
                "\t<java.lang.String field='firstUrl' value='page.html'/>\n" +
                "\t<java.lang.String field='prefix' value='c'/>\n" +
                "\t<sm field='navigation'>\n" +
                "\t\t<java.lang.String key='' value='bean_one.method'/>\n" +
                "\t\t<sm>\n" +
                "\t\t\t<java.lang.String key='' value='res'/>\n" +
                "\t\t\t<java.lang.String value='page2.html'/>\n" +
                "\t\t</sm>\n" +
                "\t</sm>\n" +
                "\t<n field=\"context\">\n" +
                "\t<java.lang.Integer field='tabWidth' value='4'/>\n" +
                "\t<sm field='styleValues' value='StyleValueRgb=___'/>\n" +
                "\t</n>\n" +
                "\t<java.lang.Integer field='tabWidth' value='4'/>\n" +
                "\t<java.lang.String field='messagesFolder' value='messages'/>\n" +
                "\t<java.lang.String field='filesConfName' value='conf_cl.txt'/>\n" +
                "\t<sm field='beans'>\n" +
                "\t\t<java.lang.String key='' value='bean_one'/>\n" +
                "\t\t<b>\n" +
                "\t\t\t<java.lang.String field='scope' value='session'/>\n" +
                "\t\t\t<java.lang.String field='className' value='pkg.BeanOne'/>\n" +
                "\t\t</b>\n" +
                "\t</sm>\n" +
                "\t<sm field='properties'>\n" +
                "\t\t<java.lang.String key='' value='msg_cust'/>\n" +
                "\t\t<java.lang.String value='sample/file'/>\n" +
                "\t</sm>\n" +
                "\t<sl field='addedFiles'>\n" +
                "\t\t<str value='page.html'/>\n" +
                "\t</sl>\n" +
                "\t<sl field='renderFiles'>\n" +
                "\t\t<str value='page.html'/>\n" +
                "\t</sl>\n" +
                "\t<sm field='lateValidators'>\n" +
                "\t\t<str key='' value='my_val'/>\n" +
                "\t\t<str value='pkg.MyVal'/>\n" +
                "\t</sm>\n" +
                "</cfg>";
        StringMap<ContentTime> cont_ = with(p, with(p, with(p, init(), "conf.txt", "content"), "src/"), "src/folder/");
        StringMap<ContentTime> contConf_ = with(p,cont_,"conf_cl.txt","src/folder/file.txt");
        StringMap<ContentTime> contRend_ = with(p,contConf_,"page.html","<html><body>_</body></html>");
        StringMap<ContentTime> content_ = with(p, contRend_, "src/folder/file.txt", "public class cl.Init{public static Object init(String[] names, String[] contents){return new String[0];}}");
        StringMap<ContentTime> contents_ = with(p, content_, "conf.xml", xmlConf_);
        byte[] zipped_ = p.getZipFact().zipBinFiles(contents_);
        StreamBinaryFile.writeFile("/_.zip",zipped_,p.getStreams());
        StreamTextFile.saveTextFile(ARG,"/_.zip\nconf.xml\ninitDb=cl.Init.init\nen", p.getStreams());
        FullDocument lg = DocumentBuilder.newDocumentBuilder().newDocument();
        Element elt_ = lg.createElement("_");
        Element locale = lg.createElement(LOCALE);
        locale.setAttribute(LOCALE, EN);
        elt_.appendChild(locale);
        lg.appendChild(elt_);
        p.getFileCoreStream().newFile(TEMP_FOLDER).mkdirs();
        StreamTextFile.saveTextFile(LANGUAGE, lg.export(),p.getStreams());
        LaunchingApplications la = new LaunchingApplications(new WithAppFactories(p,new AppFactories(new AikiFactory(p, executor(), executor()),new CardFactories(p, executor(), executor()),new CdmFactory(p,new MockInterceptor()))));
        la.loadLanguage(TEMP_FOLDER,new String[]{});
        ((WindowApps)p.getFrames().get(0)).getButtonRenders().getActionListeners().get(0).action();
        System.out.println(p.getFrames().size());
    }

    @Test
    public void wuBut() {
        MockProgramInfos p = build();
        TranslationsLg en_ = p.lg(EN);
        FileInfos.enTr(FileInfos.initComments(en_));
        p.setLanguages(new StringList(EN));
        p.setLanguage(EN);
        byte[] zipped_ = p.getZipFact().zipBinFiles(with(p,  with(p,with(p,with(p, init(), "conf.txt", "content"),"src/"),"src/folder/"),"src/folder/file.txt","public class pkg.Sample{@Test public void err(){Assert.assert(0,1);}@Test public void success(){Assert.assert(1,1);}}"));
        StreamBinaryFile.writeFile("/_.zip",zipped_,p.getStreams());
        StreamTextFile.saveTextFile(ARG,"/_.zip\nen\ntabWidth=4", p.getStreams());
        FullDocument lg = DocumentBuilder.newDocumentBuilder().newDocument();
        Element elt_ = lg.createElement("_");
        Element locale = lg.createElement(LOCALE);
        locale.setAttribute(LOCALE, EN);
        elt_.appendChild(locale);
        lg.appendChild(elt_);
        p.getFileCoreStream().newFile(TEMP_FOLDER).mkdirs();
        StreamTextFile.saveTextFile(LANGUAGE, lg.export(),p.getStreams());
        LaunchingApplications la = new LaunchingApplications(new WithAppFactories(p,new AppFactories(new AikiFactory(p, executor(), executor()),new CardFactories(p, executor(), executor()),new CdmFactory(p,new MockInterceptor()))));
        la.loadLanguage(TEMP_FOLDER,new String[]{});
        ((WindowApps)p.getFrames().get(0)).getButtonTests().getActionListeners().get(0).action();
        System.out.println(p.getFrames().size());
    }
    @Test
    public void wfBut() {
        MockProgramInfos p = build();
        TranslationsLg en_ = p.lg(EN);
        FileInfos.enTr(FileInfos.initComments(en_));
        p.setLanguages(new StringList(EN));
        p.setLanguage(EN);
        byte[] zipped_ = p.getZipFact().zipBinFiles(with(p,  with(p,with(p,with(p, init(), "conf.txt", "content"),"src/"),"src/folder/"),"src/folder/file.txt","public class pkg.Sample{public static void m(){}@Test public void err(){Assert.assert(0,1);}@Test public void success(){Assert.assert(1,1);}}"));
        StreamBinaryFile.writeFile("/_.zip",zipped_,p.getStreams());
        StreamTextFile.saveTextFile(ARG,"/_.zip\nen\nmain=pkg.Sample.m\ncover=\nargs=", p.getStreams());
        FullDocument lg = DocumentBuilder.newDocumentBuilder().newDocument();
        Element elt_ = lg.createElement("_");
        Element locale = lg.createElement(LOCALE);
        locale.setAttribute(LOCALE, EN);
        elt_.appendChild(locale);
        lg.appendChild(elt_);
        p.getFileCoreStream().newFile(TEMP_FOLDER).mkdirs();
        StreamTextFile.saveTextFile(LANGUAGE, lg.export(),p.getStreams());
        LaunchingApplications la = new LaunchingApplications(new WithAppFactories(p,new AppFactories(new AikiFactory(p, executor(), executor()),new CardFactories(p, executor(), executor()),new CdmFactory(p,new MockInterceptor()))));
        la.loadLanguage(TEMP_FOLDER,new String[]{});
        ((WindowApps)p.getFrames().get(0)).getButtonApps().getActionListeners().get(0).action();
        System.out.println(p.getFrames().size());
    }
    @Test
    public void cBut() {
        MockProgramInfos p = build();
        TranslationsLg en_ = p.lg(EN);
        Games.enTr(Games.initAppliTr(en_));
        maxiImgs(p);
        p.setLanguages(new StringList(EN));
        p.setLanguage(EN);
        FullDocument lg = DocumentBuilder.newDocumentBuilder().newDocument();
        Element elt_ = lg.createElement("_");
        Element locale = lg.createElement(LOCALE);
        locale.setAttribute(LOCALE, EN);
        elt_.appendChild(locale);
        lg.appendChild(elt_);
        p.getFileCoreStream().newFile(TEMP_FOLDER).mkdirs();
        StreamTextFile.saveTextFile(LANGUAGE, lg.export(),p.getStreams());
        LaunchingApplications la = new LaunchingApplications(new WithAppFactories(p,new AppFactories(new AikiFactory(p, executor(), executor()),new CardFactories(p, executor(), executor()),new CdmFactory(p,new MockInterceptor()))));
        la.loadLanguage(TEMP_FOLDER,new String[]{});
        ((WindowApps)p.getFrames().get(0)).getButtonCards().getActionListeners().get(0).action();
        System.out.println(p.getFrames().size());
    }
    @Test
    public void imgsBut() {
        MockProgramInfos p = build();
        TranslationsLg en_ = p.lg(EN);
        p.setLanguages(new StringList(EN));
        p.setLanguage(EN);
        updateBase(p.currentLg());
        p.getFileCoreStream().newFile("/from/one").mkdirs();
        p.getFileCoreStream().newFile("/from/one/sub1").mkdirs();
        p.getFileCoreStream().newFile("/from/one/sub2").mkdirs();
        p.getFileCoreStream().newFile("/from/two").mkdirs();
        p.getFileCoreStream().newFile("/from/two/sub1").mkdirs();
        p.getFileCoreStream().newFile("/from/two/sub2").mkdirs();
        StreamBinaryFile.writeFile("/from/one/sub1/1",new byte[0],p.getStreams());
        StreamBinaryFile.writeFile("/from/one/sub1/2",toBinary(new int[][]{new int[]{1,2},new int[]{3,4}}),p.getStreams());
        StreamBinaryFile.writeFile("/from/one/sub2/1",new byte[0],p.getStreams());
        StreamBinaryFile.writeFile("/from/one/sub2/2",toBinary(new int[][]{new int[]{1,2},new int[]{3,4},new int[]{5,6}}),p.getStreams());
        StreamBinaryFile.writeFile("/from/two/sub1/1",new byte[0],p.getStreams());
        StreamBinaryFile.writeFile("/from/two/sub1/2",toBinary(new int[][]{new int[]{1,2,3},new int[]{4,5,6}}),p.getStreams());
        StreamBinaryFile.writeFile("/from/two/sub2/1",new byte[0],p.getStreams());
        StreamBinaryFile.writeFile("/from/two/sub2/2",toBinary(new int[][]{new int[]{1,2,3},new int[]{4,5,6},new int[]{7,8,9}}),p.getStreams());
        FullDocument d_ = DocumentBuilder.newDocumentBuilder().newDocument();
        Element eltExp_ = d_.createElement(DocumentImagesUtil.ROOT_CONF);
        eltExp_.setAttribute(DocumentImagesUtil.INFO_IMP,"/from");
        eltExp_.setAttribute(DocumentImagesUtil.INFO_EXP,"/to");
        d_.appendChild(eltExp_);
        StreamTextFile.saveTextFile(ARG,d_.export(),p.getStreams());
        FullDocument lg = DocumentBuilder.newDocumentBuilder().newDocument();
        Element elt_ = lg.createElement("_");
        Element locale = lg.createElement(LOCALE);
        locale.setAttribute(LOCALE, EN);
        elt_.appendChild(locale);
        lg.appendChild(elt_);
        p.getFileCoreStream().newFile(TEMP_FOLDER).mkdirs();
        StreamTextFile.saveTextFile(LANGUAGE, lg.export(),p.getStreams());
        LaunchingApplications la = new LaunchingApplications(new WithAppFactories(p,new AppFactories(new AikiFactory(p, executor(), executor()),new CardFactories(p, executor(), executor()),new CdmFactory(p,new MockInterceptor()))));
        la.loadLanguage(TEMP_FOLDER,new String[]{});
        ((WindowApps)p.getFrames().get(0)).getButtonConverter().getActionListeners().get(0).action();
        System.out.println(p.getFrames().size());
    }
    @Test
    public void soundBut() {
        MockProgramInfos p = build();
        p.setLanguages(new StringList(EN));
        p.setLanguage(EN);
        FullDocument d_ = DocumentBuilder.newDocumentBuilder().newDocument();
        Element r_ = d_.createElement(WindowPlayer.SMIL);
        Element s1_ = d_.createElement(WindowPlayer.CST_MEDIA);
        s1_.setAttribute(WindowPlayer.CST_SRC,"file1");
        r_.appendChild(s1_);
        Element s2_ = d_.createElement(WindowPlayer.CST_MEDIA);
        s2_.setAttribute(WindowPlayer.CST_SRC,"file2");
        r_.appendChild(s2_);
        d_.appendChild(r_);
        StreamBinaryFile.writeFile(ARG, StringUtil.encode(d_.export()),p.getStreams());
        StreamBinaryFile.writeFile("file1",wrapInts('R', 'I', 'F', 'F', 0, 0, 0, 0, 'W', 'A', 'V', 'e', 1),p.getStreams());
        StreamBinaryFile.writeFile("file2",wrapInts('R', 'I', 'F', 'F', 0, 0, 0, 0, 'W', 'A', 'V', 'E', 2),p.getStreams());
        FullDocument lg = DocumentBuilder.newDocumentBuilder().newDocument();
        Element elt_ = lg.createElement("_");
        Element locale = lg.createElement(LOCALE);
        locale.setAttribute(LOCALE, EN);
        elt_.appendChild(locale);
        lg.appendChild(elt_);
        p.getFileCoreStream().newFile(TEMP_FOLDER).mkdirs();
        StreamTextFile.saveTextFile(LANGUAGE, lg.export(),p.getStreams());
        LaunchingApplications la = new LaunchingApplications(new WithAppFactories(p,new AppFactories(new AikiFactory(p, executor(), executor()),new CardFactories(p, executor(), executor()),new CdmFactory(p,new MockInterceptor()))));
        la.loadLanguage(TEMP_FOLDER,new String[]{});
        ((WindowApps)p.getFrames().get(0)).getButtonPlayer().getActionListeners().get(0).action();
        System.out.println(p.getFrames().size());

    }
    @Test
    public void netBut() {
        MockProgramInfos p = build();
        TranslationsLg en_ = p.lg(EN);
        Games.enTr(Games.initAppliTr(en_));
        GamesPk.enTr(GamesPk.initAppliTr(en_));
        NetWork.enTr(NetWork.initAppliTr(en_));
        p.setLanguages(new StringList(EN));
        p.setLanguage(EN);
        updateBase(p.currentLg());
        p.setLanguages(new StringList(EN));
        p.setLanguage(EN);
        FullDocument lg = DocumentBuilder.newDocumentBuilder().newDocument();
        Element elt_ = lg.createElement("_");
        Element locale = lg.createElement(LOCALE);
        locale.setAttribute(LOCALE, EN);
        elt_.appendChild(locale);
        lg.appendChild(elt_);
        p.getFileCoreStream().newFile(TEMP_FOLDER).mkdirs();
        StreamTextFile.saveTextFile(LANGUAGE, lg.export(),p.getStreams());
        LaunchingApplications la = new LaunchingApplications(new WithAppFactories(p,new AppFactories(new AikiFactory(p, executor(), executor()),new CardFactories(p, executor(), executor()),new CdmFactory(p,new MockInterceptor()))));
        la.loadLanguage(TEMP_FOLDER,new String[]{});
        ((WindowApps)p.getFrames().get(0)).getButtonNet().getActionListeners().get(0).action();
        System.out.println(p.getFrames().size());

    }
    @Test
    public void rtsLg1() {
        MockProgramInfos p = build();
        p.setLanguages(new StringList(EN));
        p.getFileCoreStream().newFile(TEMP_FOLDER).mkdirs();
        FullDocument fullDocument = DocumentBuilder.newDocumentBuilder().newDocument();
        fullDocument.appendChild(fullDocument.createElement("_"));
        StreamTextFile.saveTextFile(ARG, fullDocument.export(),p.getStreams());
        LaunchingApplications la = new LaunchingApplications(new WithAppFactories(p,new AppFactories(new AikiFactory(p, executor(), executor()),new CardFactories(p, executor(), executor()),new CdmFactory(p,new MockInterceptor()))));
        la.loadLanguage(TEMP_FOLDER,new String[]{ARG});
        la.getLanguageFrame().changeLanguage(EN);
        System.out.println(p.getFrames().size());
        la.getLanguageFrame().getLanguage();
//        ((MockCompoFactory)p.getCompoFactory()).invoke();
    }
    @Test
    public void rtsLg2() {
        MockProgramInfos p = build();
        p.setLanguages(new StringList(EN));
        p.getFileCoreStream().newFile(TEMP_FOLDER).mkdirs();
        FullDocument fullDocument = DocumentBuilder.newDocumentBuilder().newDocument();
        fullDocument.appendChild(fullDocument.createElement("_"));
        StreamTextFile.saveTextFile(ARG, fullDocument.export(),p.getStreams());
        LaunchingApplications la = new LaunchingApplications(new WithAppFactories(p,new AppFactories(new AikiFactory(p, executor(), executor()),new CardFactories(p, executor(), executor()),new CdmFactory(p,new MockInterceptor()))));
        la.loadLanguage(TEMP_FOLDER,new String[]{ARG});
        la.getLanguageFrame().getCommonFrame().getWindowListenersDef().get(0).windowClosing();
        System.out.println(p.getFrames().size());
//        ((MockCompoFactory)p.getCompoFactory()).invoke();
    }
    public static byte[] wrapInts(int... _files) {
        return Ints.newList(_files).toArrByte();
    }
    private static byte[] toBinary(int[][] _img) {
        AbstractImage img_ =  new MockImage(_img);
        Bytes bs_ = Bytes.newList((byte)0x89,(byte)0x50,(byte)0x4E,(byte)0x47,(byte)0x0D,(byte)0x0A,(byte)0x1A,(byte)0x0A);
        bs_.addAllElts(Bytes.newList(img_.writeImg("")));
        return bs_.toArrByte();
    }
    private static void maxiImgs(MockProgramInfos _pr) {
        StringMap<int[][]> mini_ = def();
        _pr.getTranslations().getMapping().getVal(EN).getMaxiCards().addAllEntries(mini_);
        _pr.getTranslations().getMapping().getVal(EN).getMiniCardsDef().addAllEntries(mini_);
//        _pr.getTranslations().getMapping().getVal(FR).getMaxiCards().addAllEntries(mini_);
//        _pr.getTranslations().getMapping().getVal(FR).getMiniCardsDef().addAllEntries(mini_);
    }
    private GameBelote edited(DealBelote _deal, RulesBelote _rules) {
        GameBelote g_ = new GameBelote(GameType.EDIT, _deal, _rules);
        g_.setNombre();
        return g_;
    }
    private GamePresident edited(DealPresident _deal, RulesPresident _rules) {
        GamePresident g_ = new GamePresident(GameType.EDIT, _deal, _rules,Bytes.newList());
        g_.setNombre();
        return g_;
    }

    private GameTarot edited(DealTarot _deal, RulesTarot _rules) {
        GameTarot g_ = new GameTarot(GameType.EDIT, _deal, _rules);
        g_.setNombre();
        return g_;
    }
    private BidBeloteSuit bidSuit(Suit _suit, int _pts, BidBelote _bid) {
        BidBeloteSuit suit_ = new BidBeloteSuit();
        suit_.setSuit(_suit);
        suit_.setPoints(_pts);
        suit_.setBid(_bid);
        return suit_;
    }
//    private void nextBid(MockGameBelote _m, BidBeloteSuit _bid) {
//        _m.getBids().add(_bid);
//        //        return _sort.getNextPlayer((byte) _pl);
//    }
//
//    private void nextSlam(MockGameBelote _m, BoolVal _bid) {
//        _m.getSlams().add(_bid);
//    }
//    private void nextDiscard(MockGameBelote _m, CardBelote _bid) {
//        _m.getDiscard().add(_bid);
//    }
//    private void nextDiscardIa(MockGameBelote _m, CardBelote... _bid) {
//        _m.getDiscardIa().add(create(_bid));
//    }
//
//    private void nextCard(MockGameBelote _m, CardBelote _bid) {
//        _m.getCards().add(_bid);
//        //        return _sort.getNextPlayer((byte) _pl);
//    }

    private DealPresident mix(int _d) {
        return new DealPresident(deal1(), (byte) _d);
    }
    private RulesBelote rulesThreePlayers() {
        RulesBelote rules_ = new RulesBelote();
        rules_.setDealing(DealingBelote.CLASSIC_1_VS_2);
        rules_.getCommon().setNbDeals(1);
        rules_.getCommon().setMixedCards(MixCardsChoice.NEVER);
        return rules_;
    }

    private DealBelote dealThreePlayersIa() {
        DealBelote db_ = new DealBelote();
        db_.setDealer((byte) 1);
        db_.getDeal().add(create(CardBelote.HEART_KING,CardBelote.HEART_QUEEN,CardBelote.SPADE_10,
                CardBelote.CLUB_10,CardBelote.SPADE_9,CardBelote.CLUB_7,CardBelote.HEART_8,CardBelote.HEART_7));
        db_.getDeal().add(create(CardBelote.DIAMOND_KING,CardBelote.DIAMOND_QUEEN,CardBelote.DIAMOND_JACK,CardBelote.SPADE_JACK,
                CardBelote.CLUB_JACK,CardBelote.SPADE_8,CardBelote.SPADE_7,CardBelote.DIAMOND_9));
        db_.getDeal().add(create(CardBelote.HEART_JACK,CardBelote.HEART_9,CardBelote.SPADE_KING,CardBelote.SPADE_QUEEN,
                CardBelote.DIAMOND_10,CardBelote.DIAMOND_7,CardBelote.DIAMOND_8,CardBelote.HEART_10));
        db_.getDeal().add(create(CardBelote.CLUB_KING,CardBelote.CLUB_QUEEN,CardBelote.CLUB_9,CardBelote.CLUB_8,
                CardBelote.CLUB_1,CardBelote.HEART_1,CardBelote.DIAMOND_1,CardBelote.SPADE_1));
        return db_;
    }

    static CustList<HandPresident> deal1() {
        CustList<HandPresident> hs_ = new CustList<HandPresident>();
        HandPresident h_;
        h_ = new HandPresident();
        h_.ajouter(CardPresident.CLUB_3);
        h_.ajouter(CardPresident.CLUB_4);
        h_.ajouter(CardPresident.DIAMOND_4);
        h_.ajouter(CardPresident.SPADE_7);
        h_.ajouter(CardPresident.DIAMOND_8);
        h_.ajouter(CardPresident.HEART_8);
        h_.ajouter(CardPresident.CLUB_9);
        h_.ajouter(CardPresident.SPADE_10);
        h_.ajouter(CardPresident.CLUB_JACK);
        h_.ajouter(CardPresident.SPADE_JACK);
        h_.ajouter(CardPresident.SPADE_KING);
        h_.ajouter(CardPresident.DIAMOND_1);
        h_.ajouter(CardPresident.HEART_2);
        hs_.add(h_);
        h_ = new HandPresident();
        h_.ajouter(CardPresident.SPADE_3);
        h_.ajouter(CardPresident.SPADE_4);
        h_.ajouter(CardPresident.HEART_4);
        h_.ajouter(CardPresident.CLUB_7);
        h_.ajouter(CardPresident.SPADE_8);
        h_.ajouter(CardPresident.CLUB_8);
        h_.ajouter(CardPresident.SPADE_9);
        h_.ajouter(CardPresident.CLUB_10);
        h_.ajouter(CardPresident.HEART_JACK);
        h_.ajouter(CardPresident.DIAMOND_JACK);
        h_.ajouter(CardPresident.CLUB_KING);
        h_.ajouter(CardPresident.HEART_1);
        h_.ajouter(CardPresident.DIAMOND_2);
        hs_.add(h_);
        h_ = new HandPresident();
        h_.ajouter(CardPresident.HEART_3);
        h_.ajouter(CardPresident.SPADE_5);
        h_.ajouter(CardPresident.HEART_5);
        h_.ajouter(CardPresident.SPADE_6);
        h_.ajouter(CardPresident.CLUB_6);
        h_.ajouter(CardPresident.HEART_7);
        h_.ajouter(CardPresident.HEART_9);
        h_.ajouter(CardPresident.HEART_10);
        h_.ajouter(CardPresident.SPADE_QUEEN);
        h_.ajouter(CardPresident.CLUB_QUEEN);
        h_.ajouter(CardPresident.HEART_KING);
        h_.ajouter(CardPresident.SPADE_2);
        h_.ajouter(CardPresident.CLUB_2);
        hs_.add(h_);
        h_ = new HandPresident();
        h_.ajouter(CardPresident.DIAMOND_3);
        h_.ajouter(CardPresident.CLUB_5);
        h_.ajouter(CardPresident.DIAMOND_5);
        h_.ajouter(CardPresident.HEART_6);
        h_.ajouter(CardPresident.DIAMOND_6);
        h_.ajouter(CardPresident.DIAMOND_7);
        h_.ajouter(CardPresident.DIAMOND_9);
        h_.ajouter(CardPresident.DIAMOND_10);
        h_.ajouter(CardPresident.HEART_QUEEN);
        h_.ajouter(CardPresident.DIAMOND_QUEEN);
        h_.ajouter(CardPresident.DIAMOND_KING);
        h_.ajouter(CardPresident.SPADE_1);
        h_.ajouter(CardPresident.CLUB_1);
        hs_.add(h_);
        return hs_;
    }

    private static DealTarot deal1(int _dealer) {
        CustList<HandTarot> hands_ = new CustList<HandTarot>();
        HandTarot hand_;
        hand_ = new HandTarot();
        hand_.ajouter(CardTarot.TRUMP_1);
        hand_.ajouter(CardTarot.TRUMP_4);
        hand_.ajouter(CardTarot.TRUMP_10);
        hand_.ajouter(CardTarot.TRUMP_14);
        hand_.ajouter(CardTarot.TRUMP_17);
        hand_.ajouter(CardTarot.TRUMP_21);
        hand_.ajouter(CardTarot.HEART_KING);
        hand_.ajouter(CardTarot.HEART_7);
        hand_.ajouter(CardTarot.HEART_1);
        hand_.ajouter(CardTarot.SPADE_QUEEN);
        hand_.ajouter(CardTarot.SPADE_10);
        hand_.ajouter(CardTarot.SPADE_4);
        hand_.ajouter(CardTarot.CLUB_6);
        hand_.ajouter(CardTarot.DIAMOND_JACK);
        hand_.ajouter(CardTarot.DIAMOND_2);
        hands_.add(hand_);
        hand_ = new HandTarot();
        hand_.ajouter(CardTarot.TRUMP_3);
        hand_.ajouter(CardTarot.TRUMP_6);
        hand_.ajouter(CardTarot.TRUMP_13);
        hand_.ajouter(CardTarot.TRUMP_16);
        hand_.ajouter(CardTarot.HEART_QUEEN);
        hand_.ajouter(CardTarot.HEART_8);
        hand_.ajouter(CardTarot.HEART_4);
        hand_.ajouter(CardTarot.SPADE_KING);
        hand_.ajouter(CardTarot.SPADE_KNIGHT);
        hand_.ajouter(CardTarot.SPADE_JACK);
        hand_.ajouter(CardTarot.CLUB_10);
        hand_.ajouter(CardTarot.CLUB_5);
        hand_.ajouter(CardTarot.CLUB_4);
        hand_.ajouter(CardTarot.DIAMOND_7);
        hand_.ajouter(CardTarot.DIAMOND_6);
        hands_.add(hand_);
        hand_ = new HandTarot();
        hand_.ajouter(CardTarot.TRUMP_2);
        hand_.ajouter(CardTarot.TRUMP_8);
        hand_.ajouter(CardTarot.TRUMP_12);
        hand_.ajouter(CardTarot.EXCUSE);
        hand_.ajouter(CardTarot.HEART_9);
        hand_.ajouter(CardTarot.HEART_3);
        hand_.ajouter(CardTarot.HEART_2);
        hand_.ajouter(CardTarot.SPADE_5);
        hand_.ajouter(CardTarot.SPADE_2);
        hand_.ajouter(CardTarot.SPADE_1);
        hand_.ajouter(CardTarot.CLUB_9);
        hand_.ajouter(CardTarot.CLUB_KNIGHT);
        hand_.ajouter(CardTarot.CLUB_7);
        hand_.ajouter(CardTarot.DIAMOND_KNIGHT);
        hand_.ajouter(CardTarot.DIAMOND_1);
        hands_.add(hand_);
        hand_ = new HandTarot();
        hand_.ajouter(CardTarot.TRUMP_5);
        hand_.ajouter(CardTarot.TRUMP_9);
        hand_.ajouter(CardTarot.TRUMP_15);
        hand_.ajouter(CardTarot.HEART_KNIGHT);
        hand_.ajouter(CardTarot.HEART_JACK);
        hand_.ajouter(CardTarot.HEART_10);
        hand_.ajouter(CardTarot.SPADE_8);
        hand_.ajouter(CardTarot.SPADE_3);
        hand_.ajouter(CardTarot.CLUB_QUEEN);
        hand_.ajouter(CardTarot.CLUB_JACK);
        hand_.ajouter(CardTarot.CLUB_8);
        hand_.ajouter(CardTarot.DIAMOND_5);
        hand_.ajouter(CardTarot.DIAMOND_8);
        hand_.ajouter(CardTarot.DIAMOND_9);
        hand_.ajouter(CardTarot.DIAMOND_3);
        hands_.add(hand_);
        hand_ = new HandTarot();
        hand_.ajouter(CardTarot.TRUMP_11);
        hand_.ajouter(CardTarot.TRUMP_18);
        hand_.ajouter(CardTarot.TRUMP_20);
        hand_.ajouter(CardTarot.HEART_6);
        hand_.ajouter(CardTarot.HEART_5);
        hand_.ajouter(CardTarot.SPADE_9);
        hand_.ajouter(CardTarot.SPADE_7);
        hand_.ajouter(CardTarot.SPADE_6);
        hand_.ajouter(CardTarot.DIAMOND_KING);
        hand_.ajouter(CardTarot.DIAMOND_QUEEN);
        hand_.ajouter(CardTarot.DIAMOND_10);
        hand_.ajouter(CardTarot.CLUB_KING);
        hand_.ajouter(CardTarot.CLUB_3);
        hand_.ajouter(CardTarot.CLUB_2);
        hand_.ajouter(CardTarot.CLUB_1);
        hands_.add(hand_);
        hand_ = new HandTarot();
        hand_.ajouter(CardTarot.TRUMP_19);
        hand_.ajouter(CardTarot.TRUMP_7);
        hand_.ajouter(CardTarot.DIAMOND_4);
        hands_.add(hand_);
        return new DealTarot(hands_, (byte) _dealer);
    }
    private RulesTarot rules() {
        RulesTarot rules_ = new RulesTarot();
        rules_.getCommon().setNbDeals(1);
        rules_.getCommon().setMixedCards(MixCardsChoice.NEVER);
        return rules_;
    }
    private HandBelote create(CardBelote... _cb) {
        return HandBelote.create(_cb);
    }
    public static AbstractThread tryAn(MockThreadFactory _g) {
//        assertEq(1, _g.getAllThreads().size());
        AbstractThread th_ = _g.getAllThreads().get(0);
        _g.getAllThreads().remove(0);
        th_.join();
//        checkNoAnim(_g);
        return th_;
    }

    public static StringMap<ContentTime> init() {
        return new StringMap<ContentTime>();
    }
    public static StringMap<ContentTime> with(AbstractLightProgramInfos _light, StringMap<ContentTime> _all, String _name, String _content) {
        _all.put(_name,new ContentTime(StringUtil.encode(_content),_light.getThreadFactory().millis()));
        return _all;
    }
    public static StringMap<ContentTime> with(AbstractLightProgramInfos _light, StringMap<ContentTime> _all, String _name) {
        _all.put(_name,new ContentTime(null,_light.getThreadFactory().millis()));
        return _all;
    }
    public static void updateBase(TranslationsLg _en) {
        StringMap<TranslationsFile> en_ = FileFrame.initAppliTr(_en).getMapping();
        en_.addEntry(FileFrame.FILE_DIAL, MessagesFileDialog.en());
        en_.addEntry(FileFrame.CONFIRM, MessagesConfirmDialog.en());
        en_.addEntry(FolderOpenFrame.FOLDER_OPEN_DIAL, MessagesFolderOpenDialog.en());
        en_.addEntry(FileOpenFrame.FILE_OPEN_DIAL,MessagesFileOpenDialog.en());
        en_.addEntry(FileSaveFrame.FILE_SAVE_DIAL,MessagesFileSaveDialog.en());
        en_.addEntry(FileTable.FILE_TAB,MessagesFileTable.en());
    }
    public static MockProgramInfos build() {
        return build("", "",dbs(0.75));
    }
    public static MockProgramInfos build(String _h, String _t, double[] _dbs) {
        MockProgramInfos pr_ = MockProgramInfos.inst(_h, _t, new CustomSeedGene(_dbs), new MockFileSet(0, new long[1], new String[]{"/"}));
        pr_.setLanguage(EN);
        return pr_;
    }

    public static double[] dbs(double... _args) {
        return _args;
    }
    private static <T> AbstractBaseExecutorServiceParam<T> executor() {
        return new MockBaseExecutorServiceParam<>();
    }


    public static abstract class InitDbValid2 {
        public static final String MINI6 = "mini6";
        public static final String MINI5 = "mini5";
        public static final String MINI4 = "mini4";
        public static final String MINI3 = "mini3";
        public static final String MINI2 = "mini2";
        public static final String MINI1 = "mini1";
        public static final String MINI = "mini";
        public static final String PIKACHU ="PIKACHU";
        public static final String PROG_PK2="PK_2";
        public static final String LANGUAGE = EN;
        public static final String ECLAIR = "ECLAIR";
        public static final String ECLAIR_2 = "ECLAIR2";
        public static final String ECLAIR_3 = "ECLAIR3";
        public static final String PARATONNERRE = "PARATONNERRE";
        public static final String ELECTRICK = "ELECTRICK";
        public static final String POKE_BALL = "POKE_BALL";
        public static final String ALLY = "ally";
        public static final String SNOW = "snow";
        public static final String GRASS = "grass";
        public static final String DAFAULT = "dafault";
        public static final String GERANT = "gerant";
        public static final String LINK = "link";
        public static final String TRAINER_TWO = "trainer_two";
        public static final String TRAINER_ONE = "trainer_one";
        public static final String PERSON = "person";
        public static final String TRAINER = "trainer";
        public static final String DEFAULT = "default";
        public static final String NOTHING = "nothing";
        public static final String DESERT = "desert";
        public static final String ROCK = "rock";
        public static final String WATER = "water";
        public static final String ROAD = "road";
        public static final String BUILDING = "building";
        public static final String NULL_REF = DataBase.EMPTY_STRING;
        public static final String TAB = "\t";
        public static DataBase initDb() {
            DataBase data_ = coreDataBase();
            data_.sortEndRound();
            data_.getMap().setMiniMap(new MiniMapCoordsList());
            data_.getMap().setUnlockedCity(NULL_REF);
            data_.getMap().setSideLength(1);
            data_.addLink(LINK, new int[][]{new int[]{-255}});
            data_.setImageTmHm(new int[][]{new int[]{-800}});
            data_.setAnimAbsorb(new int[][]{new int[]{-700}});
            data_.setStorage(new int[][]{new int[]{-3}});
            data_.addImage(BUILDING, new int[][]{new int[]{-32985,-32985,-32985,-32985,-32985,-32985,-32985,-32985,-32985},new int[]{-32985,-32985,-32985,-32985,-32985,-32985,-32985,-32985,-32985},new int[]{-32985,-32985,-32985,-32985,-32985,-32985,-32985,-32985,-32985},new int[]{-32985,-32985,-32985,-32985,-32985,-32985,-32985,-32985,-32985},new int[]{-32985,-32985,-32985,-32985,-32985,-32985,-32985,-32985,-32985},new int[]{-32985,-32985,-32985,-32985,-32985,-32985,-32985,-32985,-32985},new int[]{-32985,-32985,-32985,-32985,-32985,-32985,-32985,-32985,-32985},new int[]{-32985,-32985,-32985,-32985,-32985,-32985,-32985,-32985,-32985},new int[]{-32985,-32985,-32985,-32985,-32985,-32985,-32985,-32985,-32985}});
            data_.addImage(NOTHING, new int[][]{new int[]{-16777216,-16777216},new int[]{-16777216,-16777216}});
            data_.addImage(ROAD, new int[][]{new int[]{-7369361,-7369361},new int[]{-7369361,-7369361}});
            data_.addImage(WATER, new int[][]{new int[]{-16776961,-16776961},new int[]{-16776961,-16776961}});
            data_.addPerson(TRAINER, new int[][]{new int[]{-18000}});
            data_.addPerson(PERSON, new int[][]{new int[]{-1800}});
            data_.addPerson(TRAINER_ONE, new int[][]{new int[]{-19000}});
            data_.addPerson(TRAINER_TWO, new int[][]{new int[]{-19008}});
            data_.addPerson(ALLY, new int[][]{new int[]{-19508}});
            data_.addPerson(GERANT, new int[][]{new int[]{-20508}});
            data_.addTrainerImage(TRAINER, new int[][]{new int[]{-18000}});
            data_.addTrainerImage(TRAINER_ONE, new int[][]{new int[]{-19000}});
            data_.addTrainerImage(TRAINER_TWO, new int[][]{new int[]{-19008}});
            data_.addTrainerImage(ALLY, new int[][]{new int[]{-19508}});
            data_.getOverWorldHeros().addEntry(new ImageHeroKey(EnvironmentType.ROAD, Direction.DOWN, Sex.NO), new int[][]{new int[]{1}});
            data_.getOverWorldHeros().addEntry(new ImageHeroKey(EnvironmentType.ROAD, Direction.UP,Sex.NO), new int[][]{new int[]{1}});
            data_.getOverWorldHeros().addEntry(new ImageHeroKey(EnvironmentType.ROAD, Direction.LEFT,Sex.NO), new int[][]{new int[]{1}});
            data_.getOverWorldHeros().addEntry(new ImageHeroKey(EnvironmentType.ROAD, Direction.RIGHT,Sex.NO), new int[][]{new int[]{1}});
            data_.getBackHeros().addEntry(new ImageHeroKey(EnvironmentType.ROAD, Sex.NO), new int[][]{new int[]{1}});
            data_.getFrontHeros().addEntry(new ImageHeroKey(EnvironmentType.ROAD, Sex.NO), new int[][]{new int[]{1}});
            data_.getMiniPk().addEntry(PIKACHU,new int[][]{new int[]{2}});
            data_.getMaxiPkBack().addEntry(PIKACHU,new int[][]{new int[]{2}});
            data_.getMaxiPkFront().addEntry(PIKACHU,new int[][]{new int[]{2}});
            data_.getMiniItems().addEntry(POKE_BALL,new int[][]{new int[]{2}});
            data_.getAnimStatis().addEntry(Statistic.ATTACK.getStatName(), new int[][]{new int[]{3}});
            data_.getAnimStatis().addEntry(Statistic.SPECIAL_ATTACK.getStatName(), new int[][]{new int[]{3}});
            data_.getAnimStatis().addEntry(Statistic.DEFENSE.getStatName(), new int[][]{new int[]{3}});
            data_.getAnimStatis().addEntry(Statistic.SPECIAL_DEFENSE.getStatName(), new int[][]{new int[]{3}});
            data_.getAnimStatis().addEntry(Statistic.SPEED.getStatName(), new int[][]{new int[]{3}});
            data_.getAnimStatis().addEntry(Statistic.ACCURACY.getStatName(), new int[][]{new int[]{3}});
            data_.getAnimStatis().addEntry(Statistic.EVASINESS.getStatName(), new int[][]{new int[]{3}});
            data_.getAnimStatis().addEntry(Statistic.CRITICAL_HIT.getStatName(), new int[][]{new int[]{3}});
            data_.getTypesImages().addEntry(ELECTRICK,new int[][]{new int[]{4}});
            data_.getTypesColors().addEntry(ELECTRICK,"1;3;5");
            data_.setEndGameImage(new int[][]{new int[1]});
            initBegin(data_);

            initBlockFirstCity(data_);
            initBuildingsFirstCity(data_);
            initTrainersFirstCity(data_);
            initPokemonCenterFirstCity(data_);

            initLeague(data_);
            initBlockLeague(data_);
            initLeagueTrainers(data_);

            initBlockFirstRoad(data_);
            initFirstRoadAreas(data_);

            data_.getMap().join((short) 0,(short) 2,newPoint(0,0),newPoint(5,0), Direction.LEFT);

            initMiniMap(data_);
            data_.completeVariables();
            initRandomLaws(data_);
            initExpPoints(data_);
            data_.getTm().addEntry((short)2,ECLAIR);
            data_.getTmPrice().addEntry((short)2,new LgInt("1"));
            data_.initTypesByTable();
            initTranslations(data_);
            data_.initFamilies();
            return data_;
        }
        public static void initBegin(DataBase _data) {
            DataMap map_ = _data.getMap();
            WildPk pkm_ = new WildPk();
            pkm_.setName(PIKACHU);
            pkm_.setAbility(PARATONNERRE);
            pkm_.setGender(Gender.NO_GENDER);
            pkm_.setItem(NULL_REF);
            pkm_.setLevel((short) 7);
            map_.setFirstPokemon(pkm_);
            map_.setBegin(newCoords(0, 0, 2, 1));
        }
        public static DataBase coreDataBase() {
            DataBase data_ = new DataBase(DefaultGenerator.oneElt());
            data_.setLanguage(LANGUAGE);
            data_.setLanguages(new StringList(LANGUAGE));
            data_.initializeMembers();
            initConstants(data_);
            PokemonData pkData_ = Instances.newPokemonData();
            pkData_.setBaseEvo(PIKACHU);
            pkData_.setEggGroups(new StringList(data_.getDefaultEggGroup()));
            pkData_.setTypes(new StringList(ELECTRICK));
            statBase(pkData_);
            pkData_.getLevMoves().add(new LevelMove((short)1,ECLAIR));
            pkData_.setExpRate(1);
            pkData_.setHeight(Rate.one());
            pkData_.setWeight(Rate.one());
            pkData_.setCatchingRate((short) 1);
            pkData_.setHappiness((short) 1);
            pkData_.setHappinessHatch((short) 1);
            pkData_.setAbilities(new StringList(PARATONNERRE));
            data_.completeMembers(PIKACHU,pkData_);
            data_.completeMembers(PARATONNERRE,Instances.newAbilityData());
            data_.completeMembers(ECLAIR,learn(Statistic.ATTACK));
            data_.completeMembers(ECLAIR_2, learn(Statistic.SPECIAL_ATTACK));
            data_.completeMembers(ECLAIR_3, def());
            data_.completeMembers(POKE_BALL,Instances.newBall());
            data_.getTableTypes().addEntry(new TypesDuo(ELECTRICK,ELECTRICK),Rate.one());
            data_.setMap(Instances.newDataMap());
            data_.setCombos(Instances.newCombos());
            data_.getConstNum().addEntry(DataBase.STRONG_MOVE,Rate.newRate("90"));
            return data_;
        }

        private static DamagingMoveData def() {
            EffectDamage eff_;
            DamagingMoveData sec_ = Instances.newDamagingMoveData();
            eff_ = Instances.newEffectDamage();
            eff_.setPower("100");
            eff_.setFail("");
            eff_.setTargetChoice(TargetChoice.TOUS_ADV);
            eff_.setStatisAtt(Statistic.ATTACK);
            sec_.getEffects().add(eff_);
            sec_.setTargetChoice(TargetChoice.TOUS_ADV);
            sec_.setTypes(new StringList(ELECTRICK));
            sec_.setCategory("SPEC");
            sec_.setAccuracy("1");
            sec_.setPp((short) 1);
            return sec_;
        }

        private static DamagingMoveData learn(Statistic _stat) {
            DamagingMoveData move_ = Instances.newDamagingMoveData();
            EffectDamage eff_ = Instances.newEffectDamage();
            eff_.setPower("100");
            eff_.setFail("");
            eff_.setTargetChoice(TargetChoice.TOUS_ADV);
            eff_.setStatisAtt(_stat);
            move_.getEffects().add(eff_);
            move_.setTargetChoice(TargetChoice.TOUS_ADV);
            move_.setTypes(new StringList(ELECTRICK));
            move_.setCategory("SPEC");
            move_.setAccuracy("1");
            move_.setPp((short) 1);
            return move_;
        }

        public static void statBase(PokemonData _pk) {
            _pk.getStatistics().addEntry(Statistic.ATTACK,new StatBaseEv((short)1,(short)0));
            _pk.getStatistics().addEntry(Statistic.DEFENSE,new StatBaseEv((short)1,(short)0));
            _pk.getStatistics().addEntry(Statistic.SPECIAL_ATTACK,new StatBaseEv((short)1,(short)0));
            _pk.getStatistics().addEntry(Statistic.SPECIAL_DEFENSE,new StatBaseEv((short)1,(short)0));
            _pk.getStatistics().addEntry(Statistic.SPEED,new StatBaseEv((short)1,(short)0));
            _pk.getStatistics().addEntry(Statistic.HP,new StatBaseEv((short)1,(short)0));
        }

        public static void initConstants(DataBase _data) {
            _data.addConstNumTest(DataBase.MAX_EV, new Rate(20));
            _data.addConstNumTest(DataBase.MAX_IV, new Rate(31));
            _data.addConstNumTest(DataBase.DEF_MAX_ATT, new Rate(4));
            _data.addConstNumTest(DataBase.DEF_PKEQ, new Rate(6));
            _data.addConstNumTest(DataBase.ARGENT, new Rate(3000));
            _data.addConstNumTest(DataBase.NIVEAU_PK_ECLOSION, new Rate(1));
            _data.addConstNumTest(DataBase.NIVEAU_PK_MAX, new Rate(100));
            _data.addConstNumTest(DataBase.EVO_BONHEUR, new Rate(110));
            _data.addConstNumTest(DataBase.MAX_BONHEUR, new Rate(170));
            _data.addConstNumTest(DataBase.GAIN_BONHEUR_NIV, new Rate(2));
            _data.addConstNumTest(DataBase.PAS_NECES_INCREMENT_BONHEUR, new Rate(10));
            _data.addConstNumTest(DataBase.PP_MAX, new Rate(80));
            _data.addConstNumTest(DataBase.VALEUR_DEF_STATIS, new Rate(0));
            _data.addConstNumTest(DataBase.MAX_BOOST, new Rate(6));
            _data.addConstNumTest(DataBase.MIN_BOOST, new Rate(-6));
            _data.addConstNumTest(DataBase.MIN_HP, new Rate(1));
            _data.addConstNumTest(DataBase.BONUS_BOOST, new Rate("3/2"));
            _data.addConstNumTest(DataBase.MAX_STEPS, new Rate("1024"));
            _data.addConstNumTest(DataBase.MAX_STEPS_SAME_EVO_BASE, new Rate("256"));
            _data.addConstNumTest(DataBase.DEF_BASE_MOVE, new Rate("0"));
            initDefaultConsts(POKE_BALL,
                    "1",
                    "1",
                    "div(2*caracgaucheouvert(VAR__BOOST,0),max(2-VAR__BOOST,1))+div((2+VAR__BOOST)*caracdroiteferme(VAR__BOOST,0),2)",
                    "puis(2,VAR__BOOST-4)",
                    "1",
                    ECLAIR_3,
                    "METAMORPH", _data);
        }

        public static void initDefaultConsts(String _ballDef, String _rateCatching,
                                             String _rateFleeing, String _rateBoost,
                                             String _rateBoostCriticalHit, String _damageFormula,
                                             String _defMove, String _defaultEggGoup, DataBase _db) {
            _db.setBallDef(_ballDef);
            _db.setRateCatching(_rateCatching);
            _db.setRateFleeing(_rateFleeing);
            _db.setRateBoost(_rateBoost);
            _db.setRateBoostCriticalHit(_rateBoostCriticalHit);
            _db.setDamageFormula(_damageFormula);
            _db.setDefMove(_defMove);
            _db.setDefaultEggGroup(_defaultEggGoup);
            _db.setDefCategory("_");
        }
        public static void initExpPoints(DataBase _data) {
            _data.getExpGrowth().addEntry(ExpType.E,"2*VAR__NIVEAU");
            _data.getExpGrowth().addEntry(ExpType.L,"5/4*puis(VAR__NIVEAU,3)");
            _data.getExpGrowth().addEntry(ExpType.M,"puis(VAR__NIVEAU,3)");
            _data.getExpGrowth().addEntry(ExpType.P,"puis(VAR__NIVEAU,2)");
            _data.getExpGrowth().addEntry(ExpType.F,"VAR__NIVEAU");
            _data.getExpGrowth().addEntry(ExpType.R,"4/5*puis(VAR__NIVEAU,3)");
            _data.getRates().addEntry(DifficultyWinPointsFight.TRES_FACILE, "4");
            _data.getRates().addEntry(DifficultyWinPointsFight.FACILE, "2");
            _data.getRates().addEntry(DifficultyWinPointsFight.DIFFICILE, "1");
            _data.getRates().addEntry(DifficultyWinPointsFight.TRES_DIFFICILE, "1/2");
        }

        public static void initTranslations(DataBase _data) {
            IdMap<SelectedBoolean,String> bools_;
            bools_ = new IdMap<SelectedBoolean,String>();
            bools_.addEntry(SelectedBoolean.YES, SelectedBoolean.YES.getBoolName());
            bools_.addEntry(SelectedBoolean.NO, SelectedBoolean.NO.getBoolName());
            bools_.addEntry(SelectedBoolean.YES_AND_NO, SelectedBoolean.YES_AND_NO.getBoolName());
            _data.getTranslatedBooleans().addEntry(LANGUAGE, bools_);
            IdMap<DifficultyWinPointsFight,String> diffsWin_;
            diffsWin_ = new IdMap<DifficultyWinPointsFight,String>();
            diffsWin_.addEntry(DifficultyWinPointsFight.TRES_FACILE, DifficultyWinPointsFight.TRES_FACILE.getWinName());
            diffsWin_.addEntry(DifficultyWinPointsFight.FACILE, DifficultyWinPointsFight.FACILE.getWinName());
            diffsWin_.addEntry(DifficultyWinPointsFight.DIFFICILE, DifficultyWinPointsFight.DIFFICILE.getWinName());
            diffsWin_.addEntry(DifficultyWinPointsFight.TRES_DIFFICILE, DifficultyWinPointsFight.TRES_DIFFICILE.getWinName());
            _data.getTranslatedDiffWinPts().addEntry(LANGUAGE, diffsWin_);
            IdMap<DifficultyModelLaw,String> diffsLaw_;
            diffsLaw_ = new IdMap<DifficultyModelLaw,String>();
            diffsLaw_.addEntry(DifficultyModelLaw.CONSTANT_MIN, DifficultyModelLaw.CONSTANT_MIN.getModelName());
            diffsLaw_.addEntry(DifficultyModelLaw.CROISSANT, DifficultyModelLaw.CROISSANT.getModelName());
            diffsLaw_.addEntry(DifficultyModelLaw.UNIFORME, DifficultyModelLaw.UNIFORME.getModelName());
            diffsLaw_.addEntry(DifficultyModelLaw.DECROISSANT, DifficultyModelLaw.DECROISSANT.getModelName());
            diffsLaw_.addEntry(DifficultyModelLaw.CONSTANT_MAX, DifficultyModelLaw.CONSTANT_MAX.getModelName());
            _data.getTranslatedDiffModelLaw().addEntry(LANGUAGE, diffsLaw_);
            IdMap<EnvironmentType,String> envs_;
            envs_ = new IdMap<EnvironmentType,String>();
            envs_.addEntry(EnvironmentType.NOTHING, EnvironmentType.NOTHING.getEnvName());
            envs_.addEntry(EnvironmentType.ROAD, EnvironmentType.ROAD.getEnvName());
            envs_.addEntry(EnvironmentType.DESERT, EnvironmentType.DESERT.getEnvName());
            envs_.addEntry(EnvironmentType.ROCK, EnvironmentType.ROCK.getEnvName());
            envs_.addEntry(EnvironmentType.BUILDING, EnvironmentType.BUILDING.getEnvName());
            envs_.addEntry(EnvironmentType.WATER, EnvironmentType.WATER.getEnvName());
            envs_.addEntry(EnvironmentType.GRASS, EnvironmentType.GRASS.getEnvName());
            envs_.addEntry(EnvironmentType.SNOW, EnvironmentType.SNOW.getEnvName());
            envs_.addEntry(EnvironmentType.ICE, EnvironmentType.ICE.getEnvName());
            _data.getTranslatedEnvironment().addEntry(LANGUAGE, envs_);
            IdMap<Gender,String> genders_;
            genders_ = new IdMap<Gender,String>();
            genders_.addEntry(Gender.FEMALE, Gender.FEMALE.getGenderName());
            genders_.addEntry(Gender.NO_GENDER, Gender.NO_GENDER.getGenderName());
            genders_.addEntry(Gender.MALE, Gender.MALE.getGenderName());
            _data.getTranslatedGenders().addEntry(LANGUAGE, genders_);
            IdMap<Statistic,String> statistics_;
            statistics_ = new IdMap<Statistic,String>();
            statistics_.addEntry(Statistic.ATTACK, Statistic.ATTACK.getStatName());
            statistics_.addEntry(Statistic.DEFENSE, Statistic.DEFENSE.getStatName());
            statistics_.addEntry(Statistic.SPECIAL_ATTACK, Statistic.SPECIAL_ATTACK.getStatName());
            statistics_.addEntry(Statistic.SPECIAL_DEFENSE, Statistic.SPECIAL_DEFENSE.getStatName());
            statistics_.addEntry(Statistic.SPEED, Statistic.SPEED.getStatName());
            statistics_.addEntry(Statistic.CRITICAL_HIT, Statistic.CRITICAL_HIT.getStatName());
            statistics_.addEntry(Statistic.ACCURACY, Statistic.ACCURACY.getStatName());
            statistics_.addEntry(Statistic.EVASINESS, Statistic.EVASINESS.getStatName());
            statistics_.addEntry(Statistic.PV_RESTANTS, Statistic.PV_RESTANTS.getStatName());
            statistics_.addEntry(Statistic.HP, Statistic.HP.getStatName());
            _data.getTranslatedStatistics().addEntry(LANGUAGE, statistics_);
            IdMap<TargetChoice,String> targets_;
            targets_ = new IdMap<TargetChoice,String>();
            targets_.addEntry(TargetChoice.ADJ_ADV, TargetChoice.ADJ_ADV.getTargetName());
            targets_.addEntry(TargetChoice.ADJ_MULT, TargetChoice.ADJ_MULT.getTargetName());
            targets_.addEntry(TargetChoice.ADJ_UNIQ, TargetChoice.ADJ_UNIQ.getTargetName());
            targets_.addEntry(TargetChoice.ALLIE, TargetChoice.ALLIE.getTargetName());
            targets_.addEntry(TargetChoice.ALLIES, TargetChoice.ALLIES.getTargetName());
            targets_.addEntry(TargetChoice.ANY_FOE, TargetChoice.ANY_FOE.getTargetName());
            targets_.addEntry(TargetChoice.AUTRE_UNIQ, TargetChoice.AUTRE_UNIQ.getTargetName());
            targets_.addEntry(TargetChoice.GLOBALE, TargetChoice.GLOBALE.getTargetName());
            targets_.addEntry(TargetChoice.LANCEUR, TargetChoice.LANCEUR.getTargetName());
            targets_.addEntry(TargetChoice.PSEUDO_GLOBALE, TargetChoice.PSEUDO_GLOBALE.getTargetName());
            targets_.addEntry(TargetChoice.TOUS_ADV, TargetChoice.TOUS_ADV.getTargetName());
            targets_.addEntry(TargetChoice.UNIQUE_IMPORTE, TargetChoice.UNIQUE_IMPORTE.getTargetName());
            targets_.addEntry(TargetChoice.NOTHING, TargetChoice.NOTHING.getTargetName());
            _data.getTranslatedTargets().addEntry(LANGUAGE, targets_);
            StringMap<String> words_ = DataBase.basicTranslation(_data.getPokedex().getKeys());
            _data.getTranslatedPokemon().addEntry(LANGUAGE, words_);
            words_ = DataBase.basicTranslation(_data.getMoves().getKeys());
            _data.getTranslatedMoves().addEntry(LANGUAGE, words_);
            words_ = DataBase.basicTranslation(_data.getItems().getKeys());
            _data.getTranslatedItems().addEntry(LANGUAGE, words_);
            words_ = DataBase.basicTranslation(_data.getAbilities().getKeys());
            _data.getTranslatedAbilities().addEntry(LANGUAGE, words_);
            words_ = DataBase.basicTranslation(_data.getStatus().getKeys());
            _data.getTranslatedStatus().addEntry(LANGUAGE, words_);
            words_ = DataBase.basicTranslationItemsType(_data);
            _data.getTranslatedClassesDescriptions().addEntry(LANGUAGE, words_);
            words_ = DataBase.basicTranslation(_data.getTypes());
            _data.getTranslatedTypes().addEntry(LANGUAGE, words_);
            words_ = DataBase.basicTranslation(_data.getAllCategories());
            _data.getTranslatedCategories().addEntry(LANGUAGE, words_);
            words_ = DataBase.basicTranslation(EvolvedMathFactory.getFunctions());
            _data.getTranslatedFctMath().addEntry(LANGUAGE, words_);
            StringMap<String> litteral_ = new StringMap<String>();
            litteral_.addEntry("NIVEAU", StringUtil.concat("level",TAB,"l",TAB,"The level of the Pokemon"));
            litteral_.addEntry("BOOST", StringUtil.concat("boost",TAB,"b",TAB,"The boost of the Pokemon"));
            _data.getLitterals().addEntry(LANGUAGE,litteral_);
        }

        public static void initRandomLaws(DataBase _data) {
            MonteCarloNumber monteCarloNumber_;
            monteCarloNumber_ = new MonteCarloNumber();
            monteCarloNumber_.addQuickEvent(new Rate("49/50"),new LgInt("14"));
            monteCarloNumber_.addQuickEvent(new Rate("23/25"),new LgInt("8"));
            monteCarloNumber_.addQuickEvent(new Rate("89/100"),new LgInt("5"));
            monteCarloNumber_.addQuickEvent(new Rate("19/20"),new LgInt("11"));
            monteCarloNumber_.addQuickEvent(new Rate("99/100"),new LgInt("15"));
            monteCarloNumber_.addQuickEvent(new Rate("24/25"),new LgInt("12"));
            monteCarloNumber_.addQuickEvent(new Rate("43/50"),new LgInt("2"));
            monteCarloNumber_.addQuickEvent(new Rate("91/100"),new LgInt("7"));
            monteCarloNumber_.addQuickEvent(new Rate("47/50"),new LgInt("10"));
            monteCarloNumber_.addQuickEvent(new Rate("93/100"),new LgInt("9"));
            monteCarloNumber_.addQuickEvent(new Rate("97/100"),new LgInt("13"));
            monteCarloNumber_.addQuickEvent(new Rate("9/10"),new LgInt("6"));
            monteCarloNumber_.addQuickEvent(new Rate("22/25"),new LgInt("4"));
            monteCarloNumber_.addQuickEvent(new Rate("87/100"),new LgInt("3"));
            monteCarloNumber_.addQuickEvent(new Rate("1"),new LgInt("16"));
            monteCarloNumber_.addQuickEvent(new Rate("17/20"),new LgInt("1"));
            _data.getLawsDamageRate().addEntry(DifficultyModelLaw.CROISSANT,new LawNumber(monteCarloNumber_,(short)4));
            monteCarloNumber_ = new MonteCarloNumber();
            monteCarloNumber_.addQuickEvent(new Rate("99/100"),new LgInt("1"));
            monteCarloNumber_.addQuickEvent(new Rate("9/10"),new LgInt("1"));
            monteCarloNumber_.addQuickEvent(new Rate("47/50"),new LgInt("1"));
            monteCarloNumber_.addQuickEvent(new Rate("49/50"),new LgInt("1"));
            monteCarloNumber_.addQuickEvent(new Rate("93/100"),new LgInt("1"));
            monteCarloNumber_.addQuickEvent(new Rate("24/25"),new LgInt("1"));
            monteCarloNumber_.addQuickEvent(new Rate("19/20"),new LgInt("1"));
            monteCarloNumber_.addQuickEvent(new Rate("22/25"),new LgInt("1"));
            monteCarloNumber_.addQuickEvent(new Rate("1"),new LgInt("1"));
            monteCarloNumber_.addQuickEvent(new Rate("97/100"),new LgInt("1"));
            monteCarloNumber_.addQuickEvent(new Rate("43/50"),new LgInt("1"));
            monteCarloNumber_.addQuickEvent(new Rate("89/100"),new LgInt("1"));
            monteCarloNumber_.addQuickEvent(new Rate("91/100"),new LgInt("1"));
            monteCarloNumber_.addQuickEvent(new Rate("17/20"),new LgInt("1"));
            monteCarloNumber_.addQuickEvent(new Rate("23/25"),new LgInt("1"));
            monteCarloNumber_.addQuickEvent(new Rate("87/100"),new LgInt("1"));
            _data.getLawsDamageRate().addEntry(DifficultyModelLaw.UNIFORME,new LawNumber(monteCarloNumber_,(short)3));
            monteCarloNumber_ = new MonteCarloNumber();
            monteCarloNumber_.addQuickEvent(new Rate("24/25"),new LgInt("5"));
            monteCarloNumber_.addQuickEvent(new Rate("19/20"),new LgInt("6"));
            monteCarloNumber_.addQuickEvent(new Rate("9/10"),new LgInt("11"));
            monteCarloNumber_.addQuickEvent(new Rate("99/100"),new LgInt("2"));
            monteCarloNumber_.addQuickEvent(new Rate("43/50"),new LgInt("15"));
            monteCarloNumber_.addQuickEvent(new Rate("87/100"),new LgInt("14"));
            monteCarloNumber_.addQuickEvent(new Rate("23/25"),new LgInt("9"));
            monteCarloNumber_.addQuickEvent(new Rate("1"),new LgInt("1"));
            monteCarloNumber_.addQuickEvent(new Rate("93/100"),new LgInt("8"));
            monteCarloNumber_.addQuickEvent(new Rate("91/100"),new LgInt("10"));
            monteCarloNumber_.addQuickEvent(new Rate("47/50"),new LgInt("7"));
            monteCarloNumber_.addQuickEvent(new Rate("22/25"),new LgInt("13"));
            monteCarloNumber_.addQuickEvent(new Rate("97/100"),new LgInt("4"));
            monteCarloNumber_.addQuickEvent(new Rate("17/20"),new LgInt("16"));
            monteCarloNumber_.addQuickEvent(new Rate("49/50"),new LgInt("3"));
            monteCarloNumber_.addQuickEvent(new Rate("89/100"),new LgInt("12"));
            _data.getLawsDamageRate().addEntry(DifficultyModelLaw.DECROISSANT,new LawNumber(monteCarloNumber_,(short)2));
            monteCarloNumber_ = new MonteCarloNumber();
            monteCarloNumber_.addQuickEvent(new Rate("17/20"),new LgInt("1"));
            _data.getLawsDamageRate().addEntry(DifficultyModelLaw.CONSTANT_MIN,new LawNumber(monteCarloNumber_,(short)1));
            monteCarloNumber_ = new MonteCarloNumber();
            monteCarloNumber_.addQuickEvent(new Rate("1"),new LgInt("1"));
            _data.getLawsDamageRate().addEntry(DifficultyModelLaw.CONSTANT_MAX,new LawNumber(monteCarloNumber_,(short)5));
        }

        public static void initMiniMap(DataBase _data) {
            _data.getMiniMap().addEntry(MINI, new int[][]{new int[]{118}});
            _data.getMiniMap().addEntry(MINI1, new int[][]{new int[]{218}});
            _data.getMiniMap().addEntry(MINI2, new int[][]{new int[]{112}});
            _data.getMiniMap().addEntry(MINI3, new int[][]{new int[]{200}});
            _data.getMiniMap().addEntry(MINI4, new int[][]{new int[]{128}});
            _data.getMiniMap().addEntry(MINI5, new int[][]{new int[]{211}});
            _data.getMiniMap().addEntry(MINI6, new int[][]{new int[]{221}});
            DataMap map_ = _data.getMap();
            TileMiniMap tile_;
            map_.setMiniMap(new MiniMapCoordsList());
            tile_ = new TileMiniMap();
            tile_.setFile(MINI);
            tile_.setPlace((short) 0);
            map_.getMiniMap().addEntry(new MiniMapCoords((short) 0,(short) 0), tile_);
            tile_ = new TileMiniMap();
            tile_.setFile(MINI1);
            tile_.setPlace((short) 1);
            map_.getMiniMap().addEntry(new MiniMapCoords((short) 0,(short) 1), tile_);
            tile_ = new TileMiniMap();
            tile_.setFile(MINI2);
            tile_.setPlace((short) 2);
            map_.getMiniMap().addEntry(new MiniMapCoords((short) 0,(short) 2), tile_);
            map_.setUnlockedCity(MINI5);
        }

        public static void initBlockFirstCity(DataBase _data) {
            DataMap map_ = _data.getMap();
            map_.addCity("__");
            City city_ = (City) map_.getPlaces().last();
            Block block_;
            block_ = newBlock(2, 2,EnvironmentType.NOTHING,NOTHING,-1);
            city_.getLevel().getBlocks().addEntry(newPoint(0,0), block_);
            block_ = newBlock(2, 2,EnvironmentType.ROAD,ROAD,-1);
            city_.getLevel().getBlocks().addEntry(newPoint(2,0), block_);
            block_ = newBlock(2, 2,EnvironmentType.NOTHING,NOTHING,-1);
            city_.getLevel().getBlocks().addEntry(newPoint(4,0), block_);
            block_ = newBlock(2, 2,EnvironmentType.ROAD,ROAD,-1);
            city_.getLevel().getBlocks().addEntry(newPoint(0,2), block_);
            block_ = newBlock(2, 2,EnvironmentType.ROAD,ROAD,-1);
            city_.getLevel().getBlocks().addEntry(newPoint(2,2), block_);
            block_ = newBlock(2, 2,EnvironmentType.WATER,WATER,-1);
            city_.getLevel().getBlocks().addEntry(newPoint(4,2), block_);
            block_ = newBlock(2, 2,EnvironmentType.WATER,WATER,-1);
            city_.getLevel().getBlocks().addEntry(newPoint(0,4), block_);
            block_ = newBlock(2, 2,EnvironmentType.WATER,WATER,-1);
            city_.getLevel().getBlocks().addEntry(newPoint(2,4), block_);
            block_ = newBlock(2, 2,EnvironmentType.WATER,WATER,-1);
            city_.getLevel().getBlocks().addEntry(newPoint(4,4), block_);
        }

        public static void initBuildingsFirstCity(DataBase _data) {
            DataMap map_ = _data.getMap();
            City city_ = (City) map_.getPlaces().last();
            Gym gym_;
            gym_ = new Gym();
            gym_.setImageFileName(LINK);
            gym_.setLevel(new LevelIndoorGym());
            gym_.setExitCity(newPoint(4,8));
            gym_.getLevel().setBlocks(new PointsBlock());
            gym_.getLevel().getBlocks().addEntry(newPoint(0,0), newBlock(9, 9,EnvironmentType.BUILDING,BUILDING,-1));
            gym_.getIndoor().setGymTrainers(new PointsGymTrainer());
            city_.setBuildings(new PointsBuilding());
            city_.getBuildings().addEntry(newPoint(5, 1), gym_);
            PokemonCenter pkCenter_;
            pkCenter_ = new PokemonCenter();
            pkCenter_.setImageFileName(LINK);
            pkCenter_.setLevel(new LevelIndoorPokemonCenter());
            pkCenter_.setExitCity(newPoint(4,8));
            pkCenter_.getLevel().setBlocks(new PointsBlock());
            pkCenter_.getLevel().getBlocks().addEntry(newPoint(0,0), newBlock(9, 9,EnvironmentType.BUILDING,BUILDING,-1));
            pkCenter_.getIndoor().setStorageCoords(newPoint(4, 0));
            pkCenter_.getIndoor().setGerants(new PointsPerson());
            city_.getBuildings().addEntry(newPoint(1, 1), pkCenter_);
        }

        public static void initTrainersFirstCity(DataBase _data) {
            DataMap map_ = _data.getMap();
            City city_ = (City) map_.getPlaces().last();
            Gym gym_;
            GymTrainer gymTrainer_;
            GymLeader gymLeader_;
            gym_ = (Gym) city_.getBuildings().getVal(newPoint(5, 1));
            CustList<PkTrainer> team_ = new CustList<PkTrainer>();
            team_.add(toPkTrainer(new NameLevel(PIKACHU, 1), new StringList(ECLAIR)));
            gymTrainer_ = nvGymTrainer((short) 200, (byte) 1, team_);
            gym_.getIndoor().getGymTrainers().addEntry(newPoint(1, 7), gymTrainer_);
            CustList<PkTrainer> teamTwo_ = new CustList<PkTrainer>();
            teamTwo_.add(toPkTrainer(new NameLevel(PIKACHU, 1), new StringList(ECLAIR)));
            gymTrainer_ = nvGymTrainer((short) 200, (byte) 1, teamTwo_);
            gym_.getIndoor().getGymTrainers().addEntry(newPoint(7, 7), gymTrainer_);
            gym_.getIndoor().setGymLeaderCoords(newPoint(4, 1));
            CustList<PkTrainer> teamThree_ = new CustList<PkTrainer>();
            teamThree_.add(toPkTrainer(new NameLevel(PIKACHU, 1), new StringList(ECLAIR)));
            gymLeader_ = nvGymLeader((short) 500, (byte) 1, teamThree_);
            gymLeader_.setName("__");
            gym_.getIndoor().setGymLeader(gymLeader_);
        }

        public static void initPokemonCenterFirstCity(DataBase _data) {
            DataMap map_ = _data.getMap();
            City city_ = (City) map_.getPlaces().last();
            PokemonCenter pk_;
            pk_ = (PokemonCenter) city_.getBuildings().getVal(newPoint(1, 1));
            pk_.getIndoor().getGerants().addEntry(newPoint(0, 4), newGerantPokemon(GeranceType.HEAL));
            Seller seller_;
            seller_ = new Seller();
            seller_.setItems(new StringList(POKE_BALL));
            seller_.setTm(Shorts.newList());
            seller_.setSell(SellType.ITEM);
            seller_.setImageMiniFileName(GERANT);
            pk_.getIndoor().getGerants().addEntry(newPoint(8, 4), seller_);
            seller_ = new Seller();
            seller_.setItems(new StringList());
            seller_.setTm(Shorts.newList());
            seller_.setSell(SellType.MOVE);
            seller_.setImageMiniFileName(GERANT);
            pk_.getIndoor().getGerants().addEntry(newPoint(8, 6), seller_);
        }
        public static void initLeague(DataBase _data) {
            DataMap map_ = _data.getMap();
            map_.addLeague(LINK, newCoords(0, 0, 2, 0));
            League league_ =(League) map_.getPlaces().last();
            league_.getRooms().last().setFileName(LINK);
            league_.setName("__");
        }

        public static void initBlockLeague(DataBase _data) {
            DataMap map_ = _data.getMap();
            League road_ = (League) map_.getPlaces().last();
            LevelLeague level_;
            Block block_;
            level_ = (LevelLeague) road_.getLevelsMap().getVal((byte) 0);
            block_ = newBlock(9, 9,EnvironmentType.BUILDING,BUILDING,-1);
            level_.getBlocks().addEntry(newPoint(0,0), block_);
            road_.setBegin(newPoint(4,8));
            level_ = (LevelLeague) road_.getLevelsMap().getVal((byte) 0);
            level_.setAccessPoint(newPoint(4, 0));
        }

        public static void initLeagueTrainers(DataBase _data) {
            DataMap map_ = _data.getMap();
            League league_ = (League) map_.getPlaces().last();
            league_.getRooms().get(0).setTrainerCoords(newPoint(4, 4));
            league_.getRooms().get(0).setTrainer(trainerLeagueOne());
            league_.getRooms().get(0).getTrainer().setName("__");
            map_.getAccessCondition().addEntry(newCoords(0, 0, 2, 0), Condition.newList(newCoords(0, 0, 5, 1, 4, 1)));
        }

        public static void initBlockFirstRoad(DataBase _data) {
            DataMap map_ = _data.getMap();
            map_.addRoad();
            Road road_ = (Road) map_.getPlaces().last();
            road_.setName("___");
            Block block_;
            block_ = newBlock(2, 2,EnvironmentType.ROAD,ROAD, 0);
            road_.getLevel().getBlocks().addEntry(newPoint(0,0), block_);
            block_ = newBlock(2, 2,EnvironmentType.ROAD,ROAD, 0);
            road_.getLevel().getBlocks().addEntry(newPoint(2,0), block_);
            block_ = newBlock(2, 2,EnvironmentType.ROAD,ROAD, 0);
            road_.getLevel().getBlocks().addEntry(newPoint(4,0), block_);
            block_ = newBlock(2, 2,EnvironmentType.ROAD,ROAD, 0);
            road_.getLevel().getBlocks().addEntry(newPoint(0,2), block_);
            block_ = newBlock(2, 2,EnvironmentType.ROAD,ROAD, 0);
            road_.getLevel().getBlocks().addEntry(newPoint(2,2), block_);
            block_ = newBlock(2, 2,EnvironmentType.ROAD,ROAD, 0);
            road_.getLevel().getBlocks().addEntry(newPoint(4,2), block_);
            block_ = newBlock(2, 2,EnvironmentType.ROAD,ROAD, 0);
            road_.getLevel().getBlocks().addEntry(newPoint(0,4), block_);
            block_ = newBlock(2, 2,EnvironmentType.ROAD,ROAD, 0);
            road_.getLevel().getBlocks().addEntry(newPoint(2,4), block_);
            block_ = newBlock(2, 2,EnvironmentType.ROAD,ROAD, 0);
            road_.getLevel().getBlocks().addEntry(newPoint(4,4), block_);
        }

        public static void initFirstRoadAreas(DataBase _data) {
            DataMap map_ = _data.getMap();
            Road road_ = (Road) map_.getPlaces().last();
            AreaApparition area_;
            WildPk wild_;
            area_ = new AreaApparition();
            area_.setAvgNbSteps((short) 1);
            area_.setMultFight((byte) 1);
            wild_ = new WildPk();
            wild_.setName(PIKACHU);
            wild_.setLevel((short) 1);
            wild_.setAbility(PARATONNERRE);
            wild_.setGender(Gender.NO_GENDER);
            area_.setWildPokemon(new CustList<WildPk>());
            area_.setWildPokemonFishing(new CustList<WildPk>());
            area_.getWildPokemon().add(wild_);
            road_.getLevelRoad().getWildPokemonAreas().add(area_);
        }

        private static TrainerLeague trainerLeagueOne() {
            CustList<PkTrainer> team_ = new CustList<PkTrainer>();
            team_.add(toPkTrainer(new NameLevel(PIKACHU, 35), new StringList(ECLAIR)));
            return nvTrainerLeague((short) 2000, (byte) 1, team_);
        }
        private static GymLeader nvGymLeader(short _reward, byte _mult, CustList<PkTrainer> _team) {
            GymLeader gymLeader_ = new GymLeader();
            gymLeader_.setTeam(_team);
            gymLeader_.setReward(_reward);
            gymLeader_.setMultiplicityFight(_mult);
            gymLeader_.setName(NULL_REF);
            gymLeader_.setTm((short) 2);
            gymLeader_.setImageMiniFileName(TRAINER);
            gymLeader_.setImageMaxiFileName(TRAINER);
            return gymLeader_;
        }

        private static GymTrainer nvGymTrainer(short _reward, byte _mult, CustList<PkTrainer> _team) {
            GymTrainer gymTrainer_ = new GymTrainer();
            gymTrainer_.setTeam(_team);
            gymTrainer_.setReward(_reward);
            gymTrainer_.setMultiplicityFight(_mult);
            gymTrainer_.setImageMiniFileName(TRAINER);
            gymTrainer_.setImageMaxiFileName(TRAINER);
            return gymTrainer_;
        }

        private static TrainerLeague nvTrainerLeague(short _reward, byte _mult, CustList<PkTrainer> _team) {
            TrainerLeague trainerLeague_ = new TrainerLeague();
            trainerLeague_.setTeam(_team);
            trainerLeague_.setReward(_reward);
            trainerLeague_.setMultiplicityFight(_mult);
            trainerLeague_.setImageMiniFileName(TRAINER);
            trainerLeague_.setImageMaxiFileName(TRAINER);
            trainerLeague_.setName(NULL_REF);
            return trainerLeague_;
        }

        private static DualFight nvDualFight(short _reward, CustList<PkTrainer> _teamAl, CustList<PkTrainer> _team) {
            DualFight dual_ = new DualFight();
            Ally ally_ = new Ally();
            ally_.setTeam(_teamAl);
            TempTrainer trainer_ = new TempTrainer();
            trainer_.setTeam(_team);
            trainer_.setReward(_reward);
            trainer_.setImageMaxiFileName(TRAINER_ONE);
            trainer_.setImageMiniFileName(TRAINER_ONE);
            trainer_.setImageMiniSecondTrainerFileName(TRAINER_TWO);
            dual_.setAlly(ally_);
            dual_.setFoeTrainer(trainer_);
            dual_.setNames(new StringList());
            return dual_;
        }

        private static PokemonTeam nvTeam(short _reward, CustList<PkTrainer> _team) {
            PokemonTeam teamReward_ = new PokemonTeam();
            teamReward_.setTeam(_team);
            teamReward_.setReward(_reward);
            return teamReward_;
        }

        private static TrainerMultiFights newTrainer(
                CustList<PokemonTeam> _teams, int _mult) {
            TrainerMultiFights trainer_ = new TrainerMultiFights();
            trainer_.setTeamsRewards(_teams);
            trainer_.setMultiplicityFight((byte) _mult);
            trainer_.setImageMiniFileName(TRAINER);
            trainer_.setImageMaxiFileName(TRAINER);
            return trainer_;
        }

        private static GerantPokemon newGerantPokemon(GeranceType _gerance) {
            GerantPokemon gerant_ = new GerantPokemon();
            gerant_.setGerance(_gerance);
            gerant_.setImageMiniFileName(GERANT);
            return gerant_;
        }

        private static DealerItem newDealerObject(StringList _obj, Shorts _tm) {
            DealerItem dealer_ = new DealerItem();
            dealer_.setItems(new StringList(_obj));
            dealer_.setTechnicalMoves(_tm);
            dealer_.setImageMiniFileName(PERSON);
            return dealer_;
        }

        private static Block newBlock(int _h, int _w, EnvironmentType _type, String _tileFileName, int _index) {
            //black
            Block block_;
            block_ = new Block();
            block_.setHeight((short) _h);
            block_.setWidth((short) _w);
            block_.setType(_type);
            block_.setTileFileName(_tileFileName);
            block_.setIndexApparition((short) _index);
            return block_;
        }

        private static LevelPoint newLevelPoint(int _level, int _x, int _y) {
            LevelPoint begin_ = new LevelPoint();
            begin_.setLevelIndex((byte) _level);
            begin_.setPoint(newPoint(_x, _y));
            return begin_;
        }

        private static Coords newCoords(int _place, int _level, int _x, int _y) {
            Coords begin_ = new Coords();
            begin_.setNumberPlace((short) _place);
            begin_.setLevel(new LevelPoint());
            begin_.getLevel().setLevelIndex((byte) _level);
            begin_.getLevel().setPoint(newPoint(_x, _y));
            return begin_;
        }

        private static Coords newCoords(int _place, int _level, int _xi, int _yi, int _x, int _y) {
            Coords begin_ = new Coords();
            begin_.setNumberPlace((short) _place);
            begin_.affectInside(newPoint(_xi, _yi));
            begin_.setLevel(new LevelPoint());
            begin_.getLevel().setLevelIndex((byte) _level);
            begin_.getLevel().setPoint(newPoint(_x, _y));
            return begin_;
        }

        private static PkTrainer toPkTrainer(NameLevel _nameLevel, StringList _moves) {
            PkTrainer pk_ = new PkTrainer();
            pk_.setName(_nameLevel.getName());
            pk_.setLevel(_nameLevel.getLevel());
            pk_.setAbility(PARATONNERRE);
            pk_.setItem(NULL_REF);
            pk_.setMoves(_moves);
            return pk_;
        }

        private static Point newPoint(int _x, int _y) {
            return new Point((short)_x, (short)_y);
        }
    }

    public static StringMap<int[][]> def(){
        StringMap<int[][]> out_ = new StringMap<int[][]>(new CollCapacity(78));
        defTrs(out_);
        out_.addEntry(""+ CouleurValeur.HEART_KING,new int[1][1]);
        out_.addEntry(""+CouleurValeur.HEART_QUEEN,new int[1][1]);
        out_.addEntry(""+CouleurValeur.HEART_KNIGHT,new int[1][1]);
        out_.addEntry(""+CouleurValeur.HEART_JACK,new int[1][1]);
        defHeart(out_);
        out_.addEntry(""+CouleurValeur.SPADE_KING,new int[1][1]);
        out_.addEntry(""+CouleurValeur.SPADE_QUEEN,new int[1][1]);
        out_.addEntry(""+CouleurValeur.SPADE_KNIGHT,new int[1][1]);
        out_.addEntry(""+CouleurValeur.SPADE_JACK,new int[1][1]);
        defSpade(out_);
        out_.addEntry(""+CouleurValeur.DIAMOND_KING,new int[1][1]);
        out_.addEntry(""+CouleurValeur.DIAMOND_QUEEN,new int[1][1]);
        out_.addEntry(""+CouleurValeur.DIAMOND_KNIGHT,new int[1][1]);
        out_.addEntry(""+CouleurValeur.DIAMOND_JACK,new int[1][1]);
        defDiamond(out_);
        out_.addEntry(""+CouleurValeur.CLUB_KING,new int[1][1]);
        out_.addEntry(""+CouleurValeur.CLUB_QUEEN,new int[1][1]);
        out_.addEntry(""+CouleurValeur.CLUB_KNIGHT,new int[1][1]);
        out_.addEntry(""+CouleurValeur.CLUB_JACK,new int[1][1]);
        defClub(out_);
        return out_;
    }

    private static void defTrs(StringMap<int[][]> _out) {
        _out.addEntry(""+CouleurValeur.EXCUSE,new int[1][1]);
        _out.addEntry(""+CouleurValeur.TRUMP_21,new int[1][1]);
        _out.addEntry(""+CouleurValeur.TRUMP_20,new int[1][1]);
        _out.addEntry(""+CouleurValeur.TRUMP_19,new int[1][1]);
        _out.addEntry(""+CouleurValeur.TRUMP_18,new int[1][1]);
        _out.addEntry(""+CouleurValeur.TRUMP_17,new int[1][1]);
        _out.addEntry(""+CouleurValeur.TRUMP_16,new int[1][1]);
        _out.addEntry(""+CouleurValeur.TRUMP_15,new int[1][1]);
        _out.addEntry(""+CouleurValeur.TRUMP_14,new int[1][1]);
        _out.addEntry(""+CouleurValeur.TRUMP_13,new int[1][1]);
        _out.addEntry(""+CouleurValeur.TRUMP_12,new int[1][1]);
        _out.addEntry(""+CouleurValeur.TRUMP_11,new int[1][1]);
        _out.addEntry(""+CouleurValeur.TRUMP_10,new int[1][1]);
        _out.addEntry(""+CouleurValeur.TRUMP_9,new int[1][1]);
        _out.addEntry(""+CouleurValeur.TRUMP_8,new int[1][1]);
        _out.addEntry(""+CouleurValeur.TRUMP_7,new int[1][1]);
        _out.addEntry(""+CouleurValeur.TRUMP_6,new int[1][1]);
        _out.addEntry(""+CouleurValeur.TRUMP_5,new int[1][1]);
        _out.addEntry(""+CouleurValeur.TRUMP_4,new int[1][1]);
        _out.addEntry(""+CouleurValeur.TRUMP_3,new int[1][1]);
        _out.addEntry(""+CouleurValeur.TRUMP_2,new int[1][1]);
        _out.addEntry(""+CouleurValeur.TRUMP_1,new int[1][1]);
    }

    private static void defHeart(StringMap<int[][]> _out) {
        _out.addEntry(""+CouleurValeur.HEART_10,new int[1][1]);
        _out.addEntry(""+CouleurValeur.HEART_9,new int[1][1]);
        _out.addEntry(""+CouleurValeur.HEART_8,new int[1][1]);
        _out.addEntry(""+CouleurValeur.HEART_7,new int[1][1]);
        _out.addEntry(""+CouleurValeur.HEART_6,new int[1][1]);
        _out.addEntry(""+CouleurValeur.HEART_5,new int[1][1]);
        _out.addEntry(""+CouleurValeur.HEART_4,new int[1][1]);
        _out.addEntry(""+CouleurValeur.HEART_3,new int[1][1]);
        _out.addEntry(""+CouleurValeur.HEART_2,new int[1][1]);
        _out.addEntry(""+CouleurValeur.HEART_1,new int[1][1]);
    }

    private static void defSpade(StringMap<int[][]> _out) {
        _out.addEntry(""+CouleurValeur.SPADE_10,new int[1][1]);
        _out.addEntry(""+CouleurValeur.SPADE_9,new int[1][1]);
        _out.addEntry(""+CouleurValeur.SPADE_8,new int[1][1]);
        _out.addEntry(""+CouleurValeur.SPADE_7,new int[1][1]);
        _out.addEntry(""+CouleurValeur.SPADE_6,new int[1][1]);
        _out.addEntry(""+CouleurValeur.SPADE_5,new int[1][1]);
        _out.addEntry(""+CouleurValeur.SPADE_4,new int[1][1]);
        _out.addEntry(""+CouleurValeur.SPADE_3,new int[1][1]);
        _out.addEntry(""+CouleurValeur.SPADE_2,new int[1][1]);
        _out.addEntry(""+CouleurValeur.SPADE_1,new int[1][1]);
    }

    private static void defDiamond(StringMap<int[][]> _out) {
        _out.addEntry(""+CouleurValeur.DIAMOND_10,new int[1][1]);
        _out.addEntry(""+CouleurValeur.DIAMOND_9,new int[1][1]);
        _out.addEntry(""+CouleurValeur.DIAMOND_8,new int[1][1]);
        _out.addEntry(""+CouleurValeur.DIAMOND_7,new int[1][1]);
        _out.addEntry(""+CouleurValeur.DIAMOND_6,new int[1][1]);
        _out.addEntry(""+CouleurValeur.DIAMOND_5,new int[1][1]);
        _out.addEntry(""+CouleurValeur.DIAMOND_4,new int[1][1]);
        _out.addEntry(""+CouleurValeur.DIAMOND_3,new int[1][1]);
        _out.addEntry(""+CouleurValeur.DIAMOND_2,new int[1][1]);
        _out.addEntry(""+CouleurValeur.DIAMOND_1,new int[1][1]);
    }

    private static void defClub(StringMap<int[][]> _out) {
        _out.addEntry(""+CouleurValeur.CLUB_10,new int[1][1]);
        _out.addEntry(""+CouleurValeur.CLUB_9,new int[1][1]);
        _out.addEntry(""+CouleurValeur.CLUB_8,new int[1][1]);
        _out.addEntry(""+CouleurValeur.CLUB_7,new int[1][1]);
        _out.addEntry(""+CouleurValeur.CLUB_6,new int[1][1]);
        _out.addEntry(""+CouleurValeur.CLUB_5,new int[1][1]);
        _out.addEntry(""+CouleurValeur.CLUB_4,new int[1][1]);
        _out.addEntry(""+CouleurValeur.CLUB_3,new int[1][1]);
        _out.addEntry(""+CouleurValeur.CLUB_2,new int[1][1]);
        _out.addEntry(""+CouleurValeur.CLUB_1,new int[1][1]);
    }

}
