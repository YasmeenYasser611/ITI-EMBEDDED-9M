#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    int variable;
    variable = open("/sys/class/leds/input3::capslock/brightness", O_RDWR);
    if(argv[1]!= NULL)
    {
        dprintf(variable , "%s", argv[1]);
    }
    while(1);

}