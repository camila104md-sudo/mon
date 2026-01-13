// Losfahren.h
#pragma once
#include "Fahrausnahme.h"

class Losfahren : public Fahrausnahme {
public:
    Losfahren(Fahrzeug& fzg, Weg& weg) : Fahrausnahme(fzg, weg) {}
    void vBearbeiten() override;
};
