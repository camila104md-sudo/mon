// Parken.h
#pragma once
#include "Verhalten.h"

class Parken : public Verhalten {
public:
    Parken(Weg& weg, double startZeit) : Verhalten(weg), p_dStartzeit(startZeit) {}
    double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) override;

private:
    double p_dStartzeit;
};
