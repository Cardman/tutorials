package coq;

import javax.swing.*;
import javax.swing.text.*;
import java.util.*;
import java.awt.Font;
import java.awt.FontMetrics;
import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.Color;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.event.KeyEvent;
import java.awt.event.InputEvent;
import javax.swing.event.DocumentListener;
import javax.swing.event.DocumentEvent;
import javax.swing.event.CaretListener;
import javax.swing.event.CaretEvent;
import javax.swing.event.ChangeListener;
import javax.swing.event.ChangeEvent;
import javax.swing.undo.CannotUndoException;
import javax.swing.undo.CannotRedoException;
import javax.swing.undo.UndoManager;
import javax.swing.event.UndoableEditEvent;
import javax.swing.event.UndoableEditListener;

public class MyWindow {

	public JTextPane ta = new JTextPane();
	public JFrame frame = new JFrame();
	public JScrollPane jsp = new JScrollPane(ta);
	public Split spl = new SplitImpl();
	public JSpinner tabSize = new JSpinner();
	public JLabel status = new JLabel("lci");
	public UndoManager undoManager = new UndoManager();
		UndoAction undoAction = new UndoAction();
		RedoAction redoAction=new RedoAction();
	public MyWindow(){
		undoManager.setLimit(Integer.MAX_VALUE);
		ta.setFont(new Font(Font.MONOSPACED,Font.PLAIN,12));
		setTabSize(4);
		jsp.setPreferredSize(new Dimension(512,512));
		JPanel pan = new JPanel();
		pan.setLayout(new BoxLayout(pan,BoxLayout.PAGE_AXIS));
		pan.add(tabSize);
		pan.add(jsp);
		pan.add(status);
		frame.getContentPane().add(pan);
        frame.pack();
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        ta.getDocument().putProperty(DefaultEditorKit.EndOfLineStringProperty, "\n");
		Highlighter h = new Highlighter();
		h.ta = ta;
		h.spl = spl;
		h.undoManager = undoManager;
		undoAction.setEnabled(false);
		redoAction.setEnabled(false);
		h.undoAction = undoAction;
		h.redoAction = redoAction;
		Document doc = ta.getDocument();
		doc.addDocumentListener(h);
		ta.addCaretListener(new CaretListener() {
			
			@Override
			public void caretUpdate(CaretEvent _e) {
				FileMetrics m = FileMetricsCore.processLinesTabs(ta.getText(), (Integer) tabSize.getValue());
				int i = ta.getCaretPosition();
				int l = m.getRowFile(i);
				int c = m.getColFile(i,l);
				String selected = ta.getSelectedText();
				if (selected == null){
					status.setText("lci"+l+","+c+","+i);
					return;
				}
				status.setText("lci"+l+","+c+","+i+":"+selected.length());
			}
		});
		 //doc.addUndoableEditListener(undoManager);
		 doc.addUndoableEditListener(h);
		tabSize.addChangeListener(new ChangeListener() {
            
            @Override
            public void stateChanged(ChangeEvent _e) {
                int value_ = (Integer) tabSize.getValue();
                if (value_ <= 0) {
                    return;
                }
                setTabSize(value_);
                
            }
        });
        tabSize.setValue(4);
		ta.registerKeyboardAction(undoAction, KeyStroke.getKeyStroke(KeyEvent.VK_Z, InputEvent.CTRL_DOWN_MASK), JComponent.WHEN_FOCUSED);
		ta.registerKeyboardAction( redoAction, KeyStroke.getKeyStroke(KeyEvent.VK_Y, InputEvent.CTRL_DOWN_MASK), JComponent.WHEN_FOCUSED);
	}
	private void setTabSize(int tabSize) {
		FontMetrics fm = ta.getFontMetrics(ta.getFont());
		int charWidth = fm.charWidth('#');
		int tabWidth = charWidth * tabSize;
		TabStop[] tabs = new TabStop[100];
		for (int j = 0; j < tabs.length; j++) {
			tabs[j] = new TabStop((j + 1) * tabWidth);
		}
		SimpleAttributeSet attributes = new SimpleAttributeSet();
		StyleConstants.setTabSet(attributes, new TabSet(tabs));
		ta.getStyledDocument().setParagraphAttributes(0, ta.getDocument().getLength(), attributes, false);
	}
	public void init(){
		frame.setVisible(true);
	}
	private static final String UNDO = "undo";
	private static final String REDO = "redo";
	class RedoAction extends AbstractAction {
 
 
        public void actionPerformed(ActionEvent ae) {
		try{//if (!undoManager.canRedo()){return;}
            undoManager.redo();setEnabled(undoManager.canRedo());undoAction.setEnabled(undoManager.canUndo());}catch(Exception e){e.printStackTrace();}
        }

    } // end ConsoleTextEditor.RedoAction
 
 
    class UndoAction extends AbstractAction {
  
        public void actionPerformed(ActionEvent ae) {
		try{//if (!undoManager.canUndo()){return;}
            undoManager.undo();redoAction.setEnabled(undoManager.canRedo());setEnabled(undoManager.canUndo());}catch(Exception e){e.printStackTrace();}
        }
 
    }
}
//class Highlighter implements DocumentListener {
class Highlighter implements DocumentListener,UndoableEditListener {
//UndoableEditListener

	public JTextPane ta;
	public Split spl;
	/*public JLabel status;
		MyWindow.UndoAction undoAction;
		MyWindow.RedoAction redoAction;*/
		boolean store = true;
		UndoManager undoManager;
		MyWindow.UndoAction undoAction;
		MyWindow.RedoAction redoAction;
    public void insertUpdate(DocumentEvent e) {
	try{
	 //applyHighlighting();
        highlight();
		}catch(Exception f){}
    }
	@Override
	 public void undoableEditHappened(UndoableEditEvent e) {
	 /*if (!store){
	 return;
	 }*/
	 try {
	 javax.swing.text.AbstractDocument.DefaultDocumentEvent ed =
        (javax.swing.text.AbstractDocument.DefaultDocumentEvent)e.getEdit();
		if  (ed.getType().equals(DocumentEvent.EventType.CHANGE)) {
			return;
		}
		 undoManager.addEdit(ed);
		 redoAction.setEnabled(undoManager.canRedo());
		 undoAction.setEnabled(undoManager.canUndo());
		 }catch(Exception f){}
	 }

    public void removeUpdate(DocumentEvent e) {
	try{ 
		//applyHighlighting();
		highlight();
		}catch(Exception f){}
    }

    public void changedUpdate(DocumentEvent e) {
	}

    private void highlight() {
        //Edit the color only when the EDT is ready
        SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                applyHighlighting();
            }
        });
    }

    private void applyHighlighting() {
	store =false;
		String text = ta.getText();
		StyleContext style = StyleContext.getDefaultStyleContext();
        ta.getStyledDocument().setCharacterAttributes(0,text.length(),style.getEmptySet(), true);
		List<SegmentPart> ls = spl.dels(text);
		for (SegmentPart s:ls){
			AttributeSet textStyle = style.addAttribute(style.getEmptySet(),StyleConstants.Foreground,new Color(s.red,s.green,s.blue));
			textStyle = style.addAttribute(textStyle,StyleConstants.FontSize, s.size);
			textStyle = style.addAttribute(textStyle,StyleConstants.Background, new Color(255,255,255));
			ta.getStyledDocument().setCharacterAttributes(s.begin,(s.end - s.begin),textStyle, false);
		}
		store = true;
    }
}