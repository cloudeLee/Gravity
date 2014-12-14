
#ifndef __SINGLETON_H__
#define __SINGLETON_H__

/** ctor and dtor of singletone class  */
#define SINGLETON_INIT(__TYPE__) \
	friend class Singleton<__TYPE__>;  \
protected: \
	__TYPE__(){} \
private: \
	virtual ~__TYPE__(){}


/**
 * Singleton Template Class
 *
 * @see http://blog.tinywolf.com/285
 */
template <class T>
class Singleton
{
public:
	static T& getReference(void)
	{
		static T object;
		return object;
	}
	static T* getInstance(void)
	{
		return &getReference();
	}
	static const T& getConst(void)
	{
		return getReference();
	}

protected:
	Singleton()  {}
	~Singleton() {}

private:
	Singleton(const Singleton&);
	Singleton& operator=(const Singleton&);
};


#endif	//__SINGLETON_H__