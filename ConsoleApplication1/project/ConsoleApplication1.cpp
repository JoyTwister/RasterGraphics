#include <iostream>
#include "string.h"
#include "console.h"

void test01()
{
    String test("top.ppm");
    std::cout << test.getLastChars(4) << std::endl;
}

int main()
{
    try
    {
        /*String name("inPPM.ppm");
        String nameewq("portokali.ppm");
        String command("vertical");
        Session test(name);
        test.addImage(nameewq);
        test.addCommand(command);
        test.save("_modified_time");*/

        Console console;
    }
    catch (const char* message)
    {
        std::cout << message << std::endl;
    }

    return 0;
}
