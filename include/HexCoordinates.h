#ifndef HEXCOORDINATES_H
#define HEXCOORDINATES_H

#include <iostream>
#include <vector>

class HexCoordinates
{
    public:

        HexCoordinates(int _cartesianX, int _cartesianY);
        HexCoordinates(int _cubeX, int _cubeY, int _cubeZ);
        virtual ~HexCoordinates();

        bool isOrthogonal(HexCoordinates hex);
        bool isDiagonal(HexCoordinates hex);

        bool isOrthogonalRange(HexCoordinates hex, int range);
        bool isDiagonalRange(HexCoordinates hex, int range);


        std::vector<HexCoordinates> orthogonalSteps(HexCoordinates hex);
        std::vector<HexCoordinates> diagonalSteps(HexCoordinates hex);

        std::vector<HexCoordinates> getPossibleOrthogonalSteps(int range);
        std::vector<HexCoordinates> getPossibleDiagonalSteps(int range);

        bool isInRange(HexCoordinates hex, int range);
        int getDistance(HexCoordinates hex);

        int getCartesianX() const;
        int getCartesianY() const;

        int getCubeX();
        int getCubeY();
        int getCubeZ();

    protected:



        int cartesianX;
        int cartesianY;
        int cubeX;
        int cubeY;
        int cubeZ;

        void updateCubeCoordinates(void);
        void updateCartesianCoordinates(void);

        template <typename T> int sgn(T val);


     private:
};

#endif // HEXCOORDINATES_H
