// Losfahren.cpp
#include "Losfahren.h"
#include "Weg.h"
#include "Fahrzeug.h"
#include "Simulation.h"
#include <iostream>

void Losfahren::vBearbeiten() {
    Weg& w = getWeg();
    Fahrzeug& f = getFahrzeug();

    std::cout << "Losfahren: t=" << dGlobaleZeit
              << " Fahrzeug=" << f.sName()
              << " auf Weg=" << w.sName() << "\n";

    // Take the vehicle out of the road list
    auto p = w.pAbgabe(f);
    if (p) {
        // Reinsert as "driving" (push_back) -> behavior becomes Fahren
        w.vAnnahme(std::move(p));
    }
}
