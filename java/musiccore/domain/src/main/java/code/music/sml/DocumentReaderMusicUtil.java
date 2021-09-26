package code.music.sml;

import code.music.core.MetaNote;
import code.music.core.MetaPart;
import code.music.core.MetaPhrase;
import code.music.core.MetaScore;
import code.music.enums.Gamme;
import code.sml.Document;
import code.sml.DocumentBuilder;
import code.sml.Element;
import code.sml.ElementList;
import code.sml.core.DocumentReaderCoreUtil;
import code.util.CollCapacity;
import code.util.CustList;
import code.util.core.StringUtil;

public final class DocumentReaderMusicUtil {
    private static final String PARTS = "parts";
    private static final String NOTES = "notes";
    private static final String DENOMINATOR = "denominator";
    private static final String NUMERATOR = "numerator";
    private static final String NAME = "name";
    private static final String CHANNEL = "channel";
    private static final String INSTRUMENT = "instrument";
    private static final String PHRASES = "phrases";
    private static final String DYNAMIC = "dynamic";
    private static final String DURATION_DEN = "durationDen";
    private static final String DURATION_NUM = "durationNum";
    private static final String PAUSE = "pause";
    private static final String DIESE = "diese";
    private static final String LEVEL = "level";
    private static final String VALUE = "value";
    private static final String FIELD = "field";

    private static MetaNote getEvolvedNote(Element _element) {
        ElementList childElements_ = _element.getChildElements();
        MetaNote object_ = new MetaNote();
        object_.setValue(Gamme.SOL);
        for (Element c: childElements_) {
            getEvolvedNote(object_,c.getAttribute(FIELD),c);
        }
        return object_;
    }

    private static void getEvolvedNote(MetaNote _object, String _fieldName, Element _element) {
        if (StringUtil.quickEq(_fieldName, VALUE)) {
            _object.setValue(getGamme(_element));
            return;
        }
        if (StringUtil.quickEq(_fieldName, LEVEL)) {
            _object.setLevel(DocumentReaderCoreUtil.getInteger(_element));
            return;
        }
        if (StringUtil.quickEq(_fieldName, DIESE)) {
            _object.setDiese(DocumentReaderCoreUtil.getBoolean(_element));
            return;
        }
        if (StringUtil.quickEq(_fieldName, PAUSE)) {
            _object.setPause(DocumentReaderCoreUtil.getBoolean(_element));
            return;
        }
        if (StringUtil.quickEq(_fieldName, DURATION_NUM)) {
            _object.setDurationNum(DocumentReaderCoreUtil.getInteger(_element));
            return;
        }
        if (StringUtil.quickEq(_fieldName, DURATION_DEN)) {
            _object.setDurationDen(DocumentReaderCoreUtil.getInteger(_element));
            return;
        }
        if (StringUtil.quickEq(_fieldName, DYNAMIC)) {
            _object.setDynamic(DocumentReaderCoreUtil.getInteger(_element));
            return;
        }
    }

    private static MetaPart getEvolvedPart(Element _element) {
        ElementList childElements_ = _element.getChildElements();
        MetaPart object_ = new MetaPart();
        for (Element c: childElements_) {
            getEvolvedPart(object_,c.getAttribute(FIELD),c);
        }
        return object_;
    }

    private static void getEvolvedPart(MetaPart _object, String _fieldName, Element _element) {
        if (StringUtil.quickEq(_fieldName, PHRASES)) {
            _object.setPhrases(getListEvolvedPhrase(_element));
            return;
        }
        if (StringUtil.quickEq(_fieldName, INSTRUMENT)) {
            _object.setInstrument(DocumentReaderCoreUtil.getInteger(_element));
            return;
        }
        if (StringUtil.quickEq(_fieldName, CHANNEL)) {
            _object.setChannel(DocumentReaderCoreUtil.getInteger(_element));
            return;
        }
        if (StringUtil.quickEq(_fieldName, NAME)) {
            _object.setName(DocumentReaderCoreUtil.getString(_element));
            return;
        }
        if (StringUtil.quickEq(_fieldName, NUMERATOR)) {
            _object.setNumerator(DocumentReaderCoreUtil.getInteger(_element));
            return;
        }
        if (StringUtil.quickEq(_fieldName, DENOMINATOR)) {
            _object.setDenominator(DocumentReaderCoreUtil.getInteger(_element));
            return;
        }
    }

