#include "cwpopup.h"


CWPopup::CWPopup(Gtk::WindowType type)
    :Window(type)
{
       set_app_paintable(true);
    signal_focus_out_event().connect(sigc::mem_fun(this, &CWPopup::focus_out));
    auto screen = get_screen();
    auto visual = screen->get_rgba_visual();

    setVisual(visual);
    signal_draw().connect(sigc::mem_fun(*this, &CWPopup::onDraw));

    set_border_width(3);
    set_resizable (false);
    set_decorated (false);
    set_skip_taskbar_hint (true);
    set_skip_pager_hint(true);

    //set_position (Gtk::WIN_POS_MOUSE);
    set_events(Gdk::FOCUS_CHANGE_MASK);

    m_Box.set_orientation(Gtk::ORIENTATION_VERTICAL);
    m_Box.set_name("cwMenu");
    add(m_Box);
    m_Box.show();

    show();
    present();
}

bool CWPopup::onDraw(const Cairo::RefPtr<Cairo::Context>& cr)
{

    cr->save();
    cr->set_source_rgba(0.0, 0.0, 0.0, 0.0);
    cr->set_operator(Cairo::OPERATOR_SOURCE);
    cr->paint();
    cr->restore();
    return Gtk::Window::on_draw(cr);
}

void CWPopup::setVisual(Glib::RefPtr<Gdk::Visual> visual)
{
    gtk_widget_set_visual(GTK_WIDGET(gobj()), visual->gobj());
}


CWPopup::~CWPopup()
{
    for(auto &i: m_AppVector)
    {

        delete i;

    }
}

std::size_t CWPopup::getItemSize()
{

    return m_AppVector.size();
}



bool CWPopup::focus_out(GdkEventFocus* gdk_event)
{


    delete this;
    return true;
}

void CWPopup::addApp(const std::string &appName, const std::string &appPath, Glib::RefPtr<Gdk::Pixbuf> pixBuffer)
{
    CWApp* tempApp = new CWApp(appName, appPath, pixBuffer, this);
    m_Box.pack_start(*tempApp);
    m_AppVector.push_back(tempApp);
}

