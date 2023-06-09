#include "window.h"

MyWindow::MyWindow()
{
    // Set the window's title
    set_title(" Maze game");

    // Set the window's size
    set_default_size(800, 600);

    // Set the window's background color to yellow
    Gdk::RGBA yellow_color("#FFFFFF");
    override_background_color(yellow_color);

    // Connect key press event signal
    signal_key_press_event().connect(sigc::mem_fun(*this, &MyWindow::on_key_press_event));
    mysplash = new splash();
}
void MyWindow::writeStep(const Cairo::RefPtr<Cairo::Context> &cr, cell _cell)
{

    int width = 0, height = 0, cx = 0, cy = 0;
    cr->set_source_rgb(1.0, 1.0, 1.0); // Rectangle background color
    // cr->rectangle(((_cell.x * stepx) + 60) + 10, ((_cell.y * stepy) + 60) + 10, stepx - 20, stepy - 20);
    cr->rectangle(((_cell.x * stepx) + 60), ((_cell.y * stepy) + 60), stepx, stepy);
    cr->fill();

    cx = (_cell.x * stepx) + 60;
    cy = (_cell.y * stepy) + 60;

    draw_line(cr, 0 * stepx * xfactor + 60, 1 * stepy * yfactor + 60, 2 * stepx * xfactor + 60, 1 * stepy * yfactor + 60);
    draw_line(cr, 3 * stepx * xfactor + 60, 0 * stepy * yfactor + 60, 3 * stepx * xfactor + 60, 1 * stepy * yfactor + 60);
    draw_line(cr, 3 * stepx * xfactor + 60, 1 * stepy * yfactor + 60, 4 * stepx * xfactor + 60, 1 * stepy * yfactor + 60);
    draw_line(cr, 0 * stepx * xfactor + 60, 3 * stepy * yfactor + 60, 1 * stepx * xfactor + 60, 3 * stepy * yfactor + 60);

    draw_line(cr, 2 * stepx * xfactor + 60, 5 * stepy * yfactor + 60, 2 * stepx * xfactor + 60, 6 * stepy * yfactor + 60);
    draw_line(cr, 2 * stepx * xfactor + 60, 5 * stepy * yfactor + 60, 4 * stepx * xfactor + 60, 5 * stepy * yfactor + 60);
    draw_line(cr, 3 * stepx * xfactor + 60, 5 * stepy * yfactor + 60, 3 * stepx * xfactor + 60, 7 * stepy * yfactor + 60);
    draw_line(cr, 3 * stepx * xfactor + 60, 6 * stepy * yfactor + 60, 4 * stepx * xfactor + 60, 6 * stepy * yfactor + 60);

    draw_line(cr, 4 * stepx * xfactor + 60, 6 * stepy * yfactor + 60, 4 * stepx * xfactor + 60, 10 * stepy * yfactor + 60);
    draw_line(cr, 1 * stepx * xfactor + 60, 7 * stepy * yfactor + 60, 1 * stepx * xfactor + 60, 10 * stepy * yfactor + 60);
    draw_line(cr, 1 * stepx * xfactor + 60, 8 * stepy * yfactor + 60, 2 * stepx * xfactor + 60, 8 * stepy * yfactor + 60);

    // std::cout << "x:" << cx << " y:" << cy << " cellx:" << _cell.x << " celly:" << _cell.y << " xstep:" << stepx << " ystep:" << stepy << std::endl;
}
cell MyWindow::currentCell()
{
    cell tmp;
    tmp.x = ((circle_x - 60) / stepx);
    tmp.y = ((circle_y - 60) / stepy);
    return tmp;
}

