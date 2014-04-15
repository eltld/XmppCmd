#include <QCoreApplication>

#include <SystemEngine.hpp>
#include <SystemConfig.hpp>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QString configFile("");
    foreach (QString option, app.arguments())
    {
        if (option.startsWith("--config"))
            configFile = option.mid(strlen("--config") + 1);
    }

    SystemConfig::initialize(configFile);
    SystemEngine::initialize();
//    Console console;
//    forever
//    {
//        std::string input;
//        std::getline( std::cin, input);

//        console.WriteChildStdIn(QString(input.c_str()));
//    }

    return app.exec();
}
