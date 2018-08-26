#include "master-controller.h"

namespace synonats {
namespace controllers {

class MasterController::Implementation
{
public:
	Implementation(MasterController* _masterController)
		: masterController(_masterController)
	{
	}

	MasterController* masterController{nullptr};
	QString welcomeMessage = "Welcome to synonats!";
};

MasterController::MasterController(QObject* parent)
	: QObject(parent)
{
	implementation.reset(new Implementation(this));
}

MasterController::~MasterController()
{
}

const QString& MasterController::welcomeMessage() const
{
	return implementation->welcomeMessage;
}

}}
