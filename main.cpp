#include "window.h"


int main(int argc, char* argv[]) 
{
  // Initialize GTKmm
  Gtk::Main kit(argc, argv);

  // Create the window object
  MyWindow window;

  // Show the window
  window.show_all();

  // Start the main GTKmm event loop
  Gtk::Main::run(window);
  return 0;
}

// int main(int argc, char** argv)
// {

// }