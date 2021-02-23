#include "MiniginPCH.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "FPSComponent.h"

dae::GameObject::GameObject(float x, float y, RenderComponent * pRender)
	:m_pRender{ pRender }, m_VectorpBComponents{  }, m_IsDead{false}
	
{
	
	m_Transform.SetPosition(x, y, 0.0f);
}

dae::GameObject::GameObject(float x, float y, std::vector<BaseComponent*> bvComp, RenderComponent* pRender)
	: m_pRender{ pRender }, m_VectorpBComponents{ bvComp }, m_IsDead{ false }
{
	m_Transform.SetPosition(x, y, 0.0f);
}

dae::GameObject::GameObject(float x, float y, BaseComponent* bvComp, RenderComponent* pRender)
	: m_pRender{ pRender }, m_VectorpBComponents{ bvComp }, m_IsDead{ false }
{
	m_Transform.SetPosition(x, y, 0.0f);
}



void dae::GameObject::Update(float deltaTime)
{
	//renders all the components
	for (auto pBaseComp: m_VectorpBComponents)
	{
		pBaseComp->Update(deltaTime);
	}


	
	if (m_VectorpBComponents.size() > 0)
	{
		m_pRender->Update(m_VectorpBComponents.front()->GetTxt());
	}
	else
	{
		m_pRender->Update("0");
	}
	//std::cout << deltaTime;
	
}

void dae::GameObject::Render() const
{
	//update
	m_pRender->Render(m_Transform.GetPosition().x, m_Transform.GetPosition().y);
}

void dae::GameObject::AddComponent(BaseComponent* myComponent)
{
	if (myComponent)
	{
		m_VectorpBComponents.push_back({ myComponent });
	}
	else
	{
		std::cout << "Something went wrong when adding the componenent (probably is a nullptr)\n";
	}
}

bool dae::GameObject::IsDead()
{
	return m_IsDead;
}

void dae::GameObject::Die()
{
	m_IsDead = true;
	
}


dae::GameObject::~GameObject()
{
	delete m_pRender;
	m_pRender = nullptr;
	for (auto pBaseComp : m_VectorpBComponents)
	{
		delete pBaseComp;
		pBaseComp = nullptr;
	}
	m_VectorpBComponents.clear();
	
}
