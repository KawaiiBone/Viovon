#include "MiniginPCH.h"
#include "GameObject.h"
#include "ComponentsHeaders.h"
#include  "Observer.h"

dae::GameObject::GameObject(float x, float y)
	:m_pRenderComponent{ nullptr }, m_VectorpBComponents{  }, m_IsDead{ false }, m_Velocity{ 0,0,0 }, m_VectorCombinedComponents{}
{
	m_Pos.SetPosition(x, y, 0.0f);
}

dae::GameObject::GameObject(float x, float y, std::shared_ptr<RenderComponent> pRender)
	:m_pRenderComponent{ pRender }, m_VectorpBComponents{  }, m_IsDead{ false }, m_Velocity{0,0,0}, m_VectorCombinedComponents{}
{
	
	m_Pos.SetPosition(x, y, 0.0f);
}

dae::GameObject::GameObject(float x, float y, std::vector<BaseComponent*> bvComp, std::shared_ptr<RenderComponent> pRender)
	: m_pRenderComponent{ pRender }, m_VectorpBComponents{ bvComp }, m_IsDead{ false }, m_Velocity{ 0,0,0 }, m_VectorCombinedComponents{}
{
	m_Pos.SetPosition(x, y, 0.0f);
}

dae::GameObject::GameObject(float x, float y, BaseComponent* bvComp, std::shared_ptr<RenderComponent> pRender)
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

void dae::GameObject::AddRenderComponent(std::shared_ptr<RenderComponent> RenderComponent)
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




bool dae::GameObject::IsDead() const
{
	return m_IsDead;
}

void dae::GameObject::Die()
{
	m_IsDead = true;
	
}






void dae::GameObject::SetPosition(float x, float y)
{
	m_Pos.SetPosition(x, y, m_Pos.GetPosition().z);
}

dae::Transform dae::GameObject::GetPosition() const
{
	return m_Pos;
}




dae::GameObject::~GameObject()
{

	
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
