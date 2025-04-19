
//Bankomat pro více akcí

#include <iostream>
#include <string>
#include <unistd.h>  // pro funkci sleep()

using namespace std;

const int pocetuctu = 3;
string ucty[pocetuctu]     = {"1234567890", "1111111111", "2222222222"};
string piny[pocetuctu]     = {"1234",       "0000",       "2222"      };
int zustatky[pocetuctu]    = {10000,         5000,         20000       };
int delitelebankovek[6]    = {5000, 2000, 1000, 500, 200, 100};

// Kontrola, zda částka je násobkem 100 (bankovky)
bool kontrolacastky(int a) {
    return a > 0 && a % 100 == 0;
}

// Přihlášení uživatele, vrací jeho index (0..2) nebo -1
int overeni() {
    string ucet, pin;
    cout << "Cislo uctu: ";
    cin >> ucet;
    for (int i = 0; i < pocetuctu; ++i) {
        if (ucty[i] == ucet) {
            cout << "PIN: ";
            cin >> pin;
            if (piny[i] == pin) {
                return i;
            } else {
                cout << "Spatny PIN.\n";
                return -1;
            }
        }
    }
    cout << "Ucet nenalezen.\n";
    return -1;
}

// Vklad na účet 'uzivatel'
void vklad(int uzivatel) {
    int castka;
    cout << "Kolik chcete vlozit? (0 pro zpet): ";
    cin >> castka;
    if (castka == 0) return;
    if (!kontrolacastky(castka)) {
        cout << "Nelze vlozit mince.\n";
        return;
    }
    zustatky[uzivatel] += castka;
    cout << "Vlozeno " << castka << " Kc\n";
}

// Výběr z účtu 'uzivatel' s rozpiskou bankovek
void vyber(int uzivatel) {
    int castka;
    cout << "Kolik chcete vybrat? (0 pro zpet): ";
    cin >> castka;
    if (castka == 0) return;
    if (castka < 0 || castka > zustatky[uzivatel] || !kontrolacastky(castka)) {
        cout << "Nelze vybrat.\n";
        return;
    }
    zustatky[uzivatel] -= castka;
    cout << "Vybrano " << castka << " Kc\nRozpis bankovek:\n";
    int zbytek = castka;
    for (int i = 0; i < 6; ++i) {
        int nomin = delitelebankovek[i];
        int pocet = zbytek / nomin;
        if (pocet > 0) {
            cout << " " << nomin << " Kc x " << pocet << "\n";
            zbytek %= nomin;
        }
    }
    sleep(5);
}

// Kontrola zůstatku na 5 sekund pro účet 'uzivatel'
void kontrolaZustatku(int uzivatel) {
    cout << "Zustatek: " << zustatky[uzivatel] << " Kc\n";
    sleep(5);
}

int main() {
    int uzivatel = -1;
    while (true) {
        if (uzivatel < 0) {
            uzivatel = overeni();
        } else {
            int volba;
            cout << "\n1: Vklad  2: Vyber  3: Zustatek  4: Novy uzivatel  5: Konec -> ";
            cin >> volba;
            switch (volba) {
                case 1:
                    vklad(uzivatel);
                    break;
                case 2:
                    vyber(uzivatel);
                    break;
                case 3:
                    kontrolaZustatku(uzivatel);
                    break;
                case 4:
                    uzivatel = -1;  // odhlásit, nový uživatel
                    break;
                case 5:
                    return 0;       // konec programu
                default:
                    cout << "Neplatna volba.\n";
            }
        }
    }
    return 0;
}



/* Bankomat pro 1 akci a pak konec
#include <iostream>
#include <string>
#include <unistd.h>  // pro funkci sleep()

using namespace std;

const int pocetuctu = 3;
string ucty[pocetuctu]     = {"1234567890", "1111111111", "2222222222"};
string piny[pocetuctu]     = {"1234",       "0000",       "2222"      };
int zustatky[pocetuctu]    = {10000,         5000,         20000       };
int delitelebankovek[6]    = {5000, 2000, 1000, 500, 200, 100};

// Kontrola, zda částka je násobkem 100 (bankovky)
bool kontrolacastky(int a) {
    return a > 0 && a % 100 == 0;
}

// Přihlášení uživatele, vrací jeho index (0..2) nebo -1
int overeni() {
    string ucet, pin;
    cout << "\nCislo uctu: ";
    cin >> ucet;
    for (int i = 0; i < pocetuctu; ++i) {
        if (ucty[i] == ucet) {
            cout << "PIN: ";
            cin >> pin;
            if (piny[i] == pin) {
                return i;
            } else {
                cout << "Spatny PIN.\n";
                return -1;
            }
        }
    }
    cout << "Ucet nenalezen.\n";
    return -1;
}

// Vklad na účet 'uzivatel'
void vklad(int uzivatel) {
    int castka;
    cout << "Kolik chcete vlozit? (0 pro zpet): ";
    cin >> castka;
    if (castka == 0) return;
    if (!kontrolacastky(castka)) {
        cout << "Nelze vlozit mince.\n";
        return;
    }
    zustatky[uzivatel] += castka;
    cout << "Vlozeno " << castka << " Kc\n";
}

// Výběr z účtu 'uzivatel' s rozpiskou bankovek
void vyber(int uzivatel) {
    int castka;
    cout << "Kolik chcete vybrat? (0 pro zpet): ";
    cin >> castka;
    if (castka == 0) return;
    if (castka < 0 || castka > zustatky[uzivatel] || !kontrolacastky(castka)) {
        cout << "Nelze vybrat.\n";
        return;
    }
    zustatky[uzivatel] -= castka;
    cout << "Vybrano " << castka << " Kc\nRozpis bankovek:\n";
    int zbytek = castka;
    for (int i = 0; i < 6; ++i) {
        int nomin = delitelebankovek[i];
        int pocet = zbytek / nomin;
        if (pocet > 0) {
            cout << " " << nomin << " Kc x " << pocet << "\n";
            zbytek %= nomin;
        }
    }
    sleep(5);
}

// Kontrola zůstatku na 5 sekund pro účet 'uzivatel'
void kontrolaZustatku(int uzivatel) {
    cout << "Zustatek: " << zustatky[uzivatel] << " Kc\n";
    sleep(5);
}

int main() {
    int uzivatel = -1;
    while (true) {
        if (uzivatel < 0) {
            uzivatel = overeni();
        } else {
            int volba;
            cout << "\n1: Vklad  2: Vyber  3: Zustatek  4: Novy uzivatel  5: Konec -> ";
            cin >> volba;
            switch (volba) {
                case 1:
                    vklad(uzivatel);
                    uzivatel = -1;  // odhlásit po akci
                    break;
                case 2:
                    vyber(uzivatel);
                    uzivatel = -1;  // odhlásit po akci
                    break;
                case 3:
                    kontrolaZustatku(uzivatel);
                    uzivatel = -1;  // odhlásit po akci
                    break;
                case 4:
                    uzivatel = -1;  // ruční odhlášení pro nového uživatele
                    break;
                case 5:
                    return 0;       // konec programu
                default:
                    cout << "Neplatna volba.\n";
                    uzivatel = -1;  // odhlásit i po chybné volbě
            }
        }
    }
    return 0;
}


*/
