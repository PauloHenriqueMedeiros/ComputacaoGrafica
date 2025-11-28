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

    // Parâmetros da Window (coordenadas do mundo)
    double w_xmin, w_ymin, w_xmax, w_ymax;
    // Parâmetros da Viewport (coordenadas da tela)
    int v_xmin, v_ymin, v_xmax, v_ymax;

    // Matriz de transformação combinada
    Matrix matriz_transformacao;
};

#endif // TRANSFORMADOR_H
