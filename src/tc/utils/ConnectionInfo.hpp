#ifndef STATUSEVENT_HPP_
#define STATUSEVENT_HPP_

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

#include <QObject>
#include <QString>
#include <bb/AbstractBpsEventHandler>
#include <bps/netstatus.h>

namespace tc {
namespace utils {
/* This class forms part of a sample app that demonstrates how to use the
 * Qt networking APIs. This class helps to report on the status of the
 * network connection, and the interface that it's using to make the
 * connection.
 *
 * This class uses BPS APIs to report whether the network connection was
 * made, and the interface used to make the network connection, which
 * can include Wifi, Cellular, BlueTooth, USB, BB, and others. When the
 * status of the network connection or the interface used to make that
 * connection changes, the networkStatusUpdated signal is emitted.
 */
class ConnectionInfo: public QObject, public bb::AbstractBpsEventHandler {
	Q_OBJECT
	Q_ENUMS (Type)
	Q_PROPERTY(bool connected READ isConnected NOTIFY connectedChanged)
	Q_PROPERTY(QString interfaceName READ interfaceName NOTIFY interfaceNameChanged)
	Q_PROPERTY(Type interfaceType READ interfaceType NOTIFY interfaceTypeChanged)
public:
	ConnectionInfo();
	virtual ~ConnectionInfo();
	enum Type {
		Wired, Wifi, Bluetooth, Usb, VPN, Cellular, Unknown
	};
	virtual void event(bps_event_t *event);
	Q_INVOKABLE bool isConnected();
	Q_INVOKABLE QString interfaceName();
	Q_INVOKABLE Type interfaceType();
	static void qmlSetup();
signals:
	void connectedChanged(bool connected);
	void interfaceNameChanged(QString interfaceName);
	void interfaceTypeChanged(tc::utils::ConnectionInfo::Type interfaceType);

private:
	void setConnected(bool connected);
	void setInterfaceType(Type interfaceType);
	netstatus_info_t* info;
	bool m_connected;
	QString m_interfaceName;
	Type m_interfaceType;
};
}
}
#endif /* STATUSEVENT_HPP_ */
