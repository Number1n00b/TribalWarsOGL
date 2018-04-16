#include <stdio.h>
#include <stdlib.h>

#include "../src/util/containers/LinkedList.h"

void printInt(int* val){
    printf("%d", *val);
}

int main(void){
    int ii;

    printf("============ Testing LinkedList ============\n");

    LinkedList<int>* list = new LinkedList<int>;

    for(ii = 0; ii < 10; ii++){
        list->AddElementToStart(new int(ii));
    }


    printf("Appended 10 integers to the start:\n");
    list->Print(&printInt);
    printf("List sizez: %d\n", list->Length());

    for(ii = 0; ii < 10; ii++){
        list->AddElementToEnd(new int(ii));
    }
    printf("\n============ ================== ============\n");
    printf("Appended 10 integers to the end:\n");
    list->Print(&printInt);
    printf("List size: %d\n", list->Length());


    printf("\n============ ================== ============\n");
    printf("Getting some elements:\n");
    int* element;
    for(ii = 3; ii < 7; ii++){
        element = list->GetElement(ii);
        printf("Element %d: '%d'\n", ii, *element);
        list->Print(&printInt);
        printf("List size: %d\n", list->Length());
        printf("\n");
    }


    printf("\n============ ================== ============\n");
    printf("Removing some elements:\n");
    for(ii = 3; ii < 7; ii++){
        list->Print(&printInt);
        element = list->RemoveElement(ii);
        printf("Element %d: '%d'\n", ii, *element);
        list->Print(&printInt);
        printf("List size: %d\n", list->Length());
        printf("\n");

        delete element;
    }

    printf("\n============ ================== ============\n");
    printf("Deleting some elements:\n");
    for(ii = 3; ii < 7; ii++){
        list->Print(&printInt);
        list->DeleteElement(ii);
        list->Print(&printInt);
        printf("List size: %d\n", list->Length());
        printf("\n");

        delete element;
    }

    delete list;

    return 0;
}
