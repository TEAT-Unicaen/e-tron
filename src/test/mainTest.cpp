#include "./entity/test_entity.h"
#include "./map/test_map.h"

// R�alisation des tests

int main() {

	// Test des entit�s
    testGameEntity();
    testPlayer();
    testWall();

    // Test des structures de map
	testGrid();

    // Test des managers


    return 0;
}
