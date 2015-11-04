#ifndef MUTEX_H
#define MUTEX_H

#include <pthread.h>

class Mutex {
public:
	Mutex() {
		pthread_mutex_init( &m_mutex, NULL );
	}
	void lock() {
		pthread_mutex_lock( &m_mutex );
	}
	bool trylock() {
		return (0 == pthread_mutex_trylock( &m_mutex ));
	}
	void unlock() {
		pthread_mutex_unlock( &m_mutex );
	}
private:
	pthread_mutex_t m_mutex;
};


#endif
