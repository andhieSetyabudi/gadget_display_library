#ifndef gadget_display_h_
#define gadget_display_h_

#include <Arduino.h>
#include <ArduinoJson.h>
#include <U8glib.h>

#define max_menu_count      10
#define DISPLAY_MENU        1
#define DISPLAY_MAIN        0

#define FONT_DEFAULT        6
#define FONT_11             7
#define FONT_10             8
#define FONT_9              9

#define key_word            "t"

class gadget_display
{
    public:
        const bool ENABLE = true;
        const bool DISABLE = false;
        struct  header_display
        {
            uint8_t signal = 0,
                    battery_percentage = 0;
            bool gprs_status = true,
                data_status = false;
            String provider_name = "cellular"; 
            uint8_t hour = 0,
                    minute = 0;
        };
        enum menu_state
        {   
            next        = 0,
            previous    = 1,
            enter       = 2, 
            back        = 3,
            exit        = 4
        };
        struct menu_index_position
        {
            uint8_t index1,
                    index2,
                    index3;
        };
    private:
        //=================== global use for this class
        U8GLIB *lcd_driver;
        header_display header_data;
        uint8_t display_mode = DISPLAY_MAIN;
        bool charge = false;

        //================ menu display variable
            StaticJsonDocument<256> menu_doc;
           // uint8_t num_of_menu,
           //         num_of_sub_menu,
           //         num_of_sub_sub_menu;
            uint16_t index_of_menu=0;
            bool menu_reset_point = false;
            uint8_t menu_fontsize;
            menu_state proc_menu;
            menu_index_position menu_index_pos;
        //================ main display variable
            StaticJsonDocument<220> main_doc;

        //================ display control
            void draw_display_row(const char * list, char delimiter);
            void drawBattery(void);
            void drawSignal(void);
            void drawG(void) ;
            void drawTime(void);
            void drawOperator(void);
            //=================== for main page
            void drawMainPage(bool showHeader = true);
            //=================== for menu page
            void drawMenuPage(bool showHeader = true);
        //================ table control 
            uint8_t     indexOfMenu(String menu_name);                          // return index of menu if exist, -1 or 255 is not
            uint8_t     indexOfSubFromMenuExist(String menu_name, String sub_name);  // return index of sub-menu with xn ; x is menu index and n is sub-menu index; 255 if not exist
            uint16_t    indexOfSubOfSubFromMenuExist(String menu, String sub_of_menu, String sub_sub);
    public:
        gadget_display(U8GLIB &u8g):lcd_driver(&u8g){header_data.provider_name.reserve(10);};

        //================ global function for this class

        void set_display_mode   (uint8_t mode = DISPLAY_MAIN){display_mode = mode > DISPLAY_MENU ? DISPLAY_MAIN : mode; };
        void drawDisplay        (bool showHeader = true);
        void drawNotification   (String text, bool frame = true);
    //==================== data of header-display
        void set_header_data (header_display data)  {header_data=data;};
        void set_signal  ( uint8_t val)             {header_data.signal = val;};
        void set_battery (uint8_t percent)          {header_data.battery_percentage = percent;};
        void set_gprs    (bool stat)                {header_data.gprs_status = stat;};
        void set_data    (bool stat)                {header_data.data_status = stat;};
        void set_provider(String name)              { header_data.provider_name = name;};
        void set_hour    (uint8_t h)                {header_data.hour = h;};
        void set_minute  (uint8_t m)                {header_data.minute = m;};
        void set_time    (uint8_t h, uint8_t m)     {set_hour(h); set_minute(m);};
               
    //===================== method for main display
        void set_main_data          (uint8_t id, String text);
        void set_main_font_size     (uint8_t id, uint8_t font);


    //===================== menu for menu display
        void set_menu_font_size     (uint8_t s)         {menu_fontsize = s;};
        void add_var_menu           (String name);
        void add_var_sub_menu       (String main_menu, String sub_menu);
        void add_var_sub_sub_menu   (String main_menu, String sub_menu, String sub_sub_menu);
        void menu_action            (menu_state act);
        uint16_t get_menu_position      (void);


};

#endif