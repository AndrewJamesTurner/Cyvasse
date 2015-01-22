#ifndef HEXCOORDINATES_H
#define HEXCOORDINATES_H

#include <iostream>

class HexCoordinates
{
    public:

        HexCoordinates(int _cartesianX, int _cartesianY);
        HexCoordinates(int _cubeX, int _cubeY, int _cubeZ);
        virtual ~HexCoordinates();

        bool isOrthogonal(HexCoordinates hex);
        bool isInRange(HexCoordinates hex, int range);

        int getCartesianX();
        int getCartesianY();
        int getCubeX();
        int getCubeY();
        int getCubeZ();

    private:

        int cartesianX;
        int cartesianY;
        int cubeX;
        int cubeY;
        int cubeZ;

        void updateCubeCoordinates(void);
        void updateCartesianCoordinates(void);


};

#endif // HEXCOORDINATES_H
