#ifndef LAUNCHMAN_H
#define LAUNCHMAN_H
#include "headers.h"
#include <QJsonDocument>
#include <QDirIterator>
#include <QProcess>
#include <QFile>
#include <QMap>

class LaunchMan{

public:
    void launchZpp(const QString &path)
    {

        /* --------------------------------------------------------*/

        // Creates the LD_LIBRARY_PATH data
        QString libraries = ":" + path+ "/Libraries";

        // Looks for libraries in the zpp Libraries folder
        QDirIterator local(path + "/Libraries", QDir::Dirs, QDirIterator::Subdirectories);

        // Loop all folders and subfolders of the Libraries directory
        while (local.hasNext())
        {
            libraries += ":"+ local.next();
        }

        /* --------------------------------------------------------*/


        // Looks for libraries in the System Frameworks folder
        QDirIterator frameworks(SYSTEM_PATH+ "/System/Library/Frameworks", QDir::Dirs, QDirIterator::Subdirectories);

        // Loop all folders and subfolders of the Libraries directory
        while (frameworks.hasNext())
        {
            libraries += ":"+ frameworks.next();
        }


        /* --------------------------------------------------------*/


        // Looks for libraries in the System Libraries folder
        QDirIterator library(SYSTEM_PATH+ "/System/Library/Libraries", QDir::Dirs, QDirIterator::Subdirectories);

        // Loop all folders and subfolders of the Libraries directory
        while (library.hasNext())
        {
            libraries += ":"+ library.next();
        }

        // Export variable
        qputenv("QT_QPA_PLATFORM", "wayland");
        qputenv("LD_LIBRARY_PATH", libraries.toUtf8());


        /* --------------------------------------------------------*/

        // Reads the id file
        QFile info(path + "/Info.id");
        info.open(QFile::ReadOnly);

        // Reads the json
        QJsonDocument doc = QJsonDocument::fromJson(info.readAll());

        // Close the file reader
        info.close();

        // Reads the executable name
        QString ID_EXECUTABLE = doc.toVariant().toMap()["Executable"].toString();


        // Execute app
        QProcess::startDetached(path + "/Executable/" + ID_EXECUTABLE);
    }
};


#endif // LAUNCHMAN_H
