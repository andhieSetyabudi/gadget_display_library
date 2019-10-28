#ifndef gadget_confirmation_h
#define gadget_confirmation_h

#include <Arduino.h>
#include <U8glib.h>

class gadget_confirmation:public U8GLIB
{
    private :
        U8GLIB *lcd_driver;
        bool selection = true;
        char optional[2][8];
        String content;
      //  void drawFrame(void);
    public:
        gadget_confirmation(U8GLIB &lcd_);
        void draw(void);
        void next(void){selection = !selection;};
        void setOptionalText(String confirmationText, const char *yesText, const char *noText);
        uint8_t getConfirmPos(void){ return selection ? 1: 0;};
};
#endif