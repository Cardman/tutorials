package code.finder.gui;

import code.finder.core.RegExpPart;
import code.finder.gui.events.ResultSystem;
import code.finder.gui.events.SelectFolder;
import code.gui.*;
import code.gui.events.QuittingEvent;
import code.gui.images.MetaDimension;
import code.gui.initialize.AbsCompoFactory;
import code.gui.initialize.AbstractProgramInfos;
import code.stream.StreamFolderFile;
import code.stream.StreamTextFile;
import code.util.CustList;
import code.util.StringList;
import code.util.StringMap;
import code.util.core.StringUtil;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

public final class WindowFinder extends GroupFrame {

    private StringList fileNames = new StringList();
    private final AbsTextField linesRegExp;
    private final AbsTextField linesContent;
    private final AbsTextField namesRegExp;
    private final AbsTextField namesContent;
    private final AbsTextField folderPath;
    private final AbsTextArea filesResult;
    private final AbsGraphicList<String> resultLines;
    private final AbsTextArea resultTextFile;

    public WindowFinder(AbstractProgramInfos _list) {
        super("en", _list);
        setTitle("Find or replace files");
        addWindowListener(new QuittingEvent(this));
        AbsCompoFactory compoFactory_ = getCompoFactory();
        AbsMenuBar menuBar_ = compoFactory_.newMenuBar();
        AbsMenu find_ = compoFactory_.newMenu("Find");
        AbsMenuItem bySystem_ = compoFactory_.newMenuItem("By system");
        bySystem_.addActionListener(new ResultSystem(this));
//        AbsMenuItem byFileResults_ = compoFactory_.newMenuItem("By file results");

        find_.addMenuItem(bySystem_);
        menuBar_.add(find_);
        setJMenuBar(menuBar_);

        AbsPanel center_ = compoFactory_.newPageBox();
        AbsPanel files_ = compoFactory_.newPageBox();
        AbsPanel lines_ = compoFactory_.newPageBox();
        AbsTabbedPane tabs_ = compoFactory_.newAbsTabbedPane();
        AbsPanel linesForm_ = compoFactory_.newLineBox();
        AbsPanel linesLabels_ = compoFactory_.newPageBox();
        addAlignLeftTop(linesForm_,linesLabels_);
        AbsPanel linesInputs_ = compoFactory_.newPageBox();
        addAlignLeftTop(linesForm_,linesInputs_);
        addAlignLeftTop(linesLabels_,compoFactory_.newPlainLabel("Regular expression"));
        linesRegExp = compoFactory_.newTextField(32);
        addAlignLeftTop(linesInputs_,linesRegExp);
        addAlignLeftTop(linesLabels_,compoFactory_.newPlainLabel("Content"));
        linesContent = compoFactory_.newTextField();
        addAlignLeftTop(linesInputs_,linesContent);
        tabs_.add("Lines filter",linesForm_);
        AbsPanel namesForm_ = compoFactory_.newLineBox();
        AbsPanel namesLabels_ = compoFactory_.newPageBox();
        addAlignLeftTop(namesForm_,namesLabels_);
        AbsPanel namesInputs_ = compoFactory_.newPageBox();
        addAlignLeftTop(namesForm_,namesInputs_);
        addAlignLeftTop(namesLabels_,compoFactory_.newPlainLabel("Regular expression"));
        namesRegExp = compoFactory_.newTextField(32);
        addAlignLeftTop(namesInputs_,namesRegExp);
        addAlignLeftTop(namesLabels_,compoFactory_.newPlainLabel("Content"));
        namesContent = compoFactory_.newTextField();
        addAlignLeftTop(namesInputs_,namesContent);
        tabs_.add("Names filter",namesForm_);
        AbsPanel folder_ = compoFactory_.newPageBox();
        folderPath = compoFactory_.newTextField();
        addAlignLeftTop(folder_,folderPath);
        AbsPlainButton select_ = compoFactory_.newPlainButton("Select");
        select_.addActionListener(new SelectFolder(this));
        addAlignLeftTop(folder_,select_);
        tabs_.add("Folder",folder_);
        filesResult = compoFactory_.newTextArea();
        AbsScrollPane scroll_ = compoFactory_.newAbsScrollPane(filesResult);
        scroll_.setPreferredSize(new MetaDimension(256,256));
        files_.add(scroll_);
        resultLines = getFrames().getGeneGraphicList().createStrList(getImageFactory(), new StringList(), compoFactory_);
        resultTextFile = compoFactory_.newTextArea();
        lines_.add(compoFactory_.newHorizontalSplitPane(resultLines.scroll(),resultTextFile));
        addAlignLeftTop(center_,tabs_);
        addAlignLeftTop(center_,files_);
        addAlignLeftTop(center_,lines_);
        setContentPane(center_);
        pack();
        setVisible(true);
    }
    private static void addAlignLeftTop(AbsPanel _par, AbsCustComponent _comp) {
        _comp.left();
        _comp.top();
        _par.add(_comp);
    }

