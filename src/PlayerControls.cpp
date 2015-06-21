#include "PlayerControls.h"

PlayerControls::PlayerControls()
{
    //ctor
}

PlayerControls::~PlayerControls()
{
    //dtor
}


void PlayerControls::playerPlacement(HexMap* hexmap, Player player, int x, int y){

    if(hexmap->isOffBoard(x,y) || !hexmap->isInPlayerhalf(player, y)) {
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


bool PlayerControls::playerMove(HexMap* hexmap, Player player, int x, int y){

    bool moved = false;

    hexmap->clearHighlightedHexes();


    if(hexmap->isOffBoard(x,y)) {
        hexmap->setSelectedHex(nullptr);
        return false;
    }

    Hex* hexClicked = hexmap->getHexPnt(x,y);

    // if nothing selected
    if(!hexmap->isHexSelected()){

        // if clicked on an empty space, a mountain or an enemy
        if(!hexClicked->hasPiece() || hexClicked->getPiece()->isMoutain() || hexClicked->getPiece()->getPlayer() != player){
            hexmap->setSelectedHex(nullptr);
        }
        // else if is moveable player unit
        else{
            hexmap->setSelectedHex(hexClicked->getCartesianX(), hexClicked->getCartesianY());
        }
    }
    // if something is already selected
    else{

        // if clicked currently selected
        if(hexmap->getSelectedHex().equals(*hexClicked)){
            showMovements(hexmap, *hexClicked);
        }
        else{

            moved = movePiece(hexmap, hexmap->getSelectedHex(), *hexClicked);
            hexmap->setSelectedHex(nullptr);
        }
    }

    return moved;
}


bool PlayerControls::movePiece(HexMap* hexmap, Hex sourceHex, Hex destinationHex){

    bool PlayerMoved;

    if(Movement::canMove(*hexmap, sourceHex, destinationHex)){
        hexmap->movePeice(sourceHex, destinationHex);
        PlayerMoved = true;
    }
    else{
        PlayerMoved = false;
    }

    return PlayerMoved;
}


void PlayerControls::showMovements(HexMap* hexmap, Hex hex){

    std::vector<Hex> movements = Movement::getValidMovements(*hexmap, hex);

    for(auto i = movements.begin(); i<movements.end(); ++i) {
          hexmap->addHighlightedHexes((*i));
    }
}
