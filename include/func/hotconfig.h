#include <iostream>
#include <fstream>
#include <memory>
#include <atomic>
#include <unordered_map>
#include <mutex>

enum ENUM_CFG_TYPE
{
    CFG_TYPE_GAMESERVER = 0,
};

// GameServer 配置结构
struct GameServer_Configuration {
    int DealAppWinMinSize;
    int DealAppHideState;
    int DealReduseFrame;
    int ReduseFrameInterval;
    int DealReduseRegion;
    int DealMsgLogInterval;
};

class ConfigurationManager {
public:
    static ConfigurationManager& Instance() {
        static ConfigurationManager s_inc;
        return s_inc;
    }

    ConfigurationManager(const ConfigurationManager&) = delete;
    ConfigurationManager& operator=(const ConfigurationManager&) = delete;

public:
    std::shared_ptr<GameServer_Configuration> GetGSCfg() const {
        return std::atomic_load(&config_);
    }

    void Reload() {

        std::ifstream file(configFile_);
        if (!file.is_open()) {
            throw std::runtime_error("Configuration file not found: " + configFile_);
        }

        std::unique_ptr<GameServer_Configuration> newConfig(new GameServer_Configuration);

        std::unordered_map<std::string, int*> configMap = {
            {"DealAppWinMinSize", &newConfig->DealAppWinMinSize},
            {"DealAppHideState", &newConfig->DealAppHideState},
            {"DealReduseFrame", &newConfig->DealReduseFrame},
            {"ReduseFrameInterval", &newConfig->ReduseFrameInterval},
            {"DealReduseRegion", &newConfig->DealReduseRegion},
            {"DealMsgLogInterval", &newConfig->DealMsgLogInterval}
        };

        std::string line;
        while (std::getline(file, line)) {
            size_t pos = line.find('=');
            if (pos != std::string::npos) {
                std::string key = line.substr(0, pos);
                std::string valueStr = line.substr(pos + 1);
                if (configMap.find(key) != configMap.end()) {
                    *(configMap[key]) = std::stoi(valueStr);
                }
            }
        }

        if (file.fail() && !file.eof()) {
            throw std::runtime_error("Failed to read configuration from file: " + configFile_);            
        }

        file.close();

        // 在更新配置之前获取互斥锁
        std::shared_ptr<GameServer_Configuration> pCfg(std::move(newConfig));
        std::atomic_store(&config_, pCfg);
        ++loadCount_;       
    }

private:
    ConfigurationManager() : configFile_("hot_switch.cfg"), loadCount_(0) {
        Reload();
    }

    std::shared_ptr<GameServer_Configuration> config_;
    std::string configFile_;
    int loadCount_;
    ENUM_CFG_TYPE type_; 
};

