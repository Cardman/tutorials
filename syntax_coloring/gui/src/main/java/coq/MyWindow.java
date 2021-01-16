package coq;

import javax.swing.*;
import javax.swing.text.*;
import java.util.*;
import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.Color;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import javax.swing.event.DocumentListener;
import javax.swing.event.DocumentEvent;

public class MyWindow {

	public JTextPane ta = new JTextPane();
	public JFrame frame = new JFrame();
	public JScrollPane jsp = new JScrollPane(ta);
	public Split spl = new SplitImpl();
	public MyWindow(){
		jsp.setPreferredSize(new Dimension(512,512));
		frame.getContentPane().add(jsp);
        frame.pack();
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        ta.getDocument().putProperty(DefaultEditorKit.EndOfLineStringProperty, "\n");
		Highlighter h = new Highlighter();
		h.ta = ta;
		h.spl = spl;
		ta.getDocument().addDocumentListener(h);
	}

	public void init(){
		frame.setVisible(true);
	}
}

class Highlighter implements DocumentListener {

	public JTextPane ta;
	public Split spl;
    public void insertUpdate(final DocumentEvent e) {
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