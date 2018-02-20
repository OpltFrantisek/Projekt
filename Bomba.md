## Použité součástky
1) [ESP32](https://www.espressif.com/en/products/hardware/esp32/overview)  
2) Hodiny reálného času  [DS3231](https://datasheets.maximintegrated.com/en/ds/DS3231.pdf)  
3) [I2C Displej](https://arduino-shop.cz/arduino/1570-iic-i2c-display-lcd-1602-16x2-znaku-lcd-modul-modry-1487765909.html)  
4) Zdroj 5V
5) Relé 10A


Bomba má dva záklední režimy Config a Game. V režimu Config můžeme nastavit parametry hry jako například čas do výbuchu, pin pro aktivaci, pin pro deaktivaci atd.
Do režimu Config se dostaneme podržením tlačítka "#" při připojení napájení.

V režimu Game se pak pustí algoritmus zvolené hry. 
