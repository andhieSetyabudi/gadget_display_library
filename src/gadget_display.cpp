#include <gadget_display.h>

//========================== functions & methods of Menu
uint8_t gadget_display::indexOfMenu(String menu_name)
{
    uint8_t index = 255;
    if(menu_doc.containsKey(F("id")))
    {
        JsonArray arr = menu_doc[F("id")].as<JsonArray>();
        int arrSize = arr.size();
        for(uint8_t idx = 0; idx < arrSize; idx++ )
        {
            String id_name = menu_doc[F("id")][idx].as<String>();
            if(id_name.equals(menu_name))
            {
                index = idx;
                break;
            }
        }
    } 
    return index;
}

uint8_t gadget_display::indexOfSubFromMenuExist(String menu_name, String sub_name)
{
    uint8_t index = 255;
    uint8_t menuID = indexOfMenu(menu_name);
    if(menuID != 255)
    {
        String name_t = "id"+String(menuID);
        JsonArray arr = menu_doc[name_t].as<JsonArray>();
        int arrSize = arr.size();
        for(uint8_t idx = 0; idx < arrSize; idx++ )
        {
            String id_name = menu_doc[name_t][idx].as<String>();
            if(id_name.equals(sub_name))
            {
                index = (menuID*10)+idx;
                break;
            }
        }
    }
    return index;
}

uint16_t gadget_display::indexOfSubOfSubFromMenuExist(String menu, String sub_of_menu, String sub_sub)
{
    uint16_t index = 255;
    uint8_t menuID = indexOfSubFromMenuExist(menu, sub_of_menu);
    if(menuID != 255)
    {
        String name_t = "id"+String(menuID);
        JsonArray arr = menu_doc[name_t].as<JsonArray>();
        int arrSize = arr.size();
        for(uint8_t idx = 0; idx < arrSize; idx++ )
        {
            String id_name = menu_doc[name_t][idx].as<String>();
            if(id_name.equals(sub_sub))
            {
                index = (menuID*10)+idx;
                break;
            }
        }
    }
    return index;
}

void gadget_display::add_var_menu (String name)
{
    if(name.length()>16) name.remove(16);
    if(menu_doc.containsKey(F("id")))
    {
        menu_doc[F("id")].add(name);
    }    
    else
    {
        JsonArray main_menu_ = menu_doc.createNestedArray(F("id"));
        main_menu_.add(name);
    }
}

void gadget_display::add_var_sub_menu(String main_menu, String sub_menu)
{
    if(main_menu.length()>16) main_menu.remove(16);
    if(sub_menu.length()>16) sub_menu.remove(16);
    if(!menu_doc.containsKey(F("id")))
    {
        // create new table
        JsonArray main_menu_ = menu_doc.createNestedArray(F("id"));
        main_menu_.add(main_menu);
        JsonArray sub_menu_ = menu_doc.createNestedArray(F("id0"));
        sub_menu_.add(sub_menu);
    }    
    else
    {
        uint8_t id_ = indexOfMenu(main_menu);
        if( id_ != 255)     // main menu is exist, sub-menu can be able to be inputted to table
        {
            uint8_t c_id = indexOfSubFromMenuExist(main_menu, sub_menu);
            if(c_id != 255) return; // sub menu already exist, didn't need to be
            else
            {
                String id_name="id"+String(id_);
                if(menu_doc.containsKey(id_name))
                {
                    menu_doc[id_name].add(sub_menu);
                }    
                else
                {
                    JsonArray main_menu_ = menu_doc.createNestedArray(id_name);
                    main_menu_.add(sub_menu);
                }
            } 
        }
        else
        {
             /* do nothing*/
        }
    }  
    /*  
    Serial.println("sub menu");
    String output;
    serializeJson(menu_doc, output);
    Serial.println(output);*/
}

