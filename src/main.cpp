#include <Window/Window.hpp>
#include <Input/Input.h>
#include <Debug/Console.h>
int main() 
{
    var wnd = Window();
    var input = Input(); 

    Console::Println(Console::GREEN, "d", 200u, '3', "ddd");
    Console::Log(Console::TRACE, "This is an trace message.");
    Console::Log(Console::INFO, "This is an info message.");
    Console::Log(Console::DEBUG, "This is a debug message.");
    Console::Log(Console::WARNING, "This is a warning message.");
    Console::Log(Console::ERROR, "This is an error message.");
    Console::Log(Console::FATAL, "This is a fatal message.");

    
    while (!wnd.shouldClose())
    {
        wnd.pollEvents();
        if(input.isKey(KeyCode::_E, KeyState::Down)){
            break;
        }
    }

    return 0;
}
