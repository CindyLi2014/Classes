// Exercise 15.10 Solution: Draw.java
// Program randomly draws characters
import javax.swing.JFrame;

public class Draw 
{
   public static void main( String args[] )
   {
      // create frame for CharactersJPanel
      JFrame frame = new JFrame( "Drawing Characters" );
      frame.setDefaultCloseOperation( JFrame.EXIT_ON_CLOSE );

      CharactersJPanel charactersJPanel = new CharactersJPanel(); 
      frame.add( charactersJPanel ); // add charactersJPanel to frame
      frame.setSize( 380, 150 ); // set frame size
      frame.setVisible( true ); // display frame
   } // end main
} // end class Draw

