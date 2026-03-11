#include "pch.h"
#include "Framebuffer.h"

#include <glad/gl.h>

namespace UniverseEngine {

	static const uint32_t s_MaxFramebufferSize = 8192;

	Framebuffer::Framebuffer(const FramebufferSpecification& spec)
		: m_Spec(spec)
	{
		Invalidate();
	}

	Framebuffer::~Framebuffer()
	{
		Destroy();
	}

	void Framebuffer::Bind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffer);
		glViewport(0, 0, m_Spec.Width, m_Spec.Height);
		glClearColor(m_Spec.ClearColour.r, m_Spec.ClearColour.g, m_Spec.ClearColour.b, m_Spec.ClearColour.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Framebuffer::Unbind(uint32_t width, uint32_t height)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, width, height);
	}

	void Framebuffer::Resize(uint32_t width, uint32_t height)
	{
		if (width == 0 || height == 0 || width > s_MaxFramebufferSize || height > s_MaxFramebufferSize)
		{
			std::cerr << "Attempted to resize framebuffer to " << width << "," << height << "\n";
			return;
		}
		m_Spec.Width = width;
		m_Spec.Height = height;

		Invalidate();
	}

	void Framebuffer::Invalidate()
	{
		Destroy();

		glCreateFramebuffers(1, &m_Framebuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffer);

		m_ColourAttachments.reserve(m_Spec.Attachments.size());

		for (const auto& attachment : m_Spec.Attachments)
		{
			if (attachment == FramebufferAttachmentType::ColourAttachment)
			{
				uint32_t colourAttachment;
				glCreateTextures(GL_TEXTURE_2D, 1, &colourAttachment);
				glBindTexture(GL_TEXTURE_2D, colourAttachment);

				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Spec.Width, m_Spec.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

				glTextureParameteri(colourAttachment, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTextureParameteri(colourAttachment, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTextureParameteri(colourAttachment, GL_TEXTURE_WRAP_R, GL_REPEAT);
				glTextureParameteri(colourAttachment, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTextureParameteri(colourAttachment, GL_TEXTURE_WRAP_T, GL_REPEAT);

				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + (uint32_t)m_ColourAttachments.size(),
									   GL_TEXTURE_2D, colourAttachment, 0);

				m_ColourAttachments.emplace_back(colourAttachment);
			}
			else if (attachment == FramebufferAttachmentType::DepthAttachment)
			{
				glCreateTextures(GL_TEXTURE_2D, 1, &m_DepthAttachment);
				glBindTexture(GL_TEXTURE_2D, m_DepthAttachment);

				glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, m_Spec.Width, m_Spec.Height);

				glTextureParameteri(m_DepthAttachment, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTextureParameteri(m_DepthAttachment, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTextureParameteri(m_DepthAttachment, GL_TEXTURE_WRAP_R, GL_REPEAT);
				glTextureParameteri(m_DepthAttachment, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTextureParameteri(m_DepthAttachment, GL_TEXTURE_WRAP_T, GL_REPEAT);

				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_DepthAttachment, 0);
			}
		}

		assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void Framebuffer::Destroy()
	{
		glDeleteFramebuffers(1, &m_Framebuffer);

		glDeleteTextures((GLsizei)m_ColourAttachments.size(), m_ColourAttachments.data());
		glDeleteTextures(1, &m_DepthAttachment);

		m_ColourAttachments.clear();
		m_DepthAttachment = 0;
	}

}
