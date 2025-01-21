#include <iostream>
#include <cassert>
#include "../../entity/gameEntity.h"
#include "../../entity/player.h"
#include "../../entity/wall.h"
#include "test_entity.h"

void testGameEntity() {
    // Cr�ation d'un objet GameEntity
    TCoords position = { 10, 20 };
    GameEntity entity("Player1", position, 5);

    // V�rification des attributs avec les getters ajout�s
    assert(entity.getName() == "Player1");
    assert(entity.getCoords().x == 10);
    assert(entity.getCoords().y == 20);
    assert(entity.getColor() == 5);

    std::cout << "Tous les tests de gameEntity sont pass�s avec succ�s !" << std::endl;
}

void testPlayer() {
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

void testWall() {
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

/*
int main() {
    testGameEntity();
	testPlayer();
	testWall();
    return 0;
}
*/
