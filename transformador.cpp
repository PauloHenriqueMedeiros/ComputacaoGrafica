#include "transformador.h"

TransformadorCoordenadas::TransformadorCoordenadas()
    : w_xmin(0), w_ymin(0), w_xmax(100), w_ymax(100),
    v_xmin(0), v_ymin(0), v_xmax(100), v_ymax(100)
{
    recalcularTransformacao();
}

void TransformadorCoordenadas::setWindow(double xmin, double ymin, double xmax, double ymax) {
    w_xmin = xmin;
    w_ymin = ymin;
    w_xmax = xmax;
    w_ymax = ymax;
    recalcularTransformacao();
}

void TransformadorCoordenadas::setViewport(int xmin, int ymin, int xmax, int ymax) {
    v_xmin = xmin;
    v_ymin = ymin;
    v_xmax = xmax;
    v_ymax = ymax;
    recalcularTransformacao();
}

Matrix TransformadorCoordenadas::getTransformacao() const {
    return matriz_transformacao;
}

void TransformadorCoordenadas::recalcularTransformacao() {
    Matrix T1 = Matrix::criarMatrizTranslacao(-w_xmin, -w_ymin, 0.0);

    double sx = static_cast<double>(v_xmax - v_xmin) / (w_xmax - w_xmin);
    double sy = static_cast<double>(v_ymax - v_ymin) / (w_ymax - w_ymin);

    Matrix S = Matrix::criarMatrizEscala(sx, sy, 1.0);
    Matrix T2 = Matrix::criarMatrizTranslacao(v_xmin, v_ymin, 0.0);

    matriz_transformacao = T2 * S * T1;
}
