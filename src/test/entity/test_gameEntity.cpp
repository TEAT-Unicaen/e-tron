#include <iostream>
#include <cassert>
#include "../../entity/gameEntity.h"

static void testGameEntity() {
    // Création d'un objet GameEntity
    TCoords position = { 10, 20 };
    GameEntity entity("Player1", position, 5);

    // Vérification des attributs avec les getters ajoutés
    assert(entity.getName() == "Player1");
    assert(entity.getCoords().x == 10);
    assert(entity.getCoords().y == 20);
    assert(entity.getColor() == 5);

    std::cout << "Tous les tests de gameEntity sont passés avec succès !" << std::endl;
}

int main() {
    testGameEntity();
    return 0;
}