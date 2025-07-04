#include "AI.h"
#include <fstream>
#include <string>
#include <vector>

fann* TestEnemyInit() {
    fann* TestEnemyGBrain = nullptr;
    TestEnemyGBrain = fann_create_standard(3, 3, 6, 4);
    fann_set_learning_rate(TestEnemyGBrain, 0.7f);

    std::ifstream fileCheck("C:/Users/Zinc/Documents/TestEnemy_brain.net");
    if (fileCheck.good()) {
        // Try to load the network from file
        TestEnemyGBrain = fann_create_from_file("C:/Users/Zinc/Documents/TestEnemy_brain.net");
    }

    return TestEnemyGBrain;
}

void SaveTestEnemyBrain(fann* brain) {
    if (brain) {
        fann_save(brain, "C:/Users/Zinc/Documents/TestEnemy_brain.net");
    }
}

void CopyBrain(fann* source, fann* target) {
    unsigned int totalConnections = fann_get_total_connections(source);
    std::vector<fann_connection> connections(totalConnections);
    fann_get_connection_array(source, connections.data());
    fann_set_weight_array(target, connections.data(), totalConnections);
}