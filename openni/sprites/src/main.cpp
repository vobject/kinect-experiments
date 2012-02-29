#include "KinectApp.h"

#include <iostream>

int main(int argc, char* argv[])
{
   try
   {
      // TODO: Introduce real command line argument handling, e.g. with boost.

      KinectApp app((argc > 1) ? argv[1] : "");
      app.PrintCommands();
      app.Start();
   }
   catch (const char* e)
   {
      std::cout << "ERROR: " << e << std::endl;
   }
   catch (...)
   {
      std::cout << "Unknown exception thrown!" << std::endl;
   }

   return 0;
}
