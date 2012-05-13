#include "PaintApp.hpp"

#include <iostream>

int main(int argc, char* argv[])
{
   try
   {
      PaintApp app;
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
}
