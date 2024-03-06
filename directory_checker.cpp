/*!
 * \file directory_checker.cpp
 * \brief file for the definition of the class "DirectoryChecker"
 * \author doga
 * \date 2024-3-6
 *
 * \details
 *
 * \copyright
 ****************************************************************************
 *        Ce logiciel est la propriete de DOGA®.
 *         -------------------------------------
 *
 *    Il ne peut etre reproduit ni communique en totalite ou partie sans
 *    son autorisation ecrite.
 *
 ****************************************************************************
 *        This software is the property of DOGA®.
 *         -------------------------------------
 *
 *    It cannot be reproduced nor disclosed entirely or partially without
 *    a written agreement.
 *
 ****************************************************************************
 */

#include "directory_checker.h"

#include <QDir>
#include <QFileInfo>
#include <QObject>
#include <QStorageInfo>
#include <QString>

DirectoryChecker::DirectoryChecker(const QString & path)
    : QObject{nullptr}
    , m_path(path)
{}

DirectoryChecker::~DirectoryChecker()
{}

void DirectoryChecker::checkMounting()
{
    bool isMounted = false;
    QFileInfo fi(m_path);
    if (fi.exists() && fi.isDir()) {
        QDir dir(m_path);
        QStorageInfo storage(dir);
        storage.refresh();
        if (storage.isValid()) {
            if (storage.isReady()) {
                QString storageRootPath = storage.rootPath();
                QString canonicalPath(dir.canonicalPath());
                if (QDir(canonicalPath).exists()) {
                    isMounted = (storageRootPath == canonicalPath);
                }
            }
        }
    }
    emit directoryChecked(isMounted);
}
