#ifndef CWPOPUP_H
#define CWPOPUP_H

#include <gtkmm.h>
#include "cwapp.h"

class CWPopup: public Gtk::Window
{
    public:
        CWPopup(Gtk::WindowType type);
        ~CWPopup();
        std::size_t getItemSize();
        bool onDraw(const Cairo::RefPtr<Cairo::Context>& cr);
        void setVisual(Glib::RefPtr<Gdk::Visual> visual);
        bool focus_out(GdkEventFocus* gdk_event);
        void addApp(const std::string &appName, const std::string &appPath,
                                        Glib::RefPtr<Gdk::Pixbuf> pixBuffer);

    private:
        Gtk::Box m_Box;
        std::vector<CWApp*> m_AppVector;

};

#endif // CWPOPUP_H
