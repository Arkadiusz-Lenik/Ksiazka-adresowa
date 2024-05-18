#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

struct Uzytkownik
{
    int idUzytkownika = 0;
    string nazwa = "";
    string haslo = "";
};

string wczytajLinie()
{
    string wejscie = "";
    cin.sync();
    getline(cin, wejscie);
    return wejscie;
}

char wczytajZnak()
{
    string wejscie = "";
    char znak;

    while (true)
    {
        getline(cin, wejscie);

        if (wejscie.length() == 1)
        {
            znak = wejscie[0];
            break;
        }
        else
        {
            cout << "To nie jest pojedynczy znak. Sprobuj ponownie" << endl;
        }
    }

    return znak;
}

Uzytkownik rozdzielLinieZPlikuNapojedynczeDane(string liniaZPliku)
{
    stringstream mySentence(liniaZPliku);
    string fragmentDanych = "";
    int numerKolumnyDanychZPliku = 1;
    Uzytkownik osoba;

    while (!mySentence.eof())
    {
        getline(mySentence, fragmentDanych, '|');

        switch(numerKolumnyDanychZPliku)
        {
            case 1: osoba.idUzytkownika = stoi(fragmentDanych); break;
            case 2: osoba.nazwa = fragmentDanych; break;
            case 3: osoba.haslo = fragmentDanych; break;
        }
        numerKolumnyDanychZPliku++;
    }

    return osoba;
}

void zapiszNowegoUzytkownikaDoPliku(vector <Uzytkownik> &uzytkownicy)
{
    fstream plik;
    plik.open ("Uzytkownicy.txt", ios::app);

    if (plik.good() == false)
    {
        cout << "Nie udalo sie otworzyc pliku Uzytkownicy.txt i zapisac w nim danych" << endl;
        Sleep(3000);
        return;
    }

    plik << uzytkownicy.back().idUzytkownika << "|";
    plik << uzytkownicy.back().nazwa << "|";
    plik << uzytkownicy.back().haslo << "|" << endl;

    plik.close();
}

void zapiszWszystkichUzytkownikowDoPliku(vector <Uzytkownik> &uzytkownicy)
{
    fstream plik;
    plik.open ("Uzytkownicy.txt", ios::out);

    if (plik.good() == false)
    {
        cout << "Nie udalo sie otworzyc pliku Uzytkownicy.txt i zapisac w nim danych" << endl;
        Sleep(3000);
        return;
    }

    for (vector <Uzytkownik> :: iterator itr = uzytkownicy.begin(); itr != uzytkownicy.end(); itr++)
    {
        plik << itr->idUzytkownika << "|";
        plik << itr->nazwa << "|";
        plik << itr->haslo << "|" << endl;

    }

    plik.close();
}

void wczytajUzytkownikowZPliku(vector <Uzytkownik> &uzytkownicy)
{
    string liniaZPliku = "";
    Uzytkownik osoba;

    fstream plik;
    plik.open("Uzytkownicy.txt", ios::in);

    if (plik.good() == false)
    {
        cout << "Nie udalo sie otworzyc pliku Uzytkownicy.txt i odczytac z niego danych" << endl;
        Sleep(3000);
        return;
    }

    while (getline(plik, liniaZPliku))
    {
        osoba = rozdzielLinieZPlikuNapojedynczeDane(liniaZPliku);
        uzytkownicy.push_back(osoba);
        liniaZPliku.clear();
    }

    plik.close();
}

void zarejestrujUzytkownika(vector <Uzytkownik> &uzytkownicy)
{
    string nazwa = "";
    Uzytkownik osoba;
    cout << "Podaj nazwe uzytkownika: ";
    nazwa = wczytajLinie();
    vector <Uzytkownik> :: iterator itr = uzytkownicy.begin();

    while (itr != uzytkownicy.end())
    {
        if (itr->nazwa == nazwa)
        {
            cout << "Podana nazwa juz istnieje. Sprobuj ponownie" << endl;
            nazwa = wczytajLinie();
            itr = uzytkownicy.begin();
        }
        else
        {
            itr++;
        }
    }

    osoba.nazwa = nazwa;
    cout << "Podaj haslo uzytkownika: ";
    osoba.haslo = wczytajLinie();
    osoba.idUzytkownika = uzytkownicy.empty()? 1 : uzytkownicy.back().idUzytkownika + 1;
    uzytkownicy.push_back(osoba);
    zapiszNowegoUzytkownikaDoPliku(uzytkownicy);
    cout << "Gratulacje. Konto zostalo utworzone" << endl << endl;
    Sleep(1000);
}

int zalogujUzytkownika(vector <Uzytkownik> &uzytkownicy)
{
    string nazwa = "", haslo = "";
    cout << "Podaj nazwe uzytkownika: ";
    nazwa = wczytajLinie();
    vector <Uzytkownik> :: iterator itr = uzytkownicy.begin();

    while (itr != uzytkownicy.end())
    {
        if (itr->nazwa == nazwa)
        {
            for (int i = 0; i < 3; i++)
            {
                cout << "Podaj haslo. Pozostalo prob " << 3 - i << endl;
                haslo = wczytajLinie();

                if (itr->haslo == haslo)
                {
                    cout << "Zalogowales sie" << endl;
                    Sleep(1000);
                    return itr->idUzytkownika;
                }
            }

            cout << "Podano 3 razy bledne haslo." << endl;
            cout << "Za 5 sekund zostaniesz przeniesiony do ekranu glownego" << endl;
            Sleep(5000);
            return 0;
        }
        else
        {
            itr++;
        }
    }

    cout << "Nie ma takiego uzytkownika" << endl;
    Sleep(1000);
    return 0;
}

void zmienHaslo(vector <Uzytkownik> &uzytkownicy, int idZalogowanegoUzytkownika)
{
    string haslo = "";
    cout << "Podaj nowe haslo: ";
    haslo = wczytajLinie();

    for (vector <Uzytkownik> :: iterator itr = uzytkownicy.begin(); itr != uzytkownicy.end(); itr++)
    {
        if (itr->idUzytkownika == idZalogowanegoUzytkownika)
        {
            itr->haslo = haslo;
            cout << "Haslo zostalo zmienione" << endl;
            Sleep(1500);
            break;
        }
    }

    zapiszWszystkichUzytkownikowDoPliku(uzytkownicy);
}

int main()
{
    int idZalogowanegoUzytkownika = 0;
    char wybor;
    vector <Uzytkownik> uzytkownicy;

    wczytajUzytkownikowZPliku(uzytkownicy);

    while (1)
    {
        if (idZalogowanegoUzytkownika == 0)
        {
            system("cls");
            cout << "1. Rejestracja" << endl;
            cout << "2. Logowanie" << endl;
            cout << "9. Koniec programu" << endl;

            wybor = wczytajZnak();

            switch (wybor)
            {
                case '1': zarejestrujUzytkownika(uzytkownicy); break;
                case '2': idZalogowanegoUzytkownika = zalogujUzytkownika(uzytkownicy); break;
                case '9': exit(0);
            }
        }
        else if (idZalogowanegoUzytkownika > 0)
        {
            system("cls");
            cout << "1. Zmiana hasla" << endl;
            cout << "2. Wylogowanie" << endl;

            wybor = wczytajZnak();

            switch (wybor)
            {
                case '1': zmienHaslo(uzytkownicy, idZalogowanegoUzytkownika); break;
                case '2': idZalogowanegoUzytkownika = 0; break;
            }
        }

    }

    return 0;
}
