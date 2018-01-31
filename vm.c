/**
 * File: vm.c
 * Author: William Cohen
 * Student no.: s3660470
 * Course: Advanced Programming Techniques
 * Year: 2017
 **/
#include "vm.h"

int main(int argc, char ** argv)
{
    MenuItem menu[MENU_SIZE];
    MenuFunction choice;

    VmSystem * system = malloc(sizeof(VmSystem)); 

    if (!systemInit(system)) {
        printf("Error - System could not be initialised.\n");
        return EXIT_FAILURE;
    }

    if (loadData(system, argv[1], argv[2])) {
        initMenu(menu);
        do {
            choice = getMenuChoice(menu);
            printf("\n");
            if (choice == NULL) continue;
            (*choice)(system);	
        } while (choice != menu[2].function && choice != menu[8].function);
    } else {
        abortProgram(system);	
    }
    printf("Goodbye. \n\n");
    return EXIT_SUCCESS;
}
