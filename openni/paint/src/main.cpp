#include "KinectApp.hpp"

#include <iostream>

int main(int argc, char* argv[])
{
   try
   {
      KinectApp app;
      app.Start((argc > 1) ? argv[1] : "");
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
