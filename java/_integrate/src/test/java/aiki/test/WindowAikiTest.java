package aiki.test;

import aiki.db.DataBase;
import aiki.db.ImageHeroKey;
import aiki.facade.FacadeGame;
import aiki.facade.enums.SelectedBoolean;
import aiki.fight.abilities.AbilityData;
import aiki.fight.enums.Statistic;
import aiki.fight.items.Ball;
import aiki.fight.moves.DamagingMoveData;
import aiki.fight.moves.effects.EffectDamage;
import aiki.fight.moves.enums.TargetChoice;
import aiki.fight.pokemon.PokemonData;
import aiki.fight.pokemon.enums.ExpType;
import aiki.fight.util.LevelMove;
import aiki.fight.util.StatBaseEv;
import aiki.fight.util.TypesDuo;
import aiki.game.Game;
import aiki.game.fight.BallNumberRate;
import aiki.game.fight.Fight;
import aiki.game.fight.Fighter;
import aiki.game.fight.Team;
import aiki.game.fight.enums.FightState;
import aiki.game.params.enums.DifficultyModelLaw;
import aiki.game.params.enums.DifficultyWinPointsFight;
import aiki.game.player.enums.Sex;
import aiki.gui.WindowAiki;
import aiki.gui.components.fight.PlaceLabel;
import aiki.gui.threads.LoadFlagImpl;
import aiki.gui.threads.PerCentIncr;
import aiki.instances.Instances;
import aiki.main.AikiFactory;
import aiki.map.DataMap;
import aiki.map.buildings.Gym;
import aiki.map.buildings.PokemonCenter;
import aiki.map.characters.GerantPokemon;
import aiki.map.characters.GymLeader;
import aiki.map.characters.GymTrainer;
import aiki.map.characters.Seller;
import aiki.map.characters.enums.GeranceType;
import aiki.map.characters.enums.SellType;
import aiki.map.enums.Direction;
import aiki.map.levels.AreaApparition;
import aiki.map.levels.Block;
import aiki.map.levels.LevelOutdoor;
import aiki.map.levels.enums.EnvironmentType;
import aiki.map.places.City;
import aiki.map.places.Place;
import aiki.map.places.Road;
import aiki.map.pokemon.PkTrainer;
import aiki.map.pokemon.PokemonPlayer;
import aiki.map.pokemon.UsablePokemon;
import aiki.map.pokemon.WildPk;
import aiki.map.pokemon.enums.Gender;
import aiki.map.util.MiniMapCoords;
import aiki.map.util.MiniMapCoordsList;
import aiki.map.util.PlaceInterConnect;
import aiki.map.util.TileMiniMap;
import aiki.sml.LoadingGame;
import aiki.util.*;
import code.gui.AbsPaintableLabel;
import code.gui.TextAnswerValue;
import code.maths.LgInt;
import code.maths.Rate;
import code.maths.litteral.EvolvedMathFactory;
import code.maths.montecarlo.DefaultGenerator;
import code.maths.montecarlo.MonteCarloNumber;
import code.mock.*;
import code.network.EquallableNetworkUtil;
import code.util.CustList;
import code.util.IdMap;
import code.util.StringList;
import code.util.StringMap;
import org.junit.Test;

public final class WindowAikiTest extends EquallableNetworkUtil {
    protected static final String LANGUAGE = "en";
    protected static final String NULL_REF = DataBase.EMPTY_STRING;
    protected static final String PIKACHU = "PIKACHU";
    protected static final String PIKACHU2 = "PIKACHU2";
    protected static final String PIKACHU3 = "PIKACHU3";
    protected static final String PIKACHU4 = "PIKACHU4";
    protected static final String ECLAIR = "ECLAIR";
    protected static final String POKE_BALL = "POKE_BALL";
    protected static final String LUTTE = "LUTTE";
    protected static final String CHARGE = "CHARGE";
    protected static final String CHARGE2 = "CHARGE2";
    protected static final String CHARGE3 = "CHARGE3";
    protected static final String CHARGE4 = "CHARGE4";
    protected static final String TREMPETTE = "TREMPETTE";
    protected static final String TREMPETTE2 = "TREMPETTE2";
    protected static final String TREMPETTE3 = "TREMPETTE3";
    protected static final String PARATONNERRE = "PARATONNERRE";
    protected static final String ELECTRICK = "ELECTRICK";
    private static MockFileSet fileSet(long _initMillis, long[] _incrs, String... _roots) {
        return new MockFileSet(_initMillis,_incrs,_roots);
    }

