#ifndef CONFIG_H
#define CONFIG_H

#include "mere/config/kvconfig.h"

#include <QColor>
#include <QPixmap>

class Config : public Mere::Config::KVConfig
{
    explicit Config();
    explicit Config(const std::string &path, const Mere::Config::Spec::Strict &strict = Mere::Config::Spec::Strict::Soft);

public:
    int init();
    int validate() const;

    std::string screenBackground() const;
    bool checkScreenBackground() const;

    QColor screenBackgroundColor() const;
    bool checkScreenBackgroundColor() const;

    QPixmap screenBackgroundImage() const;
    bool checkScreenBackgroundImage() const;

    bool logoshow() const;
    bool checkScreenLogoShow() const;

    std::string logo() const;
    bool checkScreenLogo() const;

    static Config* instance(const std::string &path = "mere/display.conf", const Mere::Config::Spec::Strict &strict = Mere::Config::Spec::Strict::Soft)
    {
        static Config *instance = new Config(path, strict);

        return instance;
    }

private:
    bool checkBackground(const std::string &key) const;
    bool checkColor(const std::string &key, const std::string &color) const;

    bool checkLogo(const std::string &key) const;
    bool checkImage(const std::string &key, const std::string &path) const;

    bool checkInt(const std::string &key) const;
    bool checkBool(const std::string &key) const;
    bool checkKey(const std::string &key, std::string &value, bool &set) const;

    bool checkColor(const std::string &key) const;
    bool checkImage(const std::string &key) const;
};

#endif // CONFIG_H
