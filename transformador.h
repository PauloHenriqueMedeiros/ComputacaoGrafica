#ifndef TRANSFORMADOR_H
#define TRANSFORMADOR_H

#include "matrix.h"

class TransformadorCoordenadas {
public:
    TransformadorCoordenadas();

    void setWindow(double xmin, double ymin, double xmax, double ymax);
    void setViewport(int xmin, int ymin, int xmax, int ymax);

    Matrix getTransformacao() const;

private:
    void recalcularTransformacao();

    double w_xmin, w_ymin, w_xmax, w_ymax;
    int v_xmin, v_ymin, v_xmax, v_ymax;
    Matrix matriz_transformacao;
};

#endif // TRANSFORMADOR_H
