#include "game.h"
#include "menu.h"

int main()
{
    int x = menu();

    if(x==1)
    {
        x=game();
        if(x==1) main();
    }
    return 0;
}
