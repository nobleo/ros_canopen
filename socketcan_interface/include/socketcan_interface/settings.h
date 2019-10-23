#ifndef SOCKETCAN_INTERFACE_SETTINGS_H
#define SOCKETCAN_INTERFACE_SETTINGS_H

#include <map>
#include <string>
#include <boost/lexical_cast.hpp>

namespace can {
  class Settings
  {
  public:
      template <typename T> T get_optional(const std::string &n, const T& def) const {
          std::string repr;
          if(!getRepr(n, repr)){
              return def;
          }
          return boost::lexical_cast<T>(repr);
      }
      template <typename T> bool get(const std::string &n, T& val) const {
          std::string repr;
          if(!getRepr(n, repr)) return false;
          val =  boost::lexical_cast<T>(repr);
          return true;
      }
      virtual ~Settings() {}
  private:
    virtual bool getRepr(const std::string &n, std::string & repr) const = 0;
  };

  class NoSettings : public Settings {
  private:
      virtual bool getRepr(const std::string &n, std::string & repr) const { return true; }
  };

  class SettingsMap : public Settings {
    std::map<std::string, std::string> settings_;
    virtual bool getRepr(const std::string &n, std::string & repr) const {
      std::map<std::string, std::string>::const_iterator it = settings_.find(n);
      if (it == settings_.cend()) return false;
      repr = it->second;
      return true;
    }
  public:
    template <typename T> void set(const std::string &n, T& val) {
        settings_[n] = boost::lexical_cast<std::string>(val);
    }
  };

} // can

#endif
