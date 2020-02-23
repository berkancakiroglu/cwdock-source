#ifndef CWAPP_H
#define CWAPP_H

#include <gtkmm.h>
#include <iostream>
#include <unistd.h>

class CWApp: public Gtk::EventBox
{


    public:
        CWApp(std::string appName, std::string appPath, Glib::RefPtr<Gdk::Pixbuf> pixBuffer, Gtk::Window *window);
        bool on_click(GdkEventButton* event);
    private:
        std::string m_appPath;
        Gtk::Image m_Image;
        Gtk::Label m_Label;
        Gtk::Box   m_Box;
        Gtk::Window *m_Window;


};

#endif // CWAPP_H
