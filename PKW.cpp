#include "PKW.h"
#include <algorithm>
#include <iomanip>
#include <cmath>
//ctor
PKW::PKW(const std::string& name, double vmax,
         double verbrauch_l_pro_100km, double tankvolumen)
    : Fahrzeug(name, vmax) {
	//keine negative Werte
    p_dVerbrauch   = verbrauch_l_pro_100km > 0.0 ? verbrauch_l_pro_100km : 0.0;
    p_dTankvolumen = tankvolumen > 0.0 ? tankvolumen : 0.0;
    p_dTankinhalt  = 0.5 * p_dTankvolumen;   // halbvoll
}
//dtor
PKW::~PKW() = default;

void PKW::vSimulieren() {
    if (dGlobaleZeit <= p_dZeit) return;
    double deltaT = dGlobaleZeit - p_dZeit;
    //Fahrzeug verhaltnis/kein Tank model
    if (p_dVerbrauch <= 0.0 || p_dTankvolumen <= 0.0) {
        Fahrzeug::vSimulieren();
        return;
    }

    if (p_dTankinhalt <= 0.0) {
        // Kein Sprit: Fahrzeug bleibt stehen
        p_dZeit = dGlobaleZeit;
        return;
    }
    //tank Model
    double pot_km   = p_dMaxGeschwindigkeit * deltaT;
    double l_pro_km = p_dVerbrauch / 100.0;
    double moegl_km = p_dTankinhalt / l_pro_km;
    double real_km  = std::min(pot_km, moegl_km);
    double verbraucht = real_km * l_pro_km;

    p_dGesamtStrecke += real_km;
    p_dGesamtZeit    += deltaT; // gesamte Simulationszeit
    p_dTankinhalt    -= verbraucht;
    if (p_dTankinhalt < 0.0) p_dTankinhalt = 0.0;
    p_dZeit = dGlobaleZeit;
}

double PKW::dTanken(double dMenge) {
    if (p_dTankvolumen <= 0.0) return 0.0;

    double fehlmenge = p_dTankvolumen - p_dTankinhalt;
    if (fehlmenge <= 0.0) return 0.0;

    double menge = dMenge;
    if (std::isinf(dMenge) || dMenge > fehlmenge) {
        menge = fehlmenge;          // volltanken
    }
    if (menge < 0.0) menge = 0.0;

    p_dTankinhalt += menge;
    return menge;
}

void PKW::vAusgeben(std::ostream& os) const {
    Fahrzeug::vAusgeben(os);
    os << "  Tank: " << std::fixed << std::setprecision(2) << p_dTankinhalt
       << " / "   << std::fixed << std::setprecision(2) << p_dTankvolumen
       << "  Verbr: " << std::fixed << std::setprecision(2) << p_dVerbrauch;
}
#include "PKW.h"
#include "Weg.h"
#include "SimuClient.h"

void PKW::vZeichnen(const Weg& weg) const
{
    const double relPos = (weg.dLaenge() > 0.0)
        ? (dAbschnittStrecke() / weg.dLaenge())
        : 0.0;

    bZeichnePKW(
        sName(),                 // namePKW
        weg.sName(),             // nameWeg
        relPos,                  // relative position 0..1
        dGeschwindigkeit(),       // current speed
        dTankinhalt()            // current tank content (PKW must have getter)
    );
}
