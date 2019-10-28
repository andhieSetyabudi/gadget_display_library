#include "gadget_confirmation.h"

gadget_confirmation::gadget_confirmation(U8GLIB &lcd_):lcd_driver(&lcd_)
{
    content.reserve(54);
    content = F("Are you sure?");
    strcpy_P(optional[0], (const char *) F("Ya"));
    strcpy_P(optional[1], (const char *) F("Tidak"));
    selection = true;
}

void gadget_confirmation::setOptionalText(String confirmationText, const char *yesText, const char *noText)
{
    content = confirmationText;
    strcpy(optional[0], yesText);
    strcpy(optional[1], noText);
}

void gadget_confirmation::draw(void)
{
    uint8_t len = content.length()+1;
    uint8_t row = 0;
    for(uint8_t i = 0; i < len; i++)
    {
        if( content.charAt(i) == '\n' )
        {
            row++;
        }
    }
    String bufff = content;
    lcd_driver->firstPage();
    do 
    {
        lcd_driver->setFont(u8g_font_6x13r);
        lcd_driver->setFontRefHeightExtendedText();
        lcd_driver->setDefaultForegroundColor();
        lcd_driver->setFontPosTop();
        uint8_t h = lcd_driver->getFontAscent()-lcd_driver->getFontDescent();
        uint8_t w = lcd_driver->getWidth();
        content = bufff;
        char buff[20];
        if(row > 0)
        {
            uint8_t pos = 0;
            for (uint8_t i = 0; i < row+1; i++)
            {
                pos = content.indexOf("\n");
                if( pos > 0 && pos < 255 )
                {
                    content.toCharArray(buff,pos+1);
                    content.remove(0,pos+1);
                    
                }
                else 
                {
                    content.toCharArray(buff,20);
                    content.remove(0,20);
                };
                uint8_t d = (w-lcd_driver->getStrWidth(buff))/2;
                uint8_t hh =  ( ( lcd_driver->getHeight() - h - 5 )/(row+1)) *i;
                lcd_driver->drawStr(d , hh+2, buff);
            }
        }

        else
        {
            content.toCharArray(buff,18); 
            uint8_t d = (w-lcd_driver->getStrWidth(buff))/2;
            uint8_t hh = (lcd_driver->getHeight()/3) - (h/2);
            lcd_driver->drawStr(d,hh, buff);
        }

        lcd_driver->drawFrame(0, lcd_driver->getHeight() - (h+5), w, h+5 );
       uint8_t d;
       if(selection)
       {
           d = (w/4)*3-(lcd_driver->getStrWidth(optional[1])/2);
           lcd_driver->drawStr(d, lcd_driver->getHeight() - (h+3), optional[1]);
           lcd_driver->drawBox((0*(w/2))+2, lcd_driver->getHeight() - h-3, (w/2)-3, h+1);
           lcd_driver-> setDefaultBackgroundColor();
           d = (w/4)-(lcd_driver->getStrWidth(optional[0])/2);
           lcd_driver->drawStr(d, lcd_driver->getHeight() - (h+3), optional[0]);
       }
       else
       {
           d = (w/4)-(lcd_driver->getStrWidth(optional[0])/2);
           lcd_driver->drawStr(d, lcd_driver->getHeight() - (h+3), optional[0]);
           lcd_driver->drawBox((1*(w/2))+2, lcd_driver->getHeight() - h-3, (w/2)-3, h+1);
           lcd_driver-> setDefaultBackgroundColor();
           d = (w/4)*3-(lcd_driver->getStrWidth(optional[1])/2);
           lcd_driver->drawStr(d, lcd_driver->getHeight() - (h+3), optional[1]);
       }
    } while (lcd_driver->nextPage());
}