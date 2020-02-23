#include "cwclient.h"
CWAtoms::CWAtoms()
    :m_Connection(nullptr)
{


}

xcb_atom_t CWAtoms::getAtom(std::string name)
{

        xcb_atom_t atomID;
        xcb_intern_atom_cookie_t cookie;

        CWPointer<xcb_intern_atom_reply_t> reply;
        CWPointer<xcb_generic_error_t> error;


        cookie = xcb_intern_atom(m_Connection, 0, uint16_t(name.size()),(const char*) name.c_str());
        reply = xcb_intern_atom_reply(m_Connection, cookie, error.get2());

        if(reply.get())
        {
            atomID = reply->atom;

        } else if(error.get())
        {
            std::cout << "ATOM ERROR: " << error->error_code << std::endl;

        }

       return atomID;
}

void CWAtoms::init()
{

     _NET_WM_NAME = getAtom( "_NET_WM_NAME");
     _NET_WM_VISIBLE_NAME = getAtom( "_NET_WM_VISIBLE_NAME");
     _NET_WM_ICON_NAME = getAtom( "_NET_WM_ICON_NAME");
     _NET_WM_VISIBLE_ICON_NAME = getAtom( "_NET_WM_VISIBLE_ICON_NAME");
     _NET_WM_DESKTOP = getAtom( "_NET_WM_DESKTOP");
     _NET_WM_WINDOW_TYPE = getAtom( "_NET_WM_WINDOW_TYPE");
     _NET_WM_STATE = getAtom( "_NET_WM_STATE");
     _NET_WM_ALLOWED_ACTIONS = getAtom( "_NET_WM_ALLOWED_ACTIONS");
     _NET_WM_STRUT = getAtom( "_NET_WM_STRUT");
     _NET_WM_STRUT_PARTIAL = getAtom( "_NET_WM_STRUT_PARTIAL");
     _NET_WM_ICON_GEOMETRY = getAtom( "_NET_WM_ICON_GEOMETRY");
     _NET_WM_ICON = getAtom( "_NET_WM_ICON");
     _NET_WM_PID = getAtom( "_NET_WM_PID");
     _NET_WM_HANDLED_ICONS = getAtom( "_NET_WM_HANDLED_ICONS");
     _NET_WM_USER_TIME = getAtom( "_NET_WM_USER_TIME");
     _NET_FRAME_EXTENTS = getAtom( "_NET_FRAME_EXTENTS");

     _NET_WM_STATE_MODAL = getAtom( "_NET_WM_STATE_MODAL");
     _NET_WM_STATE_STICKY = getAtom( "_NET_WM_STATE_STICKY");
     _NET_WM_STATE_MAXIMIZED_VERT = getAtom( "_NET_WM_STATE_MAXIMIZED_VERT");
     _NET_WM_STATE_MAXIMIZED_HORZ = getAtom( "_NET_WM_STATE_MAXIMIZED_HORZ");
     _NET_WM_STATE_SHADED = getAtom( "_NET_WM_STATE_SHADED");
     _NET_WM_STATE_SKIP_TASKBAR = getAtom( "_NET_WM_STATE_SKIP_TASKBAR");
     _NET_WM_STATE_SKIP_PAGER = getAtom( "_NET_WM_STATE_SKIP_PAGER");
     _NET_WM_STATE_HIDDEN = getAtom( "_NET_WM_STATE_HIDDEN");
     _NET_WM_STATE_FULLSCREEN = getAtom( "_NET_WM_STATE_FULLSCREEN");
     _NET_WM_STATE_ABOVE = getAtom( "_NET_WM_STATE_ABOVE");
     _NET_WM_STATE_BELOW = getAtom( "_NET_WM_STATE_BELOW");
     _NET_WM_STATE_DEMANDS_ATTENTION = getAtom( "_NET_WM_STATE_DEMANDS_ATTENTION");

     _NET_CLIENT_LIST = getAtom( "_NET_CLIENT_LIST");
     _NET_NUMBER_OF_DESKTOPS = getAtom( "_NET_NUMBER_OF_DESKTOPS");
     _NET_DESKTOP_GEOMETRY = getAtom( "_NET_DESKTOP_GEOMETRY");
     _NET_DESKTOP_VIEWPORT = getAtom( "_NET_DESKTOP_VIEWPORT");
     _NET_CURRENT_DESKTOP = getAtom( "_NET_CURRENT_DESKTOP");
     _NET_DESKTOP_NAMES = getAtom( "_NET_DESKTOP_NAMES");
     _NET_ACTIVE_WINDOW = getAtom( "_NET_ACTIVE_WINDOW");
     _NET_WORKAREA = getAtom( "_NET_WORKAREA");
     _NET_SUPPORTING_WM_CHECK = getAtom( "_NET_SUPPORTING_WM_CHECK");
     _NET_VIRTUAL_ROOTS = getAtom( "_NET_VIRTUAL_ROOTS");
     _NET_DESKTOP_LAYOUT = getAtom( "_NET_DESKTOP_LAYOUT");
     _NET_SHOWING_DESKTOP = getAtom( "_NET_SHOWING_DESKTOP");

     _NET_WM_WINDOW_TYPE_DESKTOP = getAtom( "_NET_WM_WINDOW_TYPE_DESKTOP");
     _NET_WM_WINDOW_TYPE_DOCK = getAtom( "_NET_WM_WINDOW_TYPE_DOCK");
     _NET_WM_WINDOW_TYPE_TOOLBAR = getAtom( "_NET_WM_WINDOW_TYPE_TOOLBAR");
     _NET_WM_WINDOW_TYPE_MENU = getAtom( "_NET_WM_WINDOW_TYPE_MENU");
     _NET_WM_WINDOW_TYPE_UTILITY = getAtom( "_NET_WM_WINDOW_TYPE_UTILITY");
     _NET_WM_WINDOW_TYPE_SPLASH = getAtom( "_NET_WM_WINDOW_TYPE_SPLASH");
     _NET_WM_WINDOW_TYPE_DIALOG = getAtom( "_NET_WM_WINDOW_TYPE_DIALOG");
     _NET_WM_WINDOW_TYPE_NORMAL = getAtom( "_NET_WM_WINDOW_TYPE_NORMAL");
     UTF8_STRING = getAtom( "UTF8_STRING");

}



