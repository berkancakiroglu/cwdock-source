#include "cwbox.h"





CWBox::CWBox(std::size_t iconNorm, std::size_t iconHigh, std::string appName,
                std::string windowName, uint32_t windowId, uint32_t processId)

    :m_iconNorm{iconNorm}, m_iconHigh{iconHigh}, m_appName{appName},
        m_windowName{windowName}, m_windowId{windowId}, m_processId{processId}
{

    add_events(  Gdk::POINTER_MOTION_MASK |
                            Gdk::POINTER_MOTION_HINT_MASK |
                            Gdk::BUTTON_PRESS_MASK |
                            Gdk::BUTTON_RELEASE_MASK);


    signal_enter_notify_event().connect(sigc::mem_fun(this, &CWBox::on_over));
    signal_button_release_event().connect(sigc::mem_fun(this, &CWBox::on_click));
    signal_leave_notify_event().connect(sigc::mem_fun(this, &CWBox::on_leave));

    m_PopOver.set_position(Gtk::PositionType::POS_LEFT );
    m_PopLabel.set_text(m_windowName.c_str());
    m_PopOver.add(m_PopLabel);
    m_PopOver.set_modal(false);
    m_PopOver.set_relative_to(m_image);
    add(m_image);


    if(m_appName.size() ==0)
    {
        m_iconPath = "/opt/CWDock/appicons/application-default-icon.svg";
    }
    else
    {
        m_iconPath = "/opt/CWDock/appicons/" + m_appName + ".svg";

        if(!is_exists(m_iconPath)){
            m_iconPath = "/opt/CWDock/appicons/application-default-icon.svg";

        }
    }




    m_pixBuffer  = Gdk::Pixbuf::create_from_file(m_iconPath);
    m_pixScaleNorm  = m_pixBuffer->scale_simple(m_iconNorm, m_iconNorm, Gdk::INTERP_BILINEAR);
    m_pixScaleHigh  = m_pixBuffer->scale_simple(m_iconHigh, m_iconHigh, Gdk::INTERP_BILINEAR);



    m_image.set(m_pixScaleNorm);
    m_PopLabel.show();
    show();
    m_image.show();
}

bool CWBox::is_exists (const std::string& filePath) {
    std::ifstream filew(filePath.c_str());
    return filew.good();
}

bool CWBox::on_over(GdkEventCrossing* event)
{
    m_windowName = m_Client.getWindowName(m_windowId);
    if(m_windowName.size() >10){
        m_windowName = m_windowName.substr(0, 10)+ "...";
    }
    m_PopLabel.set_text(m_windowName.c_str());
    m_PopOver.popup();
    m_image.set(m_pixScaleHigh);

    return true;
}

bool CWBox::on_click(GdkEventButton* event)
{

    if(event->type == GDK_BUTTON_RELEASE)
    {


        bool hiddenState = m_Client.getWindowHiddenState(m_windowId);
        bool activateState = m_Client.getWindowActivate(m_windowId);

        if(hiddenState)
        {
            m_Client.setHiddenState(m_windowId, 0);
            m_Client.setWindowActivate(m_windowId);
        }
        else
        {
            if(activateState)
            {
                m_Client.setHiddenState(m_windowId, 1);
            }
            else
            {
                m_Client.setWindowActivate(m_windowId);
            }

        }



    }

    return true;
}

bool CWBox::on_leave(GdkEventCrossing* event)
{
    m_PopOver.popdown();
    m_image.set(m_pixScaleNorm);

    return true;
}




uint32_t & CWBox::getWindowId()
{

    return m_windowId;
}


