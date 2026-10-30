#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <QString>
#include <QMap>

class ConfigManager
{
public:
    ConfigManager() = default;

    // Paths
    static const QString &configPath();
    static const QString &profilePath();
    static const QString &backupDir();

    // Reading
    bool load();
    bool loadProfile();
    bool configExists() const;

    // Writing
    bool save();
    bool saveProfile();
    bool restoreFromProfile();

    // Flag management
    void setFlag(const QString &key, const QString &value);
    void removeFlag(const QString &key);
    QString getFlag(const QString &key) const;
    void clearFlags();

    // Access
    const QMap<QString, QString> &flags() const { return m_flags; }
    bool useOpenGL() const { return m_useOpenGL; }
    void setUseOpenGL(bool v) { m_useOpenGL = v; }

    // Presets
    void applyLowEndPreset();
    void applyBalancedPreset();
    void applyHighEndPreset();

    const QString &lastError() const { return m_lastError; }

private:
    QMap<QString, QString> m_flags;
    bool m_useOpenGL = false;
    QString m_lastError;
};

#endif