void gadget_display::add_var_sub_sub_menu (String main_menu, String sub_menu, String sub_sub_menu)
{
    if(main_menu.length()>16) main_menu.remove(16);
    if(sub_menu.length()>16) sub_menu.remove(16);
    if(sub_sub_menu.length()>16) sub_sub_menu.remove(16);

    if(!menu_doc.containsKey(F("id")))
    {
        // create new table
        JsonArray main_menu_ = menu_doc.createNestedArray(F("id"));
        main_menu_.add(main_menu);
        JsonArray sub_menu_ = menu_doc.createNestedArray(F("id0"));
        sub_menu_.add(sub_menu);
        JsonArray sub_sub_menu_ = menu_doc.createNestedArray(F("id00"));
        sub_sub_menu_.add(sub_sub_menu);
    }
    else
    {
        uint8_t id_ = indexOfSubFromMenuExist(main_menu, sub_menu);
        if( id_ != 255)     // main menu is exist, sub-menu can be able to be inputted to table
        {
            uint8_t c_id = indexOfSubOfSubFromMenuExist(main_menu, sub_menu, sub_sub_menu);
            if(c_id != 255) return; // sub menu already exist, didn't need to be
            else
            {
                String id_name="";
                uint8_t id_main_menu = indexOfMenu(main_menu);
                if( id_main_menu== 0)
                    id_name = "id"+String(id_main_menu)+String(id_);
                else 
                    id_name = "id"+String(id_);
                if(menu_doc.containsKey(id_name))
                {
                    menu_doc[id_name].add(sub_menu);
                }    
                else
                {
                    JsonArray main_menu_ = menu_doc.createNestedArray(id_name);
                    main_menu_.add(sub_sub_menu);
                }
            } 
        }
        else
        {
            /* do nothing*/
        }
    }
    /*
    Serial.println("sub sub menu");
    String output;
    serializeJson(menu_doc, output);
    Serial.println(output);*/
}




//===================== method for menu display
void gadget_display::set_main_data(uint8_t id, String text)
{
    if(!(id == 0 || id == 1 || id == 2 || id == 10 || id == 11 || id == 12)) return;
    String var_id = key_word+String(id);
    if(!main_doc.containsKey(var_id))
    {
        if(text.length()>10)
        text.remove(10);
        JsonArray main_disp = main_doc.createNestedArray(var_id);
        main_disp.add(text);
        main_disp.add(FONT_DEFAULT);
    }
    /*
    Serial.println("Add data text");
    String output;
    serializeJson(main_doc, output);
    Serial.println(output);*/
}
void gadget_display::set_main_font_size(uint8_t id, uint8_t font)
{
    if(!(id == 0 || id == 1 || id == 2 || id == 10 || id == 11 || id == 12)) return;
    String var_id = key_word+String(id);
    if(!(font == FONT_DEFAULT || font == FONT_9 || font == FONT_10 || font == FONT_11) )font = FONT_DEFAULT;
    if(main_doc.containsKey(var_id))
    {
        main_doc[var_id][1]=font;
    }
    /*
    Serial.println("Add data text");
    String output;
    serializeJson(main_doc, output);
    Serial.println(output);
    */
}




//============================= for general of this class
 void gadget_display::drawBattery(void)
 {
  uint8_t x = 114, y = 0;
  uint8_t power = round((float)header_data.battery_percentage/10);    // power in percent ; max 100
  // create battery layout
  lcd_driver->drawHLine(x + 0, y + 8, 13);
  lcd_driver->drawVLine(x + 0, y + 2, 6);
  lcd_driver->drawVLine(x + 12, y + 2, 6);
  lcd_driver->drawHLine(x + 0, y + 2, 13);
  lcd_driver->drawVLine(x + 13, y + 4, 3);

  // count for battery level status
  if (power > 1 && power < 20 && power != 0)
  {
    lcd_driver->drawBox(x + 2, y + 4, power-1, 3);
  }
  if(charge)
  {
    lcd_driver->setDefaultBackgroundColor();
    lcd_driver->drawLine(x+2, y+4, x+6, y+7); 
    lcd_driver->drawLine(x+2, y+4, x+5, y+7); 
    lcd_driver->drawLine(x+5, y+4, x+10, y+7);
    lcd_driver->drawLine(x+6, y+4, x+10, y+7);
    lcd_driver->setDefaultForegroundColor();
  }
}

