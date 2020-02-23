#ifndef CWDOCK_H
#define CWDOCK_H

#include <iostream>
#include <vector>
#include <string>
#include <thread>

#include <gtkmm.h>
#include <gdkmm.h>

#include "cwbox.h"
#include "cwclient.h"
#include "cwmenu.h"

class CWDock : public Gtk::Window
{
    public:
        CWDock(std::size_t windowWidth, std::size_t windowHeight,
                std::size_t iconNorm, std::size_t iconHigh, bool top);
        ~CWDock();
        bool onDraw(const Cairo::RefPtr<Cairo::Context>& cr);
        void onRealize();

        void setVisual(Glib::RefPtr<Gdk::Visual> visual);
        void loadVector(std::vector<CWdata> data);
        void updateWindows();
    private:
        std::size_t m_WindowWidth;
        std::size_t m_WindowHeight;
        std::size_t m_iconNorm;
        std::size_t m_iconHigh;
        CWClient m_Client;
        std::vector<CWdata> m_CwdataVec;
        std::vector<CWBox*> m_CWBoxVec;
        Gtk::Box m_Panel;
        Glib::Dispatcher m_Disp1;
        CWMenu *m_AppMenu;

        bool   m_top = false;
        uint32_t m_DockID;
};

#endif // CWDOCK_H