    public void read() {
        FolderOpenDialog.setFolderOpenDialog(this, getLanguageKey(), false);
        String folderPathRead_ = FolderOpenDialog.getStaticSelectedPath(getFolderOpenDialog());
        if (folderPathRead_.isEmpty()) {
            return;
        }
        folderPath.setText(folderPathRead_);
    }

    public void resultSystem() {
        StringList res_ = searchSystem();
        if (res_ == null) {
            return;
        }
        StringMap<Integer> matches_ = filterFiles(res_);
        display(matches_.getKeys());
    }

    public void resultFiles() {
        StringList res_ = searchFiles();
        StringMap<Integer> matches_ = filterFiles(res_);
        display(matches_.getKeys());
    }

    private StringMap<Integer> filterFiles(StringList _files) {
        StringMap<Integer> out_ = new StringMap<Integer>();
        StringList content_ = filterList(linesContent.getText());
        Pattern pattern_ = patternOrNull(linesRegExp.getText());
        for (String f: _files) {
            String cont_ = StreamTextFile.contentsOfFile(f,getFileCoreStream(),getStreams());
            if (cont_ != null) {
                int nbMatches_ = nbMatches(content_, cont_, pattern_);
                if (nbMatches_ > 0) {
                    out_.addEntry(f,nbMatches_);
                }
            }
        }
        return out_;
    }
    private void display(CustList<String> _res) {
        StringList displ_ = new StringList();
        String path_ = folderPath.getText().trim();
        path_ = StringUtil.replaceBackSlashDot(path_);
        for (String n: _res) {
            displ_.add(extract(n,path_));
        }
        filesResult.setText(StringUtil.join(displ_,"\n"));
    }

    public StringList searchFiles() {
        String path_ = folderPath.getText().trim();
        if (path_.isEmpty()) {
            StringList files_ = new StringList();
            for (String l:StringUtil.splitChar(filesResult.getText(), '\n')) {
                if (StreamFolderFile.isAbsolute(l,getFileCoreStream())) {
                    files_.add(l);
                }
            }
            return filterFiles(path_,files_);
        }
        path_ = StringUtil.replaceBackSlashDot(path_);
        StringList files_ = new StringList();
        for (String l:StringUtil.splitChar(filesResult.getText(), '\n')) {
            if (StreamFolderFile.isAbsolute(l,getFileCoreStream())) {
                files_.add(l);
            } else {
                files_.add(path_+l);
            }
        }
        return filterFiles(path_,files_);
    }
    public StringList searchSystem() {
        String path_ = folderPath.getText().trim();
        if (path_.isEmpty()) {
            return null;
        }
        path_ = StringUtil.replaceBackSlashDot(path_);
        StringList files_ = StreamTextFile.allSortedFiles(path_, getFileCoreStream());
        return filterFiles(path_, files_);
    }
    private static int nbMatches(StringList _contents, String _input, Pattern _regExp) {
        int index_ = 0;
        int nb_ = 0;
        while (true) {
            CustList<RegExpPart> contentParts_ = extrContentString(_contents, _input, index_);
            int content_;
            if (contentParts_.isEmpty()) {
                int nex_ = _input.indexOf('\n', index_);
                if (nex_ > -1) {
                    content_ = nex_ +1;
                } else {
                    content_ = _input.length();
                }
            } else {
                content_ = contentParts_.last().getEnd()+1;
            }
            CustList<RegExpPart> regExpParts_ = extrRegExpString(_regExp, _input, index_);
            int regExp_ = nextIndexRegExp(regExpParts_, _input, index_);
            int next_ = Math.max(content_,regExp_);
            if (next_ >= _input.length()) {
                break;
            }
            if (!contentParts_.isEmpty() || !regExpParts_.isEmpty()) {
                nb_++;
            }

            index_ = next_;
        }
        return nb_;
    }
    private StringList filterFiles(String _path, StringList _files) {
        Pattern pattern_ = patternOrNull();
        StringList out_ = new StringList();
        for (String n: _files) {
            if (ko(n, _path,pattern_)) {
                continue;
            }
            out_.add(n);
        }
        return out_;
    }

