#include "cwdock.h"
#include <gdk/gdkx.h>
CWDock:: CWDock(std::size_t windowWidth, std::size_t windowHeight,
                std::size_t iconNorm, std::size_t iconHigh, bool top)
        :m_WindowWidth{windowWidth}, m_WindowHeight{windowHeight},
        m_iconNorm{iconNorm}, m_iconHigh{iconHigh}, m_top{top}
{

    resize(m_iconHigh,m_iconHigh);
    if(m_top == true)
    {
        move((m_WindowWidth/2) - (m_iconHigh/2), 0);
    }
    else
    {
        move((m_WindowWidth/2) - (m_iconHigh/2), m_WindowHeight-m_iconHigh);
    }




    set_type_hint(Gdk::WINDOW_TYPE_HINT_DOCK);
    set_skip_taskbar_hint(true);
    set_app_paintable(true);
    set_decorated(false);



    auto screen = get_screen();
    auto visual = screen->get_rgba_visual();

    setVisual(visual);
    signal_draw().connect(sigc::mem_fun(*this, &CWDock::onDraw));
    signal_show().connect(sigc::mem_fun(*this, &CWDock::onRealize));

    m_Disp1.connect(sigc::mem_fun(*this, &CWDock::updateWindows));
    m_Panel.set_name("cwDock");

    m_AppMenu = new CWMenu("/opt/CWDock/appicons/", "/opt/CWDock/appconf", m_iconNorm, m_iconHigh);
    m_AppMenu->setPosition(m_WindowWidth, m_WindowHeight, m_CWBoxVec.size(), m_top);

    add(m_Panel);
    m_Panel.pack_start(*m_AppMenu);
    m_Panel.show();




}

bool CWDock::onDraw(const Cairo::RefPtr<Cairo::Context>& cr)
{

    cr->save();
    cr->set_source_rgba(0.0, 0.0, 0.0, 0.0);
    cr->set_operator(Cairo::OPERATOR_SOURCE);
    cr->paint();
    cr->restore();
    return Gtk::Window::on_draw(cr);
}
void CWDock::onRealize()
{

    auto gwindow = get_window();
	m_DockID = GDK_WINDOW_XID(gwindow ->gobj());

    if(m_top == true)
    {
        uint32_t data[12] = {0};
        data[2] = m_iconHigh+8;
        data[8] = 0;
        data[9] = m_WindowWidth;
        m_Client.setDockProp(m_DockID, data);

    }
    else
    {

        uint32_t data[12] = {0};
        data[3] = m_iconHigh+8;
        data[10] = 0;
        data[11] = m_WindowWidth;
        m_Client.setDockProp(m_DockID, data);
    }

}

void CWDock::setVisual(Glib::RefPtr<Gdk::Visual> visual) {
    gtk_widget_set_visual(GTK_WIDGET(gobj()), visual->gobj());
}

CWDock::~CWDock()

{

    for(size_t i=0; i< m_CWBoxVec.size(); ++i){
         delete m_CWBoxVec[i];
    }

    delete m_AppMenu;

}

void CWDock::loadVector(std::vector<CWdata> dataVec)
{
    m_CwdataVec = dataVec;
    m_Disp1();

}


void CWDock::updateWindows()
{


    if(m_CWBoxVec.size() == 0){

        for(auto &data: m_CwdataVec)
        {


            if(data.m_windowName.size() >10){
                data.m_windowName = data.m_windowName.substr(0, 10)+ "...";
            }
            CWBox *pCWBox;
            pCWBox = new CWBox(m_iconNorm, m_iconHigh,
                                data.m_appName, data.m_windowName,
                                    data.m_windowId, data.m_processId);
            m_Client.setIconGeometry(data.m_windowId, m_WindowWidth/2, m_WindowHeight/2, 1, 1);
            m_CWBoxVec.push_back(pCWBox);
            m_Panel.pack_start(*pCWBox);


        }
    }else
    {


        for(size_t i=0; i<m_CWBoxVec.size(); ++i){
            bool lock=false;
                for( size_t z=0; z<m_CwdataVec.size(); ++z)
                {

                        if(m_CWBoxVec[i]->getWindowId() == m_CwdataVec[z].m_windowId )
                        {

                            m_CwdataVec.erase(m_CwdataVec.begin()+ z);
                            --z;
                            lock =true;
                            break;
                        }


                }

                if(lock==false){

                    m_Panel.remove(*m_CWBoxVec[i]);
                    delete m_CWBoxVec[i];
                    m_CWBoxVec.erase(m_CWBoxVec.begin()+i);
                    --i;
                }

        }



        for(auto &data: m_CwdataVec)
        {


            if(data.m_windowName.size() >10){
                data.m_windowName = data.m_windowName.substr(0, 10)+ "...";
            }
            CWBox *pCWBox;
            pCWBox = new CWBox(m_iconNorm, m_iconHigh,
                                data.m_appName, data.m_windowName,
                                    data.m_windowId, data.m_processId);
            m_Client.setIconGeometry(data.m_windowId, m_WindowWidth/2, m_WindowHeight/2, 1, 1);
            m_CWBoxVec.push_back(pCWBox);
            m_Panel.pack_start(*pCWBox);

        }
    }





    resize(m_iconHigh*(m_CWBoxVec.size()+1),m_iconHigh);
    if(m_top == true)
    {
        move((m_WindowWidth/2) - (m_iconHigh*(m_CWBoxVec.size()+1)/2), 0);
    }
    else
    {
        move((m_WindowWidth/2) - (m_iconHigh*(m_CWBoxVec.size()+1)/2), m_WindowHeight-m_iconHigh-5);
    }
     m_AppMenu->setPosition(m_WindowWidth, m_WindowHeight, m_CWBoxVec.size(), m_top);
    m_CwdataVec.clear();
}






