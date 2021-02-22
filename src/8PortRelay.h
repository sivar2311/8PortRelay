#ifndef _RELAYARRAY8_H_
#define _RELAYARRAY8_H_

#include <SinricProDevice.h>
#include <Capabilities/ToggleController.h>

class RelayArray8 
: public SinricProDevice
, public ToggleController<RelayArray8> {
  friend class ToggleController<RelayArray8>;
public:
  RelayArray8(const DeviceId &deviceId) : SinricProDevice(deviceId, "RelayArray8") {};
};

#endif