bool MyWindow::on_draw(const Cairo::RefPtr<Cairo::Context> &cr)
{
    // Call the base class implementation
    Gtk::Window::on_draw(cr);
strt:
    if (startGame == true)
    {
        // playing
        // ask algorithm to move

        if (selectedAlgorithm == ALGORITHM_ALDOS)
        {

            if (aldosAlgorithm->CheckWin() == false)
            {
                drawHeadLine(cr);
                drawBoarders(cr);
                if (aldosAlgorithm->canImove(currentCell()) == true)
                {
                }
                else
                {
                    circle_x = prevx;
                    circle_y = prevy;
                }
                for (auto i : aldosAlgorithm->getVisited())
                {
                    writeStep(cr, i);
                }
                drawPlayer(cr);
            }
            else
            {
                circle_x=61; circle_y=61;
                startGame = false;
                goto strt;
            }
        }
        if (selectedAlgorithm == ALGORITHM_FUSION)
        {
            std::cout<<"inside fusion\n";
            if (fusionAlgorithm->CheckWin() == false)
            {
                drawHeadLine(cr);
                drawBoarders(cr);
                if (fusionAlgorithm->canImove(currentCell()) == true)
                {
                    std::cout<<"inside i can move \n";
                }
                else
                {
                    cell tmppp = fusionAlgorithm->getRandom();
                    circle_x = tmppp.x;
                    circle_y = tmppp.y ;
                }
                for (auto i : fusionAlgorithm->getVisited())
                {
                    writeStep(cr, i);
                }
                drawPlayer(cr);
            }
            else
            {
                circle_x=61; circle_y=61;
                startGame = false;
                goto strt;
            }
        }
    }
    else if (winner == true)
    {
        // winner
        // Set the text font and size
        Pango::FontDescription font_desc("Arial 50");
        cr->select_font_face(font_desc.get_family(), Cairo::FONT_SLANT_NORMAL, Cairo::FONT_WEIGHT_NORMAL);
        cr->set_font_size(font_desc.get_size() / Pango::SCALE);

        // Set the text color
        cr->set_source_rgb(0.0, 0.0, 0.0); // Black color
        // Draw the text "Maze Game"
        cr->move_to(280, 280); // Position of the text
        cr->show_text("You Won");

        Pango::FontDescription font_desc2("Arial 25");
        cr->select_font_face(font_desc2.get_family(), Cairo::FONT_SLANT_NORMAL, Cairo::FONT_WEIGHT_NORMAL);
        cr->set_font_size(font_desc2.get_size() / Pango::SCALE);

        // Set the text color
        cr->set_source_rgb(0.0, 1.0, 0.0); // Black color
        // Draw the text "Maze Game"
        cr->move_to(250, 550); // Position of the text
        cr->show_text("Press Enter to start the game");
    }
    else
    {
        // intro
        mysplash->draw(cr);
    }

    return true;
}
void MyWindow::drawPlayer(const Cairo::RefPtr<Cairo::Context> &cr)
{
    cr->set_source_rgb(1.0, 0.0, 0.0); // Red color

    // Draw the circle
    cr->arc(circle_x, circle_y, 8, 0, 2 * M_PI);
    cr->fill();
}

