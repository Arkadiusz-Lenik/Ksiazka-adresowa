#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

struct Adresat
{
    int id = 0;
    string imie = "";
    string nazwisko = "";
    string numerTelefonu = "";
    string email = "";
    string adres = "";
};

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

string wczytajLinie()
{
    string wejscie = "";
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

Adresat rozdzielLinieZPlikuNapojedynczeDane(string liniaZPliku)
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
            case 1: osoba.id = stoi(fragmentDanych); break;
            case 2: osoba.imie = fragmentDanych; break;
            case 3: osoba.nazwisko = fragmentDanych; break;
            case 4: osoba.numerTelefonu = fragmentDanych; break;
            case 5: osoba.email = fragmentDanych; break;
            case 6: osoba.adres = fragmentDanych; break;
        }
        numerKolumnyDanychZPliku++;
    }

    return osoba;
}

void zapiszWszystkieDaneDoPliku(vector <Adresat> adresaci)
{
    fstream plik;
    plik.open ("KsiazkaAdresowa.txt", ios::out);

    if (plik.good() == false)
    {
        cout << "Nie udalo sie otworzyc pliku i zapisac w nim danych" << endl;
        Sleep(3000);
        return;
    }

    for (vector <Adresat> :: iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
    {
        plik << itr->id << "|";
        plik << itr->imie << "|";
        plik << itr->nazwisko << "|";
        plik << itr->numerTelefonu << "|";
        plik << itr->email << "|";
        plik << itr->adres << "|" << endl;
    }

    plik.close();
}

void dolaczNowyKontaktDoPliku(Adresat osoba)
{
    fstream plik;
    plik.open ("KsiazkaAdresowa.txt", ios::out | ios::app);

    if (plik.good() == false)
    {
        cout << "Nie udalo sie otworzyc pliku i zapisac w nim danych" << endl;
        Sleep(3000);
        return;
    }

    plik << osoba.id << "|";
    plik << osoba.imie << "|";
    plik << osoba.nazwisko << "|";
    plik << osoba.numerTelefonu << "|";
    plik << osoba.email << "|";
    plik << osoba.adres << "|" << endl;

    cout << endl << "Osoba zostala dodana" << endl;
    Sleep(3000);
    plik.close();
}

void wczytajOsobyZPliku(vector <Adresat> &adresaci)
{
    string liniaZPliku = "";
    Adresat osoba;

    fstream plik;
    plik.open("KsiazkaAdresowa.txt", ios::in);

    if (plik.good() == false)
    {
        cout << "Nie udalo sie otworzyc pliku i odczytac z niego danych" << endl;
        Sleep(3000);
        return;
    }

    while (getline(plik, liniaZPliku))
    {
        osoba = rozdzielLinieZPlikuNapojedynczeDane(liniaZPliku);
        adresaci.push_back(osoba);
        liniaZPliku.clear();
    }

    plik.close();
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

void dodajOsobe(vector <Adresat> &adresaci)
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

    osoba.id = adresaci.empty()? 1 : adresaci.back().id + 1;
    adresaci.push_back(osoba);
    dolaczNowyKontaktDoPliku(osoba);
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
            cout << "ID: " << itr->id << endl;
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
            cout << "ID: " << itr->id << endl;
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

void wyswietlWszystkieOsoby(vector <Adresat> &adresaci)
{
    if (adresaci.empty())
    {
        cout << endl;
        cout << "Ksiazka adresowa jest pusta" << endl;
    }

    for (vector <Adresat> :: iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
    {
        cout << endl;
        cout << "ID: " << itr->id << endl;
        cout << "Imie: " << itr->imie << endl;
        cout << "Nazwisko: " << itr->nazwisko << endl;
        cout << "Telefon: " << itr->numerTelefonu << endl;
        cout << "Email: " << itr->email << endl;
        cout << "Adres: " << itr->adres << endl;
    }

    cin.get();
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
        if (itr->id == idDoUsuniecia)
        {
            adresaci.erase(itr);
            cout << "Wskazany adresat zostal usuniety"  << endl;
            Sleep(3000);
            break;
        }
        else if (itr->id == adresaci.back().id)
        {
            cout << "Wskazany adresat nie widnieje w ksiazce adresowej" << endl;
            Sleep(3000);
            return;
        }
    }

    zapiszWszystkieDaneDoPliku(adresaci);
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
        if (itr->id == idDoModyfikacji)
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
        else if ((itr->id == adresaci.back().id) && czyIstniejeWskazanaOsoba == false)
        {
            cout << "Wskazany adresat nie widnieje w ksiazce adresowej" << endl;
            Sleep(3000);
            return;
        }
    }

    zapiszWszystkieDaneDoPliku(adresaci);
}

int main()
{
    vector <Adresat> adresaci;
    char wybor;

    wczytajOsobyZPliku(adresaci);

    while (true)
    {
        system("cls");
        cout << "1. Dodaj adresata" << endl;
        cout << "2. Wyszukaj po imieniu" << endl;
        cout << "3. Wyszukaj po nazwisku" << endl;
        cout << "4. Wyswietl wszystkich adresatow" << endl;
        cout << "5. Usun adresata" << endl;
        cout << "6. Edytuj adresata" << endl;
        cout << "9. Zakoncz program" << endl;

        wybor = wczytajZnak();

        switch (wybor)
        {
            case '1': dodajOsobe(adresaci); break;
            case '2': wyszukajPoImieniu(adresaci); break;
            case '3': wyszukajPoNazwisku(adresaci); break;
            case '4': wyswietlWszystkieOsoby(adresaci); break;
            case '5': usunAdresata(adresaci); break;
            case '6': edytujAdresata(adresaci); break;
            case '9': exit(0);
        }
    }

    return 0;
}
