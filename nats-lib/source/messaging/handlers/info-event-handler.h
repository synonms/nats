#ifndef INFOEVENTHANDLER_H
#define INFOEVENTHANDLER_H

#include <nats-lib_global.h>
#include <messaging/handlers/i-event-handler.h>
#include <messaging/i-event-serialiser.h>
#include <networking/isocket.h>
#include <logging/i-logger.h>

#include <memory>

namespace synonms {
namespace nats {
namespace messaging {
namespace handlers {

class NATSLIBSHARED_EXPORT InfoEventHandler : public IEventHandler
{
public:
	InfoEventHandler(std::shared_ptr<logging::ILogger> logger, std::shared_ptr<networking::ISocket> socket, std::shared_ptr<IEventSerialiser> eventSerialiser);
	~InfoEventHandler() override;

	events::EventType type() const override;
	void process(events::Event* event) override;

private:
	class Implementation;
	std::unique_ptr<Implementation> implementation;
};

}}}}

#endif