    @Test
    public void des() {
        long[] incrs_ = new long[]{1, 3, 5};
        MockFileSet set_ = fileSet(123, incrs_, "/");
        MockProgramInfos pr_ = new MockProgramInfos("","", new MockEventListIncr(0.75,new int[0],new String[0],new TextAnswerValue[0]), set_);
        pr_.getFileCoreStream().newFile("tmp").mkdirs();
        pr_.setCurrentPath("tmp");
        WindowAiki wa_ = new WindowAiki("fr", pr_, new AikiFactory(new MockAdvGraphicListGeneratorGene<BallNumberRate>(),new MockAdvGraphicListGeneratorGene<Fighter>(),new MockAdvGraphicListGeneratorGene<String>(),new MockAdvGraphicListGeneratorGene<String>(),new MockAdvGraphicListGeneratorGene<String>(), new MockAdvGraphicListGeneratorGene<UsablePokemon>()));
        wa_.getFacade().setSexList(new MockLSexList());
        wa_.pack();
        wa_.setVisible(true);
        DataBase init_ = init();
        init_.validate(new PerCentIncr(pr_.getThreadFactory().newAtomicInteger()),new LoadFlagImpl(pr_.getThreadFactory().newAtomicBoolean(true)),wa_.getFacade().getSexList());
        System.out.println(!init_.isError());
        FacadeGame fac_ = wa_.getFacade();
        init_.setMessages(fac_.getData());
        fac_.setLoadedData(true);
        fac_.setZipName("");
        fac_.setData(init_);
        fac_.initializePaginatorTranslations();
        wa_.getLoadFlag().set(false);
        wa_.setLoadingConf(new LoadingGame(), false);
        wa_.pack();
        fac_.newGame("", Sex.NO);
        Game g_ = fac_.getGame();
        WildPk pokemonDonne_ = Instances.newWildPk();
        pokemonDonne_.setAbility(PARATONNERRE);
        pokemonDonne_.setItem(POKE_BALL);
        pokemonDonne_.setGender(Gender.NO_GENDER);
        pokemonDonne_.setLevel((short) 6);
        pokemonDonne_.setName(PIKACHU);
        g_.getPlayer().recevoirPokemon(pokemonDonne_,g_.getDifficulty(),init_);
        g_.getPlayer().recevoirPokemon(pokemonDonne_,g_.getDifficulty(),init_);
        g_.getPlayer().recevoirPokemon(pokemonDonne_,g_.getDifficulty(),init_);
        ((PokemonPlayer)g_.getPlayer().getTeam().get(0)).learnMove(CHARGE2,init_);
        ((PokemonPlayer)g_.getPlayer().getTeam().get(1)).learnMove(CHARGE2,init_);
        g_.setPlayerCoords(newCoords(0,0,1,1,2,3));
        g_.setPlayerOrientation(Direction.UP);
        g_.initTrainerFight(init_);
        Fighter first_ = g_.getFight().getFighter(Fight.toFoeFighter((byte) 0));
        Fighter second_ = g_.getFight().getFighter(Fight.toFoeFighter((byte) 1));
        first_.getRemainingHp().affectZero();
        first_.setGroundPlace(Fighter.BACK);
        second_.getRemainingHp().affectZero();
        second_.setGroundPlace(Fighter.BACK);
        Team equipeUt_=g_.getFight().getUserTeam();
        for(byte c: equipeUt_.getPlayerFightersAgainstFoe().getKeys()){
            equipeUt_.getPlayerFightersAgainstFoe().getVal(c).removeOneNumber(0);
            equipeUt_.getPlayerFightersAgainstFoe().getVal(c).removeOneNumber(1);
        }
        g_.getFight().setState(FightState.SWITCH_PROPOSE);
        g_.getFight().getFirstPositFoeFighters().put((byte) 0, Fighter.BACK);
        g_.getFight().getFirstPositFoeFighters().put((byte) 1, Fighter.BACK);
        g_.getFight().getFirstPositFoeFighters().put((byte) 2, (byte) 0);
        g_.getFight().getFirstPositFoeFighters().put((byte) 3, (byte) 1);

        Fighter firstUs_ = g_.getFight().getFighter(Fight.toUserFighter((byte) 0));
        Fighter secondUs_ = g_.getFight().getFighter(Fight.toUserFighter((byte) 1));
        byte firGrSub_ = firstUs_.getGroundPlaceSubst();
        byte secGrSub_ = secondUs_.getGroundPlaceSubst();
        firstUs_.setGroundPlaceSubst(secGrSub_);
        secondUs_.setGroundPlaceSubst(firGrSub_);
        byte firGr_ = firstUs_.getGroundPlace();
        byte secGr_ = secondUs_.getGroundPlace();
        firstUs_.setGroundPlace(secGr_);
        secondUs_.setGroundPlace(firGr_);
        /*Team equipe_=_fight.getTeams().getVal(_combattant.getTeam());
        if(_fight.getFighter(_combattant).isBelongingToPlayer()){
            equipe_.toutSupprimerCombattantsContreAdvMembre(_combattant.getPosition());
            _fight.getFirstPositPlayerFighters().put(_combattant.getPosition(),Fighter.BACK);
        }else if(NumberUtil.eq(_combattant.getTeam(),Fight.CST_FOE)){
            Team equipeUt_=_fight.getUserTeam();
            Bytes liste_ = FightOrder.fightersBelongingToUserHavingBeaten(_fight,_combattant.getPosition());
            addExpEvsFighters(_fight,liste_,_combattant.getPosition(),_diff,_import);
            equipeUt_.toutSupprimerCombattantsContreAdv(_combattant.getPosition());
        }*/
        System.out.println(fac_.checkAndSetGame(g_));
        fac_.load(g_);
        fac_.changeCamera(g_.getPlayerOrientation());
        wa_.drawGameWalking(true);
        wa_.interact();
        wa_.setFight(false,false);
        wa_.getBattle().getBattle().getFighterFrontPanel().getListe().setSelectedIndice(0);
        AbsPaintableLabel rowZero_ = wa_.getBattle().getBattle().getPlacesLabels().last().getPaintableLabel();
        ((MockCustComponent)rowZero_).getMouseIntRelListeners().first().mouseReleased(null,null,null);
        System.out.println("%");
        for (PlaceLabel p:  wa_.getBattle().getBattle().getPlacesLabels()) {
            System.out.println(p.isSelected());
        }
        wa_.getBattle().getBattle().getFighterFrontPanel().getListe().setSelectedIndice(1);
        ((MockCustComponent)rowZero_).getMouseIntRelListeners().first().mouseReleased(null,null,null);
        System.out.println("%");
        for (PlaceLabel p:  wa_.getBattle().getBattle().getPlacesLabels()) {
            System.out.println(p.isSelected());
        }
        wa_.getBattle().getBattle().getFighterBackPanel().getListe().setSelectedIndice(0);
        AbsPaintableLabel rowOne_ = wa_.getBattle().getBattle().getPlacesLabels().get(0).getPaintableLabel();
        ((MockCustComponent)rowOne_).getMouseIntRelListeners().first().mouseReleased(null,null,null);
        System.out.println("%");
        for (PlaceLabel p:  wa_.getBattle().getBattle().getPlacesLabels()) {
            System.out.println(p.isSelected());
        }
        wa_.getBattle().getBattle().getFighterBackPanel().getListe().setSelectedIndice(1);
        AbsPaintableLabel rowTwo_ = wa_.getBattle().getBattle().getPlacesLabels().get(1).getPaintableLabel();
        ((MockCustComponent)rowTwo_).getMouseIntRelListeners().first().mouseReleased(null,null,null);
        System.out.println("%");
        for (PlaceLabel p:  wa_.getBattle().getBattle().getPlacesLabels()) {
            System.out.println(p.isSelected());
        }

//        wa_.getBattle().getBattle().getFighterBackPanel().getListe().setSelectedIndice(1);
//        System.out.println("%");
//        for (PlaceLabel p:  wa_.getBattle().getBattle().getPlacesLabels()) {
//            System.out.println(p.isSelected());
//        }
//        paintableLabel.getMouseListeners().first();
//        System.out.println(wa_.getBattle().getBattle().getPlacesLabels().size());
    }
    @Test
    public void coeur() {
        long[] incrs_ = new long[]{1, 3, 5};
        MockFileSet set_ = fileSet(123, incrs_, "/");
        MockProgramInfos pr_ = new MockProgramInfos("","", new MockEventListIncr(0.75,new int[0],new String[0],new TextAnswerValue[0]), set_);
        pr_.getFileCoreStream().newFile("tmp").mkdirs();
        pr_.setCurrentPath("tmp");
        WindowAiki wa_ = new WindowAiki("fr", pr_, new AikiFactory(new MockAdvGraphicListGeneratorGene<BallNumberRate>(),new MockAdvGraphicListGeneratorGene<Fighter>(),new MockAdvGraphicListGeneratorGene<String>(),new MockAdvGraphicListGeneratorGene<String>(),new MockAdvGraphicListGeneratorGene<String>(), new MockAdvGraphicListGeneratorGene<UsablePokemon>()));
        wa_.getFacade().setSexList(new MockLSexList());
        wa_.pack();
        wa_.setVisible(true);
        DataBase init_ = init();
        init_.validate(new PerCentIncr(pr_.getThreadFactory().newAtomicInteger()),new LoadFlagImpl(pr_.getThreadFactory().newAtomicBoolean(true)),wa_.getFacade().getSexList());
        System.out.println(!init_.isError());
        FacadeGame fac_ = wa_.getFacade();
        init_.setMessages(fac_.getData());
        fac_.setLoadedData(true);
        fac_.setZipName("");
        fac_.setData(init_);
        fac_.initializePaginatorTranslations();
        wa_.getLoadFlag().set(false);
        wa_.setLoadingConf(new LoadingGame(), false);
        wa_.pack();
        fac_.newGame("", Sex.NO);
        Game g_ = fac_.getGame();
        WildPk pokemonDonne_ = Instances.newWildPk();
        pokemonDonne_.setAbility(PARATONNERRE);
        pokemonDonne_.setItem(POKE_BALL);
        pokemonDonne_.setGender(Gender.NO_GENDER);
        pokemonDonne_.setLevel((short) 6);
        pokemonDonne_.setName(PIKACHU);
        g_.getPlayer().recevoirPokemon(pokemonDonne_,g_.getDifficulty(),init_);
        g_.getPlayer().recevoirPokemon(pokemonDonne_,g_.getDifficulty(),init_);
        g_.getPlayer().recevoirPokemon(pokemonDonne_,g_.getDifficulty(),init_);
        ((PokemonPlayer)g_.getPlayer().getTeam().get(0)).learnMove(CHARGE2,init_);
        ((PokemonPlayer)g_.getPlayer().getTeam().get(1)).learnMove(CHARGE2,init_);
        g_.setPlayerCoords(newCoords(0,0,1,1,2,3));
        g_.setPlayerOrientation(Direction.UP);
        g_.initTrainerFight(init_);
//        Fighter first_ = g_.getFight().getFighter(Fight.toFoeFighter((byte) 0));
//        Fighter second_ = g_.getFight().getFighter(Fight.toFoeFighter((byte) 1));
//        first_.getRemainingHp().affectZero();
//        first_.setGroundPlace(Fighter.BACK);
//        second_.getRemainingHp().affectZero();
//        second_.setGroundPlace(Fighter.BACK);
//        Team equipeUt_=g_.getFight().getUserTeam();
//        for(byte c: equipeUt_.getPlayerFightersAgainstFoe().getKeys()){
//            equipeUt_.getPlayerFightersAgainstFoe().getVal(c).removeOneNumber(0);
//            equipeUt_.getPlayerFightersAgainstFoe().getVal(c).removeOneNumber(1);
//        }
//        g_.getFight().setState(FightState.SWITCH_PROPOSE);
        g_.getFight().getFirstPositFoeFighters().put((byte) 0, Fighter.BACK);
        g_.getFight().getFirstPositFoeFighters().put((byte) 1, Fighter.BACK);
        g_.getFight().getFirstPositFoeFighters().put((byte) 2, (byte) 0);
        g_.getFight().getFirstPositFoeFighters().put((byte) 3, (byte) 1);

        Fighter firstUs_ = g_.getFight().getFighter(Fight.toUserFighter((byte) 0));
        Fighter secondUs_ = g_.getFight().getFighter(Fight.toUserFighter((byte) 1));
        byte firGrSub_ = firstUs_.getGroundPlaceSubst();
        byte secGrSub_ = secondUs_.getGroundPlaceSubst();
        firstUs_.setGroundPlaceSubst(secGrSub_);
        secondUs_.setGroundPlaceSubst(firGrSub_);
        byte firGr_ = firstUs_.getGroundPlace();
        byte secGr_ = secondUs_.getGroundPlace();
        firstUs_.setGroundPlace(secGr_);
        secondUs_.setGroundPlace(firGr_);
        /*Team equipe_=_fight.getTeams().getVal(_combattant.getTeam());
        if(_fight.getFighter(_combattant).isBelongingToPlayer()){
            equipe_.toutSupprimerCombattantsContreAdvMembre(_combattant.getPosition());
            _fight.getFirstPositPlayerFighters().put(_combattant.getPosition(),Fighter.BACK);
        }else if(NumberUtil.eq(_combattant.getTeam(),Fight.CST_FOE)){
            Team equipeUt_=_fight.getUserTeam();
            Bytes liste_ = FightOrder.fightersBelongingToUserHavingBeaten(_fight,_combattant.getPosition());
            addExpEvsFighters(_fight,liste_,_combattant.getPosition(),_diff,_import);
            equipeUt_.toutSupprimerCombattantsContreAdv(_combattant.getPosition());
        }*/
        System.out.println(fac_.checkAndSetGame(g_));
        fac_.load(g_);
        fac_.changeCamera(g_.getPlayerOrientation());
        wa_.drawGameWalking(true);
        wa_.interact();
        wa_.setFight(false,false);
        wa_.getBattle().getBattle().getFighterFrontPanel().getListe().setSelectedIndice(0);
        ((MockPaintableLabelAbs)wa_.getBattle().getBattle().getMovesLabels().get(1).getPaintableLabel()).getMouseIntRelListeners().first().mouseReleased(null,null,null);
        ((MockPaintableLabelAbs)wa_.getBattle().getBattle().getTargets().getFoeTargets().get(1).getPaintableLabel()).getMouseIntRelListeners().first().mouseReleased(null,null,null);
//        wa_.getBattle().getBattle().getFighterFrontPanel().getListe().setSelectedIndice(0);
//        ((MockPaintableLabelAbs)wa_.getBattle().getBattle().getMovesLabels().get(1).getPaintableLabel()).getMouseIntRelListeners().first().mouseReleased(null,null,null);
//        ((MockPaintableLabelAbs)wa_.getBattle().getBattle().getTargets().getFoeTargets().get(1).getPaintableLabel()).getMouseIntRelListeners().first().mouseReleased(null,null,null);
//        AbsPaintableLabel rowZero_ = wa_.getBattle().getBattle().getPlacesLabels().last().getPaintableLabel();
//        ((MockCustComponent)rowZero_).getMouseIntRelListeners().first().mouseReleased(null,null,null);
//        System.out.println("%");
//        for (PlaceLabel p:  wa_.getBattle().getBattle().getPlacesLabels()) {
//            System.out.println(p.isSelected());
//        }
//        wa_.getBattle().getBattle().getFighterFrontPanel().getListe().setSelectedIndice(1);
//        ((MockCustComponent)rowZero_).getMouseIntRelListeners().first().mouseReleased(null,null,null);
//        System.out.println("%");
//        for (PlaceLabel p:  wa_.getBattle().getBattle().getPlacesLabels()) {
//            System.out.println(p.isSelected());
//        }
//        wa_.getBattle().getBattle().getFighterBackPanel().getListe().setSelectedIndice(0);
//        AbsPaintableLabel rowOne_ = wa_.getBattle().getBattle().getPlacesLabels().get(0).getPaintableLabel();
//        ((MockCustComponent)rowOne_).getMouseIntRelListeners().first().mouseReleased(null,null,null);
//        System.out.println("%");
//        for (PlaceLabel p:  wa_.getBattle().getBattle().getPlacesLabels()) {
//            System.out.println(p.isSelected());
//        }
//        wa_.getBattle().getBattle().getFighterBackPanel().getListe().setSelectedIndice(1);
//        AbsPaintableLabel rowTwo_ = wa_.getBattle().getBattle().getPlacesLabels().get(1).getPaintableLabel();
//        ((MockCustComponent)rowTwo_).getMouseIntRelListeners().first().mouseReleased(null,null,null);
//        System.out.println("%");
//        for (PlaceLabel p:  wa_.getBattle().getBattle().getPlacesLabels()) {
//            System.out.println(p.isSelected());
//        }

//        wa_.getBattle().getBattle().getFighterBackPanel().getListe().setSelectedIndice(1);
//        System.out.println("%");
//        for (PlaceLabel p:  wa_.getBattle().getBattle().getPlacesLabels()) {
//            System.out.println(p.isSelected());
//        }
//        paintableLabel.getMouseListeners().first();
//        System.out.println(wa_.getBattle().getBattle().getPlacesLabels().size());
    }
    private static DataBase init() {
        DataBase data_ = newData();
        data_.setLanguage(LANGUAGE);
        data_.setLanguages(new StringList(LANGUAGE));
        data_.initializeMembers();
        initConstants(data_);
        AbilityData ab_ = Instances.newAbilityData();
        data_.completeMembers(PARATONNERRE,ab_);
        Ball ball_ = Instances.newBall();
        data_.completeMembers(POKE_BALL,ball_);
        DamagingMoveData move_ = Instances.newDamagingMoveData();
        EffectDamage eff_ = Instances.newEffectDamage();
        eff_.setPower("100");
        eff_.setFail("");
        eff_.setTargetChoice(TargetChoice.TOUS_ADV);
        eff_.setStatisAtt(Statistic.ATTACK);
        move_.getEffects().add(eff_);
        move_.setTargetChoice(TargetChoice.TOUS_ADV);
        move_.setTypes(new StringList(ELECTRICK));
        move_.setCategory("SPEC");
        move_.setAccuracy("1");
        move_.setPp((short) 1);
        data_.completeMembers(ECLAIR,move_);
        DamagingMoveData move2_ = Instances.newDamagingMoveData();
        EffectDamage eff2_ = Instances.newEffectDamage();
        eff2_.setPower("100");
        eff2_.setFail("");
        eff2_.setTargetChoice(TargetChoice.TOUS_ADV);
        eff2_.setStatisAtt(Statistic.SPECIAL_ATTACK);
        move2_.getEffects().add(eff2_);
        move2_.setTargetChoice(TargetChoice.TOUS_ADV);
        move2_.setTypes(new StringList(ELECTRICK));
        move2_.setCategory("SPEC");
        move2_.setAccuracy("1");
        move2_.setPp((short) 1);
        data_.completeMembers(LUTTE,move2_);
        DamagingMoveData move3_ = Instances.newDamagingMoveData();
        EffectDamage eff3_ = Instances.newEffectDamage();
        eff3_.setPower("100");
        eff3_.setFail("");
        eff3_.setTargetChoice(TargetChoice.TOUS_ADV);
        eff3_.setStatisAtt(Statistic.SPECIAL_ATTACK);
        move3_.getEffects().add(eff3_);
        move3_.setTargetChoice(TargetChoice.TOUS_ADV);
        move3_.setTypes(new StringList(ELECTRICK));
        move3_.setCategory("SPEC");
        move3_.setAccuracy("1");
        move3_.setPp((short) 1);
        data_.completeMembers(CHARGE,move3_);
        DamagingMoveData move4_ = Instances.newDamagingMoveData();
        EffectDamage eff4_ = Instances.newEffectDamage();
        eff4_.setPower("100");
        eff4_.setFail("");
        eff4_.setTargetChoice(TargetChoice.ANY_FOE);
        eff4_.setStatisAtt(Statistic.SPECIAL_ATTACK);
        move4_.getEffects().add(eff4_);
        move4_.setTargetChoice(TargetChoice.ANY_FOE);
        move4_.setTypes(new StringList(ELECTRICK));
        move4_.setCategory("SPEC");
        move4_.setAccuracy("1");
        move4_.setPp((short) 1);
        data_.completeMembers(CHARGE2,move4_);
        PokemonData pkData_ = Instances.newPokemonData();
        pkData_.setBaseEvo(PIKACHU);
        pkData_.setEggGroups(new StringList(data_.getDefaultEggGroup()));
        pkData_.setTypes(new StringList(ELECTRICK));
        pkData_.getStatistics().addEntry(Statistic.ATTACK,new StatBaseEv((short)1,(short)0));
        pkData_.getStatistics().addEntry(Statistic.DEFENSE,new StatBaseEv((short)1,(short)0));
        pkData_.getStatistics().addEntry(Statistic.SPECIAL_ATTACK,new StatBaseEv((short)1,(short)0));
        pkData_.getStatistics().addEntry(Statistic.SPECIAL_DEFENSE,new StatBaseEv((short)1,(short)0));
        pkData_.getStatistics().addEntry(Statistic.SPEED,new StatBaseEv((short)1,(short)0));
        pkData_.getStatistics().addEntry(Statistic.HP,new StatBaseEv((short)1,(short)0));
        pkData_.getLevMoves().add(new LevelMove((short)1,ECLAIR));
        pkData_.getLevMoves().add(new LevelMove((short)1,CHARGE));
        pkData_.setExpRate(1);
        pkData_.setHeight(Rate.one());
        pkData_.setWeight(Rate.one());
        pkData_.setCatchingRate((short) 1);
        pkData_.setHappiness((short) 1);
        pkData_.setHappinessHatch((short) 1);
        pkData_.setAbilities(new StringList(PARATONNERRE));
        data_.completeMembers(PIKACHU,pkData_);
        data_.getTableTypes().addEntry(new TypesDuo(ELECTRICK,ELECTRICK),new Rate("1"));
        data_.getTm().addEntry((short)100,ECLAIR);
        data_.sortEndRound();
        initPlaces(data_);
        MiniMapCoordsList miniMap_ = new MiniMapCoordsList();
        TileMiniMap v_ = Instances.newTileMiniMap();
        v_.setPlace((short) 1);
        v_.setFile("1");
        miniMap_.addEntry(new MiniMapCoords((short) 0, (short) 0), v_);
        TileMiniMap v2_ = Instances.newTileMiniMap();
        v2_.setFile("2");
        miniMap_.addEntry(new MiniMapCoords((short) 0, (short) 1), v2_);
        data_.getMap().setMiniMap(miniMap_);
        data_.getMap().setUnlockedCity("3");
        data_.getMap().setSideLength(1);
        DataMap map_ = data_.getMap();
        WildPk pkm_ = new WildPk();
        pkm_.setName(PIKACHU);
        pkm_.setAbility(PARATONNERRE);
        pkm_.setGender(Gender.NO_GENDER);
        pkm_.setItem(NULL_REF);
        pkm_.setLevel((short) 7);
        map_.setFirstPokemon(pkm_);
        map_.setBegin(newCoords(0, 0, 0, 1));
        data_.completeVariables();
        data_.addConstNumTest(DataBase.STRONG_MOVE,new Rate(90));
        initRandomLaws(data_);
        initExpPointsSec(data_);
        data_.initCombosTest();
        data_.initTypesByTable();
        City city_ = Instances.newCity();
        PokemonCenter pokemonCenter_ = Instances.newPokemonCenter();
        Block blInside_ = Instances.newBlock();
        blInside_.setHeight((short) 6);
        blInside_.setWidth((short) 6);
        blInside_.setTileFileName("6_6");
        pokemonCenter_.getIndoor().getBlocks().addEntry(new Point((short)0,(short)0), blInside_);
        Seller seller_ = Instances.newSeller();
        seller_.getItems().add(POKE_BALL);
        seller_.setSell(SellType.ITEM);
        seller_.setImageMiniFileName("1_1");
        pokemonCenter_.getIndoor().getGerants().addEntry(new Point((short)1,(short)3),seller_);
        seller_ = Instances.newSeller();
        seller_.setSell(SellType.MOVE);
        seller_.setImageMiniFileName("1_1");
        pokemonCenter_.getIndoor().getGerants().addEntry(new Point((short)1,(short)4),seller_);
        GerantPokemon healer_ = Instances.newGerantPokemon();
        healer_.setGerance(GeranceType.HEAL);
        healer_.setImageMiniFileName("1_1");
        pokemonCenter_.getIndoor().getGerants().addEntry(new Point((short)2,(short)4),healer_);
        pokemonCenter_.getIndoor().setStorageCoords(new Point((short)1,(short)5));
        pokemonCenter_.setImageFileName("1_1");
        city_.getBuildings().addEntry(new Point((short)0,(short)0), pokemonCenter_);
        Gym gym_ = Instances.newGym();
        GymLeader gymLeader_ = Instances.newGymLeader();
        PkTrainer pkg_ = new PkTrainer();
        pkg_.setName(PIKACHU);
        pkg_.setAbility(PARATONNERRE);
        pkg_.setGender(Gender.NO_GENDER);
        pkg_.setItem(NULL_REF);
        pkg_.setLevel((short) 7);
        pkg_.setMoves(new StringList(ECLAIR));
        gymLeader_.getTeam().add(pkg_);
        gymLeader_.setReward((short) 1);
        gymLeader_.setTm((short)100);
        gymLeader_.setImageMiniFileName("1_1");
        gymLeader_.setImageMaxiFileName("1_1");
        Block block_ = Instances.newBlock();
        block_.setType(EnvironmentType.BUILDING);
        block_.setWidth((short)11);
        block_.setHeight((short)11);
        block_.setTileFileName("11_11");
        gym_.getIndoor().getBlocks().addEntry(new Point((short)0,(short)0),block_);
        gym_.getIndoor().setGymLeader(gymLeader_);
        GymTrainer gt_ = Instances.newGymTrainer();
        PkTrainer pkt_ = new PkTrainer();
        pkt_.setName(PIKACHU);
        pkt_.setAbility(PARATONNERRE);
        pkt_.setGender(Gender.NO_GENDER);
        pkt_.setItem(NULL_REF);
        pkt_.setLevel((short) 7);
        pkt_.setMoves(new StringList(ECLAIR));
        gt_.getTeam().add(pkt_);
        gt_.getTeam().add(pkt_);
        gt_.getTeam().add(pkt_);
        gt_.getTeam().add(pkt_);
        gt_.setMultiplicityFight((byte) 2);
        gt_.setReward((short) 1);
        gt_.setImageMiniFileName("1_1");
        gt_.setImageMaxiFileName("1_1");
        gym_.setImageFileName("1_1");
        gym_.getIndoor().getGymTrainers().addEntry(new Point((short)2,(short)2), gt_);
        gym_.getIndoor().setGymLeaderCoords(new Point((short)5,(short)5));
        gym_.setExitCity(new Point((short)10,(short)10));
        city_.getBuildings().addEntry(new Point((short)1,(short)1), gym_);
        LevelOutdoor outd_ = Instances.newLevelOutdoor();
        Block outBl_ = Instances.newBlock();
        outBl_.setType(EnvironmentType.GRASS);
        outBl_.setHeight((short) 1);
        outBl_.setWidth((short) 1);
        outBl_.setTileFileName("1_1");
        outd_.getBlocks().addEntry(new Point((short)0,(short)1), outBl_);
        Block outBl2_ = Instances.newBlock();
        outBl2_.setType(EnvironmentType.GRASS);
        outBl2_.setHeight((short) 1);
        outBl2_.setWidth((short) 1);
        outBl2_.setTileFileName("1_1");
        outd_.getBlocks().addEntry(new Point((short)1,(short)0), outBl2_);
        Block door1_ = Instances.newBlock();
        door1_.setType(EnvironmentType.NOTHING);
        door1_.setHeight((short) 1);
        door1_.setWidth((short) 1);
        door1_.setTileFileName("1_1");
        outd_.getBlocks().addEntry(new Point((short)0,(short)0), door1_);
        Block door2_ = Instances.newBlock();
        door2_.setType(EnvironmentType.NOTHING);
        door2_.setHeight((short) 1);
        door2_.setWidth((short) 1);
        door2_.setTileFileName("1_1");
        outd_.getBlocks().addEntry(new Point((short)1,(short)1), door2_);
        Block outBl3_ = Instances.newBlock();
        outBl3_.setType(EnvironmentType.GRASS);
        outBl3_.setHeight((short) 1);
        outBl3_.setWidth((short) 2);
        outBl3_.setTileFileName("1_2");
        outd_.getBlocks().addEntry(new Point((short)0,(short)2), outBl3_);
        city_.setLevel(outd_);
        map_.getPlaces().add(city_);
        Road r_ = Instances.newRoad();
        Block gr_ = Instances.newBlock();
        gr_.setHeight((short) 2);
        gr_.setWidth((short) 2);
        gr_.setTileFileName("2_2");
        gr_.setIndexApparition((short)0);
        AreaApparition area_ = Instances.newAreaApparition();
        area_.getWildPokemon().add(pkm_);
        area_.setMultFight((byte)1);
        area_.setAvgNbSteps((byte)1);
        r_.getLevelRoad().getWildPokemonAreas().add(area_);
        r_.getLevelRoad().getBlocks().addEntry(new Point((short)0,(short)0), gr_);
        map_.getPlaces().add( r_);
        r_.getPointsWithCitiesAndOtherRoads().addEntry(new PlaceInterConnect(new Point((short) 0,(short)1), Direction.UP),newCoords(0,0,0,2));
        city_.getPointsWithCitiesAndOtherRoads().addEntry(new PlaceInterConnect(new Point((short) 0,(short)2), Direction.DOWN),newCoords(1,0,0,1));
        map_.setAccessCondition(new CoordsLists());
        data_.getAnimStatis().addEntry("ATTACK",new int[1][1]);
        data_.getAnimStatis().addEntry("DEFENSE",new int[1][1]);
        data_.getAnimStatis().addEntry("SPECIAL_ATTACK",new int[1][1]);
        data_.getAnimStatis().addEntry("SPECIAL_DEFENSE",new int[1][1]);
        data_.getAnimStatis().addEntry("SPEED",new int[1][1]);
        data_.getAnimStatis().addEntry("ACCURACY",new int[1][1]);
        data_.getAnimStatis().addEntry("EVASINESS",new int[1][1]);
        data_.getAnimStatis().addEntry("CRITICAL_HIT",new int[1][1]);
        data_.getTypesImages().addEntry(ELECTRICK,new int[1][1]);
        data_.getTypesColors().addEntry(ELECTRICK,"0;0;0");
        data_.getImages().addEntry("6_6",new int[6][6]);
        data_.getLinks().addEntry("1_1",new int[1][1]);
        data_.getPeople().addEntry("1_1",new int[1][1]);
        data_.getTrainers().addEntry("1_1",new int[1][1]);
        data_.getImages().addEntry("1_1",new int[1][1]);
        data_.getImages().addEntry("11_11",new int[11][11]);
        data_.getImages().addEntry("1_2",new int[1][2]);
        data_.getImages().addEntry("2_2",new int[2][2]);
        data_.getOverWorldHeros().addEntry(new ImageHeroKey(EnvironmentType.ROAD, Direction.DOWN, Sex.NO),new int[1][1]);
        data_.getOverWorldHeros().addEntry(new ImageHeroKey(EnvironmentType.ROAD, Direction.UP, Sex.NO),new int[1][1]);
        data_.getOverWorldHeros().addEntry(new ImageHeroKey(EnvironmentType.ROAD, Direction.LEFT, Sex.NO),new int[1][1]);
        data_.getOverWorldHeros().addEntry(new ImageHeroKey(EnvironmentType.ROAD, Direction.RIGHT, Sex.NO),new int[1][1]);
        data_.getFrontHeros().addEntry(new ImageHeroKey(EnvironmentType.ROAD, Sex.NO),new int[1][1]);
        data_.getBackHeros().addEntry(new ImageHeroKey(EnvironmentType.ROAD, Sex.NO),new int[1][1]);
//        data_.getOverWorldHeros().addEntry(new ImageHeroKey(EnvironmentType.ROAD, Direction.DOWN, Sex.GIRL),new int[1][1]);
//        data_.getOverWorldHeros().addEntry(new ImageHeroKey(EnvironmentType.ROAD, Direction.DOWN, Sex.BOY),new int[1][1]);
//        data_.getOverWorldHeros().addEntry(new ImageHeroKey(EnvironmentType.ROAD, Direction.UP, Sex.GIRL),new int[1][1]);
//        data_.getOverWorldHeros().addEntry(new ImageHeroKey(EnvironmentType.ROAD, Direction.UP, Sex.BOY),new int[1][1]);
//        data_.getOverWorldHeros().addEntry(new ImageHeroKey(EnvironmentType.ROAD, Direction.LEFT, Sex.GIRL),new int[1][1]);
//        data_.getOverWorldHeros().addEntry(new ImageHeroKey(EnvironmentType.ROAD, Direction.LEFT, Sex.BOY),new int[1][1]);
//        data_.getOverWorldHeros().addEntry(new ImageHeroKey(EnvironmentType.ROAD, Direction.RIGHT, Sex.GIRL),new int[1][1]);
//        data_.getOverWorldHeros().addEntry(new ImageHeroKey(EnvironmentType.ROAD, Direction.RIGHT, Sex.BOY),new int[1][1]);
//        data_.getFrontHeros().addEntry(new ImageHeroKey(EnvironmentType.ROAD, Sex.GIRL),new int[1][1]);
//        data_.getFrontHeros().addEntry(new ImageHeroKey(EnvironmentType.ROAD, Sex.BOY),new int[1][1]);
//        data_.getBackHeros().addEntry(new ImageHeroKey(EnvironmentType.ROAD, Sex.GIRL),new int[1][1]);
//        data_.getBackHeros().addEntry(new ImageHeroKey(EnvironmentType.ROAD, Sex.BOY),new int[1][1]);
        data_.setAnimAbsorb(new int[1][1]);
        data_.setStorage(new int[1][1]);
        data_.setImageTmHm(new int[1][1]);
        data_.getMiniPk().addEntry(PIKACHU,new int[1][1]);
        data_.getMaxiPkBack().addEntry(PIKACHU,new int[1][1]);
        data_.getMaxiPkFront().addEntry(PIKACHU,new int[1][1]);
        data_.getMiniItems().addEntry(POKE_BALL,new int[1][1]);
        data_.setEndGameImage(new int[1][1]);
        data_.getMiniMap().addEntry("1", new int[1][1]);
        int[][] ig_ = new int[1][1];
        ig_[0][0] = 1;
        data_.getMiniMap().addEntry("2", ig_);
        int[][] ig2_ = new int[1][1];
        ig2_[0][0] = 2;
        data_.getMiniMap().addEntry("3", ig2_);
        IdMap<Gender, String> gdrs_ = new IdMap<Gender, String>();
        gdrs_.addEntry(Gender.NO_GENDER,"NO_GENDER");
        gdrs_.addEntry(Gender.FEMALE,"FEMALE");
        gdrs_.addEntry(Gender.MALE,"MALE");
        data_.getTranslatedGenders().addEntry(LANGUAGE, gdrs_);
        IdMap<SelectedBoolean, String> bools_ = new IdMap<SelectedBoolean, String>();
        bools_.addEntry(SelectedBoolean.NO,"NO");
        bools_.addEntry(SelectedBoolean.YES,"YES");
        bools_.addEntry(SelectedBoolean.YES_AND_NO,"YES_AND_NO");
        data_.getTranslatedBooleans().addEntry(LANGUAGE, bools_);
        IdMap<DifficultyWinPointsFight, String> wfn_ = new IdMap<DifficultyWinPointsFight, String>();
        wfn_.addEntry(DifficultyWinPointsFight.TRES_DIFFICILE,"TRES_DIFFICILE");
        wfn_.addEntry(DifficultyWinPointsFight.DIFFICILE,"DIFFICILE");
        wfn_.addEntry(DifficultyWinPointsFight.FACILE,"FACILE");
        wfn_.addEntry(DifficultyWinPointsFight.TRES_FACILE,"TRES_FACILE");
        data_.getTranslatedDiffWinPts().addEntry(LANGUAGE, wfn_);
        IdMap<DifficultyModelLaw, String> ml_ = new IdMap<DifficultyModelLaw, String>();
        ml_.addEntry(DifficultyModelLaw.CONSTANT_MIN,"CONSTANT_MIN");
        ml_.addEntry(DifficultyModelLaw.CROISSANT,"CROISSANT");
        ml_.addEntry(DifficultyModelLaw.UNIFORME,"UNIFORME");
        ml_.addEntry(DifficultyModelLaw.DECROISSANT,"DECROISSANT");
        ml_.addEntry(DifficultyModelLaw.CONSTANT_MAX,"CONSTANT_MAX");
        data_.getTranslatedDiffModelLaw().addEntry(LANGUAGE, ml_);
        IdMap<EnvironmentType, String> et_ = new IdMap<EnvironmentType, String>();
        et_.addEntry(EnvironmentType.ROAD,"ROAD");
        et_.addEntry(EnvironmentType.ROCK,"ROCK");
        et_.addEntry(EnvironmentType.NOTHING,"NOTHING");
        et_.addEntry(EnvironmentType.BUILDING,"BUILDING");
        et_.addEntry(EnvironmentType.GRASS,"GRASS");
        et_.addEntry(EnvironmentType.DESERT,"DESERT");
        et_.addEntry(EnvironmentType.ICE,"ICE");
        et_.addEntry(EnvironmentType.SNOW,"SNOW");
        et_.addEntry(EnvironmentType.WATER,"WATER");
        data_.getTranslatedEnvironment().addEntry(LANGUAGE, et_);
        IdMap<Statistic, String> stats_ = new IdMap<Statistic, String>();
        stats_.addEntry(Statistic.ATTACK,"ATTACK");
        stats_.addEntry(Statistic.SPECIAL_ATTACK,"SPECIAL_ATTACK");
        stats_.addEntry(Statistic.DEFENSE,"DEFENSE");
        stats_.addEntry(Statistic.SPECIAL_DEFENSE,"SPECIAL_DEFENSE");
        stats_.addEntry(Statistic.SPEED,"SPEED");
        stats_.addEntry(Statistic.ACCURACY,"ACCURACY");
        stats_.addEntry(Statistic.EVASINESS,"EVASINESS");
        stats_.addEntry(Statistic.HP,"HP");
        stats_.addEntry(Statistic.PV_RESTANTS,"PV_RESTANTS");
        stats_.addEntry(Statistic.CRITICAL_HIT,"CRITICAL_HIT");
        data_.getTranslatedStatistics().addEntry(LANGUAGE, stats_);
        IdMap<TargetChoice, String> tar_ = new IdMap<TargetChoice, String>();
        tar_.addEntry(TargetChoice.ADJ_ADV,"ADJ_ADV");
        tar_.addEntry(TargetChoice.ADJ_MULT,"ADJ_MULT");
        tar_.addEntry(TargetChoice.ANY_FOE,"ANY_FOE");
        tar_.addEntry(TargetChoice.ALLIE,"ALLIE");
        tar_.addEntry(TargetChoice.ALLIES,"ALLIES");
        tar_.addEntry(TargetChoice.AUTRE_UNIQ,"AUTRE_UNIQ");
        tar_.addEntry(TargetChoice.ADJ_UNIQ,"ADJ_UNIQ");
        tar_.addEntry(TargetChoice.GLOBALE,"GLOBALE");
        tar_.addEntry(TargetChoice.LANCEUR,"LANCEUR");
        tar_.addEntry(TargetChoice.NOTHING,"NOTHING");
        tar_.addEntry(TargetChoice.TOUS_ADV,"TOUS_ADV");
        tar_.addEntry(TargetChoice.PSEUDO_GLOBALE,"PSEUDO_GLOBALE");
        tar_.addEntry(TargetChoice.UNIQUE_IMPORTE,"UNIQUE_IMPORTE");
        data_.getTranslatedTargets().addEntry(LANGUAGE, tar_);
        data_.getTranslatedTypes().addEntry(LANGUAGE,tr(ELECTRICK,ELECTRICK));
        data_.getTranslatedPokemon().addEntry(LANGUAGE,tr(PIKACHU,PIKACHU));
        data_.getTranslatedItems().addEntry(LANGUAGE,tr(POKE_BALL,POKE_BALL));
        data_.getTranslatedAbilities().addEntry(LANGUAGE,tr(PARATONNERRE,PARATONNERRE));
        StringMap<String> trMov_ = tr(LUTTE, LUTTE);
        trMov_.addAllEntries(tr(ECLAIR,ECLAIR));
        trMov_.addAllEntries(tr(CHARGE,CHARGE));
        trMov_.addAllEntries(tr(CHARGE2,CHARGE2));
        data_.getTranslatedMoves().addEntry(LANGUAGE, trMov_);
        data_.getTranslatedStatus().addEntry(LANGUAGE,new StringMap<String>());
        data_.getTranslatedCategories().addEntry(LANGUAGE,tr("SPEC","SPEC"));
        StringMap<String> trFct_ = new StringMap<String>();
        for (String f: EvolvedMathFactory.getFunctions()) {
            trFct_.addEntry(f,f);
        }
        data_.getTranslatedFctMath().addEntry(LANGUAGE,trFct_);
        data_.getTranslatedClassesDescriptions().addEntry(LANGUAGE,tr("aiki.fight.items.Ball","BALLON"));
        data_.getLitterals().addEntry(LANGUAGE,new StringMap<String>());
        return data_;
    }
    private static StringMap<String> tr(String _k, String _v) {
        StringMap<String> t_ = new StringMap<String>();
        t_.addEntry(_k, _v);
        return t_;
    }
    static void initExpPointsSec(DataBase _data) {
        _data.getExpGrowth().put(ExpType.E,"2*VAR__NIVEAU");
        _data.getExpGrowth().put(ExpType.L,"5/4*puis(VAR__NIVEAU,3)");
        _data.getExpGrowth().put(ExpType.M,"puis(VAR__NIVEAU,3)");
        _data.getExpGrowth().put(ExpType.P,"puis(VAR__NIVEAU,2)");
        _data.getExpGrowth().put(ExpType.F,"VAR__NIVEAU");
        _data.getExpGrowth().put(ExpType.R,"4/5*puis(VAR__NIVEAU,3)");
        _data.getRates().put(DifficultyWinPointsFight.TRES_FACILE, "4");
        _data.getRates().put(DifficultyWinPointsFight.FACILE, "2");
        _data.getRates().put(DifficultyWinPointsFight.DIFFICILE, "1");
        _data.getRates().put(DifficultyWinPointsFight.TRES_DIFFICILE, "1/2");
    }

