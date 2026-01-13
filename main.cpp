//preprocessor include directives
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <cmath>
//classes(header files)
#include "Fahrzeug.h"
#include "PKW.h"
#include "Fahrrad.h"
#include "Simulation.h"
#include "Weg.h"
#include "PKW.h"
#include "Fahrrad.h"
#include "SimuClient.h"

//using directives
using namespace std;
//globalen Varibalen
extern double dGlobaleZeit;
const double dEpsilon = 1e-6;;

void vAufgabe1();
void vAufgabe1a();
void vAufgabe2();
void vAufgabe3();
void vAufgabe3();
void vAufgabe_Probe();
void vAufgabe_AB1();
void vAufgabe_4();
void vAufgabe5_4_Test();
void vAufgabe6();

//int main() {
    //vAufgabe1();
    //vAufgabe1a();
    //vAufgabe2();
    //vAufgabe3();
    //vAufgabe_Probe();
    //vAufgabe_AB1();
	//vAufgabe_4();
	//vAufgabe5_4_Test();
	//vAufgabe5_5_Test();
    //return 0;
//}

void vAufgabe1() {
    cout << "Aufgabe 1\n";

    //static
    Fahrzeug f1("Alpha");
    Fahrzeug f2("Bravo");
    //raw pointer
    Fahrzeug* pF3 = new Fahrzeug("Charlie");

    delete pF3;
    //smart pointers
    std::unique_ptr<Fahrzeug> pUni1 = make_unique<Fahrzeug>("Uni-1", 100.0);
    std::unique_ptr pUni2 = make_unique<Fahrzeug>("Uni-2", 120.0);
    //smart pointer shared
    std::shared_ptr<Fahrzeug> pShare1 = make_shared<Fahrzeug>("Share-1", 80.0);
    cout << "use_count before copy: " << pShare1.use_count() << "\n";
    std::shared_ptr<Fahrzeug> pShare2 = pShare1;
    cout << "use_count after copy:  " << pShare1.use_count() << "\n";
    //vector unique_ptr
    vector<unique_ptr<Fahrzeug>> vecUni;
    vecUni.push_back(std::move(pUni1));
    vecUni.push_back(std::move(pUni2));
    //vector shared_ptr
    vector<shared_ptr<Fahrzeug>> vecShare;
    vecShare.push_back(pShare1);
    vecShare.push_back(pShare2);

    cout << "vecShare[0] use_count: " << vecShare[0].use_count() << "\n";
    cout << "vecShare[1] use_count: " << vecShare[1].use_count() << "\n";
}

void vAufgabe1a() {
    cout << "Aufgabe 1a\n";
    int n;
    cout << "Wie viele Fahrzeuge wollen Sie haben? ";
    cin >> n;
    //neue fahrzeug vector
    vector<unique_ptr<Fahrzeug>> fahrzeuge;
    fahrzeuge.reserve(n);

    for (int i = 0; i < n; ++i) {
        string name;
        double vmax;
        cout << "Bitte Name und MaxGeschwindigkeit (km/h) fuer Fahrzeug "
             << (i+1) << " eingeben: ";
        cin >> name >> vmax;
        fahrzeuge.push_back(make_unique<Fahrzeug>(name, vmax));
    }
    //Header von der Ausgabe/0 punkt der fahrzeug
    dGlobaleZeit = 0.0;
    Fahrzeug::vKopf();
    for (auto& f : fahrzeuge) {
        cout << *f << '\n';
    }
    //Bewegung der Fahrzeuge und herstellung die Daten in der Tabelle
    const double dt = 0.5;
    for (int step = 0; step < 6; ++step) {
        dGlobaleZeit += dt;
        for (auto & f : fahrzeuge) {
            f->vSimulieren();
        }
        cout << "\nZeit = " << dGlobaleZeit << " h\n";
        Fahrzeug::vKopf();
        for (auto& f : fahrzeuge) {
            cout << *f << '\n';
        }
    }
}

