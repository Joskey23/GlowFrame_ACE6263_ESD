#include <Deneyap_HareketIsikRenkAlgilayiciMesafeOlcer.h>       // Deneyap Hareket, Işık, Renk Algılayıcı, Mesafe Ölçer Algılayıcısı kütüphanesi eklenmesi 

APDS9960 Yakinlik;                                              // APDS9960 için class tanımlanması

void setup() {
    Serial.begin(115200);                                       // Seri haberleşme başlatılması
    if (!Yakinlik.begin(0x39)) {                                // begin(slaveAdress) fonksiyonu ile cihazların haberleşmesi başlatılması
        delay(3000);
        Serial.println("I2C bağlantısı başarısız");             // I2C bağlantısı başarısız olursa seri port ekranına yazdırılması
    }
    Yakinlik.enableProximity(true);                             // Yakınlık ölçüm aktifleştirilmesi
}

void loop() {
    /*  255 => yakın
        0   => uzak
        -1  => hata   */
    Serial.print("yakınlık :");
    Serial.println(Yakinlik.readProximity());                  // Okunan yakınlık değerinin seri port ekranına yazdırılması
    delay(500);
}