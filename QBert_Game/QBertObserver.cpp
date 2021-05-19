#include "QBertObserver.h"

#include <iostream>
#include "SceneManager.h"
#include "GameObject.h"
#include "Scene.h"
#include "Subject.h"


dae::QBertObserver::QBertObserver(int maxPlatforms):
	m_MaxPlatforms(maxPlatforms), m_PLatformCounter(0)
{
}

void dae::QBertObserver::OnNotify(std::shared_ptr<dae::GameObject> object, EventObserver event)
{
	switch (event)
	{
	case dae::EventObserver::lostPlatform:
		m_PLatformCounter--;
		std::cout << "LostOne!\n";
		break;
	case EventObserver::gainedPlatform:
		m_PLatformCounter++;
		if (m_MaxPlatforms == m_PLatformCounter)
		{
			//TypeOfScene tmpTypeScene{ SceneManager::GetInstance().GetCurrentScene()->GetSceneName() };

		
			std::cout << "victory!\n";//bad
		/*	if (tmpTypeScene != TypeOfScene::level3)
			{
				tmpTypeScene = static_cast<TypeOfScene>(static_cast<int>(tmpTypeScene) + 1);
				SceneManager::GetInstance().ChangeScene(tmpTypeScene);
			}*/
		}
		//gets through when coily is defeated
		break;
	case EventObserver::flyingDisc:
		//gets through when usin a flyingDisc
		break;
	case EventObserver::catchingSlickAndSam:
		//gets through when catchingSlickAndSam 
		break;
	case EventObserver::remainingDisc:
		//gets through when there are at the end  any remainingDisc
		break;
	case EventObserver::none:
		break;
	default:;
	}
}

void dae::QBertObserver::Render() const
{
}
