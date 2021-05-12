#pragma once
#include <memory>

#include "Observer.h"
#include "Transform.h"

namespace dae
{

	class GameObject;
	class QBertObserver final: public  Observer
	{
	public:
		QBertObserver(int maxPlatforms);
		~QBertObserver() = default;
		void OnNotify(std::shared_ptr<dae::GameObject> entity, EventObserver event) override;
		void Render() const override;
	private:
		const int m_MaxPlatforms;
		int m_PLatformCounter;
	};
}
