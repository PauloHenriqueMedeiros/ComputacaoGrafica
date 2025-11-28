#ifndef CLIPPING_H
#define CLIPPING_H

#include "ponto.h"
#include "windowgrafica.h"

class Clipping {
public:
    Clipping();

    enum RegionCode {
        INSIDE = 0,       // 000000
        LEFT = 1,         // 000001
        RIGHT = 2,        // 000010
        BOTTOM = 4,       // 000100
        TOP = 8,          // 001000
        NEAR_PLANE = 16,  // 010000
        FAR_PLANE = 32    // 100000
    };

    bool clipReta(Ponto& p1, Ponto& p2, const LimitesWindow& limites) const;
    bool clipPonto(const Ponto& p, const LimitesWindow& limites) const;
    bool clipReta3D(Ponto& p1, Ponto& p2, const LimitesWindow& limites) const;
    int computeCode3D(const Ponto& p, const LimitesWindow& limites) const;

private:
    int computeCode(const Ponto& p, const LimitesWindow& limites) const;
};

#endif // CLIPPING_H