void vAufgabe2() {
    cout << "Aufgabe 2\n";

    int nPKW, nFahrrad;
    cout << "Anzahl der PKW: ";
    cin >> nPKW;
    cout << "Anzahl der Fahrraeder: ";
    cin >> nFahrrad;

    vector<unique_ptr<Fahrzeug>> fahrzeuge;
    fahrzeuge.reserve(nPKW + nFahrrad);

    for (int i = 0; i < nPKW; ++i) {
        string name;
        double vmax, verbrauch, tankvol;
        cout << "PKW " << (i+1)<<"\n"
             << "Bitte gibt mal die Name, MaxGeschwindigkeit, Verbrauch(l/100km) und Tankvolumen ein \n";
        cin >> name >> vmax >> verbrauch >> tankvol;
        fahrzeuge.push_back(make_unique<PKW>(name, vmax, verbrauch, tankvol));
    }

    for (int i = 0; i < nFahrrad; ++i) {
        string name;
        double vmax;
        cout << "Fahrrad " << (i+1) << " Name und MaxGeschwindigkeit: ";
        cin >> name >> vmax;
        fahrzeuge.push_back(make_unique<Fahrrad>(name, vmax));
    }

    dGlobaleZeit = 0.0;
    const double dt    = 0.5;
    const double t_max = 5.0;

    while (dGlobaleZeit < t_max - dEpsilon) {
        dGlobaleZeit += dt;

        if (std::fabs(dGlobaleZeit - 3.0) < dEpsilon) {
            // nach 3 Stunden alle PKW volltanken
            for (auto& f : fahrzeuge) {
                PKW* pPKW = dynamic_cast<PKW*>(f.get());
                if (pPKW) {
                    pPKW->dTanken(); // volltanken
                }
            }
        }

        for (auto& f : fahrzeuge) {
            f->vSimulieren();
        }

        cout << "\nZeit = " << dGlobaleZeit << " h\n";
        Fahrzeug::vKopf();
        for (auto& f : fahrzeuge) {
            cout << *f << '\n';
        }
    }
}

void vAufgabe3() {
    cout << "Aufgabe 3\n";

    vector<unique_ptr<Fahrzeug>> v;
    v.push_back(make_unique<PKW>("Audi", 150.0, 8.0));
    v.push_back(make_unique<Fahrrad>("Giant", 20.0));
    v.push_back(make_unique<Fahrzeug>("VW", 45.0));

    dGlobaleZeit = 0.0;
    const double dt = 0.5;

    for (int step = 0; step < 4; ++step) {
        dGlobaleZeit += dt;
        for (auto& f : v) {
            f->vSimulieren();
        }
    }

    cout << "Unsortiert:\n";
    Fahrzeug::vKopf();
    for (auto& f : v) {
        cout << *f << '\n';
    }

    std::sort(v.begin(), v.end(),
              [](const std::unique_ptr<Fahrzeug>& a,
                 const std::unique_ptr<Fahrzeug>& b) {
                  return *a < *b;
              });

    cout << "\nSortiert nach Gesamtstrecke:\n";
    Fahrzeug::vKopf();
    for (auto& f : v) {
        cout << *f << '\n';
    }
}

void vAufgabe_Probe() {
    cout << "Aufgabe Probe\n";
    PKW* pF1 = new PKW("Audi", 150.0, 8.0);
    dGlobaleZeit = 0.0;
    Fahrzeug::vKopf();
    dGlobaleZeit = 5.0;
    cout << endl << "Globalezeit = " << dGlobaleZeit << endl;
    pF1->vSimulieren();
    std::cout << *pF1 << endl;
    delete pF1;
    char c;
    std::cin >> c;
}

