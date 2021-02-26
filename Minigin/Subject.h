#pragma once

namespace dae
{
	class Observer;
	enum class eventObeserver;
	class GameObject;
	class Subject final
	{
	public:
		Subject();
		~Subject();
		void AddObserver(Observer* observer);
	
		void RemoveObserver(Observer* observer);
	
		void Notify( std::shared_ptr<dae::GameObject> entity, eventObeserver event);

		void Render() const;
	private:
		std::vector<Observer*> m_ObserversVec;
	};
}
