#include "sessionapp.h"

int main(int argc, char *argv[])
{
    SessionApp app(argc, argv);
    app.init();
    app.start();
    return app.exec();
}
