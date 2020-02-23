#include "cwapp.h"


CWApp::CWApp(std::string appName, std::string appPath, Glib::RefPtr<Gdk::Pixbuf> pixBuffer, Gtk::Window *window)
    :m_appPath(appPath), m_Window(window)
{

    signal_button_release_event().connect(sigc::mem_fun(this, &CWApp::on_click));

    m_Label.set_text(appName);
    m_Image.set(pixBuffer->scale_simple(24, 24, Gdk::INTERP_BILINEAR));
    m_Box.pack_start(m_Image,Gtk::PACK_SHRINK);
    m_Box.pack_start(m_Label,Gtk::PACK_SHRINK);
    add(m_Box);
    m_Image.show();
    m_Label.show();
    m_Box.show();
    show();

}
#include <thread>
bool CWApp::on_click(GdkEventButton* event){

    if(event->type == GDK_BUTTON_RELEASE)
    {

    std::thread t1([&] {system(m_appPath.c_str());});
    t1.detach();



 /*
 //test
 pid_t p = fork();
        if(p==0)
        {

            system(m_appPath.c_str());
            //execvp(m_appPath.c_str(), 0);
        }
*/

        delete m_Window;

    }
    return true;
}
