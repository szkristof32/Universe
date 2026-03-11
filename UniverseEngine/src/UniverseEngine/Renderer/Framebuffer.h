#pragma once

namespace UniverseEngine {

	enum class FramebufferAttachmentType
	{
		None = 0,
		ColourAttachment, DepthAttachment
	};

	struct FramebufferSpecification
	{
		uint32_t Width = 1;
		uint32_t Height = 1;
		glm::vec4 ClearColour = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

		std::vector<FramebufferAttachmentType> Attachments;
	};

	class Framebuffer
	{
	public:
		Framebuffer(const FramebufferSpecification& spec);
		~Framebuffer();

		void Bind() const;
		void Unbind(uint32_t width, uint32_t height);

		void Resize(uint32_t width, uint32_t height);

		FramebufferSpecification& GetSpec() { return m_Spec; }
		const FramebufferSpecification& GetSpec() const { return m_Spec; }

		uint32_t GetColourAttachment() const { return m_ColourAttachments[0]; }

		void Invalidate();
	private:
		void Destroy();
	private:
		FramebufferSpecification m_Spec;

		uint32_t m_Framebuffer = 0;
		std::vector<uint32_t> m_ColourAttachments;
		uint32_t m_DepthAttachment = 0;
	};

}
