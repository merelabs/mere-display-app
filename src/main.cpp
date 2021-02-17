#include "displayapp.h"

int main(int argc, char *argv[])
{
    DisplayApp app(argc, argv);
    app.init();
    app.start();
    return app.exec();
}
