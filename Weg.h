#pragma once

#include "Simulationsobjekt.h"
#include "Tempolimit.h"

#include <list>
#include <memory>

// forward declaration gegen zirkuläre Includes
class Fahrzeug;

class Weg : public Simulationsobjekt {
private:
    double p_dLaenge;
    std::list<std::unique_ptr<Fahrzeug>> p_pFahrzeuge;
    Tempolimit p_eTempolimit;
    mutable bool p_bGezeichnet = false;

public:
    Weg()=delete;
    Weg(const std::string& name, double laenge, Tempolimit limit = Tempolimit::Autobahn);
    virtual ~Weg();

    double dLaenge() const { return p_dLaenge; }

    // Tempolimit als double (50 / 100 / unbegrenzt)
    double getTempolimit() const;

    static void vKopf();

    virtual void vSimulieren() override;
    virtual void vAusgeben(std::ostream& os) const override;
    void vAnnahme(std::unique_ptr<Fahrzeug> pFzg);              // driving
    void vAnnahme(std::unique_ptr<Fahrzeug> pFzg, double startZeit); // parked
    std::unique_ptr<Fahrzeug> pAbgabe(const Fahrzeug& aFzg);
       virtual void vZeichnen() const;
       void vSetzeGezeichnet(bool gezeichnet = true) const;


};
