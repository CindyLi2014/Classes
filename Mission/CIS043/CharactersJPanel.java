// Exercise 15.10 Solution: CharactersJPanel.java
// Program randomly draws characters
import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics;
import java.util.Random;
import javax.swing.JPanel;

public class CharactersJPanel extends JPanel
{
   // random-number generator
   private static final Random random = new Random();

   // draw characters
   public void paintComponent( Graphics g )
   {
   // Use 5 fonts, 4 styles and 6 letters for this example
      final String fonts[] =
         { "Serif", "Monospaced", "SansSerif", "Dialog", "DialogInput" };
      final int styles[] =
         { Font.PLAIN, Font.ITALIC, Font.BOLD, Font.ITALIC + Font.BOLD };
      final String letters[] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};

      super.paintComponent( g ); // call superclass's paintComponent

	  int x = 50;  // set x coordinates
	  int y = 50;  // set y coordinates
	  
	  // Create a 4 letter random string
	  String letter = letters[ random.nextInt( letters.length ) ] + letters[ random.nextInt( letters.length ) ] + letters[ random.nextInt( letters.length ) ] + letters[ random.nextInt( letters.length ) ];
      
	  // randomly choose font name, style and character
      // select font size randomly from size 12 to size 60
		int fontSize = random.nextInt(48)+12;
	  // select font name randomly from the fonts array
    int nameIdx = random.nextInt(fonts.length);
		String fontName = fonts[nameIdx];
	  // select font style randomly from the styles array
    int styleIdx = random.nextInt(styles.length);
		int fontStyle = styles[styleIdx];
      // create font from the three component above
    Font rdmFont = new Font(fontName, fontStyle, fontSize);
	  // set font of the graphics
	  g.setFont(rdmFont);
      // set color of the graphics with random RGB value
		int R = (int)(Math.random()*256);
		int G = (int)(Math.random()*256);
		int B= (int)(Math.random()*256);
		Color rdmColor = new Color(R, G, B);
		g.setColor(rdmColor);
	  // draw string with letter at x, y coordinates.
    g.drawString(letter, x, y);
   } // end method paintComponent
} // end class CharactersJPanel


