#include "MiniginPCH.h"
#include "GameObject.h"
#include "ComponentsHeaders.h"
#include  "Observer.h"

dae::GameObject::GameObject(float x, float y, RenderComponent * pRender)
	:m_pRender{ pRender }, m_VectorpBComponents{  }, m_IsDead{ false }, m_Velocity{0,0,0}
{
	
	m_Pos.SetPosition(x, y, 0.0f);
}

dae::GameObject::GameObject(float x, float y, std::vector<BaseComponent*> bvComp, RenderComponent* pRender)
	: m_pRender{ pRender }, m_VectorpBComponents{ bvComp }, m_IsDead{ false }, m_Velocity{ 0,0,0 }
{
	m_Pos.SetPosition(x, y, 0.0f);
}

dae::GameObject::GameObject(float x, float y, BaseComponent* bvComp, RenderComponent* pRender)
	: m_pRender{ pRender }, m_VectorpBComponents{ bvComp }, m_IsDead{ false }
{
	m_Pos.SetPosition(x, y, 0.0f);
}



void dae::GameObject::Update(float deltaTime)
{
	//renders all the components
	for (auto pBaseComp: m_VectorpBComponents)
	{
		pBaseComp->Update(deltaTime, *this);
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
	m_pRender->Render(m_Pos.GetPosition().x, m_Pos.GetPosition().y);
	m_subject.Render();
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

void dae::GameObject::SetMovement(float x, float y)
{
	m_Pos.SetPosition(m_Pos.GetPosition().x + x, m_Pos.GetPosition().y + y, m_Pos.GetPosition().z);
}


bool dae::GameObject::IsDead() const
{
	return m_IsDead;
}

void dae::GameObject::Die()
{
	m_IsDead = true;
	
}

void dae::GameObject::SetVelocity(Transform vel)
{
	m_Velocity = vel;
}


dae::Transform dae::GameObject::GetVelocity() const
{
	return m_Velocity;
}

dae::Subject& dae::GameObject::GetSubject()  
{
	return m_subject;
}

void dae::GameObject::AddObeserver(Observer* pObs)
{
	m_subject.AddObserver(pObs);
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
