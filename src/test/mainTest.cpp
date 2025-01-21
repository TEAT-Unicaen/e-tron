#include "./entity/test_entity.h"
#include "./map/test_map.h"

// Réalisation des tests

int main() {

	// Test des entités
    testGameEntity();
    testPlayer();
    testWall();

    // Test des structures de map
	testGrid();

    // Test des managers


    return 0;
}
