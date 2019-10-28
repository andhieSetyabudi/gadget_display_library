#include <gadget_menu.h>

gadget_menu &gadget_menu::draw(bool showHeader) 
{
  lcd_driver->firstPage();
  do {
    drawMenu(showHeader);
  } while (lcd_driver->nextPage());
  ret_v
}

void gadget_menu::drawMenu(bool showHeader) {
  const int x = 0, y =0;
  
  unsigned char totalMenuShowed = totalMenu < TOTAL_MENU_DISPLAYED ? totalMenu : TOTAL_MENU_DISPLAYED;
  //static unsigned char menuOffset = position < TOTAL_MENU_DISPLAYED ? 0 : position - totalMenuShowed - 1;
  //char *menuShowed[totalMenuShowed];

 // lcd_driver->setFont(u8g_font_7x13r);
  //lcd_driver->setFontRefHeightText();
  //lcd_driver->setFontPosTop();
  
 /* if (position < menuOffset) {
    menuOffset = position;
  } else if(menuOffset + totalMenuShowed - 1 < position) {
    menuOffset = position - totalMenuShowed + 1;
  }*/

  for (size_t i = 0; i < totalMenuShowed; i++) 
  {
      lcd_driver->setDefaultForegroundColor();
      int8_t loc = position - 2 + i;
      if(loc < 0)
        loc += totalMenu;
      else if ( loc >= totalMenu)
        loc -= totalMenu;
  //  menuShowed[i] = //menu[i + menuOffset]; 
     if(i == 2)
      {
        lcd_driver->setFont(u8g_font_7x13);
        lcd_driver->setFontRefHeightText();
        lcd_driver->setFontPosTop();
        uint8_t h_ = lcd_driver->getFontAscent()-lcd_driver->getFontDescent();
        lcd_driver->drawFilledEllipse(4,y + (14 * i)+4,1,2);

        lcd_driver->drawTriangle(x+113, y + (14 * i)-3, 127, y + (14 * i)-3+(3*h_/4),x+113, y + (14 * i)-3+h_+(h_/2));
        lcd_driver->drawBox(x+8, y + (14 * i)-3, 105, h_+(h_/2));
        lcd_driver->setDefaultBackgroundColor();
        
        lcd_driver->drawStr(x + 10, y + (14 * i)-1, menu[loc]);//menuShowed[i]);
        
        
       // lcd_driver->drawHLine(x+8, y + (14 * i) + h_,100);
       // lcd_driver->drawHLine(x+8, y + (14 * i) +1,100);
        
      }
      else
      {
        lcd_driver->setFont(u8g_font_6x12);
        lcd_driver->setFontRefHeightText();
        lcd_driver->setFontPosTop();
        lcd_driver->drawStr(x + 10, y + (14 * i), menu[loc]);//menuShowed[i]);  
      }   
  }
  /*
  for (unsigned char i = 0; i < totalMenuShowed; i++) 
  {
     
     // lcd_driver->drawEllipse(2,y + (14 * i)+5,2,2);
      
    /*  
    if (position - menuOffset == i) {
	  lcd_driver->setFont(u8g_font_8x13r);
      lcd_driver->setFontRefHeightText();
      lcd_driver->setFontPosTop();
      lcd_driver->drawStr(x + 10, y + (12 * i)-2, menuShowed[i]);
      lcd_driver->drawFilledEllipse(2,y + (12 * i)+5,1,1);
    }
    else
    {
        lcd_driver->setFont(u8g_font_6x12r);
        lcd_driver->setFontRefHeightText();
        lcd_driver->setFontPosTop();
        lcd_driver->drawStr(x + 10, y + (12 * i), menuShowed[i]);
    }
    lcd_driver->drawEllipse(2,y + (12 * i)+5,2,2);
    
  }*/
}