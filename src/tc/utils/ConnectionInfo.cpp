/* Copyright (c) 2013 BlackBerry Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "ConnectionInfo.hpp"
#include <bps/bps.h>
#include <bps/netstatus.h>
#include <bb/cascades/QmlDocument>

namespace tc {
namespace utils {

ConnectionInfo::ConnectionInfo() :
		m_connected(false), m_interfaceName("Unknown"), m_interfaceType(
				ConnectionInfo::Unknown) {
	subscribe(netstatus_get_domain());

	bps_initialize();

	// Request all network status events.
	netstatus_request_events(0);

	info = NULL;
}

ConnectionInfo::~ConnectionInfo() {
	bps_shutdown();
}

void ConnectionInfo::qmlSetup() {
	qmlRegisterType<tc::utils::ConnectionInfo>("tc.utils", 1, 0,
			"ConnectionInfo");
	qmlRegisterUncreatableType<tc::utils::ConnectionInfo>("tc.utils", 1, 0,
			"ConnectionInfoType", "");
}
void ConnectionInfo::event(bps_event_t *event) {
	bool status = false;
	const char* interface = "";
	Type type = Unknown;
	netstatus_interface_details_t* details = NULL;

	// Verify that the event coming in is a network status event.
	if (bps_event_get_domain(event) == netstatus_get_domain()) {
		// Using the BPS event code of the network status event,
		// verify that the event is a network information event.
		if (NETSTATUS_INFO == bps_event_get_code(event)) {
			// Retrieve the network status information, and verify
			// that the procedure is successful.
			if (BPS_SUCCESS == netstatus_get_info(&info)) {
				status = netstatus_info_get_availability(info);
				interface = netstatus_info_get_default_interface(info);
				int success = netstatus_get_interface_details(interface,
						&details);

				if (success == BPS_SUCCESS) {
					switch (netstatus_interface_get_type(details)) {
					case NETSTATUS_INTERFACE_TYPE_WIRED:
						type = Wired;
						break;

					case NETSTATUS_INTERFACE_TYPE_WIFI:
						type = Wifi;
						break;

					case NETSTATUS_INTERFACE_TYPE_BLUETOOTH_DUN:
						type = Bluetooth;
						break;

					case NETSTATUS_INTERFACE_TYPE_USB:
					case NETSTATUS_INTERFACE_TYPE_BB:
						type = Usb;
						break;

					case NETSTATUS_INTERFACE_TYPE_VPN:
						type = VPN;
						break;

					case NETSTATUS_INTERFACE_TYPE_CELLULAR:
						type = Cellular;
						break;

					case NETSTATUS_INTERFACE_TYPE_P2P:
					case NETSTATUS_INTERFACE_TYPE_UNKNOWN:
						type = Unknown;
						break;
					}
					netstatus_free_info(&info);
				}
			}

			// Emit the signal to trigger networkStatusUpdated slot.
			this->setConnected(status);
			this->setInterfaceType(type);
		}
	}
}
bool ConnectionInfo::isConnected() {
	return m_connected;
}
QString ConnectionInfo::interfaceName() {
	return m_interfaceName;
}
tc::utils::ConnectionInfo::Type ConnectionInfo::interfaceType() {
	return m_interfaceType;
}

void ConnectionInfo::setConnected(bool connected) {
	if (connected != m_connected) {
		m_connected = connected;
		emit this->connectedChanged(m_connected);
	}
}

void ConnectionInfo::setInterfaceType(Type interfaceType) {
	if (interfaceType != m_interfaceType) {
		m_interfaceType = interfaceType;
		QString name;
		switch (interfaceType) {
		case ConnectionInfo::Wired:
			name = "Wired";
			break;
		case ConnectionInfo::Wifi:
			name = "Wifi";
			break;
		case ConnectionInfo::Bluetooth:
			name = "Bluetooth";
			break;
		case ConnectionInfo::Usb:
			name = "Usb";
			break;
		case ConnectionInfo::VPN:
			name = "VPN";
			break;
		case ConnectionInfo::Cellular:
			name = "Cellular";
			break;
		default:
			name = "Unknown";
		}
		emit this->interfaceTypeChanged(m_interfaceType);
		m_interfaceName = name;
		emit this->interfaceNameChanged(m_interfaceName);
	}
}
}
}
