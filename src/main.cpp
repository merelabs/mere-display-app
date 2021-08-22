#include "displayapp.h"

int main(int argc, char *argv[])
{
    DisplayApp app(argc, argv);
    int err = app.init();
    if (err) ::exit(err);

    err = app.start();
    if (err) ::exit(err);

    return app.exec();

}
