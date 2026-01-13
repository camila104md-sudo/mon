// Streckenende.h
#pragma once
#include "Fahrausnahme.h"

class Streckenende : public Fahrausnahme {
public:
    Streckenende(Fahrzeug& fzg, Weg& weg) : Fahrausnahme(fzg, weg) {}
    void vBearbeiten() override;
};
