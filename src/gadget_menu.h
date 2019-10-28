#ifndef gadget_menu_h_
#define gadget_menu_h_

#include <Arduino.h>
#include <U8glib.h>

#define ret_v       return *this;

#ifndef NUM_OF_MENU
    #define NUM_OF_MENU             4
#endif

#define MAX_OF_CHAR_EACH_MENU       17
#define TOTAL_MENU_DISPLAYED        5
#define MAX_OF_MENU                 10
#if NUM_OF_MENU > MAX_OF_MENU
    #define NUM_OF_MENU MAX_OF_MENU
#endif

class gadget_menu : public U8GLIB
{
    protected:
    U8GLIB *lcd_driver;
    char (*menu)[MAX_OF_CHAR_EACH_MENU];
    char header_name[24];
    uint8_t totalMenu;
    uint8_t position;
    virtual void drawMenu(bool showHeader);

 public:
    gadget_menu (U8GLIB &lcd, char (*menu)[17], uint8_t totalMenu):lcd_driver(&lcd), menu(menu), totalMenu(totalMenu){};
    gadget_menu &setHeader      (const char txt[])    { sprintf_P(header_name, (const char *)F("%24s"), txt);ret_v};
    gadget_menu &next           (void)                {position++; position = (position >= totalMenu)?0:position; ret_v};
    gadget_menu &previous       (void)                {position--; position = (position >= totalMenu)?totalMenu-1:position; ret_v};
    gadget_menu &resetPosition  (void)                {position = 0;ret_v};
    gadget_menu &draw           (bool showHeader=true);

    uint8_t getPosition         (void)                {return position;};   

    void clear();

    public :
        
};
#endif