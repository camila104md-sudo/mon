// Fahren.h
#pragma once
#include "Verhalten.h"

class Fahren : public Verhalten {
public:
    explicit Fahren(Weg& weg) : Verhalten(weg) {}
    double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) override;
};