    private static MetaPhrase getEvolvedPhrase(Element _element) {
        ElementList childElements_ = _element.getChildElements();
        MetaPhrase object_ = new MetaPhrase();
        for (Element c: childElements_) {
            getEvolvedPhrase(object_,c.getAttribute(FIELD),c);
        }
        return object_;
    }

    private static void getEvolvedPhrase(MetaPhrase _object, String _fieldName, Element _element) {
        if (StringUtil.quickEq(_fieldName, NOTES)) {
            _object.setNotes(getListEvolvedNote(_element));
            return;
        }
        if (StringUtil.quickEq(_fieldName, NUMERATOR)) {
            _object.setNumerator(DocumentReaderCoreUtil.getInteger(_element));
            return;
        }
        if (StringUtil.quickEq(_fieldName, DENOMINATOR)) {
            _object.setDenominator(DocumentReaderCoreUtil.getInteger(_element));
            return;
        }
    }

    public static MetaScore getEvolvedScore(String _string) {
        Document doc_ = DocumentBuilder.parseSax(_string);
        return getEvolvedScore(doc_.getDocumentElement());
    }

    public static MetaScore getEvolvedScore(Element _element) {
        ElementList childElements_ = _element.getChildElements();
        MetaScore object_ = new MetaScore();
        for (Element c: childElements_) {
            getEvolvedScore(object_,c.getAttribute(FIELD),c);
        }
        return object_;
    }

    private static void getEvolvedScore(MetaScore _object, String _fieldName, Element _element) {
        if (StringUtil.quickEq(_fieldName, PARTS)) {
            _object.setParts(getListEvolvedPart(_element));
            return;
        }
        if (StringUtil.quickEq(_fieldName, NAME)) {
            _object.setName(DocumentReaderCoreUtil.getString(_element));
            return;
        }
    }

    private static Gamme getGamme(Element _elt) {
        for (Gamme e: Gamme.values()) {
            if (StringUtil.quickEq(e.name(),_elt.getAttribute(VALUE))) {
                return e;
            }
        }
        return null;
    }

    private static CustList<MetaNote> getListEvolvedNote(Element _elt) {
        ElementList childElements_ = _elt.getChildElements();
        int len_ = childElements_.getLength();
        CollCapacity cap_ = new CollCapacity(len_);
        CustList<MetaNote> list_ = new CustList<MetaNote>(cap_);
        for (Element c: childElements_) {
            list_.add(getEvolvedNote(c));
        }
        return list_;
    }

    private static CustList<MetaPart> getListEvolvedPart(Element _elt) {
        ElementList childElements_ = _elt.getChildElements();
        int len_ = childElements_.getLength();
        CollCapacity cap_ = new CollCapacity(len_);
        CustList<MetaPart> list_ = new CustList<MetaPart>(cap_);
        for (Element c: childElements_) {
            list_.add(getEvolvedPart(c));
        }
        return list_;
    }

    private static CustList<MetaPhrase> getListEvolvedPhrase(Element _elt) {
        ElementList childElements_ = _elt.getChildElements();
        int len_ = childElements_.getLength();
        CollCapacity cap_ = new CollCapacity(len_);
        CustList<MetaPhrase> list_ = new CustList<MetaPhrase>(cap_);
        for (Element c: childElements_) {
            list_.add(getEvolvedPhrase(c));
        }
        return list_;
    }
}
