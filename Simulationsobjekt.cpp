#include "Simulationsobjekt.h"

int Simulationsobjekt::p_iMaxID = 0;

Simulationsobjekt::Simulationsobjekt()
    : p_iID(++p_iMaxID), p_sName(""), p_dZeit(0.0) {}

Simulationsobjekt::Simulationsobjekt(const std::string& name)
    : p_iID(++p_iMaxID), p_sName(name), p_dZeit(0.0) {}

Simulationsobjekt::~Simulationsobjekt() = default;

// Wichtig: ID bleibt unverändert (const). Wir kopieren nur den Namen.
// (Zeit/ID sollen nicht “umgeschrieben” werden.)
Simulationsobjekt& Simulationsobjekt::operator=(const Simulationsobjekt& rhs) {
    if (this != &rhs) {
        p_sName = rhs.p_sName;
    }
    return *this;
}

void Simulationsobjekt::vAusgeben(std::ostream& os) const {
    os << std::resetiosflags(std::ios::right) << std::setiosflags(std::ios::left)
       << std::setw(4)  << p_iID
       << std::setw(16) << p_sName
       << std::resetiosflags(std::ios::left);
}
