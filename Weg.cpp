#include "Weg.h"
#include "Fahrzeug.h"
#include "Fahrausnahme.h"
#include "SimuClient.h"
#include <iostream>
#include <limits>
#include <utility>



Weg::Weg(const std::string& name, double laenge, Tempolimit limit)
    : Simulationsobjekt(name),
      p_dLaenge(laenge > 0.0 ? laenge : 0.0),
      p_eTempolimit(limit) {}

Weg::~Weg() = default;

double Weg::getTempolimit() const {
    switch (p_eTempolimit) {
    case Tempolimit::Innerorts:   return 50.0;
    case Tempolimit::Landstrasse: return 100.0;
    case Tempolimit::Autobahn:    return static_cast<double>(std::numeric_limits<int>::max());
    }
    return static_cast<double>(std::numeric_limits<int>::max());
}

void Weg::vSimulieren() {
    // (optional time check like before)
    // vSetZeit(dGlobaleZeit);

    for (auto it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end(); ) {
        auto current = it++; // advance first, so erasing current is safe
        if (!(*current)) continue;

        try {
            (*current)->vSimulieren();
        }
        catch (Fahrausnahme& e) {
            e.vBearbeiten(); // Losfahren or Streckenende
        }
    }
}


void Weg::vAusgeben(std::ostream& os) const {
    // ID+Name von Simulationsobjekt nutzen
    Simulationsobjekt::vAusgeben(os);

    // Länge + (Fahrzeugnamen)
    os << " : " << p_dLaenge << " ( ";
    for (const auto& pfzg : p_pFahrzeuge) {
        os << pfzg->sName() << " ";
    }
    os << ")";
}

void Weg::vKopf() {
    std::cout << "ID | Name | Laenge | Fahrzeuge\n";
    std::cout << "------------------------------------------------\n";
}
void Weg::vAnnahme(std::unique_ptr<Fahrzeug> pFzg) {
    // driving vehicle
    pFzg->vNeueStrecke(*this);
    p_pFahrzeuge.push_back(std::move(pFzg)); // driving goes to the back
}

void Weg::vZeichnen() const
{
    if (sName().empty()) return;

    if (!p_bGezeichnet) {
        int y = 100 + 60 * iID();
        int coords[4] = { 100, y, 700, y };

        bool ok = bZeichneStrasse(sName(), "", (int)p_dLaenge, 2, coords);
        std::cout << "bZeichneStrasse('" << sName() << "') -> " << ok << "\n";

        p_bGezeichnet = true;
    }

    for (const auto& pfzg : p_pFahrzeuge) {
        if (pfzg) pfzg->vZeichnen(*this);
    }
}


void Weg::vAnnahme(std::unique_ptr<Fahrzeug> pFzg, double startZeit) {
    // parked vehicle
    pFzg->vNeueStrecke(*this, startZeit);
    p_pFahrzeuge.push_front(std::move(pFzg)); // parked goes to the front
}
std::unique_ptr<Fahrzeug> Weg::pAbgabe(const Fahrzeug& aFzg) {
    for (auto it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end(); ++it) {
        if (!(*it)) continue;
        if (**it == aFzg) {                 // compares by ID (Simulationsobjekt::operator==)
            auto ret = std::move(*it);      // take ownership out
            p_pFahrzeuge.erase(it);         // remove list node
            return ret;
        }
    }
    return nullptr;
}
