#ifndef CWCLIENT_H
#define CWCLIENT_H

#include <iostream>
#include <xcb/xcb.h>
#include <cstring>
#include <string>
#include <vector>

#include <unistd.h>
#include <linux/limits.h>





template < typename Type >
class CWPointer
{

    public:
        CWPointer()
            : m_pData(nullptr)
        {

        }


        CWPointer(Type * pointer)
            : m_pData(pointer)
        {
        }
        ~CWPointer()
        {
            if(m_pData!=nullptr)
            {
                free(m_pData);
                m_pData = nullptr;
            }

        }
        Type* get()
        {

            return m_pData;
        }
        Type** get2()
        {

            return &m_pData;
        }
        Type& operator* ()
        {
            return *m_pData;
        }

        Type* operator-> ()
        {
            return m_pData;
        }
        void operator= (const Type * pointer)
        {
            m_pData = (Type*)pointer;

        }
    private:
        Type * m_pData;
};



class CWAtoms{

    public:
        CWAtoms();
        xcb_atom_t getAtom(std::string name);
        void init();


    protected:
        xcb_connection_t* m_Connection;
    public:
        xcb_atom_t _NET_WM_NAME;
        xcb_atom_t _NET_WM_VISIBLE_NAME;
        xcb_atom_t _NET_WM_ICON_NAME;
        xcb_atom_t _NET_WM_VISIBLE_ICON_NAME;
        xcb_atom_t _NET_WM_DESKTOP;
        xcb_atom_t _NET_WM_WINDOW_TYPE;
        xcb_atom_t _NET_WM_STATE;
        xcb_atom_t _NET_WM_ALLOWED_ACTIONS;
        xcb_atom_t _NET_WM_STRUT;
        xcb_atom_t _NET_WM_STRUT_PARTIAL;
        xcb_atom_t _NET_WM_ICON_GEOMETRY;
        xcb_atom_t _NET_WM_ICON;
        xcb_atom_t _NET_WM_PID;
        xcb_atom_t _NET_WM_HANDLED_ICONS;
        xcb_atom_t _NET_WM_USER_TIME;
        xcb_atom_t _NET_FRAME_EXTENTS;

        xcb_atom_t _NET_WM_STATE_MODAL;
        xcb_atom_t _NET_WM_STATE_STICKY;
        xcb_atom_t _NET_WM_STATE_MAXIMIZED_VERT;
        xcb_atom_t _NET_WM_STATE_MAXIMIZED_HORZ;
        xcb_atom_t _NET_WM_STATE_SHADED;
        xcb_atom_t _NET_WM_STATE_SKIP_TASKBAR;
        xcb_atom_t _NET_WM_STATE_SKIP_PAGER;
        xcb_atom_t _NET_WM_STATE_HIDDEN;
        xcb_atom_t _NET_WM_STATE_FULLSCREEN;
        xcb_atom_t _NET_WM_STATE_ABOVE;
        xcb_atom_t _NET_WM_STATE_BELOW;
        xcb_atom_t _NET_WM_STATE_DEMANDS_ATTENTION;

        xcb_atom_t _NET_CLIENT_LIST;
        xcb_atom_t _NET_NUMBER_OF_DESKTOPS;
        xcb_atom_t _NET_DESKTOP_GEOMETRY;
        xcb_atom_t _NET_DESKTOP_VIEWPORT;
        xcb_atom_t _NET_CURRENT_DESKTOP;
        xcb_atom_t _NET_DESKTOP_NAMES;
        xcb_atom_t _NET_ACTIVE_WINDOW;
        xcb_atom_t _NET_WORKAREA;
        xcb_atom_t _NET_SUPPORTING_WM_CHECK;
        xcb_atom_t _NET_VIRTUAL_ROOTS;
        xcb_atom_t _NET_DESKTOP_LAYOUT;
        xcb_atom_t _NET_SHOWING_DESKTOP;

        xcb_atom_t _NET_WM_WINDOW_TYPE_DESKTOP;
        xcb_atom_t _NET_WM_WINDOW_TYPE_DOCK;
        xcb_atom_t _NET_WM_WINDOW_TYPE_TOOLBAR;
        xcb_atom_t _NET_WM_WINDOW_TYPE_MENU;
        xcb_atom_t _NET_WM_WINDOW_TYPE_UTILITY;
        xcb_atom_t _NET_WM_WINDOW_TYPE_SPLASH;
        xcb_atom_t _NET_WM_WINDOW_TYPE_DIALOG;
        xcb_atom_t _NET_WM_WINDOW_TYPE_NORMAL;
        xcb_atom_t UTF8_STRING;
};


struct CWdata{
    std::string m_appName;
    std::string m_windowName;
    uint32_t m_windowId;
    uint32_t m_processId;
};


class CWClient: public CWAtoms
{
    public:
        CWClient();
        ~CWClient();
        void setDockProp(uint32_t dock_id, uint32_t data[12]);
        void setIconGeometry(uint32_t window_id, uint32_t x, uint32_t y, uint32_t w, uint32_t h);
        void setHiddenState(xcb_window_t window_id, uint32_t state);
        void setWindowActivate(xcb_window_t window_id);

        uint32_t getProcessId(xcb_window_t window_id);
        bool getWindowSkipBar(xcb_window_t window_id);
        bool windowIsHidden(xcb_window_t window_id);
        bool getWindowHiddenState(xcb_window_t window_id);
        bool getWindowActivate(xcb_window_t window_id);

        std::string getIconName(xcb_window_t window_id);
        std::string getWindowName(xcb_window_t window_id);
        std::string getApplicationName(uint32_t process_id);
        std::vector<CWdata> getWindows();



};

#endif // CWCLIENT_H
