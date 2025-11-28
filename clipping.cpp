#include "clipping.h"

Clipping::Clipping() {}

int Clipping::computeCode(const Ponto& p, const LimitesWindow& limites) const {
    int code = INSIDE;
    if (p.getX() < limites.xmin) code |= LEFT;
    else if (p.getX() > limites.xmax) code |= RIGHT;
    if (p.getY() < limites.ymin) code |= BOTTOM;
    else if (p.getY() > limites.ymax) code |= TOP;
    return code;
}

bool Clipping::clipReta(Ponto& p1, Ponto& p2, const LimitesWindow& limites) const {
    return true;
}

bool Clipping::clipPonto(const Ponto& p, const LimitesWindow& limites) const {
    return computeCode(p, limites) == INSIDE;
}

int Clipping::computeCode3D(const Ponto& p, const LimitesWindow& limites) const {
    int code = INSIDE;
    if (p.getX() < limites.xmin) code |= LEFT;
    else if (p.getX() > limites.xmax) code |= RIGHT;
    if (p.getY() < limites.ymin) code |= BOTTOM;
    else if (p.getY() > limites.ymax) code |= TOP;
    if (p.getZ() < limites.zmin) code |= NEAR_PLANE;
    else if (p.getZ() > limites.zmax) code |= FAR_PLANE;
    return code;
}

bool Clipping::clipReta3D(Ponto& p1, Ponto& p2, const LimitesWindow& limites) const {
    int code1 = computeCode3D(p1, limites);
    int code2 = computeCode3D(p2, limites);
    bool aceito = false;

    while (true) {
        if ((code1 == 0) && (code2 == 0)) {
            aceito = true;
            break;
        } else if (code1 & code2) {
            break;
        } else {
            int code_out = (code1 != 0) ? code1 : code2;
            double x = 0, y = 0, z = 0;

            if (code_out & TOP) {
                x = p1.getX() + (p2.getX() - p1.getX()) * (limites.ymax - p1.getY()) / (p2.getY() - p1.getY());
                y = limites.ymax;
                z = p1.getZ() + (p2.getZ() - p1.getZ()) * (limites.ymax - p1.getY()) / (p2.getY() - p1.getY());
            } else if (code_out & BOTTOM) {
                x = p1.getX() + (p2.getX() - p1.getX()) * (limites.ymin - p1.getY()) / (p2.getY() - p1.getY());
                y = limites.ymin;
                z = p1.getZ() + (p2.getZ() - p1.getZ()) * (limites.ymin - p1.getY()) / (p2.getY() - p1.getY());
            } else if (code_out & RIGHT) {
                y = p1.getY() + (p2.getY() - p1.getY()) * (limites.xmax - p1.getX()) / (p2.getX() - p1.getX());
                x = limites.xmax;
                z = p1.getZ() + (p2.getZ() - p1.getZ()) * (limites.xmax - p1.getX()) / (p2.getX() - p1.getX());
            } else if (code_out & LEFT) {
                y = p1.getY() + (p2.getY() - p1.getY()) * (limites.xmin - p1.getX()) / (p2.getX() - p1.getX());
                x = limites.xmin;
                z = p1.getZ() + (p2.getZ() - p1.getZ()) * (limites.xmin - p1.getX()) / (p2.getX() - p1.getX());
            } else if (code_out & FAR_PLANE) {
                z = limites.zmax;
                x = p1.getX() + (p2.getX() - p1.getX()) * (limites.zmax - p1.getZ()) / (p2.getZ() - p1.getZ());
                y = p1.getY() + (p2.getY() - p1.getY()) * (limites.zmax - p1.getZ()) / (p2.getZ() - p1.getZ());
            } else if (code_out & NEAR_PLANE) {
                z = limites.zmin;
                x = p1.getX() + (p2.getX() - p1.getX()) * (limites.zmin - p1.getZ()) / (p2.getZ() - p1.getZ());
                y = p1.getY() + (p2.getY() - p1.getY()) * (limites.zmin - p1.getZ()) / (p2.getZ() - p1.getZ());
            }

            if (code_out == code1) {
                p1.setX(x); p1.setY(y); p1.setZ(z);
                code1 = computeCode3D(p1, limites);
            } else {
                p2.setX(x); p2.setY(y); p2.setZ(z);
                code2 = computeCode3D(p2, limites);
            }
        }
    }
    return aceito;
}
