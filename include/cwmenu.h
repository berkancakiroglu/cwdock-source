#ifndef CWMENU_H
#define CWMENU_H

#include <gtkmm.h>
#include <gdkmm.h>
#include <fstream>
#include "cwpopup.h"

class CWMenu : public Gtk::EventBox
{
    public:
        CWMenu(std::string iconPath, std::string configPath, std::size_t iconNorm, std::size_t iconHigh);
        bool is_exist (const std::string& filePath);
        bool on_over(GdkEventCrossing* event);
        bool on_click(GdkEventButton* event);
        bool on_leave(GdkEventCrossing* event);
        void setPosition(std::size_t w, std::size_t h, std::size_t items, bool top);
    private:

        std::string m_IconPath;
        std::string m_ConfigPath;

        Glib::RefPtr<Gdk::Pixbuf> m_pixScaleNorm;
        Glib::RefPtr<Gdk::Pixbuf> m_pixScaleHigh;
        Glib::RefPtr<Gdk::Pixbuf> m_pixBuffer;
        std::size_t m_xpos, m_ypos, m_iconHigh;
        bool m_top;
        CWPopup *m_Popup;
        Gtk::Image m_Image;
};

#endif // CWMENU_H
