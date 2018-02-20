## Použité součástky
1) [ESP32](https://www.espressif.com/en/products/hardware/esp32/overview)  
2) Hodiny reálného času  [DS3231](https://datasheets.maximintegrated.com/en/ds/DS3231.pdf)  
3) [I2C Displej](https://arduino-shop.cz/arduino/1570-iic-i2c-display-lcd-1602-16x2-znaku-lcd-modul-modry-1487765909.html) 
4) [Klávesnice](https://arduino-shop.cz/arduino-vstupni-periferie/824-arduino-klavesnice-membranova-4x4-1500635994.html)
4) Zdroj 5V
5) Relé 10A


Bomba má dva záklední režimy Config a Game. V režimu Config můžeme nastavit parametry hry jako například čas do výbuchu, pin pro aktivaci, pin pro deaktivaci atd.
Do režimu Config se dostaneme podržením tlačítka "#" při připojení napájení.

V režimu Game se pak pustí algoritmus zvolené hry. 

## Jednotlivé soubory v projektu:
1) [Configurace.ino](https://github.com/OpltFrantisek/Projekt/blob/master/Source/EPS32_program_(Arduino%20IDE)/bomba/Configurace.ino) - obsahuje metody sloužící pro konfiguraci bomby
2) [Hra.ino](https://github.com/OpltFrantisek/Projekt/blob/master/Source/EPS32_program_(Arduino%20IDE)/bomba/Hra.ino) - obsahuje algorimy pro herní režimy
3) [Klavesnice.cpp](https://github.com/OpltFrantisek/Projekt/blob/master/Source/EPS32_program_(Arduino%20IDE)/bomba/Klavesnice.cpp) - Naše knihovna pro obsluhu klávesnice
4) [bomba.ino](https://github.com/OpltFrantisek/Projekt/blob/master/Source/EPS32_program_(Arduino%20IDE)/bomba/bomba.ino) - Záklandí soubor projektu obsahuje Setup() a Loop()
5) [http.ino](https://github.com/OpltFrantisek/Projekt/blob/master/Source/EPS32_program_(Arduino%20IDE)/bomba/http.ino) - Stará se o vše co souvisí s WiFi
6) [pamet.ino](https://github.com/OpltFrantisek/Projekt/blob/master/Source/EPS32_program_(Arduino%20IDE)/bomba/pamet.ino) - Obstarava čtení a zápis dat z/do paměti EEPROM
7) [vybuch.ino](https://github.com/OpltFrantisek/Projekt/blob/master/Source/EPS32_program_(Arduino%20IDE)/bomba/vybuch.ino) - tady se řeší jak se má bomba chovat pokud dojde k výbuchu (odpálení dýmovnice, zastavení časovače atd.)

Zrojový kód pro bombu naleznete [zde](https://github.com/OpltFrantisek/Projekt/tree/master/Source/EPS32_program_(Arduino%20IDE)/bomba)

