// Parken.cpp
#include "Parken.h"
#include "Fahrzeug.h"
#include "Simulation.h"   // for dGlobaleZeit
#include <iostream>
#include "Weg.h"
#include "Losfahren.h"

double Parken::dStrecke(Fahrzeug& aFzg, double /*dZeitIntervall*/) {
    // until start time: do not move
    if (dGlobaleZeit + dEpsilon < p_dStartzeit) {
        return 0.0;
    }
    throw Losfahren(aFzg, p_rWeg);


    // start time reached: (in 5.4: only print message)
    std::cout << "Losfahren: Fahrzeug " << aFzg.sName()
              << " startet auf Weg " << p_rWeg.sName()
              << " bei t=" << dGlobaleZeit << "\n";

    // In 5.4 we only output a message. In 5.5 this becomes an exception.
    return 0.0;
}
