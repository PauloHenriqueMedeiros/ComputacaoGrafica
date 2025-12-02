#include "matrix.h"
#include "ponto.h" // <--- CORREÇÃO: Incluímos aqui para ter acesso aos métodos de Ponto
#include <cstring>
#include <cmath> // Garantir que abs e outras funcoes matematicas existam

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Matrix::Matrix() : rows(4), cols(4) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            data[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }
}

Matrix::Matrix(int r, int c) : rows(r), cols(c) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            data[i][j] = 0.0;
        }
    }
}

Matrix Matrix::operator*(const Matrix& other) const {
    if (this->cols != other.rows) {
        throw std::runtime_error("Erro de multiplicação: Dimensões de matriz incompatíveis.");
    }
    Matrix result(this->rows, other.cols);
    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j < other.cols; ++j) {
            double sum = 0.0;
            for (int k = 0; k < this->cols; ++k) {
                sum += this->data[i][k] * other.data[k][j];
            }
            result.at(i, j) = sum;
        }
    }
    return result;
}

double& Matrix::at(int row, int col) { return data[row][col]; }
const double& Matrix::at(int row, int col) const { return data[row][col]; }

Matrix Matrix::criarMatrizTranslacao(double dx, double dy, double dz) {
    Matrix t;
    t.at(0, 3) = dx;
    t.at(1, 3) = dy;
    t.at(2, 3) = dz;
    return t;
}

Matrix Matrix::criarMatrizEscala(double sx, double sy, double sz) {
    Matrix s;
    s.at(0, 0) = sx;
    s.at(1, 1) = sy;
    s.at(2, 2) = sz;
    return s;
}

Matrix Matrix::criarMatrizRotacaoX(double anguloGraus) {
    Matrix r;
    double anguloRad = anguloGraus * M_PI / 180.0;
    double cosA = cos(anguloRad);
    double sinA = sin(anguloRad);
    r.at(1, 1) = cosA;
    r.at(1, 2) = -sinA;
    r.at(2, 1) = sinA;
    r.at(2, 2) = cosA;
    return r;
}

Matrix Matrix::criarMatrizRotacaoY(double anguloGraus) {
    Matrix r;
    double anguloRad = anguloGraus * M_PI / 180.0;
    double cosA = cos(anguloRad);
    double sinA = sin(anguloRad);
    r.at(0, 0) = cosA;
    r.at(0, 2) = sinA;
    r.at(2, 0) = -sinA;
    r.at(2, 2) = cosA;
    return r;
}

Matrix Matrix::criarMatrizRotacaoZ(double anguloGraus) {
    Matrix r;
    double anguloRad = anguloGraus * M_PI / 180.0;
    double cosA = cos(anguloRad);
    double sinA = sin(anguloRad);
    r.at(0, 0) = cosA;
    r.at(0, 1) = -sinA;
    r.at(1, 0) = sinA;
    r.at(1, 1) = cosA;
    return r;
}

Matrix Matrix::criarMatrizProjecaoOrtogonal(double left, double right, double bottom, double top, double near, double far) {
    Matrix p;
    p.at(0, 0) = 2.0 / (right - left);
    p.at(1, 1) = 2.0 / (top - bottom);
    p.at(2, 2) = -2.0 / (far - near);
    p.at(0, 3) = -(right + left) / (right - left);
    p.at(1, 3) = -(top + bottom) / (top - bottom);
    p.at(2, 3) = -(far + near) / (far - near);
    return p;
}

Matrix Matrix::criarMatrizProjecaoPerspectiva(double fov, double aspect, double near, double far) {
    Matrix p(4, 4);
    double fovRad = (fov / 2.0) * M_PI / 180.0;
    double f = 1.0 / tan(fovRad);

    p.at(0, 0) = f / aspect;
    p.at(1, 1) = f;
    p.at(2, 2) = (far + near) / (near - far);
    p.at(2, 3) = (2 * far * near) / (near - far);
    p.at(3, 2) = -1.0;
    p.at(3, 3) = 0.0;
    return p;
}

Matrix Matrix::criarMatrizSombra(const Ponto& luz, double yPlano) {
    Matrix m(4, 4);

    double Lx = luz.getX();
    double Ly = luz.getY();
    double Lz = luz.getZ();

    if (std::abs(Ly) < 0.001) Ly = 0.001;

    m.at(0, 0) = Ly;
    m.at(0, 1) = -Lx;
    m.at(0, 2) = 0;
    m.at(0, 3) = 0;

    m.at(1, 0) = 0;
    m.at(1, 1) = 0;
    m.at(1, 2) = 0;
    m.at(1, 3) = 0;

    m.at(2, 0) = 0;
    m.at(2, 1) = -Lz;
    m.at(2, 2) = Ly;
    m.at(2, 3) = 0;

    m.at(3, 0) = 0;
    m.at(3, 1) = -1;
    m.at(3, 2) = 0;
    m.at(3, 3) = Ly;

    Matrix T_down = Matrix::criarMatrizTranslacao(0, -yPlano, 0);
    Matrix T_up = Matrix::criarMatrizTranslacao(0, yPlano, 0);

    return T_up * m * T_down;
}
