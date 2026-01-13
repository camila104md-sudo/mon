// Fahren.cpp
#include "Fahren.h"
#include "Fahrzeug.h"
#include "Weg.h"
#include <iostream>
#include "Streckenende.h"
#include "Simulation.h"

double Fahren::dStrecke(Fahrzeug& aFzg, double dZeitIntervall) {
    // distance you would like to travel in this step
    const double wunsch = aFzg.dGeschwindigkeit() * dZeitIntervall;

    // remaining distance on this road
    const double rest = p_rWeg.dLaenge() - aFzg.dAbschnittStrecke();

    // if already at the end: (in 5.4: only print message)
    if (rest <= dEpsilon) {
    	throw Streckenende(aFzg, p_rWeg);
    }

    // do not overshoot the end of the road
    return (wunsch < rest) ? wunsch : rest;
}
