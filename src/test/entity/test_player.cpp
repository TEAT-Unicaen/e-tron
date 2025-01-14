#include <iostream>
#include <cassert>
#include "../../entity/player.h"

static void testGameEntity() {
    // Cr�ation d'un objet GameEntity
    TCoords position = { 10, 20 };
	Player player("Player1", position, 5, 0);

    // V�rification des attributs avec les getters ajout�s
    assert(player.getName() == "Player1");
    assert(player.getCoords().x == 10);
    assert(player.getCoords().y == 20);
    assert(player.getColor() == 5);
	assert(player.getId() == 0);

    std::cout << "Tous les tests de player sont pass�s avec succ�s !" << std::endl;
}

int main() {
    testGameEntity();
    return 0;
}