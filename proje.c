#include <stdio.h>

struct { // anlık bilgilerin tutuldugu değişkenler
    int id;
    char ad[25];
    char soyad[25];
    char email[50];
    char telefon[20];
}Kullanici;


int main(void){
    FILE *fptr; // Dosya Objesi oluşturma
    char OkunanVeri[1000];
    int secim; // durum değişkeni
    int intMi;
    while(1){
        printf("\n\n\n");
        printf("*****************************************************\n1. Müşteri Kayit\n2. Muşteri Listesi\n3. Müşteri Güncelleme\n4. Çikiş Yap\n*****************************************************\n");
        printf("İşlem Seçiniz: "); scanf("%d", &secim);
        printf("\n\n");

        // kullanıcı Kayıt Durumu
        if(secim == 1){
            printf("Musteri ID: "); scanf("%d", &Kullanici.id);
            printf("Musteri Adi: "); scanf("%s",Kullanici.ad);
            printf("Musteri Soyadi: "); scanf("%s",Kullanici.soyad);
            printf("Musteri Emaili: "); scanf("%s",Kullanici.email);
            printf("Musteri Telefonu: "); scanf("%s",Kullanici.telefon);

            fptr = fopen("Kullanici.txt", "a"); // Dosyayı "a" (ekleme) modunda aç

            fprintf(fptr, "%d %s %s %s %s\n",Kullanici.id , Kullanici.ad, Kullanici.soyad, Kullanici.email, Kullanici.telefon); // Dosyaya yeni veriyi yaz
                
            fclose(fptr);  // dosya kapatma işlemi
        }

        // kullanıcı Kayıtlarını Gösterme Durumu
        else if(secim == 2){

            int gerigit;

            while(1){
                fptr = fopen("Kullanici.txt","r"); // Dosyayı "r" (Okuma) modunda aç => Kullanici dosyası varsa yazar, yoksa oluşturup yazar. 

                while(fscanf(fptr, "%d %s %s %s %s", &Kullanici.id, Kullanici.ad, Kullanici.soyad, Kullanici.email, Kullanici.telefon) != EOF){
                    printf("ID: %d,  İsim: %s,  Soyad: %s,  Email: %s,  Telefon: %s\n\n", Kullanici.id, Kullanici.ad, Kullanici.soyad, Kullanici.email, Kullanici.telefon);
                }

                fclose(fptr);// dosya kapatma işlemi

                printf("Geri gitmek için `1`e  bas: "); scanf("%d", &gerigit); // geri gitme seceneği
                if(gerigit == 1){
                    break;                
                }
            }
        }

        else if(secim == 3){ // Güncelleme Durumu
            int id;
            printf("Güncellenecek Musteri ID: "); scanf("%d", &id);
            fptr = fopen("Kullanici.txt","r");
            FILE *tempFile = fopen("temp.txt", "w");

            if(!fptr || !tempFile){
                printf("Dosya Açılamadı.");
            }

            int Musteri_Bulma = 0;
            while(fscanf(fptr, "%d %s %s %s %s", &Kullanici.id, Kullanici.ad, Kullanici.soyad, Kullanici.email, Kullanici.telefon) != EOF){
                if(Kullanici.id == id){
                    printf("Güncellenecek Musteri Adi: "); scanf("%s",Kullanici.ad);
                    printf("Güncellenecek Musteri Soyadi: "); scanf("%s",Kullanici.soyad);
                    printf("Güncellenecek Musteri Emaili: "); scanf("%s",Kullanici.email);
                    printf("Güncellenecek Musteri Telefonu: "); scanf("%s",Kullanici.telefon);
                    Musteri_Bulma = 1;
                }
                fprintf(tempFile, "%d %s %s %s %s\n", Kullanici.id, Kullanici.ad, Kullanici.soyad, Kullanici.email, Kullanici.telefon);
            }
            fclose(fptr);
            fclose(tempFile);

            // boş dosya ile değitirme işlemi
            remove("musteriler.txt");
            rename("temp.txt", "Kullanici.txt");

            if(Musteri_Bulma){
                printf("Müsteri Bilgileri Güncellendi.\n");
            }
            else{
                printf("Musteri Bulunamadi.\n");
            }
        }

        else if(secim == 4){ // Programdan Çıkış Durumu
            break;
        }
        
        else{ // Yanlış işlem Durumu
            printf("Yanliş işlem girişi...\n");
        }
    } 

    
}