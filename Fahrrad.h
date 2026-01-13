#pragma once
#include "Fahrzeug.h"

class Fahrrad : public Fahrzeug {
public:
    Fahrrad(const std::string& name, double vmax);
    virtual ~Fahrrad();

    virtual double dGeschwindigkeit() const override;
    virtual void vAusgeben(std::ostream& os) const override;
    void vZeichnen(const Weg& weg) const override;

};
