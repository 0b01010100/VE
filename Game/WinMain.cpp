#include <MyGame.hpp>
#include <stdexcept>
int main()
{
	try
	{
		MyGame game = {};
		game.run();
	}
	catch (const std::exception&)
	{
		return -1 ;
	}
	return 0;
}