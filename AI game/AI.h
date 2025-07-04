#pragma once
#include <fann.h>

void CopyBrain(struct fann* source, struct fann* target);

fann* TestEnemyInit();
void SaveTestEnemyBrain(fann* brain);