package keys;

import java.awt.*;
import java.awt.event.*;
import java.net.*;
import java.util.Map;
import java.util.HashMap;
import javax.swing.*;

public class KeyboardAnimation
{
	private final static String PRESSED = "pressed ";
	private final static String RELEASED = "released ";

	private JComponent component;
	private JLabel status;
	private Map<String, Point> pressedKeys = new HashMap<String, Point>();

	public KeyboardAnimation(JLabel status,JComponent component, int delay)
	{
		this.component = component;
		this.status = status;

	}

	/*
	*  &param keyStroke - see KeyStroke.getKeyStroke(String) for the format of
	*                     of the String. Except the "pressed|released" keywords
	*                     are not to be included in the string.
	*/
	public void addAction(String keyStroke, int deltaX, int deltaY)
	{
		//  Separate the key identifier from the modifiers of the KeyStroke

		int offset = keyStroke.lastIndexOf(" ");
		String key = offset == -1 ? keyStroke :  keyStroke.substring( offset + 1 );
		String modifiers = keyStroke.replace(key, "");

		//  Get the InputMap and ActionMap of the component

		InputMap inputMap = component.getInputMap(JComponent.WHEN_IN_FOCUSED_WINDOW);
		ActionMap actionMap = component.getActionMap();

		//  Create Action and add binding for the pressed key

		Action pressedAction = new AnimationAction(key, new Point(deltaX, deltaY));
		String pressedKey = modifiers + PRESSED + key;
		KeyStroke pressedKeyStroke = KeyStroke.getKeyStroke(pressedKey);
		inputMap.put(pressedKeyStroke, pressedKey);
		actionMap.put(pressedKey, pressedAction);

		//  Create Action and add binding for the released key

		Action releasedAction = new AnimationAction(key, null);
		String releasedKey = modifiers + RELEASED + key;
		KeyStroke releasedKeyStroke = KeyStroke.getKeyStroke(releasedKey);
		inputMap.put(releasedKeyStroke, releasedKey);
		actionMap.put(releasedKey, releasedAction);
	}

	//  Invoked whenever a key is pressed or released

	private void handleKeyEvent(String key, Point moveDelta)
	{
		//  Keep track of which keys are pressed

		if (moveDelta == null)
			pressedKeys.remove( key );
		else
			pressedKeys.put(key, moveDelta);
		SwingUtilities.invokeLater(new Runnable(){
			public void run(){
				status.setText(pressedKeys.keySet().toString());
			}
		});
	}

	//  Action to keep track of the key and a Point to represent the movement
	//  of the component. A null Point is specified when the key is released.

	private class AnimationAction extends AbstractAction implements ActionListener
	{
		private Point moveDelta;

		public AnimationAction(String key, Point moveDelta)
		{
			super(key);

			this.moveDelta = moveDelta;
		}

		public void actionPerformed(ActionEvent e)
		{
			handleKeyEvent((String)getValue(NAME), moveDelta);
		}
	}

	public static void main(String[] args)
	{
		JPanel contentPane = new JPanel();
		contentPane.setLayout( new BoxLayout(contentPane,BoxLayout.PAGE_AXIS) );

		JLabel status = new JLabel("[]");
		status.setAlignmentX(Component.LEFT_ALIGNMENT);
		JLabel label = new JLabel( new ColorIcon(Color.BLUE, 40, 40) );
		label.setAlignmentX(Component.LEFT_ALIGNMENT);
		contentPane.add( label );

		KeyboardAnimation animation = new KeyboardAnimation(status,label, 24);
		animation.addAction("LEFT", -3,  0);
		animation.addAction("RIGHT", 3,  0);
		animation.addAction("UP",    0, -3);
		animation.addAction("DOWN",  0,  3);

		animation.addAction("control LEFT", -5,  0);
		animation.addAction("V",  5,  5);

		JLabel label2 = new JLabel( new ColorIcon(Color.GREEN, 40, 40) );
		label2.setAlignmentX(Component.LEFT_ALIGNMENT);
		contentPane.add( label2 );
		contentPane.add( status );

		KeyboardAnimation animation2 = new KeyboardAnimation(status,label2, 24);
		animation2.addAction("A", -3,  0);
		animation2.addAction("D", 3,  0);
		animation2.addAction("W",    0, -3);
		animation2.addAction("S",  0,  3);

		JFrame frame = new JFrame();
		frame.setDefaultCloseOperation( JFrame.EXIT_ON_CLOSE );
		frame.getContentPane().add(contentPane);
		frame.setVisible(true);
		frame.pack();
	}

	static class ColorIcon implements Icon
	{
		private Color color;
		private int width;
		private int height;

		public ColorIcon(Color color, int width, int height)
		{
			this.color = color;
			this.width = width;
			this.height = height;
		}

		public int getIconWidth()
		{
			return width;
		}

		public int getIconHeight()
		{
			return height;
		}

		public void paintIcon(Component c, Graphics g, int x, int y)
		{
			g.setColor(color);
			g.fillRect(x, y, width, height);
		}
	}
}