#include <iostream>
#include <cassert>
#include "../../entity/wall.h"
#include "../../entity/player.h"

static void testGameEntity() {
    // Cr�ation d'un objet GameEntity
    TCoords position = { 10, 20 };
	Player* p = new Player("Player1", position, 5, 0);
	Wall wall("Wall1", position, 5, p);

    // V�rification des attributs avec les getters ajout�s
    assert(wall.getName() == "Player1");
    assert(wall.getCoords().x == 10);
    assert(wall.getCoords().y == 20);
    assert(wall.getColor() == 5);
    assert(wall.getOwner() == p);

    std::cout << "Tous les tests de wall sont pass�s avec succ�s !" << std::endl;
}

int main() {
    testGameEntity();
    return 0;
}