CWClient::CWClient()
{

    m_Connection = xcb_connect(NULL, NULL);
    init();

}

CWClient::~CWClient()
{
    xcb_disconnect(m_Connection);
}


void CWClient::setDockProp(uint32_t dock_id, uint32_t data[12])
{
	xcb_change_property(m_Connection, XCB_PROP_MODE_APPEND,  dock_id, _NET_WM_STATE, XCB_ATOM_ATOM, 32, 2, &_NET_WM_STATE_STICKY);
	xcb_change_property(m_Connection, XCB_PROP_MODE_REPLACE, dock_id, _NET_WM_STRUT, XCB_ATOM_CARDINAL, 32, 4, data);
    xcb_change_property(m_Connection, XCB_PROP_MODE_REPLACE, dock_id, _NET_WM_STRUT_PARTIAL, XCB_ATOM_CARDINAL, 32, 12, data);
	xcb_flush(m_Connection);
}

void CWClient::setIconGeometry(uint32_t window_id, uint32_t x, uint32_t y, uint32_t w, uint32_t h)
{

	uint32_t data[4] = {0};

    data[0] = x;
    data[1] = y;
    data[2] = w;
    data[3] = h;

    xcb_change_property(m_Connection, XCB_PROP_MODE_REPLACE, window_id, _NET_WM_ICON_GEOMETRY, XCB_ATOM_CARDINAL, 32, 4, data);
    xcb_flush(m_Connection);
}




