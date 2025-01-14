#include <iostream>
#include <cassert>
#include "../../entity/wall.h"
#include "../../entity/player.h"

static void testGameEntity() {
    // Création d'un objet GameEntity
    TCoords position = { 10, 20 };
	Player* p = new Player("Player1", position, 5, 0);
	Wall wall("Wall1", position, 5, p);

    // Vérification des attributs avec les getters ajoutés
    assert(wall.getName() == "Player1");
    assert(wall.getCoords().x == 10);
    assert(wall.getCoords().y == 20);
    assert(wall.getColor() == 5);
    assert(wall.getOwner() == p);

    std::cout << "Tous les tests de wall sont passés avec succès !" << std::endl;
}

int main() {
    testGameEntity();
    return 0;
}