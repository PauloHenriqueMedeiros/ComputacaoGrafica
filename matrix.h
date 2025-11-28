#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <cmath>

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
    static Matrix criarMatrizProjecaoOrtogonal();
    static Matrix criarMatrizProjecaoPerspectiva(double fov, double aspect, double near, double far);

    double& at(int row, int col);
    const double& at(int row, int col) const;
    int getRows() const { return rows; }
    int getCols() const { return cols; }

protected:
    int rows, cols;
    std::vector<std::vector<double>> data;
};

#endif // MATRIX_H
