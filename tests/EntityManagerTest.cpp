#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>

#include "../src/model/EntityManager.h"

int main(void){
    int ii;

    printf("============ Testing EntityManager ============\n");

    EntityManager* manager = new EntityManager();

    printf("Adding some Entities:\n");
    for(ii = 0; ii < 10; ii++){
        std::stringstream n;
        n << "name" << ii;
        new Entity(manager, n.str(), ii, 10 - ii);
        manager->PrintAllEntities();
    }

    delete manager;

    return 0;
}
