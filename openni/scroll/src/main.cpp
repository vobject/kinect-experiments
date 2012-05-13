#include "ScrollApp.hpp"

#include <iostream>

int main(int argc, char* argv[])
{
   (void) argc;
   (void) argv;

   try
   {
      // TODO: Introduce real command line argument handling, e.g. with boost.

      ScrollApp app;
      app.Start();
//      app.Start((argc > 1) ? argv[1] : "");
   }
   catch (const char* e)
   {
      std::cout << "ERROR: " << e << std::endl;
   }
   catch (...)
   {
      std::cout << "Unknown exception thrown!" << std::endl;
   }
}
