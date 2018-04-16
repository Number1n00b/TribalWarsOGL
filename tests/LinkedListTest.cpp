#include <stdio.h>
#include <stdlib.h>

#include "../src/util/containers/LinkedList.h"

class te{
    public:
        te(){
            //Empty
        }

        int x;
};

int main(void){
    printf("============ Testing LinkedList ============\n");

    LinkedList<te>* list = new LinkedList<te>;

    delete list;


    return 0;
}