void gadget_display::drawSignal(void)
{
  uint8_t x = 1, y = 0;
  lcd_driver->drawHLine(x + 6,  y + 9, 13);
  lcd_driver->drawVLine(x + 19, y + 0, 10);
  if( header_data.signal < 1 )
  {
    lcd_driver->drawStr  (x + 5, y, "Y");
    lcd_driver->drawHLine(x + 5, y+1, 5);
  }
  else
  {
    if (header_data.signal >=1)
    {
      lcd_driver->drawVLine(x + 7, y + 6, 2);
      lcd_driver->drawVLine(x + 8, y + 6, 2);
    }
    if (header_data.signal >=2)
    {
      lcd_driver->drawVLine(x + 10,  y + 4, 4);
      lcd_driver->drawVLine(x + 11,  y + 4, 4);
    }
    if (header_data.signal >=3)
    {
      lcd_driver->drawVLine(x + 13, y + 2, 6);
      lcd_driver->drawVLine(x + 14, y + 2, 6);
    }
    if (header_data.signal >=4)
    {
      lcd_driver->drawVLine(x + 16, y + 0, 8);
      lcd_driver->drawVLine(x + 17, y + 0, 8);
    }    
  }
}

void gadget_display::drawG(void) 
{
  uint8_t x = 1, y = 0;
  lcd_driver->drawHLine(x + 2, y + 2, 4);
  lcd_driver->drawHLine(x + 2, y + 5, 4);
  lcd_driver->drawHLine(x + 4, y + 4, 2);
  lcd_driver->drawVLine(x + 2, y + 2, 4);
}

void gadget_display::drawTime(void)
{
    char buffer[5];
    uint8_t x = 82, y = 0;
    sprintf_P(buffer, (const char *)F("%02d:%02d"), header_data.hour, header_data.minute);
    lcd_driver->drawStr(x, y, buffer);
}

void gadget_display::drawOperator(void)
{
    uint8_t x = 23, y = 0;
    uint8_t len = header_data.provider_name.length()+1;
    if(len > 9) len = 9;
    char ope[len];
    header_data.provider_name.toCharArray(ope,len);
    lcd_driver->drawStr(x, y, ope);
}


void gadget_display::drawMainPage(bool showHeader)
{
    uint8_t header = 0;
    menu_reset_point = true;
    menu_index_pos = {0,0,0};
    if(showHeader)
    {
        lcd_driver->setFont(u8g_font_6x12r);
        lcd_driver->setFontRefHeightExtendedText();
        header = lcd_driver->getFontAscent()-lcd_driver->getFontDescent();
        header+=2;
    }
    uint8_t v_interval = ( lcd_driver->getHeight() - header - 2) / 3;
    for(uint8_t id_y = 0; id_y < 3; id_y++)     // take row data
    {
        for(uint8_t id_x = 0; id_x < 2; id_x++ )        // take column data
        {
            char text_buf[17];
            String var_id =  key_word+String((id_x*10)+id_y);
            if(!main_doc.containsKey(var_id)) continue;
            JsonArray arr = main_doc[var_id].as<JsonArray>();
            String tmp = arr[0].as<String>();
            tmp.toCharArray(text_buf,16);
            uint8_t ui = arr[1];
            switch(ui)
            {
                case FONT_11   : lcd_driver->setFont(u8g_font_7x14r); break;
                case FONT_10   : lcd_driver->setFont(u8g_font_6x13); break;
                case FONT_9    : lcd_driver->setFont(u8g_font_6x12); break;
                default        : lcd_driver->setFont(u8g_font_8x13r); break; //u8g_font_unifont
            };
            lcd_driver->setFontRefHeightExtendedText();
            lcd_driver->setFontPosTop();
            uint8_t h_ = lcd_driver->getFontAscent()-lcd_driver->getFontDescent();
            lcd_driver->drawStr( id_x * 64 , header + ( v_interval * id_y)+(h_/2) , text_buf);
        }

    }    
    
}

