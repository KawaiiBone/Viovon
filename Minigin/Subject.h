#pragma once

namespace dae
{


	enum class EventObserver
	{
		died,
		healthChanged,
		scoreChaned,
		defeatingCoily,
		flyingDisc,
		remainingDisc,
		catchingSlickAndSam,
		none,
	};






	enum class InterFaceNames
	{
		start,
		howToPlay,
		buttons,
		modes,
		none,
	};


	
	class Observer;
//	enum class EventObserver;
	class GameObject;
	class Subject final
	{
	public:
		Subject();
		~Subject();
		void AddObserver(Observer* observer);
	
		void RemoveObserver(Observer* observer);
	
		void Notify( std::shared_ptr<dae::GameObject> entity, EventObserver event);

		void Render() const;
	private:
		std::vector<Observer*> m_ObserversVec;
	};
}
