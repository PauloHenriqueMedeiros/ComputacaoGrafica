#include "objetografico.h"
#include <QPainter>
#include <QFile>
#include <QTextStream>
#include <QRegularExpression>
#include <numeric>

QString tipoParaString(TipoObjeto tipo) {
    switch (tipo) {
    case TipoObjeto::PONTO: return "Ponto";
    case TipoObjeto::RETA: return "Reta";
    case TipoObjeto::POLIGONO: return "Polígono";
    case TipoObjeto::OBJETO3D: return "Objeto 3D";
    default: return "Desconhecido";
    }
}

ObjetoGrafico::ObjetoGrafico(QString nome, TipoObjeto tipo) : nome(nome), tipo(tipo), visivel(true) {}
QString ObjetoGrafico::getNome() const { return nome; }
TipoObjeto ObjetoGrafico::getTipo() const { return tipo; }
QVector<Ponto>& ObjetoGrafico::getPontos() { return pontos; }
void ObjetoGrafico::setVisivel(bool v) { visivel = v; }
bool ObjetoGrafico::isVisivel() const { return visivel; }

void ObjetoGrafico::aplicarTransformacao(const Matrix& matriz) {
    for (Ponto& p : pontos) {
        Matrix pontoComoMatriz = p;
        Matrix resultado = matriz * pontoComoMatriz;
        p.setX(resultado.at(0, 0));
        p.setY(resultado.at(1, 0));
        if (resultado.getRows() > 2) {
            p.setZ(resultado.at(2, 0));
        }
    }
}

PontoGrafico::PontoGrafico(QString nome, const Ponto& p) : ObjetoGrafico(nome, TipoObjeto::PONTO) {
    pontos.append(p);
}
void PontoGrafico::desenhar(QPainter& painter) const {
    if (pontos.isEmpty()) return;
    painter.save();
    painter.setPen(QPen(painter.pen().color(), 5));
    painter.drawPoint(pontos.first().getX(), pontos.first().getY());
    painter.restore();
}
Ponto PontoGrafico::calcularCentro() const {
    return pontos.isEmpty() ? Ponto(0,0,0) : pontos.first();
}

RetaGrafica::RetaGrafica(QString nome, const Ponto& p1, const Ponto& p2) : ObjetoGrafico(nome, TipoObjeto::RETA) {
    pontos.append(p1);
    pontos.append(p2);
}
void RetaGrafica::desenhar(QPainter& painter) const {
    if (pontos.size() < 2) return;
    painter.drawLine(pontos[0].getX(), pontos[0].getY(), pontos[1].getX(), pontos[1].getY());
}
Ponto RetaGrafica::calcularCentro() const {
    if (pontos.size() < 2) return Ponto(0,0,0);
    return Ponto(
        (pontos[0].getX() + pontos[1].getX()) / 2.0,
        (pontos[0].getY() + pontos[1].getY()) / 2.0,
        (pontos[0].getZ() + pontos[1].getZ()) / 2.0
        );
}

PoligonoGrafico::PoligonoGrafico(QString nome, const QVector<Ponto>& vertices) : ObjetoGrafico(nome, TipoObjeto::POLIGONO) {
    pontos = vertices;
}
void PoligonoGrafico::desenhar(QPainter& painter) const {
    if (pontos.size() < 2) return;
    for (int i = 0; i < pontos.size(); ++i) {
        const Ponto& p1 = pontos[i];
        const Ponto& p2 = pontos[(i + 1) % pontos.size()];
        painter.drawLine(p1.getX(), p1.getY(), p2.getX(), p2.getY());
    }
}
Ponto PoligonoGrafico::calcularCentro() const {
    if (pontos.isEmpty()) return Ponto(0,0,0);
    double somaX = 0, somaY = 0, somaZ = 0;
    for (const Ponto& p : pontos) {
        somaX += p.getX();
        somaY += p.getY();
        somaZ += p.getZ();
    }
    return Ponto(somaX / pontos.size(), somaY / pontos.size(), somaZ / pontos.size());
}

Objeto3D::Objeto3D(QString nome) : ObjetoGrafico(nome, TipoObjeto::OBJETO3D) {}

void Objeto3D::desenhar(QPainter& painter) const {
    painter.save();
    painter.setPen(QPen(Qt::green, 1));
    for (const auto& face : faces) {
        for (int i = 0; i < face.size(); ++i) {
            const Ponto& p1 = pontos[face[i]];
            const Ponto& p2 = pontos[face[(i + 1) % face.size()]];
            painter.drawLine(p1.getX(), p1.getY(), p2.getX(), p2.getY());
        }
    }
    painter.restore();
}

Ponto Objeto3D::calcularCentro() const {
    if (pontos.isEmpty()) return Ponto(0,0,0);
    double somaX = 0, somaY = 0, somaZ = 0;
    for (const Ponto& p : pontos) {
        somaX += p.getX();
        somaY += p.getY();
        somaZ += p.getZ();
    }
    return Ponto(somaX / pontos.size(), somaY / pontos.size(), somaZ / pontos.size());
}

bool Objeto3D::carregarDeOBJ(const QString& caminhoArquivo) {
    QFile arquivo(caminhoArquivo);
    if (!arquivo.open(QIODevice::ReadOnly | QIODevice::Text)) return false;

    pontos.clear();
    faces.clear();
    QTextStream in(&arquivo);
    while (!in.atEnd()) {
        QString linha = in.readLine().trimmed();
        QStringList partes = linha.split(QRegularExpression("\\s+"));
        if (partes.isEmpty()) continue;
        if (partes[0] == "v") {
            if (partes.size() < 4) continue;
            pontos.append(Ponto(partes[1].toDouble(), partes[2].toDouble(), partes[3].toDouble()));
        } else if (partes[0] == "f") {
            if (partes.size() < 4) continue;
            QVector<int> face;
            for (int i = 1; i < partes.size(); ++i) {
                QStringList indices = partes[i].split('/');
                face.append(indices[0].toInt() - 1);
            }
            faces.append(face);
        }
    }
    arquivo.close();
    return !pontos.isEmpty() && !faces.isEmpty();
}

const QVector<QVector<int>>& Objeto3D::getFaces() const {
    return faces;
}