void CWClient::setHiddenState(xcb_window_t window_id, uint32_t state)
{
    xcb_window_t rootwin;
    xcb_query_tree_cookie_t qtree_cookie;

    CWPointer<xcb_query_tree_reply_t> qtree_reply;
    CWPointer<xcb_generic_error_t> error;


    qtree_cookie = xcb_query_tree(m_Connection, window_id);
    qtree_reply = xcb_query_tree_reply(m_Connection, qtree_cookie, error.get2());


    if (qtree_reply.get())
    {
        rootwin = qtree_reply->root;

    }
    else if (error.get())
    {
       std::cout << "QUERY TREE ERROR: " << error->error_code << std::endl;
    }

    xcb_void_cookie_t voidCookie;
    xcb_client_message_event_t client_msg;

    std::memset(&client_msg, 0, sizeof(xcb_client_message_event_t));
    client_msg.response_type = XCB_CLIENT_MESSAGE;
    client_msg.format = 32;
    client_msg.sequence = 0;
    client_msg.window = window_id;
    client_msg.type = _NET_WM_STATE;
    client_msg.data.data32[0] = state;
    client_msg.data.data32[1] = _NET_WM_STATE_HIDDEN;
    client_msg.data.data32[2] = 0;
    client_msg.data.data32[3] = 0;
    client_msg.data.data32[4] = 0;
    voidCookie = xcb_send_event(m_Connection, 1, rootwin,XCB_EVENT_MASK_SUBSTRUCTURE_NOTIFY |
                                    XCB_EVENT_MASK_SUBSTRUCTURE_REDIRECT, (const char *)&client_msg);

    xcb_flush(m_Connection);

}

void CWClient::setWindowActivate(xcb_window_t window_id)
{

    xcb_window_t rootwin;
    xcb_query_tree_cookie_t qtree_cookie;

    CWPointer<xcb_query_tree_reply_t> qtree_reply;
    CWPointer<xcb_generic_error_t> error;


    qtree_cookie = xcb_query_tree(m_Connection, window_id);
    qtree_reply = xcb_query_tree_reply(m_Connection, qtree_cookie, error.get2());


    if (qtree_reply.get())
    {
        rootwin = qtree_reply->root;

    }
    else if (error.get())
    {
       std::cout << "QUERY TREE ERROR: " << error->error_code << std::endl;
    }

    xcb_void_cookie_t voidCookie;
    xcb_client_message_event_t client_msg;

    std::memset(&client_msg, 0, sizeof(xcb_client_message_event_t));
    client_msg.response_type = XCB_CLIENT_MESSAGE;
    client_msg.format = 32;
    client_msg.sequence = 0;
    client_msg.window = window_id;
    client_msg.type = _NET_ACTIVE_WINDOW;
    client_msg.data.data32[0] = 0;
    client_msg.data.data32[1] = 0;
    client_msg.data.data32[2] = 0;
    client_msg.data.data32[3] = 0;
    client_msg.data.data32[4] = 0;
    voidCookie = xcb_send_event(m_Connection, 1, rootwin,XCB_EVENT_MASK_SUBSTRUCTURE_NOTIFY |
                                    XCB_EVENT_MASK_SUBSTRUCTURE_REDIRECT, (const char *)&client_msg);

    xcb_flush(m_Connection);

}

bool CWClient::getWindowSkipBar(xcb_window_t window_id)
{

    xcb_atom_t *state;
    xcb_get_property_cookie_t cookie;

    CWPointer<xcb_get_property_reply_t> reply;
    CWPointer<xcb_generic_error_t> error;

    cookie = xcb_get_property(m_Connection, 0, window_id, _NET_WM_STATE, XCB_ATOM_ATOM, 0, 5);
    reply  = xcb_get_property_reply(m_Connection, cookie, error.get2());

    if(error.get())
    {
        std::cout << "GET WM SKIP: " << error->error_code << std::endl;

    }

    if(reply.get())
    {
        if(xcb_get_property_value_length(reply.get()))
        {
            state = (xcb_atom_t*)xcb_get_property_value(reply.get());
            for(int i=0; i<5; ++i)
            {

                if (state[i] == _NET_WM_STATE_SKIP_TASKBAR)
                {

                    return true;
                }

            }
        }
    }

    return false;
}

