#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Zamanı dakikaya çeviren fonksiyon
int dakikayaCevir(char *zaman) {
    int saat, dakika;
    sscanf(zaman, "%d:%d", &saat, &dakika);
    return saat * 60 + dakika;
}

int main() {
    FILE *gunlukDosya, *gecDosya, *erkenDosya;
    char sicilNo[20], saat[6], yon;
    int dakikaCinsinden;

    char enGecGelenSicil[20], enErkenCikanSicil[20];
    int enGecDakika = -1, enErkenDakika = 9999;

    // Dosyaları aç
    gunlukDosya = fopen("gunluk.dat.txt", "r");
    gecDosya = fopen("gec.dat.txt", "w");
    erkenDosya = fopen("erken.dat.txt", "w");

    // Dosya kontrolü
    if (gunlukDosya == NULL || gecDosya == NULL || erkenDosya == NULL) {
        printf("Dosya acilamadi!\n");
        return 1;
    }

    // Dosyadan veri oku
    while (fscanf(gunlukDosya, "%s %s %c", sicilNo, saat, &yon) != EOF) {
        dakikaCinsinden = dakikayaCevir(saat);

        if (yon == '<') { // Giriş saati kontrolü
            if (dakikaCinsinden > enGecDakika) { // En geç geleni bul
                enGecDakika = dakikaCinsinden;
                strcpy(enGecGelenSicil, sicilNo);
            }
        } else if (yon == '>') { // Çıkış saati kontrolü
            if (dakikaCinsinden < enErkenDakika) { // En erken çıkanı bul
                enErkenDakika = dakikaCinsinden;
                strcpy(enErkenCikanSicil, sicilNo);
            }
        }
    }

    // Sonuçları dosyalara yaz
    if (enGecDakika > 540) { // Eğer bir geç kalma varsa
        fprintf(gecDosya, "%s %d\n", enGecGelenSicil, enGecDakika - 540);
    }
    if (enErkenDakika < 1020) { // Eğer bir erken çıkış varsa
        fprintf(erkenDosya, "%s %d\n", enErkenCikanSicil, 1020 - enErkenDakika);
    }

    printf("Islem tamamlandi. Sonuclar gec.dat ve erken.dat dosyalarina yazildi.\n");

    // Dosyaları kapat
    fclose(gunlukDosya);
    fclose(gecDosya);
    fclose(erkenDosya);
    return 0;
}