    protected static void initConstants(DataBase _data) {
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
        initDefaultConsts(POKE_BALL,
                "caracdroiteferme(div(VAR__FOE_PK_MAX_HP,VAR__FOE_PK_REMOTE_HP),2)",
                "caracdroiteferme(div(VAR__PK_UT_VITESSE,VAR__PK_SAUVAGE_VITESSE),1)",
                "div(2*caracgaucheouvert(VAR__BOOST,0),max(2-VAR__BOOST,1))+div((2+VAR__BOOST)*caracdroiteferme(VAR__BOOST,0),2)",
                "puis(2,VAR__BOOST-4)",
                "div((5+VAR__LANCEUR_NIVEAU)*VAR__ATTACK*VAR__POWER,(125*VAR__DEFENSE))",
                LUTTE,
                "METAMORPH", _data);
    }
    static void initDefaultConsts(String _ballDef, String _rateCatching,
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
        _db.setDefCategory("AUTRE");
    }
    protected static void initExpPoints(DataBase _data) {
        _data.getExpGrowth().put(ExpType.E,"2*NIVEAU");
        _data.getExpGrowth().put(ExpType.L,"5/4*puis(VAR__NIVEAU,3)");
        _data.getExpGrowth().put(ExpType.M,"puis(VAR__NIVEAU,3)");
        _data.getExpGrowth().put(ExpType.P,"puis(VAR__NIVEAU,2)");
        _data.getExpGrowth().put(ExpType.F,"VAR__NIVEAU");
        _data.getExpGrowth().put(ExpType.R,"4/5*puis(VAR__NIVEAU,3)");
        _data.getRates().put(DifficultyWinPointsFight.TRES_FACILE, "4");
        _data.getRates().put(DifficultyWinPointsFight.FACILE, "2");
        _data.getRates().put(DifficultyWinPointsFight.DIFFICILE, "1");
        _data.getRates().put(DifficultyWinPointsFight.TRES_DIFFICILE, "1/2");
    }