bool CWClient::windowIsHidden(xcb_window_t window_id)
{

    xcb_atom_t *state;
    xcb_get_property_cookie_t cookie;

    CWPointer<xcb_get_property_reply_t> reply;
    CWPointer<xcb_generic_error_t> error;

    cookie = xcb_get_property(m_Connection, 0, window_id, _NET_WM_WINDOW_TYPE, XCB_ATOM_ATOM, 0, 5);
    reply  = xcb_get_property_reply(m_Connection, cookie, error.get2());

    if(error.get())
    {
        std::cout << "GET WMTYPE: " << (int)error->error_code << std::endl;

    }

    if(reply.get())
    {
        if(xcb_get_property_value_length(reply.get()))
        {
            state = (xcb_atom_t*)xcb_get_property_value(reply.get());
            for(int i=0; i<5; ++i)
            {

                if (state[i] == _NET_WM_WINDOW_TYPE_DOCK)
                {

                    return true;
                }
                if (state[i] == _NET_WM_WINDOW_TYPE_DESKTOP)
                {

                    return true;
                }
                if (state[i] == _NET_WM_WINDOW_TYPE_TOOLBAR)
                {

                    return true;
                }
                if (state[i] == _NET_WM_WINDOW_TYPE_MENU)
                {

                    return true;
                }
                if (state[i] == _NET_WM_WINDOW_TYPE_SPLASH)
                {

                    return true;
                }
            }
        }
    }

    return false;
}


bool CWClient::getWindowActivate(xcb_window_t window_id)
{
    xcb_window_t rootwin;
    xcb_atom_t *state;

    xcb_get_property_cookie_t cookie;
    xcb_query_tree_cookie_t qtree_cookie;

    CWPointer<xcb_get_property_reply_t> reply;
    CWPointer<xcb_query_tree_reply_t> qtree_reply;
    CWPointer<xcb_generic_error_t> error;


    qtree_cookie = xcb_query_tree(m_Connection, window_id);
    qtree_reply = xcb_query_tree_reply(m_Connection, qtree_cookie, error.get2());


    if (qtree_reply.get())
    {
        rootwin = qtree_reply->root;

    }
    else if (error.get())
    {
       std::cout << "QUERY TREE ERROR: " << error->error_code << std::endl;

    }


    cookie = xcb_get_property(m_Connection, 0, rootwin, _NET_ACTIVE_WINDOW, XCB_ATOM_WINDOW, 0, 1);
    reply  = xcb_get_property_reply(m_Connection, cookie, error.get2());

    if(error.get())
    {
        std::cout << "GET WM STATE ERROR: " << error->error_code << std::endl;

    }

    if(reply.get())
    {
        if(xcb_get_property_value_length(reply.get()))
        {
            state = (xcb_atom_t*)xcb_get_property_value(reply.get());
            if(*state == window_id)
            {

                return true;
            }

        }
    }

    return false;
}

bool CWClient::getWindowHiddenState(xcb_window_t window_id)
{

    xcb_atom_t *state;
    xcb_get_property_cookie_t cookie;

    CWPointer<xcb_get_property_reply_t> reply;
    CWPointer<xcb_generic_error_t> error;

    cookie = xcb_get_property(m_Connection, 0, window_id, _NET_WM_STATE, XCB_ATOM_ATOM, 0, 5);
    reply  = xcb_get_property_reply(m_Connection, cookie, error.get2());

    if(error.get())
    {
        std::cout << "GET WM STATE ERROR: " << error->error_code << std::endl;

    }

    if(reply.get())
    {
        if(xcb_get_property_value_length(reply.get()))
        {
            state = (xcb_atom_t*)xcb_get_property_value(reply.get());

            for(int i=0; i<5; ++i)
            {


                if (state[i] == _NET_WM_STATE_HIDDEN)
                {

                    return true;
                }

            }

        }

    }


    return false;
}


