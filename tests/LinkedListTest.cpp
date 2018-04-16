#include <stdio.h>
#include <stdlib.h>

<<<<<<< HEAD
#include "../src/util/LinkedList.h"
=======
#include "../src/util/containers/LinkedList.h"
>>>>>>> tmp

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

<<<<<<< HEAD

=======
    delete list;
>>>>>>> tmp


    return 0;
}
