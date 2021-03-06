﻿#pragma once
#include "RenderComponent.h"


namespace dae
{
	class Texture2D;
	class TextureComponent final : public RenderComponent
	{
	public:
		TextureComponent(const std::string& filename);
		TextureComponent(const std::string& filename,float scale);
		void Render(float x, float y) const override;
		void Update(const std::string& string) override;
		float GetWidth();
		float GetHeight();

		~TextureComponent() = default;
		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) = delete;
	private:

		std::shared_ptr<Texture2D> m_Texture;
		std::string m_FileName;

		float m_Width;
		float m_Height;
	

	};
}