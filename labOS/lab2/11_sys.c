//
//  11_sys.c
//  labOS
//
//  Created by Alyona Borushnova on 25.10.2023.
//

#include <stdlib.h>

//с помощью библиотечной функции system.

int main(int argc, char * argv[]) {
    system(argv[1]);
    exit(EXIT_SUCCESS);
}
