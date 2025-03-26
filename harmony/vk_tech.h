#pragma once
#include "lvk/lvk.h"

namespace harmony
{
	namespace VkTech
	{
        template<size_t ClearValueCount>
		void ClearRenderPass(
            lvk::VkState& vk, VkCommandBuffer& cmd, uint32_t frameIndex, 
            VkRenderPass& rp, VkFramebuffer& fb, VkExtent2D extent, lvk::Array<VkClearValue, ClearValueCount>& clearValues)
		{
            lvk::debug::BeginDebugMarker(cmd, "Clear Swapchain");

            VkRenderPassBeginInfo renderPassInfo{};
            renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
            renderPassInfo.renderPass = rp;
            renderPassInfo.framebuffer = fb;
            renderPassInfo.renderArea.offset = { 0,0 };
            renderPassInfo.renderArea.extent = extent;

            renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
            renderPassInfo.pClearValues = clearValues.data();

            vkCmdBeginRenderPass(cmd, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
            vkCmdEndRenderPass(cmd);
            lvk::debug::EndDebugMarker(cmd);
		}
	}
}