#ifndef NAV_PROJECT_H
#define NAV_PROJECT_H

#include <QFuture>
#include <QList>
#include <QString>
#include <QStringList>
#include <QSettings>

#include <memory>
#include <vector>
#include <stdint.h>

#include "../libindexdb/IndexDb.h"
#include "File.h"

namespace indexdb {
    class Index;
    class StringTable;
    class Table;
}

namespace Nav {

class Project;
class FileManager;
class Ref;

extern std::unique_ptr<Project> theProject;

class Project
{
public:
    explicit Project(const QString &indexPath, QSettings &settings);
    ~Project();
    FileManager &fileManager() { return *m_fileManager; }

    QList<Ref> queryReferencesOfSymbol(const QString &symbol);
    void queryAllSymbols(std::vector<const char*> &output);
    QStringList queryAllPaths();
    Ref findSingleDefinitionOfSymbol(const QString &symbol);
    indexdb::ID fileID(const QString &path);
    QString fileName(indexdb::ID fileID);
    const char *fileNameCStr(indexdb::ID fileID);
    const std::vector<Ref> &globalSymbolDefinitions();
    template <typename Func> void queryFileRefs(
            File &file,
            Func callback,
            uint32_t firstLine = 0,
            uint32_t lastLine = static_cast<uint32_t>(-1));
    indexdb::ID querySymbolType(indexdb::ID symbolID);
    indexdb::ID getSymbolTypeID(const char *symbolType);
    const char *getSymbolType(indexdb::ID symbolTypeID);

    indexdb::StringTable &symbolStringTable() { return *m_symbolStringTable; }
    indexdb::StringTable &refTypeStringTable() {
        return *m_refTypeStringTable;
    }

private:
    std::vector<Ref> *queryGlobalSymbolDefinitions();

private:
    const QString m_indexPath;
    QSettings &m_settings;
    FileManager *m_fileManager;
    indexdb::Index *m_index;
    indexdb::StringTable *m_symbolStringTable;
    indexdb::StringTable *m_symbolTypeStringTable;
    indexdb::StringTable *m_refTypeStringTable;
    indexdb::Table *m_refTable;
    indexdb::Table *m_refIndexTable;
    indexdb::Table *m_symbolTable;
    indexdb::Table *m_symbolTypeIndexTable;
    indexdb::Table *m_globalSymbolTable;
    QFuture<std::vector<Ref>*> m_globalSymbolDefinitions;
    std::vector<indexdb::ID> m_symbolType;
};

// Reference table
enum RefColumn {
    RC_File         = 0,
    RC_Line         = 1,
    RC_StartColumn  = 2,
    RC_EndColumn    = 3,
    RC_Symbol       = 4,
    RC_RefType      = 5,
    RC_Count        = 6
};

// ReferenceIndex table
enum RefIndexColumn {
    RIC_Symbol      = 0,
    RIC_RefType     = 1,
    RIC_File        = 2,
    RIC_Line        = 3,
    RIC_StartColumn = 4,
    RIC_EndColumn   = 5,
    RIC_Count       = 6
};

// Symbol table
enum SymbolColumn {
    SC_Symbol       = 0,
    SC_SymbolType   = 1,
    SC_Count        = 2
};

} // namespace Nav

#endif // NAV_PROJECT_H
