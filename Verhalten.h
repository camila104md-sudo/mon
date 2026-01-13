#pragma once

class Fahrzeug;
class Weg;

class Verhalten {
public:
    explicit Verhalten(Weg& weg) : p_rWeg(weg) {}
    virtual ~Verhalten() = default;

    Verhalten(const Verhalten&) = delete;
    Verhalten& operator=(const Verhalten&) = delete;

    // How far can the vehicle travel in dZeitIntervall without exceeding the road end?
    virtual double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) = 0;

    Weg& getWeg() const { return p_rWeg; }

protected:
    Weg& p_rWeg; // behavior depends on the road
};
