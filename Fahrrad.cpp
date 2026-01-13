#include "Fahrrad.h"
#include <cmath>

Fahrrad::Fahrrad(const std::string& name, double vmax)
    : Fahrzeug(name, vmax) {
}

Fahrrad::~Fahrrad() = default;

double Fahrrad::dGeschwindigkeit() const {
    if (p_dMaxGeschwindigkeit <= 0.0) return 0.0;

    int    n_blocks = static_cast<int>(std::floor(p_dGesamtStrecke / 20.0)); //10% weniger pro 20km
    double factor   = std::pow(0.9, n_blocks);
    double v_eff    = p_dMaxGeschwindigkeit * factor;

    if (v_eff < 12.0) v_eff = 12.0;
    return v_eff;
}

void Fahrrad::vAusgeben(std::ostream& os) const {
    Fahrzeug::vAusgeben(os);
    os << "  (Fahrrad)";
}
#include "Fahrrad.h"
#include "Weg.h"
#include "SimuClient.h"

void Fahrrad::vZeichnen(const Weg& weg) const
{
    const double relPos = (weg.dLaenge() > 0.0)
        ? (dAbschnittStrecke() / weg.dLaenge())
        : 0.0;

    bZeichneFahrrad(
        sName(),                 // nameFahrrad
        weg.sName(),             // nameWeg
        relPos,
        dGeschwindigkeit()
    );
}
