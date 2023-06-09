#include <gtkmm.h>
#include <cairomm/context.h>
#include <vector>
#include <iostream>
#include "splash.h"

#define M_PI 3.14159265358979323846

typedef struct {
  int x1;
  int y1;
  int x2;
  int y2;
} Line;


typedef struct {
  int x;
  int y;
} cell;



class MyWindow : public Gtk::Window 
{
public:
  MyWindow() ;


protected:
    bool on_key_press_event(GdkEventKey* event) ;
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;

private:

    void  drawBoarders(const Cairo::RefPtr<Cairo::Context>& cr);
    void  drawHeadLine(const Cairo::RefPtr<Cairo::Context>& cr);
    void  drawPlayer(const Cairo::RefPtr<Cairo::Context>& cr);
    void  draw_line(const Cairo::RefPtr<Cairo::Context>& cr, double x1, double y1, double x2, double y2);

    void getLinePoints(int x1, int y1, int x2, int y2) ;
    bool checkBoundaries(int direction);
    void writeStep(const Cairo::RefPtr<Cairo::Context>& cr,cell _cell);
    cell currentCell();

  
  //double circle_x=600, circle_y=540;
  double circle_x=80, circle_y=80;
  int stepx=0,stepy=0,xfactor=0,yfactor=0;
  std::vector<Line> vline;
  std::vector<Line> hline;
  bool once=true,startGame=false,winner=false;
  splash *mysplash;


};