#include "windowgrafica.h"
#include <QPainter>
#include <algorithm>

WindowGrafica::WindowGrafica(QString nome, const Ponto& p1, const Ponto& p2)
    : ObjetoGrafico(nome, TipoObjeto::POLIGONO)
{
    double xmin = std::min(p1.getX(), p2.getX());
    double ymin = std::min(p1.getY(), p2.getY());
    double xmax = std::max(p1.getX(), p2.getX());
    double ymax = std::max(p1.getY(), p2.getY());

    pontos.append(Ponto(xmin, ymin));
    pontos.append(Ponto(xmax, ymin));
    pontos.append(Ponto(xmax, ymax));
    pontos.append(Ponto(xmin, ymax));

    zmin_limite = -150.0;
    zmax_limite = 150.0;
}

void WindowGrafica::desenhar(QPainter& painter) const {
    if (pontos.size() < 4) return;
    painter.save();
    QPen pen(Qt::cyan, 2, Qt::DashDotLine);
    painter.setPen(pen);
    for (int i = 0; i < pontos.size(); ++i) {
        const Ponto& p1 = pontos[i];
        const Ponto& p2 = pontos[(i + 1) % pontos.size()];
        painter.drawLine(p1.getX(), p1.getY(), p2.getX(), p2.getY());
    }
    painter.restore();
}

Ponto WindowGrafica::calcularCentro() const {
    if (pontos.isEmpty()) return Ponto(0, 0, 0);
    double somaX = 0, somaY = 0;
    for (const Ponto& p : pontos) {
        somaX += p.getX();
        somaY += p.getY();
    }
    return Ponto(somaX / pontos.size(), somaY / pontos.size());
}

LimitesWindow WindowGrafica::getLimites() const {
    if (pontos.isEmpty()) return {0, 0, 0, 0, 0, 0};
    double xmin = pontos[0].getX();
    double ymin = pontos[0].getY();
    double xmax = xmin;
    double ymax = ymin;
    for (const Ponto& p : pontos) {
        xmin = std::min(xmin, p.getX());
        xmax = std::max(xmax, p.getX());
        ymin = std::min(ymin, p.getY());
        ymax = std::max(ymax, p.getY());
    }
    return {xmin, ymin, xmax, ymax, zmin_limite, zmax_limite};
}

void WindowGrafica::atualizarLimites(double xmin, double ymin, double xmax, double ymax) {
    pontos.clear();
    pontos.append(Ponto(xmin, ymin));
    pontos.append(Ponto(xmax, ymin));
    pontos.append(Ponto(xmax, ymax));
    pontos.append(Ponto(xmin, ymax));
}

void WindowGrafica::setZMin(double z) {
    zmin_limite = z;
}

void WindowGrafica::setZMax(double z) {
    zmax_limite = z;
}
