/*!
 * \file directory_checker.h
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

#ifndef DIRECTORY_CHECKER_H
#define DIRECTORY_CHECKER_H

#include <QObject>
#include <QString>

class DirectoryChecker : public QObject
{
    Q_OBJECT
public:
    explicit    DirectoryChecker        (const QString & path);
    virtual     ~DirectoryChecker       ();

public slots:
    void        checkMounting           ();

signals:
    void        directoryChecked        (bool isMounted);

private:
    QString     m_path;
};

#endif // DIRECTORY_CHECKER_H
