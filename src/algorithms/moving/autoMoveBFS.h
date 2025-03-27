#include "../AlgorithmUtils.h"
#include <memory>
#include <vector>

class AutoMoveBFS : public AlgorithmUtils {
public:
    AutoMoveBFS(MapManager* mapMan);

    int bfsArea(std::shared_ptr<Player> player, int depth);

    std::pair<std::pair<int, int>, int> decideMoveBFS(std::shared_ptr<Player> player, int depth);
};
