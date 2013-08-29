#ifndef SCRIPTMGR_H
#define SCRIPTMGR_H

#include <QtCore>
#include "utils/singleton.h"

class ScriptObject
{
    friend class ScriptMgr;

public:
    ScriptObject(const QString& name) : m_name(name) {}
    virtual ~ScriptObject() {}

    const QString& GetName() const { return m_name; }

private:
    const QString m_name;
};

class ServerScript : public ScriptObject
{
public:
    ServerScript(const QString& name);

    // Hook test
    virtual void OnLoad() {}
};

class ScriptMgr : public Singleton<ScriptMgr>
{
    friend class ScriptObject;

public:
    ScriptMgr();
    ~ScriptMgr();

    void Initialize();

    // ServerScript hooks
    void OnLoad();

private:
};

#endif // SCRIPTMGR_H
