#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct kuyruk
{
    int adet;
    char *str;
    struct kuyruk *sonraki;
} kelimeler;


kelimeler *kelime_olustur(char *kelime)
{

    kelimeler *yeniKelime = malloc (sizeof (kelimeler));

    if (NULL != yeniKelime)
    {
        yeniKelime->str = (char *) malloc ((strlen (kelime)) + 1);
        strcpy (yeniKelime->str, kelime);
        yeniKelime->str[strlen (kelime)] = '\0';

        yeniKelime->adet = 1;
        yeniKelime->sonraki = NULL;
    }

    return yeniKelime;

}


kelimeler *kelime_ekle (kelimeler **kelimeListesi, char *kelime)
{
    if (!*kelimeListesi)
    {

        return *kelimeListesi = kelime_olustur (kelime);
    }

    kelimeler *temp = *kelimeListesi;

    while (temp->sonraki != NULL)
    {

        if (strcmp (temp->str, kelime) == 0)
        {
            temp->adet = temp->adet + 1;
            return *kelimeListesi;
        }
        else
        {
            temp = temp->sonraki;
        }

    }

    kelimeler *yeniKelime = kelime_olustur(kelime);

    if (NULL != yeniKelime)
    {
        temp->sonraki = yeniKelime;
    }

    return yeniKelime;
}


int main()
{

    char *token,*delim = " ,;\t\n";
    char line[1000];
    FILE *okunacakDosya;
    FILE *yazilacakDosya;
    kelimeler *tutulanKelimeler;
    tutulanKelimeler = NULL;

    okunacakDosya = fopen ("dosya.txt", "r");

    if (okunacakDosya == NULL)
    {
        printf("Dosya Acilamadi.");
    }
    else
    {
     while ( fgets (line , 500 , okunacakDosya) != NULL )
     {
       token = strtok (line,delim);
       while (token != NULL)
       {
         kelime_ekle(&tutulanKelimeler,token);
         token = strtok (NULL,delim);

       }
     }
    }

    yazilacakDosya = fopen ("output.txt", "w+");
    int i = 1;
    while (tutulanKelimeler != NULL)
    {
        fprintf (yazilacakDosya,"%d. %s : %d \n",i,tutulanKelimeler->str, tutulanKelimeler->adet);
        tutulanKelimeler = tutulanKelimeler->sonraki;
        i++;
    }

    return 0;
}
