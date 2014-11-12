/* Copyright (c) 2012 Research In Motion Limited.
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

#ifndef PUSHMANAGER_HPP_
#define PUSHMANAGER_HPP_

#include <QObject>

#include <bb/system/InvokeRequest>
#include <bb/network/PushErrorCode>
#include <bb/network/PushService>
#include <bb/network/PushStatus>
#include <bb/system/InvokeManager>

using namespace bb::network;
using namespace bb::system;

class PushManager: public QObject {
Q_OBJECT
public:
	PushManager(InvokeManager* invokeManager);
	virtual ~PushManager();

	enum PushPriority {
		Low = 0, Medium = 1, High = 2
	};

	void updatePushList();

signals:
	void pushListChanged(const QVariantList &pushList);

public slots:
	void clearPushList();
	QByteArray getPayload(const bb::system::InvokeRequest&);

private slots:
	void createSessionCompleted(const bb::network::PushStatus&);
	void createChannelCompleted(const bb::network::PushStatus&, const QString&);
	void onPushTransportReady(const bb::network::PushCommand::Type);

private:

	static const QString BLACKBERRY_PUSH_APPLICATION_ID;
	static const QString BLACKBERRY_PUSH_URL;
	static const QString BLACKBERRY_INVOKE_TARGET_ID;

	PushService* m_pushService; //The service that will handle push registration/reception
	InvokeManager* invokeManager; //Created to handle only push invocations
	QSettings settings; //Persistent store for the app
	QVariantList pushList; //Handle to a usable list of all push messages

	void log(const QString &);
	bool appWasAutoStarted();
	void logPush(const QString &);

};

#endif /* PUSHMANAGER_HPP_ */
