#include <QCoreApplication>
#include <QObject>
#include "include/fake_advertiser.h"

FakeAdvertiser* fake_advertiser;

int main(int argc, char *argv[])
{
    QCoreApplication FakeAdvertiser(argc, argv);
    FakeAdvertiser.setApplicationName("MS3-FakeAdvertiser");
    FakeAdvertiser.setApplicationVersion("1.0.0");

    fake_advertiser = new class FakeAdvertiser();

    return FakeAdvertiser.exec();
}
