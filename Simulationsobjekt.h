#pragma once

#include <iostream>
#include <iomanip>
#include <string>

class Simulationsobjekt {
protected:
    static int p_iMaxID;
    const int  p_iID;
    std::string p_sName;
    double      p_dZeit;   // lokale Zeit (letzter Simulationszeitpunkt)
    void vSetZeit(double zeit) { p_dZeit = zeit; }

public:
    Simulationsobjekt();
    explicit Simulationsobjekt(const std::string& name);
    virtual ~Simulationsobjekt();

    Simulationsobjekt(const Simulationsobjekt&) = delete;
    Simulationsobjekt& operator=(const Simulationsobjekt& rhs);

    int iID() const { return p_iID; }
    const std::string& sName() const { return p_sName; }
    double dZeit() const { return p_dZeit; }

    // Vergleich nur über ID
    bool operator==(const Simulationsobjekt& rhs) const { return p_iID == rhs.p_iID; }

    // Simulation muss jede Unterklasse implementieren (abstrakt!)
    virtual void vSimulieren() = 0;

    // Ausgabe-Baustein: nur ID und Name
    virtual void vAusgeben(std::ostream& os) const;

    // Ausgabeoperator nur einmal hier (Polymorphie über vAusgeben)
    friend std::ostream& operator<<(std::ostream& os, const Simulationsobjekt& so) {
        so.vAusgeben(os);
        return os;
    }
};
