// Streckenende.cpp
#include "Streckenende.h"
#include "Weg.h"
#include "Fahrzeug.h"
#include "Simulation.h"
#include <iostream>

void Streckenende::vBearbeiten() {
    Weg& w = getWeg();
    Fahrzeug& f = getFahrzeug();

    std::cout << "Streckenende: t=" << dGlobaleZeit
              << " Fahrzeug=" << f.sName()
              << " erreicht Ende von Weg=" << w.sName() << "\n";

    // For 5.5: remove vehicle from this road (later 5.8: move to Kreuzung)
    auto p = w.pAbgabe(f);
    (void)p; // unique_ptr gets destroyed here -> vehicle disappears from simulation
}
