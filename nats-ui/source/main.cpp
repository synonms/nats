#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <iostream>

#include <master-controller.h>
#include <natsclient.h>
#include <networking/qtsocket.h>

int main(int argc, char *argv[])
{
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

	QGuiApplication app(argc, argv);

	qmlRegisterType<synonats::controllers::MasterController>("CM", 1, 0, "MasterController");

	synonats::controllers::MasterController masterController;

	QQmlApplicationEngine engine;
	engine.addImportPath("qrc:/");
	engine.rootContext()->setContextProperty("masterController", &masterController);
	engine.load(QUrl(QStringLiteral("qrc:/views/MasterView.qml")));

	if (engine.rootObjects().isEmpty())
		return -1;

	std::cout << "Creating connection" << std::endl;

	synonms::nats::networking::QtSocket socket;

	socket._connectedEventHandlers.push_back([](){
		std::cout << "CONNECTED!!!" << std::endl;
	});

	socket._disconnectedEventHandlers.push_back([](){
		std::cout << "DISCONNECTED!!!" << std::endl;
	});

	socket._socketErrorEventHandlers.push_back([](std::string&& error){
		std::cout << "Connection Error: " << error << std::endl;
	});

	socket.Connect("127.0.0.1", 4222);
	socket.Disconnect();

//	Nats::Client client;
//	   client.connect("127.0.0.1", 4222, [&]
//	   {
//		   // simple subscribe
//		   client.subscribe("foo", [](QString message, QString inbox, QString subject)
//		   {
//			   qDebug() << "received: " << message << inbox << subject;
//		   });

//		   // simple publish
//		   client.publish("foo", "Hello NATS!");
//	   });

	std::cout << "Connection created" << std::endl;

	return app.exec();
}
