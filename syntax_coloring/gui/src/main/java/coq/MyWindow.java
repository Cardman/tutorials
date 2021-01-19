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
	public MyWindow(){
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
		h.status = status;
		ta.getDocument().addDocumentListener(h);
		ta.addCaretListener(new CaretListener() {
			
			@Override
			public void caretUpdate(CaretEvent _e) {
				FileMetrics m = FileMetricsCore.processLinesTabs(ta.getText(), (Integer) tabSize.getValue());
				int i = ta.getCaretPosition();
				int l = m.getRowFile(i);
				int c = m.getColFile(i,l);
				status.setText("lci"+l+","+c+","+i);
			}
		});
		Document doc = ta.getDocument();
		 doc.addUndoableEditListener(new UndoableEditListener() {
			 @Override
			 public void undoableEditHappened(UndoableEditEvent e) {
				 undoManager.addEdit(e.getEdit());
			 }
		 });
		tabSize.addChangeListener(new ChangeListener() {
            
            @Override
            public void stateChanged(ChangeEvent _e) {
                // TODO Auto-generated method stub
                int value_ = (Integer) tabSize.getValue();
                if (value_ < 0) {
                    return;
                }
                setTabSize(value_);
                
            }
        });
        tabSize.setValue(4);
		ta.registerKeyboardAction(new AbstractAction() {
			 @Override
			 public void actionPerformed(ActionEvent e) {
				 try {
					 /*if (undoManager.canUndo()) {
						 undoManager.undo();
					 }*/
					 undoManager.undo();
				 } catch (CannotUndoException exp) {
					
				 }
			 }
		 }, KeyStroke.getKeyStroke(KeyEvent.VK_Z, InputEvent.CTRL_MASK), JComponent.WHEN_FOCUSED);
		ta.registerKeyboardAction( new AbstractAction() {
			 @Override
			 public void actionPerformed(ActionEvent e) {
				 try {
					 /*if (undoManager.canRedo()) {
						 undoManager.redo();
					 }*/
					 undoManager.redo();
				 } catch (CannotUndoException exp) {
					
				 }
			 }
		 }, KeyStroke.getKeyStroke(KeyEvent.VK_Y, InputEvent.CTRL_MASK), JComponent.WHEN_FOCUSED);
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
}

class Highlighter implements DocumentListener {

	public JTextPane ta;
	public Split spl;
	public JLabel status;
    public void insertUpdate(DocumentEvent e) {
        highlight(e.getDocument(),e.getOffset(),e.getLength());
    }

    public void removeUpdate(DocumentEvent e) {
        highlight(e.getDocument(), e.getOffset(), 0);
    }

    public void changedUpdate(DocumentEvent e) {}

    private void highlight(Document doc, int offset, int length) {
        //Edit the color only when the EDT is ready
        SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                applyHighlighting();
            }
        });
    }

    private void applyHighlighting() {
		String text = ta.getText();
        ta.getStyledDocument().setCharacterAttributes(0,text.length(),StyleContext.getDefaultStyleContext().getEmptySet(), true);
		List<SegmentPart> ls = spl.dels(text);
		for (SegmentPart s:ls){
			StyleContext style = StyleContext.getDefaultStyleContext();
			AttributeSet textStyle = style.addAttribute(style.getEmptySet(),StyleConstants.Foreground,new Color(s.red,s.green,s.blue));
			textStyle = style.addAttribute(textStyle,StyleConstants.FontSize, s.size);
			ta.getStyledDocument().setCharacterAttributes(s.begin,(s.end - s.begin),textStyle, false);
		}
    }
}