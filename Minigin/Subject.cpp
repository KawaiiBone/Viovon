#include "MiniginPCH.h"
#include "Subject.h"
#include "Observer.h"

dae::Subject::Subject():
	m_ObserversVec{}
{
	std::cout << "a";
}

dae::Subject::~Subject()
{
	for (Observer* pObser : m_ObserversVec)
	{
		delete pObser;
		pObser = nullptr;
	}
}

void dae::Subject::AddObserver(Observer* observer)
{
	m_ObserversVec.push_back(observer);
}

void dae::Subject::RemoveObserver(Observer* observer)
{
	std::vector<Observer*>::iterator it{ m_ObserversVec.begin() };
	for (; it != m_ObserversVec.end(); ++it)
	{
		if (*it == observer)
		{
			break;
		}
	}
	
	m_ObserversVec.erase(it);
	
}

void dae::Subject::Notify(std::shared_ptr<dae::GameObject> entity, EventObeserver event)
{
	for (Observer* pObser: m_ObserversVec)
	{
		pObser->OnNotify(entity, event);
	}
}

void dae::Subject::Render() const
{
	for (Observer* pObser : m_ObserversVec)
	{
		pObser->Render();
	}
}
