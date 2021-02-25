#pragma once
#include "SingletonGC.h"
#include <QObject>
class SlotMgrSingleton;
typedef SingletonGC<SlotMgrSingleton> SlotMgr;

// ÐÅºÅ´«µÝµ¥Àý
class SlotMgrSingleton : public QObject, public SingletonBase<SlotMgrSingleton>
{
	friend SlotMgr;
	Q_OBJECT

public:
signals:
	void YuvData(const QByteArray& arr, const uint w, const uint h) const;
	void RemoteYuvData(const QByteArray& arr, const uint w, const uint h) const;
	void RemoteH264Data(const QByteArray& arr, const uint w, const uint h) const;

private:
	SlotMgrSingleton() = default;
};