void gadget_display::drawMenuPage(bool showHeader = true)
{
    
    uint8_t header = 0;
    if(showHeader)
    {
        lcd_driver->setFont(u8g_font_6x12r);
        lcd_driver->setFontRefHeightExtendedText();
        header = lcd_driver->getFontAscent()-lcd_driver->getFontDescent();
        header+=2;
    }
    uint8_t v_interval = ( lcd_driver->getHeight() - header - 2) / 3;
    uint8_t i, h;
    u8g_uint_t w, d;
    lcd_driver->setFont(u8g_font_6x13r);
    lcd_driver->setFontRefHeightText();
    lcd_driver->setFontPosTop();
    h = lcd_driver->getFontAscent()-lcd_driver->getFontDescent();
    w = lcd_driver->getWidth();

    if(menu_reset_point)
    {
        JsonArray arr = menu_doc["id"].as<JsonArray>();
        int arrSize = arr.size();
        for(uint8_t idx = 0; idx < arrSize; idx++ )
        {
            String id_name = menu_doc["id"][idx].as<String>();
            
        }
    }
    else
    {
        
    }
    
}

void gadget_display::drawDisplay(bool showHeader)
{
    String output;
    serializeJson(menu_doc, output);
    Serial.println(output);

    lcd_driver->firstPage();
    do 
    {
        if (showHeader) 
        {
            lcd_driver->setFont(u8g_font_6x12);
            lcd_driver->setFontRefHeightExtendedText();
            lcd_driver->setDefaultForegroundColor();
            lcd_driver->setFontPosTop();
            if(header_data.gprs_status && header_data.signal > 0)
                drawG();
            drawSignal();  
            drawOperator();
            drawTime();
            drawBattery();
            int h = lcd_driver->getFontAscent()-lcd_driver->getFontDescent();
            int w = lcd_driver->getWidth();
            lcd_driver->drawHLine(0, h + 1, w);
        }
        if(display_mode == DISPLAY_MENU) 
            drawMainPage(showHeader);
        else
            drawMainPage(showHeader);

    } while (lcd_driver->nextPage());
}

uint8_t countCharOf(String txt, char de)
{
    uint8_t len = txt.length()+1;
    uint8_t val = 0;
    for(uint8_t i = 0; i < len; i++)
    {
        if( txt.charAt(i) == de )
        {
            val++;
        }
    }
    return val;
}

void gadget_display::drawNotification(String text, bool frame)
{   
    if(text.length() > 72)  text.remove(72);
    uint8_t row = countCharOf(text,'\n')+1;      
    lcd_driver->firstPage();
    String bufff = text;
    do 
    {
        text = bufff;
        lcd_driver->setFont(u8g_font_7x14r);
        lcd_driver->setFontRefHeightText();
        lcd_driver->setFontPosTop();
        uint8_t h = lcd_driver->getFontAscent()-lcd_driver->getFontDescent();
        uint8_t w = lcd_driver->getWidth();
        char buff[19];
        if(row > 0)
        {
            uint8_t pos = 0;
            for (uint8_t i = 0; i < row; i++)
            {
                pos = text.indexOf("\n");
                if( pos > 0 && pos < 255 )
                {
                    text.toCharArray(buff,pos+1);
                    text.remove(0,pos+1);
                    
                }
                else 
                {
                    text.toCharArray(buff,18);
                    text.remove(0,18);
                };
                uint8_t d = (w-lcd_driver->getStrWidth(buff))/2;
                uint8_t hh =  (lcd_driver->getHeight()/row);
                lcd_driver->drawStr(d , (hh) * i +2, buff);
            }
        }

        else
        {
            text.toCharArray(buff,18); 
            uint8_t d = (w-lcd_driver->getStrWidth(buff))/2;
            uint8_t hh = (lcd_driver->getHeight()/2) - (h/2);
            lcd_driver->drawStr(d,hh, buff);
        }
        if(frame)
            lcd_driver->drawFrame(0, 0, w, lcd_driver->getHeight());
    }while (lcd_driver->nextPage());
}