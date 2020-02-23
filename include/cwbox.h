#ifndef CWBOX_H
#define CWBOX_H

#include <iostream>
#include <fstream>

#include <gtkmm.h>
#include <gdkmm.h>

#include "cwclient.h"



class CWBox: public Gtk::EventBox
{

    public:
        CWBox(std::size_t iconNorm, std::size_t iconHigh,std::string appName,
            std::string windowName, uint32_t windowId, uint32_t processId);

        bool is_exists(const std::string& filePath);
        bool on_over(GdkEventCrossing* event);
        bool on_click(GdkEventButton* event);
        bool on_leave(GdkEventCrossing* event);

        uint32_t &getWindowId();


    private:

        std::size_t m_iconNorm;
        std::size_t m_iconHigh;
        std::string m_appName;
        std::string m_windowName;
        uint32_t m_windowId;
        uint32_t m_processId;
        std::string m_iconPath;

        Gtk::Label m_PopLabel;
        Gtk::Popover m_PopOver;
        Glib::RefPtr<Gdk::Pixbuf> m_pixScaleNorm;
        Glib::RefPtr<Gdk::Pixbuf> m_pixScaleHigh;
        Glib::RefPtr<Gdk::Pixbuf> m_pixBuffer;

        Gtk::Image m_image;
        CWClient m_Client;

};


#endif // CWBOX_H
