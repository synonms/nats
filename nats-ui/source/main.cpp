#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <iostream>

#include <master-controller.h>
#include <networking/qtsocket.h>

int main(int argc, char *argv[])
{
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

	QGuiApplication app(argc, argv);

	qmlRegisterType<synonms::nats::controllers::MasterController>("CM", 1, 0, "MasterController");

	synonms::nats::controllers::MasterController masterController;

	QQmlApplicationEngine engine;
	engine.addImportPath("qrc:/");
	engine.rootContext()->setContextProperty("masterController", &masterController);
	engine.load(QUrl(QStringLiteral("qrc:/views/MasterView.qml")));

	if (engine.rootObjects().isEmpty())
		return -1;

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

	return app.exec();
}
