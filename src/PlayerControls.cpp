#include "PlayerControls.h"

PlayerControls::PlayerControls()
{
    //ctor
}

PlayerControls::~PlayerControls()
{
    //dtor
}


void PlayerControls::player1placement(HexMap* hexmap, int x, int y){

    if(hexmap->isOffBoard(x,y) || hexmap->isInPlayerhalf(Player::player2, y)) {
        hexmap->setSelectedHex(nullptr);
        return;
    }

    Hex* hexClicked = hexmap->getHexPnt(x,y);

    // if nothing selected
    if(!hexmap->isHexSelected()){

        // if clicked on an empty space
        if(!hexClicked->hasPiece()){
            hexmap->setSelectedHex(nullptr);
        }
        // else if is moveable player unit
        else{
            hexmap->setSelectedHex(hexClicked->getCartesianX(), hexClicked->getCartesianY());
        }
    }
    // if something is already selected
    else{

        if(!hexClicked->hasPiece()){
            hexmap->movePeice(hexmap->getSelectedHex(), *hexClicked);
        }

        hexmap->setSelectedHex(nullptr);
    }
}