void MyWindow::drawHeadLine(const Cairo::RefPtr<Cairo::Context> &cr)
{

    // Set the text font and size
    Pango::FontDescription font_desc("Arial 30");
    cr->select_font_face(font_desc.get_family(), Cairo::FONT_SLANT_NORMAL, Cairo::FONT_WEIGHT_NORMAL);
    cr->set_font_size(font_desc.get_size() / Pango::SCALE);

    // Set the text color
    cr->set_source_rgb(0.0, 0.0, 0.0); // Black color
    // Draw the text "Maze Game"
    cr->move_to(350, 30); // Position of the text
    cr->show_text("Maze Game");

    Pango::FontDescription font_desc2("Arial 20");
    cr->select_font_face(font_desc2.get_family(), Cairo::FONT_SLANT_NORMAL, Cairo::FONT_WEIGHT_NORMAL);
    cr->set_font_size(font_desc2.get_size() / Pango::SCALE);

    // // Set the text color
    // cr->set_source_rgb(0.0, 0.0, 1.0); // Black color
    // // Draw the text "Maze Game"
    // cr->move_to(580, 580); // Position of the text
    // cr->show_text("Start");

    // // Set the text color
    // cr->set_source_rgb(1.0, 0.0, 1.0); // Black color
    // // Draw the text "Maze Game"
    // cr->move_to(60, 400); // Position of the text
    // cr->show_text("end");
}
void MyWindow::getLinePoints(int x1, int y1, int x2, int y2)
{

    if (x1 == x2)
    {
        // vertical line
        vline.push_back({x1, y1, x2, y2});
    }
    else if (y1 == y2)
    {
        // horizontal line
        hline.push_back({x1, y1, x2, y2});
    }
}
void MyWindow::draw_line(const Cairo::RefPtr<Cairo::Context> &cr, double x1, double y1, double x2, double y2)
{
    // Set the line color and thickness
    cr->set_source_rgb(0.0, 0.0, 0.0); // Black color
    if (once == true)
    {
        getLinePoints(x1, y1, x2, y2);
    }
    cr->set_line_width(8.0);
    cr->move_to(x1, y1);
    cr->line_to(x2, y2);
    cr->stroke();
}
void MyWindow::drawBoarders(const Cairo::RefPtr<Cairo::Context> &cr)
{
    // Draw the maze border
    draw_line(cr, 50, 50, 750, 50);
    draw_line(cr, 50, 50, 50, 550);
    draw_line(cr, 750, 50, 750, 550);
    draw_line(cr, 50, 550, 750, 550);
    if (startGame == true)
    {
        cr->set_source_rgb(0.0, 0.0, 0.0);
        cr->rectangle(60, 60, 680, 480);
        cr->fill();
    }

    if (once == true)
    {

        draw_line(cr, 0 * stepx * xfactor + 60, 1 * stepy * yfactor + 60, 2 * stepx * xfactor + 60, 1 * stepy * yfactor + 60);
        draw_line(cr, 3 * stepx * xfactor + 60, 0 * stepy * yfactor + 60, 3 * stepx * xfactor + 60, 1 * stepy * yfactor + 60);
        draw_line(cr, 3 * stepx * xfactor + 60, 1 * stepy * yfactor + 60, 4 * stepx * xfactor + 60, 1 * stepy * yfactor + 60);
        draw_line(cr, 0 * stepx * xfactor + 60, 3 * stepy * yfactor + 60, 1 * stepx * xfactor + 60, 3 * stepy * yfactor + 60);

        draw_line(cr, 2 * stepx * xfactor + 60, 5 * stepy * yfactor + 60, 2 * stepx * xfactor + 60, 6 * stepy * yfactor + 60);
        draw_line(cr, 2 * stepx * xfactor + 60, 5 * stepy * yfactor + 60, 4 * stepx * xfactor + 60, 5 * stepy * yfactor + 60);
        draw_line(cr, 3 * stepx * xfactor + 60, 5 * stepy * yfactor + 60, 3 * stepx * xfactor + 60, 7 * stepy * yfactor + 60);
        draw_line(cr, 3 * stepx * xfactor + 60, 6 * stepy * yfactor + 60, 4 * stepx * xfactor + 60, 6 * stepy * yfactor + 60);

        draw_line(cr, 4 * stepx * xfactor + 60, 6 * stepy * yfactor + 60, 4 * stepx * xfactor + 60, 10 * stepy * yfactor + 60);
        draw_line(cr, 1 * stepx * xfactor + 60, 7 * stepy * yfactor + 60, 1 * stepx * xfactor + 60, 10 * stepy * yfactor + 60);
        draw_line(cr, 1 * stepx * xfactor + 60, 8 * stepy * yfactor + 60, 2 * stepx * xfactor + 60, 8 * stepy * yfactor + 60);
    }
    // // Draw the middle links
    // draw_line(cr, 50, 200, 300, 200);
    // draw_line(cr, 300, 50, 300, 200);
    // draw_line(cr, 300, 350, 300, 550);
    // draw_line(cr, 450, 200, 750, 200);
    // draw_line(cr, 450, 350, 450, 550);
    // // Draw additional links
    // draw_line(cr, 100, 200, 100, 350);
    // draw_line(cr, 100, 350, 200, 350);
    // draw_line(cr, 200, 100, 200, 200);
    // draw_line(cr, 200, 350, 200, 450);
    // draw_line(cr, 350, 100, 350, 300);
    // draw_line(cr, 350, 450, 350, 550);
    // draw_line(cr, 400, 100, 400, 300);
    // draw_line(cr, 400, 450, 400, 550);
    // draw_line(cr, 500, 100, 500, 300);
    // draw_line(cr, 500, 450, 500, 550);
    // draw_line(cr, 600, 200, 600, 350);
    // draw_line(cr, 600, 350, 700, 350);
    // // Draw additional links - Path from (600, 540) to (50, 50)
    // draw_line(cr, 650, 540, 650, 500);
    // draw_line(cr, 550, 500, 500, 500);
    // draw_line(cr, 500, 450, 500, 400);
    // draw_line(cr, 550, 400, 600, 400);
    // draw_line(cr, 650, 350, 650, 300);
    // draw_line(cr, 550, 300, 500, 300);
    // draw_line(cr, 500, 250, 500, 200);
    // draw_line(cr, 550, 200, 600, 200);
    // draw_line(cr, 600, 150, 600, 100);
    // draw_line(cr, 550, 100, 500, 100);
    // draw_line(cr, 450, 100, 400, 100);
    // draw_line(cr, 400, 150, 400, 200);
    // draw_line(cr, 350, 200, 300, 200);
    // draw_line(cr, 250, 200, 200, 200);
    // draw_line(cr, 200, 200, 150, 200);
    // draw_line(cr, 150, 150, 150, 100);
    // draw_line(cr, 150, 50, 100, 50);
    // draw_line(cr, 100, 100, 100, 150);
    // draw_line(cr, 100, 200, 100, 250);
    // draw_line(cr, 50, 250, 50, 300);
    // draw_line(cr, 100, 300, 100, 350);
    // draw_line(cr, 100, 400, 100, 450);
    // draw_line(cr, 50, 450, 50, 500);
    // draw_line(cr, 100, 500, 150, 500);
    // draw_line(cr, 200, 500, 250, 500);
    // draw_line(cr, 300, 500, 350, 500);
    // draw_line(cr, 400, 500, 450, 500);
    // draw_line(cr, 500, 500, 550, 500);
    // draw_line(cr, 600, 500, 600, 450);
    // draw_line(cr, 600, 400, 600, 350);
    // draw_line(cr, 650, 350, 700, 350);
    // draw_line(cr, 700, 300, 700, 250);
    // draw_line(cr, 700, 200, 700, 150);
    // draw_line(cr, 700, 100, 700, 50);
    // draw_line(cr, 650, 50, 600, 50);
    // draw_line(cr, 550, 50, 500, 50);
    // draw_line(cr, 450, 50, 400, 50);
    // draw_line(cr, 350, 50, 300, 50);
    // draw_line(cr, 250, 50, 200, 50);
    // draw_line(cr, 150, 50, 100, 50);
    once = false;
}
bool MyWindow::checkBoundaries(int direction)
{
    if (direction == GDK_KEY_Right || direction == GDK_KEY_Left)
    {
        for (int i = 0; i < vline.size(); i++)
        {
            if ((circle_x) == vline.at(i).x1)
            {

                if (vline.at(i).y1 > vline.at(i).y2)
                {
                    if (circle_y > vline.at(i).y2 && circle_y < vline.at(i).y1)
                    {
                        std::cout << "v stop\n";
                        return false;
                    }
                }
                else
                {
                    if (circle_y < vline.at(i).y2 && circle_y > vline.at(i).y1)
                    {
                        std::cout << "v stop\n";
                        return false;
                    }
                }
            }
        }
    }
    if (direction == GDK_KEY_Up || direction == GDK_KEY_Down)
    {
        for (int i = 0; i < hline.size(); i++)
        {
            if ((circle_y) == hline.at(i).y1)
            {
                if (hline.at(i).x2 > hline.at(i).x1)
                {
                    if (circle_x > hline.at(i).x1 && circle_x < hline.at(i).x2)
                    {
                        std::cout << "h stop\n";
                        return false;
                    }
                }
                else
                {
                    if (circle_x < hline.at(i).x1 && circle_x > hline.at(i).x2)
                    {
                        std::cout << "h stop\n";
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

bool MyWindow::on_key_press_event(GdkEventKey *event)
{
    prevx = circle_x;
    prevy = circle_y;
    // Handle key press events

    mysplash->setEvent(event->keyval);
    if (event->keyval == GDK_KEY_Return || event->keyval == GDK_KEY_KP_Enter)
    {
        std::cout << "Hello" << std::endl;
        gameparams myprms = mysplash->getParams();
        int algx, algy;
        if (myprms.level == LVL_EASY)
        {
            algx = 5;
            algy = 10;
            stepx = 680 / 5;
            stepy = 480 / 10;
            xfactor = 1;
            yfactor = 1;

            std::cout << "stepx:" << stepx << " stepy:" << stepy << " xfactor:" << xfactor << " yfactor:" << yfactor << std::endl;
        }
        else if (myprms.level == LVL_Mid)
        {
            algx = 20;
            algy = 30;
            stepx = 680 / 20;
            stepy = 480 / 30;
            xfactor = 4;
            yfactor = 3;
            std::cout << "stepx:" << stepx << " stepy:" << stepy << " xfactor:" << xfactor << " yfactor:" << yfactor << std::endl;
        }
        else
        {
            algx = 40;
            algy = 50;
            stepx = 680 / 40;
            stepy = 480 / 50;
            xfactor = 8;
            yfactor = 5;
            std::cout << "stepx:" << stepx << " stepy:" << stepy << " xfactor:" << xfactor << " yfactor:" << yfactor << std::endl;
        }
        if (myprms.algorithm == ALGORITHM_ALDOS)
        {
            selectedAlgorithm = ALGORITHM_ALDOS;
            aldosAlgorithm = new aldosBroder(algx, algy);
        }
        else
        {
            selectedAlgorithm = ALGORITHM_FUSION;
            fusionAlgorithm = new fusion(algx, algy);
        }

        startGame = true;
    }
    switch (event->keyval)
    {
    case GDK_KEY_Left:
        // circle_x -= 10;
        for (int i = 0; i < stepx; i++)
        {
            circle_x--;
            if (checkBoundaries(event->keyval) == false)
            {
                circle_x++;
                break;
            }
        }
        break;
    case GDK_KEY_Right:
        // circle_x += 10;
        for (int i = 0; i < stepx; i++)
        {
            circle_x++;
            if (checkBoundaries(event->keyval) == false)
            {
                circle_x--;
                break;
            }
        }
        break;
    case GDK_KEY_Up:
        // circle_y -=8;
        for (int i = 0; i < stepy; i++)
        {
            circle_y--;
            if (checkBoundaries(event->keyval) == false)
            {
                circle_y++;
                break;
            }
        }
        break;
    case GDK_KEY_Down:
        // circle_y += 8;
        for (int i = 0; i < stepy; i++)
        {
            circle_y++;
            if (checkBoundaries(event->keyval) == false)
            {
                circle_y--;
                break;
            }
        }
        break;
    }
    // if (checkBoundaries(event->keyval) == false)
    // {
    //     switch (event->keyval)
    //     {
    //     case GDK_KEY_Left:
    //         circle_x +=10;
    //         break;
    //     case GDK_KEY_Right:
    //         circle_x -= 10;
    //         break;
    //     case GDK_KEY_Up:
    //         circle_y += 8;
    //         break;
    //     case GDK_KEY_Down:
    //         circle_y -=8;
    //         break;
    //     }
    // }

    // Check if the circle exceeds the boundaries
    if (circle_x < 60 || circle_x > 740 || circle_y < 60 || circle_y > 540)
    {
        // Restore the previous position if the circle exceeds the boundaries
        circle_x = prevx;
        circle_y = prevy;
    }

    // if (((circle_x >= 60) && (circle_x <= 100)) && ((circle_y >= 400) && (circle_y <= 450)))
    // {
    //     std::cout << "you win\n";
    //     circle_x = 600;
    //     circle_y = 540;
    //     startGame = false;
    //     winner = true;
    // }

    // Request redrawing of the window
    auto window = get_window();
    if (window)
    {
        Gdk::Rectangle rect(0, 0, get_allocation().get_width(), get_allocation().get_height());
        window->invalidate_rect(rect, false);
    }

    return true;
}