#include "ponto.h"

Ponto::Ponto(double x, double y, double z) : Matrix(4, 1) {
    at(0, 0) = x;
    at(1, 0) = y;
    at(2, 0) = z;
    at(3, 0) = 1.0;
}

double Ponto::getX() const { return at(0, 0); }
double Ponto::getY() const { return at(1, 0); }
double Ponto::getZ() const { return at(2, 0); }

void Ponto::setX(double x) { at(0, 0) = x; }
void Ponto::setY(double y) { at(1, 0) = y; }
void Ponto::setZ(double z) { at(2, 0) = z; }