uint32_t CWClient::getProcessId(xcb_window_t window_id)
{
    uint32_t *processId;
    xcb_get_property_cookie_t cookie;

    CWPointer<xcb_get_property_reply_t> reply;
    CWPointer<xcb_generic_error_t> error;

    cookie = xcb_get_property(m_Connection, 0, window_id, _NET_WM_PID, XCB_GET_PROPERTY_TYPE_ANY, 0, 1);
    reply  = xcb_get_property_reply(m_Connection, cookie, error.get2());

    if(error.get())
    {
        std::cout << "GET PROCESS ERROR: " << error->error_code << std::endl;
        //do anything
    }

    if(reply.get())
    {
        if( xcb_get_property_value_length(reply.get()) )
        {
            processId = (uint32_t*)xcb_get_property_value(reply.get());
        }
    }

    return *processId;
}

std::string CWClient::getIconName(xcb_window_t window_id)
{
    std::string name;
    xcb_get_property_cookie_t cookie;

    CWPointer<xcb_get_property_reply_t> reply;
    CWPointer<xcb_generic_error_t> error;

    cookie = xcb_get_property(m_Connection, 0, window_id, _NET_WM_ICON_NAME, UTF8_STRING, 0, 25);
    reply  = xcb_get_property_reply(m_Connection, cookie, error.get2());

    if(error.get())
    {
        std::cout << "GET WİNDOW NAME ERROR: " << error->error_code << std::endl;

    }

    if(reply.get())
    {
        if(size_t length = xcb_get_property_value_length(reply.get()))
        {
            name = (char*)xcb_get_property_value(reply.get());
            name[length] = '\0';
        }
    }

    return name;

}



std::string CWClient::getWindowName(xcb_window_t window_id)
{
    std::string name;
    xcb_get_property_cookie_t cookie;

    CWPointer<xcb_get_property_reply_t> reply;
    CWPointer<xcb_generic_error_t> error;

    cookie = xcb_get_property(m_Connection, 0, window_id, _NET_WM_NAME, UTF8_STRING, 0, 25);
    reply  = xcb_get_property_reply(m_Connection, cookie, error.get2());

    if(error.get())
    {
        std::cout << "GET WİNDOW NAME ERROR: " << error->error_code << std::endl;

    }

    if(reply.get())
    {
        if(size_t length = xcb_get_property_value_length(reply.get()))
        {
            name = (char*)xcb_get_property_value(reply.get());
            name[length] = '\0';
        }
    }

    return name;

}

std::string CWClient::getApplicationName(uint32_t process_id)
{

    char path[PATH_MAX];
    std::memset(path, 0, PATH_MAX);
    std::string cmd = "/proc/" + std::to_string(process_id) + "/exe";
    readlink(cmd.c_str(), path, PATH_MAX);
    return (std::string(path)).substr( (std::string(path)).find_last_of("/") + 1 );
}

std::vector<CWdata> CWClient::getWindows()
{

    xcb_window_t* windows;
    xcb_screen_t* screen;
    xcb_get_property_cookie_t cookie;
    std::vector<CWdata> winData;


    CWPointer<xcb_get_property_reply_t> reply;
    CWPointer<xcb_generic_error_t> error;

    screen = xcb_setup_roots_iterator(xcb_get_setup(m_Connection)).data;
    cookie = xcb_get_property(m_Connection, 0, screen->root, _NET_CLIENT_LIST, XCB_GET_PROPERTY_TYPE_ANY, 0, 100);
    reply  = xcb_get_property_reply(m_Connection, cookie, error.get2());

    if(error.get())
    {
        std::cout << "GET WINDOW ERROR: " << error->error_code << std::endl;

    }

    if(reply.get())
    {
        int length = xcb_get_property_value_length(reply.get());


        if(length)
        {
            windows = ( xcb_window_t*)xcb_get_property_value(reply.get());

            for(std::size_t i=0; i < length/ sizeof(xcb_window_t); ++i)
            {

                if(windowIsHidden(windows[i]) == false && getWindowSkipBar(windows[i]) == false)
                {
                    uint32_t tempProcId = getProcessId(windows[i]);

                    CWdata temp{getApplicationName(tempProcId),
                                getWindowName(windows[i]),
                                windows[i],
                                tempProcId};


                    winData.push_back(temp);


                }

            }
        }

    }
    return winData;
}


