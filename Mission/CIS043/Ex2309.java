import java.awt.Graphics;       // program uses class Graphics
import javax.swing.JApplet;     // program uses class JApplet
import javax.swing.JOptionPane; // program uses class JOptionPane

public class Ex2309 extends JApplet 
{
   private int x;
   private int y;
   private int width;
   private int height;

   // initialize applet by obtaining values from user
   public void init()
   {
      // obtain x from user
      String szx = JOptionPane.showInputDialog(
         "Enter x value" );

      // obtain y from user
      String szy = JOptionPane.showInputDialog(
         "Enter y value" );

      // obtain width from user
      String szwidth = JOptionPane.showInputDialog(
         "Enter width value" );

      // obtain height from user
      String szheight = JOptionPane.showInputDialog(
         "Enter height value" );

      // convert numbers from type String to type double
      x = Integer.parseInt( szx );
			y = Integer.parseInt( szy ); 
      width = Integer.parseInt( szwidth );
			height = Integer.parseInt( szheight ); 
   } // end method init

   // draw results in a rectangle on applet’s background
   public void paint( Graphics g )
   {
      super.paint( g ); // call superclass version of method paint

      // draw rectangle starting from (x, y) that is width 
      // pixels wide and height pixels tall
      g.drawRoundRect( 0, 0, width, height );
   } // end method paint
} // end class AdditionApplet
