// Exercise 15.19 Solution: Saver2.java
// Program simulates a simple screen saver
import javax.swing.JFrame;

public class Saver2
{
   public static void main( String args[] )
   {
      // create frame for SaverJPanel
       JFrame frame = new JFrame( "Screen Saver2" );     
	  // set default close operation
       frame.setDefaultCloseOperation( JFrame.EXIT_ON_CLOSE );
      // create new SaverJPanel
			SaverJPanel saverJPanel = new SaverJPanel(); 
      // add saverJPanel to frame
      frame.add( saverJPanel );
      // set frame size (300, 300)
      frame.setSize( 300, 300 );
      // display frame
      frame.setVisible( true );	  
   } // end main
} // end class Saver2


