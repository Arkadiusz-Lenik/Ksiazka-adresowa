#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <stdio.h>

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

int wczytajLiczbeCalkowita()
{
    string wejscie = "";
    int liczba = 0;

    while (true)
    {
        getline(cin, wejscie);
        stringstream myStream(wejscie);

        if (myStream >> liczba)
        {
            break;
        }

        cout << "To nie jest liczba. Sprobuj ponownie" << endl;
    }

    return liczba;
}

char wczytajZnakPotwierdzajacy()
{
    string wejscie = "";
    char znak;

    while (true)
    {
        getline(cin, wejscie);

        if (wejscie == "t" || wejscie == "n")
        {
            znak = wejscie[0];
            break;
        }
        else
        {
            cout << "Wprowadzono niewlasciwy znak. Sprobuj ponownie" << endl;
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

int znajdzPozycjeModyfikowanegoAdresata(vector <Adresat> &adresaci, int idModyfikowanegoAdresata)
{
    int pozycjaModyfikowanegoAdresata = 0;

    for (size_t i = 0; i < adresaci.size(); i++)
    {
        if (adresaci[i].idAdresata == idModyfikowanegoAdresata)
        {
            pozycjaModyfikowanegoAdresata = i;
            break;
        }
    }

    return pozycjaModyfikowanegoAdresata;
}

void zapiszWszystkichAdresatowDoPlikuPoEdycji(vector <Adresat> &adresaci, int idModyfikowanegoAdresata)
{
    fstream plikBazowy, plikDocelowy;
    string liniaZPliku = "";
    int pozycjaModyfikowanegoAdresata = 0;
    Adresat osoba;
    plikBazowy.open ("Adresaci.txt", ios::in);
    plikDocelowy.open ("Adresaci_tymczasowy.txt", ios::out);

    if (plikBazowy.good() == false || plikDocelowy.good() == false)
    {
        cout << "Nie udalo sie otworzyc pliku Adresaci.txt i/lub Adresaci_tymczasowy.txt oraz zapisac w nim danych" << endl;
        Sleep(3000);
        return;
    }

    pozycjaModyfikowanegoAdresata = znajdzPozycjeModyfikowanegoAdresata(adresaci, idModyfikowanegoAdresata);

    while (getline(plikBazowy, liniaZPliku))
    {
        osoba = rozdzielLinieZPlikuAdresaciNapojedynczeDane(liniaZPliku);

        if (osoba.idAdresata == idModyfikowanegoAdresata)
        {
            plikDocelowy << adresaci[pozycjaModyfikowanegoAdresata].idAdresata << "|";
            plikDocelowy << adresaci[pozycjaModyfikowanegoAdresata].idUzytkownika << "|";
            plikDocelowy << adresaci[pozycjaModyfikowanegoAdresata].imie << "|";
            plikDocelowy << adresaci[pozycjaModyfikowanegoAdresata].nazwisko << "|";
            plikDocelowy << adresaci[pozycjaModyfikowanegoAdresata].numerTelefonu << "|";
            plikDocelowy << adresaci[pozycjaModyfikowanegoAdresata].email << "|";
            plikDocelowy << adresaci[pozycjaModyfikowanegoAdresata].adres << "|" << endl;
        }
        else
        {
            plikDocelowy << osoba.idAdresata << "|";
            plikDocelowy << osoba.idUzytkownika << "|";
            plikDocelowy << osoba.imie << "|";
            plikDocelowy << osoba.nazwisko << "|";
            plikDocelowy << osoba.numerTelefonu << "|";
            plikDocelowy << osoba.email << "|";
            plikDocelowy << osoba.adres << "|" << endl;
        }

        liniaZPliku.clear();
    }

    plikBazowy.close();
    plikDocelowy.close();
    remove ("Adresaci.txt");
    rename("Adresaci_tymczasowy.txt", "Adresaci.txt");
}

void zapiszWszystkichAdresatowDoPlikuPoUsuwaniu(vector <Adresat> &adresaci, int idUsuwanegoAdresata)
{
    fstream plikBazowy, plikDocelowy;
    string liniaZPliku = "";
    Adresat osoba;
    plikBazowy.open ("Adresaci.txt", ios::in);
    plikDocelowy.open ("Adresaci_tymczasowy.txt", ios::out);

    if (plikBazowy.good() == false || plikDocelowy.good() == false)
    {
        cout << "Nie udalo sie otworzyc pliku Adresaci.txt i/lub Adresaci_tymczasowy.txt oraz zapisac w nim danych" << endl;
        Sleep(3000);
        return;
    }

    while (getline(plikBazowy, liniaZPliku))
    {
        osoba = rozdzielLinieZPlikuAdresaciNapojedynczeDane(liniaZPliku);

        if (osoba.idAdresata == idUsuwanegoAdresata)
        {
            continue;
        }
        else
        {
            plikDocelowy << osoba.idAdresata << "|";
            plikDocelowy << osoba.idUzytkownika << "|";
            plikDocelowy << osoba.imie << "|";
            plikDocelowy << osoba.nazwisko << "|";
            plikDocelowy << osoba.numerTelefonu << "|";
            plikDocelowy << osoba.email << "|";
            plikDocelowy << osoba.adres << "|" << endl;
        }

        liniaZPliku.clear();
    }

    plikBazowy.close();
    plikDocelowy.close();
    remove ("Adresaci.txt");
    rename("Adresaci_tymczasowy.txt", "Adresaci.txt");
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

void wczytajAdresatowZPliku(vector <Adresat> &adresaci, int idZalogowanegoUzytkownika)
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

        if (osoba.idUzytkownika == idZalogowanegoUzytkownika)
        {
            adresaci.push_back(osoba);
        }
        else
        {
            continue;
        }

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

int znajdzMaksymalnaWartoscIdAdresataWPliku()
{
    string liniaZPliku = "";
    int maksymalnaWartoscIdAdresata = 0;
    Adresat osoba;
    fstream plik;
    plik.open("Adresaci.txt", ios::in);

    if (plik.good() == false)
    {
        cout << "Nie udalo sie otworzyc pliku Adresaci.txt i odczytac z niego danych" << endl;
        Sleep(3000);
        return 0;
    }

    while (getline(plik, liniaZPliku))
    {
        osoba = rozdzielLinieZPlikuAdresaciNapojedynczeDane(liniaZPliku);
        maksymalnaWartoscIdAdresata = osoba.idAdresata;
        liniaZPliku.clear();
    }

    plik.close();
    return maksymalnaWartoscIdAdresata;
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

    osoba.idAdresata = znajdzMaksymalnaWartoscIdAdresataWPliku() + 1;
    osoba.idUzytkownika = idZalogowanegoUzytkownika;
    adresaci.push_back(osoba);
    zapiszNowegoAdresataDoPliku(adresaci);
    cout << "Adresat zostal dodany" << endl << endl;
    Sleep(1000);
}

void wyswietlWszystkichAdresatow(vector <Adresat> &adresaci)
{
    if (adresaci.empty())
    {
        cout << endl;
        cout << "Ksiazka adresowa jest pusta" << endl;
    }

    for (vector <Adresat> :: iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
    {
        cout << endl;
        cout << "ID: " << itr->idAdresata << endl;
        cout << "Imie: " << itr->imie << endl;
        cout << "Nazwisko: " << itr->nazwisko << endl;
        cout << "Telefon: " << itr->numerTelefonu << endl;
        cout << "Email: " << itr->email << endl;
        cout << "Adres: " << itr->adres << endl;
    }

    cin.get();
}

void wyszukajPoImieniu(vector <Adresat> &adresaci)
{
    string imie = "";
    int licznikWystapien = 0;

    cout << endl << "Podaj imie osoby do wyszukania: ";
    imie = wczytajLinie();

    for (vector <Adresat> :: iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
    {
        if (itr->imie == imie)
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

void wyszukajPoNazwisku(vector <Adresat> &adresaci)
{
    string nazwisko = "";
    int licznikWystapien = 0;

    cout << endl << "Podaj nazwisko osoby do wyszukania: ";
    nazwisko = wczytajLinie();

    for (vector <Adresat> :: iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
    {
        if (itr->nazwisko == nazwisko)
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

void wyswietlPodmenuModyfikacji()
{
    cout << endl << "Wybierz dane ktore chcesz zmodyfikowac: " << endl;
    cout << "1 - imie" << endl;
    cout << "2 - nazwisko" << endl;
    cout << "3 - numer telefonu" << endl;
    cout << "4 - email" << endl;
    cout << "5 - adres" << endl;
    cout << "6 - powrot do menu" << endl;
}

void edytujAdresata(vector <Adresat> &adresaci)
{
    Adresat osoba;
    int idDoModyfikacji = 0, wyborDanychDoModyfikacji = 0;
    bool czyIstniejeWskazanaOsoba = false;

    cout << endl << "Podaj nr ID adresata ktorego chcesz zmodyfikowac: ";
    idDoModyfikacji = wczytajLiczbeCalkowita();

    for (vector <Adresat> :: iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
    {
        if (itr->idAdresata == idDoModyfikacji)
        {
            czyIstniejeWskazanaOsoba = true;
            wyswietlPodmenuModyfikacji();
            wyborDanychDoModyfikacji = wczytajLiczbeCalkowita();

            switch (wyborDanychDoModyfikacji)
            {
                case 1:
                    cout << endl << "Prosze podac nowe imie: ";
                    (*itr).imie = wczytajLinie();
                    cout << endl << "Imie zostalo zmienione" << endl;
                    Sleep(3000);
                    break;
                case 2:
                    cout << endl << "Prosze podac nowe nazwisko: ";
                    (*itr).nazwisko = wczytajLinie();
                    cout << endl << "Nazwisko zostalo zmienione" << endl;
                    Sleep(3000);
                    break;
                case 3:
                    cout << endl << "Prosze podac nowy numer telefonu: ";
                    osoba.numerTelefonu = wczytajLinie();
                    (*itr).numerTelefonu = zweryfikujWprowadzonyNumerTelefonu(osoba, adresaci);
                    cout << endl << "Numer telefonu zostal zmieniony" << endl;
                    Sleep(3000);
                    break;
                case 4:
                    cout << endl << "Prosze podac nowy email: ";
                    osoba.email = wczytajLinie();
                    (*itr).email = zweryfikujWprowadzonyEmail(osoba, adresaci);
                    cout << endl << "Email zostal zmieniony" << endl;
                    Sleep(3000);
                    break;
                case 5:
                    cout << endl << "Prosze podac nowy adres: ";
                    (*itr).adres = wczytajLinie();
                    cout << endl << "Adres zostal zmieniony" << endl;
                    Sleep(3000);
                    break;
                case 6:
                    cout << endl << "Powrot do menu glownego" << endl;
                    Sleep(3000);
                    return;
            }
        }
        else if ((itr->idAdresata == adresaci.back().idAdresata) && czyIstniejeWskazanaOsoba == false)
        {
            cout << "Wskazany adresat nie widnieje w ksiazce adresowej" << endl;
            Sleep(3000);
            return;
        }
    }

    zapiszWszystkichAdresatowDoPlikuPoEdycji(adresaci, idDoModyfikacji);
}

void usunAdresata(vector <Adresat> &adresaci)
{
    int idDoUsuniecia = 0;
    char potwierdzenieUsuniecia;

    cout << endl << "Podaj nr ID adresata ktorego chcesz usunac: ";
    idDoUsuniecia = wczytajLiczbeCalkowita();
    cout << "Czy potwierdzasz usuniecie wskazanego adresata? (t/n)" << endl;
    potwierdzenieUsuniecia = wczytajZnakPotwierdzajacy();

    if (potwierdzenieUsuniecia == 'n')
    {
        return;
    }

    for (vector <Adresat> :: iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
    {
        if (itr->idAdresata == idDoUsuniecia)
        {
            adresaci.erase(itr);
            cout << "Wskazany adresat zostal usuniety"  << endl;
            Sleep(3000);
            break;
        }
        else if (itr->idAdresata == adresaci.back().idAdresata)
        {
            cout << "Wskazany adresat nie widnieje w ksiazce adresowej" << endl;
            Sleep(3000);
            return;
        }
    }

    zapiszWszystkichAdresatowDoPlikuPoUsuwaniu(adresaci, idDoUsuniecia);
}

int main()
{
    int idZalogowanegoUzytkownika = 0;
    char wybor;
    vector <Uzytkownik> uzytkownicy;
    vector <Adresat> adresaci;

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
                case '2': idZalogowanegoUzytkownika = zalogujUzytkownika(uzytkownicy);
                    wczytajAdresatowZPliku(adresaci, idZalogowanegoUzytkownika);
                    break;
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
            cout << "5. Usun adresata" << endl;
            cout << "6. Edytuj adresata" << endl;
            cout << "7. Zmiana hasla" << endl;
            cout << "8. Wylogowanie" << endl;

            wybor = wczytajZnak();

            switch (wybor)
            {
                case '1': dodajAdresata(adresaci, idZalogowanegoUzytkownika); break;
                case '2': wyszukajPoImieniu(adresaci); break;
                case '3': wyszukajPoNazwisku(adresaci); break;
                case '4': wyswietlWszystkichAdresatow(adresaci); break;
                case '5': usunAdresata(adresaci); break;
                case '6': edytujAdresata(adresaci); break;
                case '7': zmienHaslo(uzytkownicy, idZalogowanegoUzytkownika); break;
                case '8': idZalogowanegoUzytkownika = 0;
                    adresaci.clear();
                    break;
            }
        }
    }

    return 0;
}
