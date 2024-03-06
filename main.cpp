/*!
 * \file main.cpp
 * \brief file for the definition of the main function
 * \author doga
 * \date 2024-3-5
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
#include <QCoreApplication>
#include <QDebug>

#include "my_dir.h"


int main(int argc, char * argv[]) {
    QCoreApplication a(argc, argv);

    if (argc != 2) {
        qDebug() << "Usage: " << argv[0] << " <mountPoint>";
        return 1;
    }

    QString mountPoint = argv[1];

    MyDir dir{mountPoint, & a};

    return a.exec();
}
