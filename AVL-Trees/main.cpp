#include <conio.h>

#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

int main()
{
	int result = Catch::Session().run();

	_getch();

	return (result < 0xff ? result : 0xff);
}