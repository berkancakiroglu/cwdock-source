#include <iostream>
#include <thread>

#include "cwdock.h"
#include "cwclient.h"

void eventLoop(CWClient & client1 ,CWDock& cwDock, Display*display, Window & root)
{


    for (;;)
    {

        XEvent event;
        XNextEvent(display, &event);

        if(event.type == PropertyNotify)
        {

            if(event.xproperty.atom == client1._NET_CLIENT_LIST){
                cwDock.loadVector(client1.getWindows());

            }

        }
    }



}

int main(int argc, char *argv[])
{

    CWClient client1;
    Display *display;
    Window root;

  auto css = Gtk::CssProvider::create();
  if(not css->load_from_path("/opt/CWDock/style.css")) {

      std::exit(1);
  }

    display = XOpenDisplay(NULL);
    root = DefaultRootWindow(display);
    XSelectInput(display, root, PropertyChangeMask);

    XWindowAttributes wndData;
    XGetWindowAttributes(display, root, &wndData);
    std::ifstream confFile("/opt/CWDock/dconf");
    std::string line;
    std::size_t miconNorm;
    std::size_t miconHigh;
    bool mtop;

    getline(confFile, line);
    miconNorm = std::stoi(line);

    getline(confFile, line);
    miconHigh = std::stoi(line);

    getline(confFile, line);
    mtop = std::stoi(line);

    confFile.close();

    auto app = Gtk::Application::create("www.cyber-warrior.org");
    CWDock cwDock(wndData.width, wndData.height, miconNorm, miconHigh, mtop);


      auto screen = Gdk::Screen::get_default();
      Glib::RefPtr< Gtk::StyleContext > 	ctx;
      ctx->add_provider_for_screen(screen, css, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    std::thread loopThread(eventLoop,std::ref(client1), std::ref(cwDock), display, std::ref(root));
    loopThread.detach();

    return app->run(cwDock, argc, argv);
}
