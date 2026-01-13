#pragma once
#include <exception>

class Fahrzeug;
class Weg;

class Fahrausnahme : public std::exception {
public:
    Fahrausnahme(Fahrzeug& fzg, Weg& weg) : p_rFahrzeug(fzg), p_rWeg(weg) {}
    virtual ~Fahrausnahme() = default;

    Fahrausnahme(const Fahrausnahme&) = delete;
    Fahrausnahme& operator=(const Fahrausnahme&) = delete;

    Fahrzeug& getFahrzeug() const { return p_rFahrzeug; }
    Weg& getWeg() const { return p_rWeg; }

    // Each derived exception defines what to do
    virtual void vBearbeiten() = 0;

private:
    Fahrzeug& p_rFahrzeug;
    Weg& p_rWeg;
};
