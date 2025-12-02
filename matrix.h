#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <cmath>
#include <stdexcept>

class Matrix {
public:
    Matrix();
    Matrix(int rows, int cols);

    Matrix operator*(const Matrix& other) const;

    static Matrix criarMatrizTranslacao(double dx, double dy, double dz);
    static Matrix criarMatrizEscala(double sx, double sy, double sz);
    static Matrix criarMatrizRotacaoX(double anguloGraus);
    static Matrix criarMatrizRotacaoY(double anguloGraus);
    static Matrix criarMatrizRotacaoZ(double anguloGraus);

    // ATUALIZADO: Agora recebe os limites do volume de visualização
    static Matrix criarMatrizProjecaoOrtogonal(double left, double right, double bottom, double top, double near, double far);

    static Matrix criarMatrizProjecaoPerspectiva(double fov, double aspect, double near, double far);

    double& at(int row, int col);
    const double& at(int row, int col) const;
    int getRows() const { return rows; }
    int getCols() const { return cols; }

protected:
    int rows, cols;
    double data[4][4];
};

#endif // MATRIX_H
