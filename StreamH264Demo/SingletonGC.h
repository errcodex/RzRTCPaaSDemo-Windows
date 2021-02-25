#pragma once
#include <mutex>

/* 
 * µ¥ÀýÄ£°åÀà
 * -------------------------------
 * using: 
 * class MySingleton : public SingletonBase<MySingleton>
 * typedef SingletonGC<MySingleton> My;
 * My::instance();
 * -------------------------------
 * notice that subclasses should set the access permission
 * of constructor as private or protected.
 * 
 */
template <typename T>
class SingletonGC
{
public:
	static T* instance()
	{
		std::lock_guard<std::mutex> lck(mutex);
		if (!m_instance)
			m_instance = new T;
		return m_instance;
	}

	void static release()
	{
		std::lock_guard<std::mutex> lck(mutex);
		if (m_instance)
			delete m_instance;
		m_instance = nullptr;
	}

	void static instanceLock(void (*cb)(T*))
	{
		std::lock_guard<std::mutex> lck(mutex);
		if (!m_instance)
			m_instance = new T;
		cb(m_instance);
	}

protected:
	SingletonGC() = default;
	virtual ~SingletonGC() = default;

private:
	static T* m_instance;
	static std::mutex mutex;
};

template <typename T>
T* SingletonGC<T>::m_instance = nullptr;

template <typename T>
std::mutex SingletonGC<T>::mutex;


template <typename T>
class SingletonBase
{
	friend class SingletonGC<T>;
protected:
	SingletonBase() = default;
	virtual ~SingletonBase() = default;

private:
	SingletonBase& operator=(const SingletonBase&) = delete;
	SingletonBase(const SingletonBase&) = delete;
};