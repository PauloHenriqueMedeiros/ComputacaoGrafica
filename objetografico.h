#ifndef OBJETOGRAFICO_H
#define OBJETOGRAFICO_H

#include <QString>
#include <QVector>
#include "ponto.h"
#include "matrix.h"

class QPainter;

enum class TipoObjeto { PONTO, RETA, POLIGONO, OBJETO3D };

QString tipoParaString(TipoObjeto tipo);

class ObjetoGrafico {
public:
    ObjetoGrafico(QString nome, TipoObjeto tipo);
    virtual ~ObjetoGrafico() = default;

    virtual void desenhar(QPainter& painter) const = 0;
    virtual Ponto calcularCentro() const = 0;
    virtual ObjetoGrafico* clone() const = 0;

    void aplicarTransformacao(const Matrix& matriz);

    QString getNome() const;
    TipoObjeto getTipo() const;
    QVector<Ponto>& getPontos();
    void setVisivel(bool visivel);
    bool isVisivel() const;

    // Novo método para acessar a matriz de modelo acumulada
    Matrix getMatrizModel() const;

protected:
    QString nome;
    TipoObjeto tipo;
    QVector<Ponto> pontos;
    bool visivel;

    // Matriz que guarda a posição/rotação/escala do objeto no mundo
    Matrix matrizModel;
};

class PontoGrafico : public ObjetoGrafico {
public:
    PontoGrafico(QString nome, const Ponto& p);
    void desenhar(QPainter& painter) const override;
    Ponto calcularCentro() const override;
    ObjetoGrafico* clone() const override { return new PontoGrafico(*this); }
};

class RetaGrafica : public ObjetoGrafico {
public:
    RetaGrafica(QString nome, const Ponto& p1, const Ponto& p2);
    void desenhar(QPainter& painter) const override;
    Ponto calcularCentro() const override;
    ObjetoGrafico* clone() const override { return new RetaGrafica(*this); }
};

class PoligonoGrafico : public ObjetoGrafico {
public:
    PoligonoGrafico(QString nome, const QVector<Ponto>& vertices);
    void desenhar(QPainter& painter) const override;
    Ponto calcularCentro() const override;
    ObjetoGrafico* clone() const override { return new PoligonoGrafico(*this); }
};

class Objeto3D : public ObjetoGrafico {
public:
    Objeto3D(QString nome);
    void desenhar(QPainter& painter) const override;
    Ponto calcularCentro() const override;
    ObjetoGrafico* clone() const override { return new Objeto3D(*this); }
    bool carregarDeOBJ(const QString& caminhoArquivo);
    const QVector<QVector<int>>& getFaces() const;

private:
    QVector<QVector<int>> faces;
};


#endif // OBJETOGRAFICO_H
