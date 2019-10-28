#include <main.h>

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);
gadget_display display(u8g);

char optionsCalibration[7][17];
gadget_menu menu(u8g, optionsCalibration, 7);

void setup() 
{
  Serial.begin(115200);
  while(!Serial){};
  display.set_main_data(00,"value 1");
  display.set_main_data(01,"hallo");
  display.set_main_data(02,"oeee");

  display.set_main_data(10,"hallo_10");
  display.set_main_data(11,"hallo 11");
  display.set_main_data(12,"oeee 12");

  display.set_main_font_size(00,FONT_9);
  display.drawDisplay(false);
  display.set_provider("hetayo");
  delay(500);
   display.drawNotification("mohon mengisi\ndaya untuk \nmelanjutkan\nkembali ");
  // put your setup code here, to run once:

  strcpy(optionsCalibration[0], (const char *)"menu 1");
  strcpy(optionsCalibration[1], (const char *)"menu 2");
  strcpy(optionsCalibration[2], (const char *)"menu 3");
  strcpy(optionsCalibration[3], (const char *)"menu 4 jklmnopq");
  strcpy(optionsCalibration[4], (const char *)"menu 5");
  strcpy(optionsCalibration[5], (const char *)"menu 6");
  strcpy(optionsCalibration[6], (const char *)"menu 7");

}
uint8_t powerr  = 0;
uint8_t signal = 0;
void loop() {
  display.set_signal(signal);
  display.set_battery(powerr);
 // display.drawDisplay(false);
  signal++;
  if(signal>4)signal = 0;
  powerr+=10;
  if(powerr>100) powerr = 0;
  delay(500);
  menu.previous();
  //display.drawNotification("mohon mengisi\ndaya untuk \nmelanjutkan\nkembali ");  // max char 18
  delay(500);
  menu.draw();
  Serial.println(menu.getPosition());
  // put your main code here, to run repeatedly:
}
