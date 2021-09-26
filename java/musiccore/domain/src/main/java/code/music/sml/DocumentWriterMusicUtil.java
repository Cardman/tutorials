package code.music.sml;

import code.music.core.MetaNote;
import code.music.core.MetaPart;
import code.music.core.MetaPhrase;
import code.music.core.MetaScore;
import code.music.enums.Gamme;
import code.sml.Document;
import code.sml.DocumentBuilder;
import code.sml.Element;
import code.sml.core.DocumentWriterCoreUtil;
import code.util.CustList;

public class DocumentWriterMusicUtil {
    private static final String LIST = "l";
    private static final String GAMME = "Gamme";
    private static final String PARTS = "parts";
    private static final String EVOLVED_SCORE = "MetaScore";
    private static final String EMPTY_STRING = "";
    private static final String NOTES = "notes";
    private static final String EVOLVED_PHRASE = "MetaPhrase";
    private static final String DENOMINATOR = "denominator";
    private static final String NUMERATOR = "numerator";
    private static final String NAME = "name";
    private static final String CHANNEL = "channel";
    private static final String INSTRUMENT = "instrument";
    private static final String PHRASES = "phrases";
    private static final String EVOLVED_PART = "MetaPart";
    private static final String DYNAMIC = "dynamic";
    private static final String DURATION_DEN = "durationDen";
    private static final String DURATION_NUM = "durationNum";
    private static final String PAUSE = "pause";
    private static final String DIESE = "diese";
    private static final String LEVEL = "level";
    private static final String VALUE = "value";
    private static final String EVOLVED_NOTE = "MetaNote";

    private static Element setEvolvedNote(MetaNote _object, String _fieldName, Document _document) {
        Element element_ = _document.createElement(EVOLVED_NOTE);
        DocumentWriterCoreUtil.setFieldName(element_, _fieldName);
        setEvolvedNote(_object,element_,_document);
        return element_;
    }

    private static void setEvolvedNote(MetaNote _object, Element _element, Document _document) {
        _element.appendChild(setGamme(_object.getValue(),VALUE,_document));
        _element.appendChild(DocumentWriterCoreUtil.setInteger(_object.getLevel(),LEVEL,_document));
        _element.appendChild(DocumentWriterCoreUtil.setBoolean(_object.isDiese(),DIESE,_document));
        _element.appendChild(DocumentWriterCoreUtil.setBoolean(_object.isPause(),PAUSE,_document));
        _element.appendChild(DocumentWriterCoreUtil.setInteger(_object.getDurationNum(),DURATION_NUM,_document));
        _element.appendChild(DocumentWriterCoreUtil.setInteger(_object.getDurationDen(),DURATION_DEN,_document));
        _element.appendChild(DocumentWriterCoreUtil.setInteger(_object.getDynamic(),DYNAMIC,_document));
    }

    private static Element setEvolvedPart(MetaPart _object, String _fieldName, Document _document) {
        Element element_ = _document.createElement(EVOLVED_PART);
        DocumentWriterCoreUtil.setFieldName(element_, _fieldName);
        setEvolvedPart(_object,element_,_document);
        return element_;
    }

    private static void setEvolvedPart(MetaPart _object, Element _element, Document _document) {
        _element.appendChild(setListEvolvedPhrase(_object.getPhrases(),PHRASES,_document));
        _element.appendChild(DocumentWriterCoreUtil.setInteger(_object.getInstrument(),INSTRUMENT,_document));
        _element.appendChild(DocumentWriterCoreUtil.setInteger(_object.getChannel(),CHANNEL,_document));
        _element.appendChild(DocumentWriterCoreUtil.setString(_object.getName(),NAME,_document));
        _element.appendChild(DocumentWriterCoreUtil.setInteger(_object.getNumerator(),NUMERATOR,_document));
        _element.appendChild(DocumentWriterCoreUtil.setInteger(_object.getDenominator(),DENOMINATOR,_document));
    }

    private static Element setEvolvedPhrase(MetaPhrase _object, String _fieldName, Document _document) {
        Element element_ = _document.createElement(EVOLVED_PHRASE);
        DocumentWriterCoreUtil.setFieldName(element_, _fieldName);
        setEvolvedPhrase(_object,element_,_document);
        return element_;
    }

    private static void setEvolvedPhrase(MetaPhrase _object, Element _element, Document _document) {
        _element.appendChild(setListEvolvedNote(_object.getNotes(),NOTES,_document));
        _element.appendChild(DocumentWriterCoreUtil.setInteger(_object.getNumerator(),NUMERATOR,_document));
        _element.appendChild(DocumentWriterCoreUtil.setInteger(_object.getDenominator(),DENOMINATOR,_document));
    }

    public static String setEvolvedScore(MetaScore _object) {
        Document doc_ = DocumentBuilder.newXmlDocument();
        doc_.appendChild(setEvolvedScore(_object, EMPTY_STRING, doc_));
        return doc_.export();
    }

    public static Element setEvolvedScore(MetaScore _object, String _fieldName, Document _document) {
        Element element_ = _document.createElement(EVOLVED_SCORE);
        DocumentWriterCoreUtil.setFieldName(element_, _fieldName);
        setEvolvedScore(_object,element_,_document);
        return element_;
    }

    private static void setEvolvedScore(MetaScore _object, Element _element, Document _document) {
        _element.appendChild(setListEvolvedPart(_object.getParts(),PARTS,_document));
        _element.appendChild(DocumentWriterCoreUtil.setString(_object.getName(),NAME,_document));
    }

    private static Element setGamme(Gamme _object, String _fieldName, Document _document) {
        Element elt_ = _document.createElement(GAMME);
        DocumentWriterCoreUtil.setFieldName(elt_, _fieldName);
        elt_.setAttribute(VALUE,_object.name());
        return elt_;
    }

    private static Element setListEvolvedNote(CustList<MetaNote> _object, String _fieldName, Document _document) {
        Element elt_ = _document.createElement(LIST);
        DocumentWriterCoreUtil.setFieldName(elt_, _fieldName);
        for (MetaNote s: _object) {
            elt_.appendChild(setEvolvedNote(s,EMPTY_STRING,_document));
        }
        return elt_;
    }

    private static Element setListEvolvedPart(CustList<MetaPart> _object, String _fieldName, Document _document) {
        Element elt_ = _document.createElement(LIST);
        DocumentWriterCoreUtil.setFieldName(elt_, _fieldName);
        for (MetaPart s: _object) {
            elt_.appendChild(setEvolvedPart(s,EMPTY_STRING,_document));
        }
        return elt_;
    }

    private static Element setListEvolvedPhrase(CustList<MetaPhrase> _object, String _fieldName, Document _document) {
        Element elt_ = _document.createElement(LIST);
        DocumentWriterCoreUtil.setFieldName(elt_, _fieldName);
        for (MetaPhrase s: _object) {
            elt_.appendChild(setEvolvedPhrase(s,EMPTY_STRING,_document));
        }
        return elt_;
    }
}