    private Pattern patternOrNull() {
        String nameRegExp_ = namesRegExp.getText().trim();
        return patternOrNull(nameRegExp_);
    }

    private static Pattern patternOrNull(String _regExp) {
        Pattern pattern_;
        if (_regExp.isEmpty()) {
            pattern_ = null;
        } else {
            try {
                pattern_ = Pattern.compile(_regExp);
            } catch (Exception e) {
                pattern_ = null;
            }
        }
        return pattern_;
    }

    private boolean ko(String _name, String _path, Pattern _patt) {
        String nameContent_ = namesContent.getText();
        if (getFileCoreStream().newFile(_name).isDirectory()) {
            return true;
        }
        String rel_ = extract(_name, _path);
        return koString(_patt, nameContent_, rel_);
    }

    private static boolean koString(Pattern _patt, String _content, String _input) {
        return _patt != null && !_patt.matcher(_input).find() || !StringUtil.match(_input, _content.trim());
    }

    private String extract(String _name, String _path) {
        String rel_;
        if (_name.startsWith(_path)) {
            rel_ = _name.substring(_path.length());
        } else {
            rel_ = _name;
        }
        return rel_;
    }

    private static CustList<RegExpPart> extrContentString(StringList _contents, String _input, int _from) {
        CustList<RegExpPart> res_ = new CustList<RegExpPart>();
        int indexContent_ = 0;
        int index_ = 0;
        while (true) {
            RegExpPart regExpPart_ = tryRegExpPart(_contents, _input, _from, index_, indexContent_);
            if (regExpPart_ == null) {
                int next_ = _input.indexOf('\n', index_+_from);
                if (next_>-1&&_contents.isValidIndex(indexContent_)) {
                    return new CustList<RegExpPart>();
                }
                break;
            }
            res_.add(regExpPart_);
            indexContent_++;
            index_ = regExpPart_.getEnd()-_from+1;
        }
        return res_;
    }
    private static RegExpPart tryRegExpPart(StringList _contents, String _input, int _from, int _index, int _indexContent) {
        int next_ = _input.indexOf('\n', _index+_from);
        if (next_ < 0 || !_contents.isValidIndex(_indexContent)) {
            return null;
        }
        String curr_ = _input.substring(_index+_from,next_);
        if (!StringUtil.match(curr_,_contents.get(_indexContent))) {
            return null;
        }
        return new RegExpPart(curr_,_from+_index,next_);
    }
    private static int nextIndexRegExp(CustList<RegExpPart> _res, String _input, int _from) {
        int next_ = _input.indexOf('\n', _from);
        if (_res.isEmpty()) {
            if (next_ > -1) {
                return next_+1;
            }
            return _from;
        }
        return _res.last().getEnd()+1;
    }
    private static CustList<RegExpPart> extrRegExpString(Pattern _patt, String _input, int _from) {
        CustList<RegExpPart> res_ = new CustList<RegExpPart>();
        if (_patt == null) {
            return res_;
        }
        Matcher matcher_ = _patt.matcher(_input.substring(_from));
        while (matcher_.find()) {
            String group_ = matcher_.group();
            res_.add(new RegExpPart(group_,matcher_.start(),matcher_.end()));
        }
        return res_;
    }

    private static StringList filterList(String _filter) {
        StringList out_ = new StringList();
        if (_filter.isEmpty()) {
            return out_;
        }
        StringBuilder str_ = new StringBuilder();
        boolean esc_ = false;
        int i = 0;
        int len_ = _filter.length();
        while (i < len_) {
            char ch_ = _filter.charAt(i);
            if (esc_) {
                esc_ = false;
                if (ch_ == 'n') {
                    out_.add(str_.toString());
                    str_.delete(0,str_.length());
                } else {
                    str_.append(ch_);
                }
                i++;
                continue;
            }
            if (ch_ == '\\') {
                esc_ = true;
            } else {
                str_.append(ch_);
            }
            i++;
        }
        out_.add(str_.toString());
        return out_;
    }
    @Override
    public void quit() {
        exit();
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
    public void changeLanguage(String s) {
        //
    }
}