void vAufgabe_AB1() {

    int l = 0; // Laufindex für gezielte AUsgabe
    vector<int> ausgabe{13};
    double dTakt = 0.4;

    std::vector<unique_ptr<Fahrzeug>> vecFahrzeuge;
    vecFahrzeuge.push_back(make_unique <PKW>("Audi", 231, 11.4));
    vecFahrzeuge.push_back(make_unique <Fahrrad>("BMX", 19.8));
    for (dGlobaleZeit = 0; dGlobaleZeit < 10; dGlobaleZeit += dTakt)
    {
        auto itL = find(ausgabe.begin(), ausgabe.end(), l);
        if (itL != ausgabe.end()) {
            std::cout << std::endl << l <<  " Globalezeit = " << dGlobaleZeit << std::endl;
            Fahrzeug::vKopf();
        }

        for (int i = 0; i < (int) vecFahrzeuge.size(); i++)
        {
            vecFahrzeuge[i]->vSimulieren();
            if (fabs(dGlobaleZeit - 3.0) < dTakt/2)
            {
                vecFahrzeuge[i]->dTanken();
            }
            if (itL != ausgabe.end()) {
                std::cout << *vecFahrzeuge[i] << endl;
            }
        }
        l++;
    }
    char c;
    std::cin >> c;}



void vAufgabe_4() {
    Weg::vKopf();
    Weg w("weg", 100.0, Tempolimit::Landstrasse);
    std::cout << w << "\n";
}
void vAufgabe5_4_Test() {
    Weg w("TestWeg", 100.0);

    auto p1 = std::make_unique<PKW>("Auto1", 50.0, 8.0);
    auto p2 = std::make_unique<Fahrrad>("Rad1", 30.0);

    // driving immediately
    w.vAnnahme(std::move(p1));

    // parked until t = 3.0
    w.vAnnahme(std::move(p2), 3.0);

    for (int i = 0; i <= 10; ++i) {
        dGlobaleZeit = i * 0.5;
        std::cout << "\nZeit = " << dGlobaleZeit << "\n";
        w.vSimulieren();
        std::cout << w << "\n";
    }
}
void vTestLosfahren(double dt) {
    Weg w("TestWeg", 100.0);

    // Vehicle parked until 3.0
    w.vAnnahme(std::make_unique<Fahrrad>("Rad", 30.0), 3.0);

    for (int k = 0; k < 50; ++k) {
        dGlobaleZeit = k * dt;

        std::cout << "t = " << dGlobaleZeit << "\n";
        w.vSimulieren();
    }
}


void vAufgabe6Simulation(double dt) {
    std::cout << "\n=== Aufgabe 6 Simulation (dt=" << dt << ") ===\n";
    dGlobaleZeit = 0.0;

    bInitialisiereGrafik(800, 500);

    Weg wegHin("Hinweg", 500.0, Tempolimit::Innerorts);
    Weg wegRueck("Rueckweg", 500.0, Tempolimit::Autobahn);

    wegHin.vAnnahme(std::make_unique<PKW>("PKW_Hin", 120.0, 7.0));
    wegHin.vAnnahme(std::make_unique<Fahrrad>("Rad_Hin", 30.0), 3.0);

    wegRueck.vAnnahme(std::make_unique<PKW>("PKW_Rueck", 140.0, 6.5), 3.0);
    wegRueck.vAnnahme(std::make_unique<Fahrrad>("Rad_Rueck", 25.0));

    int coords[4] = { 700, 250, 100, 250 };
    bZeichneStrasse(wegHin.sName(), wegRueck.sName(), 500, 2, coords);
    wegHin.vSetzeGezeichnet();
    wegRueck.vSetzeGezeichnet();

    for (int step = 0; step < 30; ++step) {
        dGlobaleZeit = step * dt;
        std::cout << "\nZeit = " << dGlobaleZeit << "\n";
        vSetzeZeit(dGlobaleZeit);

        wegHin.vSimulieren();
        wegRueck.vSimulieren();

        wegHin.vZeichnen();
        wegRueck.vZeichnen();

        vSleep(100);
    }

    vBeendeGrafik();
}

void vAufgabe6() {
    vAufgabe6Simulation(0.25);
    vAufgabe6Simulation(0.3);
}

int main() {
    vAufgabe6();
    return 0;
}
