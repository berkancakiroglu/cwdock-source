#include "cwmenu.h"




CWMenu::CWMenu(std::string iconPath, std::string configPath, std::size_t iconNorm, std::size_t iconHigh)
    :m_IconPath{iconPath}, m_ConfigPath{configPath}
{
    m_iconHigh = iconHigh;
    m_pixBuffer  = Gdk::Pixbuf::create_from_file(iconPath+"cwapp.svg");
    m_pixScaleNorm  = m_pixBuffer->scale_simple(iconNorm, iconNorm, Gdk::INTERP_BILINEAR);
    m_pixScaleHigh  = m_pixBuffer->scale_simple(iconHigh, iconHigh, Gdk::INTERP_BILINEAR);

    signal_enter_notify_event().connect(sigc::mem_fun(this, &CWMenu::on_over));
    signal_button_release_event().connect(sigc::mem_fun(this, &CWMenu::on_click));
    signal_leave_notify_event().connect(sigc::mem_fun(this, &CWMenu::on_leave));
    m_Image.set(m_pixScaleNorm);
    m_Image.show();
    add(m_Image);
    show();
}

bool CWMenu::is_exist (const std::string& filePath) {
    std::ifstream filew(filePath.c_str());
    return filew.good();
}

bool CWMenu::on_over(GdkEventCrossing* event)
{
    m_Image.set(m_pixScaleHigh);
    return true;
}

bool CWMenu::on_click(GdkEventButton* event)
{
    CWPopup* cwpop = new CWPopup(Gtk::WINDOW_TOPLEVEL);

    std::ifstream confFile(m_ConfigPath);
    std::string line, icon_name;

    while(getline(confFile, line))
    {
        std::string app_name = line.substr(line.find_last_of("/") + 1 );
        if(!is_exist(m_IconPath + app_name + ".svg")){
            icon_name = m_IconPath + "application-default-icon.svg";

        }
        else
        {
            icon_name = m_IconPath + app_name + ".svg";
        }

        cwpop->addApp(app_name , line, Gdk::Pixbuf::create_from_file(icon_name));
        line = "";
    }
    confFile.close();

    if(m_top==false)
    {

        m_ypos = m_ypos - cwpop->getItemSize();
    }

    cwpop->move(m_xpos, m_ypos);

    return true;
}

bool CWMenu::on_leave(GdkEventCrossing* event)
{
    m_Image.set(m_pixScaleNorm);
    return true;
}

void CWMenu::setPosition(std::size_t w, std::size_t h, std::size_t items, bool top)
{

    m_top = top;

    if(m_top==true)
    {
        m_xpos = w/2 - (((items+1) * m_iconHigh)/2);
        m_ypos = m_iconHigh + 8;

    }
    else
    {
        m_xpos = w/2 - (((items+1) * m_iconHigh)/2);
        m_ypos = h - (m_iconHigh+8);
    }

}
