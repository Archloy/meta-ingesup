#include <QCoreApplication>
#include <QDebug>
#include <QFile>

QString readValueFromFile(QString filePath)
{
    QString data;
    QStringList response;

    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly))
    {
        data = file.readAll();
        response = data.split("t=");
        data.remove(data.length() - 1, 1);
        data = response.at(1);
        file.close();
    }

    return data;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString temp = readValueFromFile("/sys/bus/w1/devices/28-000008cd2c5c/w1_slave");

    qDebug() << temp.toInt() / 1000.0;

    return 0;
}

