#include "config.h"

#include "mere/utils/stringutils.h"
#include "mere/utils/fileutils.h"

#include <iostream>
#include <QApplication>

static const std::string KEY_SCREEN_LOGO             = "mere.display.screen.logo";
static const std::string VAL_SCREEN_LOGO             = "/usr/local/share/mere/display/mere-logo.png";

static const std::string KEY_SCREEN_LOGO_SHOW        = "mere.display.screen.logo.show";
static const std::string VAL_SCREEN_LOGO_SHOW        = "true";

static const std::string KEY_SCREEN_BACKGROUND       = "mere.display.screen.background";
static const std::string VAL_SCREEN_BACKGROUND       = "#0B6623";

static const std::string KEY_SCREEN_BACKGROUND_COLOR = "mere.display.screen.background.color";
static const std::string KEY_SCREEN_BACKGROUND_IMAGE = "mere.display.screen.background.image";

Config::Config():
    Config::Config("mere/display.conf", Mere::Config::Spec::Strict::Soft)
{
}

Config::Config(const std::string &path, const Mere::Config::Spec::Strict &strict) :
    Mere::Config::KVConfig(path, strict)
{
}

int Config::validate() const
{
    int err = 0;

    std::cout << qApp->translate("DisplayConfig", "DisplayConfigValueCheck").toStdString() << std::endl,

    err = checkScreenLogo()            ? err : 1;
    err = checkScreenLogoShow()        ? err : 1;
    err = checkScreenBackground()      ? err : 1;
    err = checkScreenBackgroundColor() ? err : 1;
    err = checkScreenBackgroundImage() ? err : 1;

    if(err)
        std::cout << qApp->translate("DisplayConfig", "DisplayConfigCheckFailed").toStdString() << std::endl;

    return err;
}

std::string Config::screenBackground() const
{
    std::string value = this->get(KEY_SCREEN_BACKGROUND);
    if (value.empty()) return VAL_SCREEN_BACKGROUND;

    return value;
}

bool Config::checkScreenBackground() const
{
    return checkBackground(KEY_SCREEN_BACKGROUND);
}

QColor Config::screenBackgroundColor() const
{
    std::string value = this->get(KEY_SCREEN_BACKGROUND_COLOR);
    if (value.empty())
    {
        value = this->get(KEY_SCREEN_BACKGROUND);
        if (!value.empty())
        {
            auto parts = Mere::Utils::StringUtils::split(value, '|');
            if (parts.size() > 0)
                value = Mere::Utils::StringUtils::trim(parts.at(0));
        }
    }

    if (value.empty() || value.at(0) != '#')
        return QColor(QString::fromStdString(VAL_SCREEN_BACKGROUND));

    QColor color(QString::fromStdString(value));
    if(!color.isValid()) return QColor(QString::fromStdString(VAL_SCREEN_BACKGROUND));

    return color;
}

bool Config::checkScreenBackgroundColor() const
{
    return checkColor(KEY_SCREEN_BACKGROUND_COLOR);
}

QPixmap Config::screenBackgroundImage() const
{
    std::string value = this->get(KEY_SCREEN_BACKGROUND_IMAGE);
    if (value.empty())
    {
        value = this->get(KEY_SCREEN_BACKGROUND);
        if (!value.empty())
        {
            auto parts = Mere::Utils::StringUtils::split(value, '|');
            if (parts.size() > 1)
                value = Mere::Utils::StringUtils::trim(parts.at(1));
        }
    }

    if (value.empty() || value.at(0) != '/')
        return QPixmap();

    if(Mere::Utils::FileUtils::isNotExist(value))
        return QPixmap();

    return QPixmap(QString::fromStdString(value));
}

bool Config::checkScreenBackgroundImage() const
{
    return checkImage(KEY_SCREEN_BACKGROUND_IMAGE);
}

bool Config::logoshow() const
{
    std::string value = this->get(KEY_SCREEN_LOGO_SHOW);
    if (value.empty()) return true;

    return Mere::Utils::StringUtils::isTrue(value);
}

bool Config::checkScreenLogoShow() const
{
    return checkBool(KEY_SCREEN_LOGO_SHOW);
}

std::string Config::logo() const
{
    std::string value = this->get(KEY_SCREEN_LOGO);
    if (value.empty()) return VAL_SCREEN_LOGO;

    return value;
}

bool Config::checkScreenLogo() const
{
    return checkLogo(KEY_SCREEN_LOGO);
}

bool Config::checkBackground(const std::string &key) const
{
    bool set =false;
    std::string value;
    if(!checkKey(key, value, set))
        return false;

    if (!set) return true;

    if(value.at(0) == '#')
        return checkColor(key, value);
    else if(value.at(0) == '/')
        return checkImage(key, value);

    std::cout << qApp->translate("DisplayConfig", "DisplayConfigValueInvalid").arg(key.c_str()).arg(value.c_str()).toStdString() << std::endl;

    return false;
}

bool Config::checkColor(const std::string &key, const std::string &color) const
{
    QColor c(QString::fromStdString(color));
    if (!c.isValid())
    {
        std::cout << qApp->translate("DisplayConfig", "DisplayConfigValueInvalidColor").arg(key.c_str()).arg(color.c_str()).toStdString() << std::endl;

        return false;
    }

    return true;
}

bool Config::checkLogo(const std::string &key) const
{
    bool set;
    std::string value;
    if(!checkKey(key, value, set))
        return false;

    if (!set) return true;

    return checkImage(key, value);
}

bool Config::checkImage(const std::string &key, const std::string &path) const
{
    if(Mere::Utils::FileUtils::isNotExist(path))
    {
        std::cout << qApp->translate("DisplayConfig", "DisplayConfigValueInvalidFile").arg(key.c_str()).arg(path.c_str()).toStdString() << std::endl;

        return false;
    }

    QPixmap pixmap(QString::fromStdString(path));
    if(pixmap.isNull())
    {
        std::cout << qApp->translate("DisplayConfig", "DisplayConfigValueInvalidImage").arg(key.c_str()).arg(path.c_str()).toStdString() << std::endl;

        return false;
    }

    return true;
}

bool Config::checkInt(const std::string &key) const
{
    bool set;
    std::string value;
    if(!checkKey(key, value, set))
        return false;

    if (!set) return true;

    return Mere::Utils::StringUtils::toInt(value);
}

bool Config::checkBool(const std::string &key) const
{
    bool set;
    std::string value;
    if(!checkKey(key, value, set))
        return false;

    if (!set) return true;

    return Mere::Utils::StringUtils::isBoolean(value);
}

bool Config::checkColor(const std::string &key) const
{
    bool set;
    std::string value;
    if(!checkKey(key, value, set))
        return false;

    if (!set) return true;

    QColor color(QString::fromStdString(value));
    return color.isValid();
}

bool Config::checkImage(const std::string &key) const
{
    bool set;
    std::string value;
    if(!checkKey(key, value, set))
        return false;

    if (!set) return true;

    if (value.at(0) != '/')
        return false;

    if(Mere::Utils::FileUtils::isNotExist(value))
        return false;

    QPixmap pixmap(QString::fromStdString(value));

    return !pixmap.isNull();
}

bool Config::checkKey(const std::string &key, std::string &value, bool &set) const
{
    value = this->get(key, &set);
    if (set)
    {
        value = Mere::Utils::StringUtils::trim(value);
        if (value.empty())
        {
            std::cout << qApp->translate("DisplayConfig", "DisplayConfigValueEmpty").arg(key.c_str()).toStdString() << std::endl;

            return false;
        }
    }

    return true;
}
