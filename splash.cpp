#include "splash.h"

splash::splash()
{

    levels.push_back("Easy (5*10)");
    levels.push_back("Medium (20*30)");
    levels.push_back("Hard (40*50)");

    algorithms.push_back("aldos-broder");
    algorithms.push_back("fusion");
}
void splash::draw(const Cairo::RefPtr<Cairo::Context> &cr)
{
    // Set the text font and size
    Pango::FontDescription font_desc("Arial 50");
    cr->select_font_face(font_desc.get_family(), Cairo::FONT_SLANT_NORMAL, Cairo::FONT_WEIGHT_NORMAL);
    cr->set_font_size(font_desc.get_size() / Pango::SCALE);
    cr->set_source_rgb(0.0, 0.0, 0.0); // Black color
    cr->move_to(280, 100);             // Position of the text
    cr->show_text("Maze Game");

    label(cr, "Press Enter to start , up,down,left,right to chose ", 250, 550);
    label(cr, "Level ", 180, 200);
    label(cr, "Algorithm ", 180, 360);

    std::string tmplvl, tmpalg;
    tmplvl = levels.at(lvlIdx);
    tmpalg = algorithms.at(AlgIdx);

    btn(cr, tmplvl, 1, 350, 200, 200, 80);
    btn(cr, tmpalg, 2, 350, 350, 200, 80);
}
void splash::setEvent(int event)
{
    switch (event)
    {
    case GDK_KEY_Left:
        if (cursorIdx == 1)
        {
            if (lvlIdx != 0)
            {
                lvlIdx--;
            }
        }
        else
        {
            if (AlgIdx != 0)
            {
                AlgIdx--;
            }
        }
        break;
    case GDK_KEY_Right:
        if (cursorIdx == 1)
        {
            if (lvlIdx != levels.size() - 1)
            {
                lvlIdx++;
            }
        }
        else
        {
            if (AlgIdx != algorithms.size() - 1)
            {
                AlgIdx++;
            }
        }
        break;
    case GDK_KEY_Up:
        if (cursorIdx != 1)
            cursorIdx--;
        break;
    case GDK_KEY_Down:
        if (cursorIdx != 2)
            cursorIdx++;
        break;
    }
}

void splash::on_button_clicked(const std::string &buttonText)
{
}
void splash::label(const Cairo::RefPtr<Cairo::Context> &cr, std::string text, int x, int y)
{

    Pango::FontDescription font_desc2("Arial 25");
    cr->select_font_face(font_desc2.get_family(), Cairo::FONT_SLANT_NORMAL, Cairo::FONT_WEIGHT_NORMAL);
    cr->set_font_size(font_desc2.get_size() / Pango::SCALE);

    // Set the text color
    cr->set_source_rgb(0.0, 1.0, 1.0); // Black color
                                       // Draw the text "Maze Game"
                                       // cr->move_to(250, 550); // Position of the text
    cr->move_to(x, y);                 // Position of the text

    // cr->show_text("Press Enter to start , up ,down left ,right to chose");
    cr->show_text(text);
}

void splash::btn(const Cairo::RefPtr<Cairo::Context> &cr, std::string text, int cursor, int x, int y, int width, int heigth)
{

    // splash mysplash(cr);
    if (cursor != cursorIdx)
    {
        cr->set_source_rgb(0.9, 0.9, 0.9); // Rectangle background color
        cr->rectangle(x, y, width, heigth);
        cr->fill();
    }
    else
    {
        cr->set_source_rgb(0.0, 0.9, 0.0); // Rectangle background color
        cr->rectangle(x, y, width, heigth);
        cr->fill();
    }

    // Draw text
    cr->set_source_rgb(0.0, 0.0, 0.0); // Text color
    cr->select_font_face("Sans", Cairo::FONT_SLANT_NORMAL, Cairo::FONT_WEIGHT_NORMAL);
    cr->set_font_size(18.0);
    cr->move_to(x + width / 2 - 40, y + heigth / 2);
    cr->show_text(text);
}

gameparams splash::getParams()
{

    std::string tmplvl, tmpalg;
    tmplvl = levels.at(lvlIdx);
    tmpalg = algorithms.at(AlgIdx);
    gameparams tmp;

    if (tmplvl == "Easy (5*10)")
    {
        tmp.level = LVL_EASY;
    }
    if (tmplvl == "Medium (20*30)")
    {
        tmp.level = LVL_Mid;
    }
    if (tmplvl == "Hard (40*50)")
    {
        tmp.level = LVL_HIGH;
    }
    if (tmplvl == "aldos-broder")
    {
        tmp.algorithm = ALGORITHM_ALDOS;
    }
    if (tmplvl == "fusion")
    {
        tmp.algorithm = ALGORITHM_FUSION;
    }
    return tmp;
}
