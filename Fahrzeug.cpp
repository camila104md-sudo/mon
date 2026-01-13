#include "Fahrzeug.h"
#include <cmath>
#include "Fahren.h"
#include "Parken.h"
#include "Weg.h"
#include "Verhalten.h"
// globale Zeit wie bisher
double dGlobaleZeit = 0.0;
extern const double dEpsilon;

Fahrzeug::Fahrzeug()
    : Simulationsobjekt(""),
      p_dMaxGeschwindigkeit(0.0),
      p_dGesamtStrecke(0.0),
      p_dGesamtZeit(0.0) {}

Fahrzeug::Fahrzeug(const std::string& name)
    : Simulationsobjekt(name),
      p_dMaxGeschwindigkeit(0.0),
      p_dGesamtStrecke(0.0),
      p_dGesamtZeit(0.0) {}

Fahrzeug::Fahrzeug(const std::string& name, double vmax)
    : Simulationsobjekt(name),
      p_dMaxGeschwindigkeit(vmax > 0.0 ? vmax : 0.0),
      p_dGesamtStrecke(0.0),
      p_dGesamtZeit(0.0) {}

Fahrzeug::~Fahrzeug() = default;

// wie vorher: Name + vmax kopieren, ID/Strecken/Zeiten NICHT
Fahrzeug& Fahrzeug::operator=(const Fahrzeug& rhs) {
    if (this != &rhs) {
        Simulationsobjekt::operator=(rhs);     // kopiert nur Name
        p_dMaxGeschwindigkeit = rhs.p_dMaxGeschwindigkeit;
    }
    return *this;
}

void Fahrzeug::vKopf() {
    std::cout << std::resetiosflags(std::ios::right) << std::setiosflags(std::ios::left)
              << std::setw(4)  << "ID"
              << std::setw(16) << "Name"
              << std::resetiosflags(std::ios::left) << std::setiosflags(std::ios::right)
              << std::setw(20) << "MaxGeschwindigkeit"
              << std::setw(15) << "Strecke"
              << std::setw(10) << "Zeit"
              << std::setw(20) << "AktGeschwindigkeit"
              << '\n';

    std::cout << std::resetiosflags(std::ios::left);
    std::cout << std::string(4 + 16 + 20 + 15 + 10 + 20, '-') << "\n";
}

void Fahrzeug::vAusgeben(std::ostream& os) const {
    // ID + Name aus Simulationsobjekt
    Simulationsobjekt::vAusgeben(os);

    os << std::resetiosflags(std::ios::left) << std::setiosflags(std::ios::right)
       << std::fixed << std::setprecision(2)
       << std::setw(20) << p_dMaxGeschwindigkeit
       << std::setw(15) << p_dGesamtStrecke
       << std::setw(10) << p_dGesamtZeit
       << std::setw(20) << dGeschwindigkeit()
       << std::resetiosflags(std::ios::right);
}

void Fahrzeug::vNeueStrecke(Weg& weg) {
    p_dAbschnittStrecke = 0.0;
    p_pVerhalten = std::make_unique<Fahren>(weg);  // old instance is deleted automatically
}

void Fahrzeug::vNeueStrecke(Weg& weg, double startZeit) {
    p_dAbschnittStrecke = 0.0;
    p_pVerhalten = std::make_unique<Parken>(weg, startZeit);
}

void Fahrzeug::vSimulieren() {
    if (dZeit() + dEpsilon >= dGlobaleZeit) return;

    const double dt = dGlobaleZeit - dZeit();
    vSetZeit(dGlobaleZeit);

    if (!p_pVerhalten) {
        p_dGesamtZeit += dt;
        return;
    }

    // IMPORTANT: call dStrecke only once per step and cache it
    const double ds = p_pVerhalten->dStrecke(*this, dt);  // exactly once
    p_dGesamtZeit += dt;
    p_dGesamtStrecke += ds;
    p_dAbschnittStrecke += ds;
}
double Fahrzeug::dGeschwindigkeit() const {
    return p_dMaxGeschwindigkeit;
}

double Fahrzeug::dTanken(double /*dMenge*/) {
    return 0.0;
}

bool Fahrzeug::operator<(const Fahrzeug& rhs) const {
    return p_dGesamtStrecke < rhs.p_dGesamtStrecke;
}
void Fahrzeug::vZeichnen(const Weg&) const{
    // Base class does nothing
}