    protected static Coords newCoords(int _place, int _level, int _x, int _y) {
        Coords begin_ = new Coords();
        begin_.setNumberPlace((short) _place);
        begin_.setLevel(new LevelPoint());
        begin_.getLevel().setLevelIndex((byte) _level);
        begin_.getLevel().setPoint(newPoint(_x, _y));
        return begin_;
    }

    protected static Coords newCoords(int _place, int _level, int _xi, int _yi, int _x, int _y) {
        Coords begin_ = new Coords();
        begin_.setNumberPlace((short) _place);
        begin_.affectInside(newPoint(_xi, _yi));
        begin_.setLevel(new LevelPoint());
        begin_.getLevel().setLevelIndex((byte) _level);
        begin_.getLevel().setPoint(newPoint(_x, _y));
        return begin_;
    }

    protected static Point newPoint(int _x, int _y) {
        return new Point((short)_x, (short)_y);
    }

    protected static void initRandomLaws(DataBase _data) {
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
        _data.getLawsDamageRate().put(DifficultyModelLaw.CROISSANT,new LawNumber(monteCarloNumber_,(short)4));
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
        _data.getLawsDamageRate().put(DifficultyModelLaw.UNIFORME,new LawNumber(monteCarloNumber_,(short)3));
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
        _data.getLawsDamageRate().put(DifficultyModelLaw.DECROISSANT,new LawNumber(monteCarloNumber_,(short)2));
        monteCarloNumber_ = new MonteCarloNumber();
        monteCarloNumber_.addQuickEvent(new Rate("17/20"),new LgInt("1"));
        _data.getLawsDamageRate().put(DifficultyModelLaw.CONSTANT_MIN,new LawNumber(monteCarloNumber_,(short)1));
        monteCarloNumber_ = new MonteCarloNumber();
        monteCarloNumber_.addQuickEvent(new Rate("1"),new LgInt("1"));
        _data.getLawsDamageRate().put(DifficultyModelLaw.CONSTANT_MAX,new LawNumber(monteCarloNumber_,(short)5));
    }

    private static DataBase newData() {
        return new DataBase(DefaultGenerator.oneElt());
    }

    private static void initPlaces(DataBase _data) {
        _data.getMap().setPlaces(new CustList<Place>());
    }
}
