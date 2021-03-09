#include "MiniginPCH.h"
#include "GameObject.h"
#include "ComponentsHeaders.h"
#include  "Observer.h"

dae::GameObject::GameObject(float x, float y)
	:m_pRenderComponent{ nullptr }, m_VectorpBComponents{  }, m_IsDead{ false }, m_Velocity{ 0,0,0 }, m_VectorCombinedComponents{}
{
	m_Pos.SetPosition(x, y, 0.0f);
}

dae::GameObject::GameObject(float x, float y, RenderComponent * pRender)
	:m_pRenderComponent{ pRender }, m_VectorpBComponents{  }, m_IsDead{ false }, m_Velocity{0,0,0}, m_VectorCombinedComponents{}
{
	
	m_Pos.SetPosition(x, y, 0.0f);
}

dae::GameObject::GameObject(float x, float y, std::vector<BaseComponent*> bvComp, RenderComponent* pRender)
	: m_pRenderComponent{ pRender }, m_VectorpBComponents{ bvComp }, m_IsDead{ false }, m_Velocity{ 0,0,0 }, m_VectorCombinedComponents{}
{
	m_Pos.SetPosition(x, y, 0.0f);
}

dae::GameObject::GameObject(float x, float y, BaseComponent* bvComp, RenderComponent* pRender)
	: m_pRenderComponent{ pRender }, m_VectorpBComponents{ bvComp }, m_IsDead{ false }, m_VectorCombinedComponents{}
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


	
	for (auto pPairComp : m_VectorCombinedComponents)
	{
		pPairComp.second->Update(deltaTime, *this);
		pPairComp.first->Update(pPairComp.second->GetTxt());
	}
	

	if (m_pRenderComponent)
	{
		
		m_pRenderComponent->Update("0");
	}
	
}

void dae::GameObject::Render() const
{
	for (auto pPairComp: m_VectorCombinedComponents)
	{
		pPairComp.first->Render(m_Pos.GetPosition().x, m_Pos.GetPosition().y);
	}
	
	if (m_pRenderComponent)
	{
		m_pRenderComponent->Render(m_Pos.GetPosition().x, m_Pos.GetPosition().y);
	}
	
	for (auto pBaseComp : m_VectorpBComponents)
	{
		pBaseComp->SubjectRender();
	}
	
}

void dae::GameObject::AddBaseComponent(BaseComponent* myComponent)
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

void dae::GameObject::AddRenderComponent(RenderComponent* RenderComponent)
{
	if (!m_pRenderComponent)
	{
		m_pRenderComponent = RenderComponent;
	}
}

void dae::GameObject::AddPairComponent(RenderComponent* RenderComponent, BaseComponent* myComponent)
{
	m_VectorCombinedComponents.push_back({ RenderComponent, myComponent });
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

void dae::GameObject::SetVelocity(float x, float y)
{
	if (x == 0)
	{
		m_Velocity.SetPosition(m_Velocity.GetPosition().x, y, m_Velocity.GetPosition().z);
	}
	else if (y == 0)
	{
		m_Velocity.SetPosition(x, m_Velocity.GetPosition().y, m_Velocity.GetPosition().z);
	}
}


dae::Transform dae::GameObject::GetVelocity() const
{
	return m_Velocity;
}

void dae::GameObject::ResetVelocity()
{
	m_Velocity.SetPosition(0, 0, 0);
}



dae::GameObject::~GameObject()
{
	delete m_pRenderComponent;
	m_pRenderComponent = nullptr;
	
	for (auto pBaseComp : m_VectorpBComponents)
	{
		delete pBaseComp;
		pBaseComp = nullptr;
	}
	m_VectorpBComponents.clear();

	for (auto pPairComp : m_VectorCombinedComponents)
	{
		delete pPairComp.first;
		delete pPairComp.second;
		pPairComp.first = nullptr;
		pPairComp.second = nullptr;
	}
	m_VectorCombinedComponents.clear();
	
}
