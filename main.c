#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LENGTH 100
#define MAX_TIME 24 * 60 // dakika cinsinden en fazla süre

struct Record {
    //Çalışanın sicil numarası
    int sicilno;
    //Çalışanın geldiği saat
    int saat;
    //Çalışanın geldiği dakika
    int dakika;
    //Kayıt türü (gelme < veya gitme >)
    char type;
};

// Saat ve dakikayı dakikaya çevirir
int dakika_cevir(int saat, int dakika) {
    return saat * 60 + dakika;
}

int main() {
    //Dosyaları açar
    FILE *inputFile, *gecFile, *erkenFile;
    //Okunan satırları kaydetmek için oluşturduğumuz bir dizi
    char satir[MAX_LENGTH];
    //Geçerli değeri tutmak için oluşturduğumuz bir yapı
    struct Record gecerli;
    int songirme = -1, erkencikma = MAX_TIME;
    int songirensicil = -1, enerkencikansicil = -1;
    //Girdi dosyasının açılıp okunmasını sağlar
    inputFile = fopen("C:\\Users\\ilhan\\Desktop\\Proje\\gunluk.dat", "r");
    //Eğer dosya açılmazsa hata mesajı verir ve program sonlanır
    if (inputFile == NULL) {
        printf("Dosya acilamadi: gunluk.dat\n");
        return 1;
    }
    //Dosyadan satır satır okuma işlemi yapar
    while (fgets(satir, sizeof(satir), inputFile)) {
        //Okunan satırdan sicil numarası, saat, dakika ve tür bilgileri ayrıştırılır.
        sscanf(satir, "%d %d:%d %c", &gecerli.sicilno, &gecerli.saat, &gecerli.dakika, &gecerli.type);
        //Eğer kayıt türü < (gelme) ise ve zaman daha önceki en geç gelme zamanından büyükse, bu zaman güncellenir
        if (gecerli.type == '<' && dakika_cevir(gecerli.saat, gecerli.dakika) > songirme) {
            songirme = dakika_cevir(gecerli.saat, gecerli.dakika);
            songirensicil = gecerli.sicilno;

        }
        //Eğer kayıt türü > (gitme) ise ve zaman daha önceki en erken çıkma zamanından küçükse, bu zaman güncellenir
        if (gecerli.type == '>' && dakika_cevir(gecerli.saat, gecerli.dakika) < erkencikma) {
            erkencikma = dakika_cevir(gecerli.saat, gecerli.dakika);
            enerkencikansicil = gecerli.sicilno;
        }
    }
    //Dosya kapanır
    fclose(inputFile);
    //Geç kalanlar için çıktı dosyası açılır. Eğer açılamazsa hata mesajı yazdırılır
    gecFile = fopen("C:\\Users\\ilhan\\Desktop\\Proje\\gec.dat", "w");
    if (gecFile == NULL) {
        printf("Dosya açılamadı: gec.dat\n");
        return 1;
    }
    //Geç kalan çalışanın sicil numarası ve geç kalma süresi yazılır
    fprintf(gecFile, "%d %d", songirensicil, songirme - dakika_cevir(9, 0));
    //Dosya kapanır
    fclose(gecFile);
    //Erken çıkanlar için çıktı dosyası açılır. Eğer açılamazsa hata mesajı yazdırılır
    erkenFile = fopen("C:\\Users\\ilhan\\Desktop\\Proje\\erken.dat", "w");
    if (erkenFile == NULL) {
        printf("Dosya açılamadı: erken.dat\n");
        return 1;
    }
    //Erken çıkan çalışanın sicil numarası ve erken çıkma süresi yazılır
    fprintf(erkenFile, "%d %d", enerkencikansicil, dakika_cevir(17, 0) - erkencikma);
    fclose(erkenFile);

    return 0;
}
