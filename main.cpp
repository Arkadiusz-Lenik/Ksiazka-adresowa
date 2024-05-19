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

struct Adresat
{
    int idAdresata = 0;
    int idUzytkownika = 0;
    string imie = "";
    string nazwisko = "";
    string numerTelefonu = "";
    string email = "";
    string adres = "";
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

Uzytkownik rozdzielLinieZPlikuUzytkownicyNapojedynczeDane(string liniaZPliku)
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

Adresat rozdzielLinieZPlikuAdresaciNapojedynczeDane(string liniaZPliku)
{
    stringstream mySentence(liniaZPliku);
    string fragmentDanych = "";
    int numerKolumnyDanychZPliku = 1;
    Adresat osoba;

    while (!mySentence.eof())
    {
        getline(mySentence, fragmentDanych, '|');

        switch(numerKolumnyDanychZPliku)
        {
            case 1: osoba.idAdresata = stoi(fragmentDanych); break;
            case 2: osoba.idUzytkownika = stoi(fragmentDanych); break;
            case 3: osoba.imie = fragmentDanych; break;
            case 4: osoba.nazwisko = fragmentDanych; break;
            case 5: osoba.numerTelefonu = fragmentDanych; break;
            case 6: osoba.email = fragmentDanych; break;
            case 7: osoba.adres = fragmentDanych; break;
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

void zapiszNowegoAdresataDoPliku(vector <Adresat> &adresaci)
{
    fstream plik;
    plik.open ("Adresaci.txt", ios::app);

    if (plik.good() == false)
    {
        cout << "Nie udalo sie otworzyc pliku Adresaci.txt i zapisac w nim danych" << endl;
        Sleep(3000);
        return;
    }

    plik << adresaci.back().idAdresata << "|";
    plik << adresaci.back().idUzytkownika << "|";
    plik << adresaci.back().imie << "|";
    plik << adresaci.back().nazwisko << "|";
    plik << adresaci.back().numerTelefonu << "|";
    plik << adresaci.back().email << "|";
    plik << adresaci.back().adres << "|" << endl;

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
        osoba = rozdzielLinieZPlikuUzytkownicyNapojedynczeDane(liniaZPliku);
        uzytkownicy.push_back(osoba);
        liniaZPliku.clear();
    }

    plik.close();
}

void wczytajAdresatowZPliku(vector <Adresat> &adresaci)
{
    string liniaZPliku = "";
    Adresat osoba;

    fstream plik;
    plik.open("Adresaci.txt", ios::in);

    if (plik.good() == false)
    {
        cout << "Nie udalo sie otworzyc pliku Adresaci.txt i odczytac z niego danych" << endl;
        Sleep(3000);
        return;
    }

    while (getline(plik, liniaZPliku))
    {
        osoba = rozdzielLinieZPlikuAdresaciNapojedynczeDane(liniaZPliku);
        adresaci.push_back(osoba);
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

string zweryfikujWprowadzonyNumerTelefonu(Adresat osoba, vector <Adresat> &adresaci)
{
    string numerTelefonu = osoba.numerTelefonu;
    vector <Adresat> :: iterator itr = adresaci.begin();

    while (itr != adresaci.end())
    {
        if (itr->numerTelefonu == numerTelefonu)
        {
            cout << endl << "Podany numer telefonu jest juz zajety. Sprobuj ponownie" << endl;
            numerTelefonu = wczytajLinie();
            itr = adresaci.begin();
        }
        else
        {
            itr++;
        }
    }

    return numerTelefonu;
}

string zweryfikujWprowadzonyEmail(Adresat osoba, vector <Adresat> &adresaci)
{
    string email = osoba.email;
    vector <Adresat> :: iterator itr = adresaci.begin();

    while (itr != adresaci.end())
    {
        if (itr->email == email)
        {
            cout << endl << "Podany email jest juz zajety. Sprobuj ponownie" << endl;
            email = wczytajLinie();
            itr = adresaci.begin();
        }
        else
        {
            itr++;
        }
    }

    return email;
}

void dodajAdresata(vector <Adresat> &adresaci, int idZalogowanegoUzytkownika)
{
    Adresat osoba;

    cout << endl << "Prosze podac imie: ";
    osoba.imie = wczytajLinie();
    cout << "Prosze podac nazwisko: ";
    osoba.nazwisko = wczytajLinie();
    cout << "Prosze podac numer telefonu: ";
    osoba.numerTelefonu = wczytajLinie();
    cout << "Prosze podac adres email: ";
    osoba.email = wczytajLinie();
    cout << "Prosze podac adres: ";
    osoba.adres = wczytajLinie();

    osoba.numerTelefonu = zweryfikujWprowadzonyNumerTelefonu(osoba, adresaci);
    osoba.email = zweryfikujWprowadzonyEmail(osoba, adresaci);

    osoba.idAdresata = adresaci.empty()? 1 : adresaci.back().idAdresata + 1;
    osoba.idUzytkownika = idZalogowanegoUzytkownika;
    adresaci.push_back(osoba);
    zapiszNowegoAdresataDoPliku(adresaci);
    cout << "Adresat zostal dodany" << endl << endl;
    Sleep(1000);
}

void wyswietlWszystkichAdresatow(vector <Adresat> &adresaci, int idZalogowanegoUzytkownika)
{
    if (adresaci.empty())
    {
        cout << endl;
        cout << "Ksiazka adresowa jest pusta" << endl;
    }

    for (vector <Adresat> :: iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
    {
        if (itr->idUzytkownika == idZalogowanegoUzytkownika)
        {
            cout << endl;
            cout << "ID: " << itr->idAdresata << endl;
            cout << "Imie: " << itr->imie << endl;
            cout << "Nazwisko: " << itr->nazwisko << endl;
            cout << "Telefon: " << itr->numerTelefonu << endl;
            cout << "Email: " << itr->email << endl;
            cout << "Adres: " << itr->adres << endl;
        }
    }

    cin.get();
}

void wyszukajPoImieniu(vector <Adresat> &adresaci, int idZalogowanegoUzytkownika)
{
    string imie = "";
    int licznikWystapien = 0;

    cout << endl << "Podaj imie osoby do wyszukania: ";
    imie = wczytajLinie();

    for (vector <Adresat> :: iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
    {
        if (itr->idUzytkownika == idZalogowanegoUzytkownika && itr->imie == imie)
        {
            cout << endl;
            cout << "ID: " << itr->idAdresata << endl;
            cout << "Imie: " << itr->imie << endl;
            cout << "Nazwisko: " << itr->nazwisko << endl;
            cout << "Telefon: " << itr->numerTelefonu << endl;
            cout << "Email: " << itr->email << endl;
            cout << "Adres: " << itr->adres << endl;
            licznikWystapien++;
        }
    }

    if (licznikWystapien == 0)
    {
        cout << endl << "Podane imie nie istnieje w zestawieniu" << endl;
    }
    cin.get();
}

void wyszukajPoNazwisku(vector <Adresat> &adresaci, int idZalogowanegoUzytkownika)
{
    string nazwisko = "";
    int licznikWystapien = 0;

    cout << endl << "Podaj nazwisko osoby do wyszukania: ";
    nazwisko = wczytajLinie();

    for (vector <Adresat> :: iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
    {
        if (itr->idUzytkownika == idZalogowanegoUzytkownika && itr->nazwisko == nazwisko)
        {
            cout << endl;
            cout << "ID: " << itr->idAdresata << endl;
            cout << "Imie: " << itr->imie << endl;
            cout << "Nazwisko: " << itr->nazwisko << endl;
            cout << "Telefon: " << itr->numerTelefonu << endl;
            cout << "Email: " << itr->email << endl;
            cout << "Adres: " << itr->adres << endl;
            licznikWystapien++;
        }
    }

    if (licznikWystapien == 0)
    {
        cout << endl << "Podane nazwisko nie istnieje w zestawieniu" << endl;
    }
    cin.get();
}

int main()
{
    int idZalogowanegoUzytkownika = 0;
    char wybor;
    vector <Uzytkownik> uzytkownicy;
    vector <Adresat> adresaci;

    wczytajUzytkownikowZPliku(uzytkownicy);
    wczytajAdresatowZPliku(adresaci);

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
            cout << "1. Dodaj adresata" << endl;
            cout << "2. Wyszukaj po imieniu" << endl;
            cout << "3. Wyszukaj po nazwisku" << endl;
            cout << "4. Wyswietl wszystkich adresatow" << endl;
            cout << "5. Zmiana hasla" << endl;
            cout << "6. Wylogowanie" << endl;

            wybor = wczytajZnak();

            switch (wybor)
            {
                case '1': dodajAdresata(adresaci, idZalogowanegoUzytkownika); break;
                case '2': wyszukajPoImieniu(adresaci, idZalogowanegoUzytkownika); break;
                case '3': wyszukajPoNazwisku(adresaci, idZalogowanegoUzytkownika); break;
                case '4': wyswietlWszystkichAdresatow(adresaci, idZalogowanegoUzytkownika); break;
                case '5': zmienHaslo(uzytkownicy, idZalogowanegoUzytkownika); break;
                case '6': idZalogowanegoUzytkownika = 0; break;
            }
        }

    }

    return 0;
}
