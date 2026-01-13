#pragma once
#include "Fahrzeug.h"
//Subclass creation
class PKW : public Fahrzeug {
//PKW exclusive
protected:
    double p_dVerbrauch;   // l / 100 km
    double p_dTankvolumen; // l
    double p_dTankinhalt;  // l

public:
    // Tankvolumen mit Default 55 l, Tankinhalt = 1/2 Tankvolumen
    PKW(const std::string& name, double vmax,
        double verbrauch_l_pro_100km, double tankvolumen = 55.0);
    virtual ~PKW();

    virtual void vAusgeben(std::ostream& os) const override;
    virtual void vSimulieren() override;
    virtual double dTanken(double dMenge = std::numeric_limits<double>::infinity()) override;
    void vZeichnen(const Weg& weg) const override;
    double dTankinhalt() const { return p_dTankinhalt; }
};
