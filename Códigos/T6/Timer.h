#ifndef TIMER_H
#define TIMER_H

// Classe "Timer"
class Timer {
	private:
		float time;

	public:
		Timer();
		void Restart();
		void Update(float dt);
		float Get();
};

#endif // TIMER_H
