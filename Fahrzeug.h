#pragma once

#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
#include <memory>


#include "Simulationsobjekt.h"

// globale Variablen bleiben wie bei dir
extern double dGlobaleZeit;
extern const double dEpsilon;
class Verhalten;
class Weg;

class Fahrzeug : public Simulationsobjekt {
protected:
    double p_dMaxGeschwindigkeit;
    double p_dGesamtStrecke;
    double p_dGesamtZeit;
    double p_dAbschnittStrecke = 0.0;              // distance on current road
    std::unique_ptr<Verhalten> p_pVerhalten;       // choose unique_ptr (owned by Fahrzeug)


public:
    Fahrzeug();
    explicit Fahrzeug(const std::string& name);
    Fahrzeug(const std::string& name, double vmax);
    virtual ~Fahrzeug();

    Fahrzeug(const Fahrzeug&) = delete;
    Fahrzeug& operator=(const Fahrzeug& rhs);
    double dAbschnittStrecke() const { return p_dAbschnittStrecke; }
    static void vKopf();

    virtual void vAusgeben(std::ostream& os) const override;
    virtual void vSimulieren() override;

    virtual void vNeueStrecke(Weg& weg);
    virtual void vNeueStrecke(Weg& weg, double startZeit);

    virtual double dGeschwindigkeit() const;
    virtual double dTanken(double dMenge = std::numeric_limits<double>::infinity());
    virtual void vZeichnen(const Weg& weg) const;

    bool operator<(const Fahrzeug& rhs) const;
};
