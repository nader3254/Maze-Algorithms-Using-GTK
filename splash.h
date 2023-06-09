#include <gtkmm.h>
#include <cairomm/context.h>
#include <vector>
#include <iostream>

#define LVL_EASY             0
#define LVL_Mid              1
#define LVL_HIGH             2
#define ALGORITHM_ALDOS      3
#define ALGORITHM_FUSION     4


typedef struct
{

  int level=0;
  int algorithm=0;

}gameparams;
class splash : public Gtk::Window
{
public:
  splash();
  void draw(const Cairo::RefPtr<Cairo::Context> &cr);
  void setEvent(int event);
  gameparams getParams();

private:
  void on_button_clicked(const std::string &buttonText);
  void btn(const Cairo::RefPtr<Cairo::Context> &cr,std::string text,int cursor,int x,int y, int width ,int heigth);
  void label(const Cairo::RefPtr<Cairo::Context> &cr,std::string text,int x,int y);
  std::vector<std::string> levels;
  std::vector<std::string> algorithms;
  int lvlIdx = 0, AlgIdx = 0,cursorIdx=1;

};