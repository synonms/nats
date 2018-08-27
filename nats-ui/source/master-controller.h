#ifndef MASTERCONTROLLER_H
#define MASTERCONTROLLER_H

#include <QObject>
#include <QScopedPointer>
#include <QString>

namespace synonms {
namespace nats {
namespace controllers {

class MasterController : public QObject
{
	Q_OBJECT

public:
	explicit MasterController(QObject* parent = nullptr);
	~MasterController();

public slots:
	void connect();
	void disconnect();

private:
	class Implementation;
	QScopedPointer<Implementation> implementation;
};

}}}

#endif
