#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "math.h"
#include <iostream>

#include "GameLogic.h"


const unsigned int WIDTH = 400;
const unsigned int HEIGHT = 400;

const float SIZE = 60;
const float HEXHEIGHT = 2 * SIZE;
const float HEXWIDTH = HEXHEIGHT * (sqrt(3) / 2);

#endif // HEADER_H_INCLUDED
