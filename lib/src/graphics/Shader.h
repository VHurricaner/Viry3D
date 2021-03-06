/*
* Viry3D
* Copyright 2014-2018 by Stack - stackos@qq.com
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#pragma once

#include "Display.h"
#include "RenderState.h"
#include "string/String.h"
#include "container/List.h"
#include "container/Map.h"

namespace Viry3D
{
    class Shader
    {
    public:
		static Ref<Shader> Find(const String& name);
		static void AddCache(const String& name, const Ref<Shader>& shader);
		static void Done();
        static void OnRenderPassDestroy(VkRenderPass render_pass);
        Shader(
            const String& vs_predefine,
            const Vector<String>& vs_includes,
            const String& vs_source,
            const String& fs_predefine,
            const Vector<String>& fs_includes,
            const String& fs_source,
            const RenderState& render_state);
        ~Shader();
        const RenderState& GetRenderState() const { return m_render_state; }
        VkPipeline GetPipeline(VkRenderPass render_pass, bool color_attachment, bool depth_attachment);
        void CreateDescriptorSets(Vector<VkDescriptorSet>& descriptor_sets, Vector<UniformSet>& uniform_sets);
        VkPipelineLayout GetPipelineLayout() const { return m_pipeline_layout; }

    private:
        static List<Shader*> m_shaders;
		static Map<String, Ref<Shader>> m_shader_cache;
        RenderState m_render_state;
        VkShaderModule m_vs_module;
        VkShaderModule m_fs_module;
        Vector<UniformSet> m_uniform_sets;
        VkPipelineCache m_pipeline_cache;
        Vector<VkDescriptorSetLayout> m_descriptor_layouts;
        VkPipelineLayout m_pipeline_layout;
        VkDescriptorPool m_descriptor_pool;
        Map<VkRenderPass, VkPipeline> m_pipelines;
    };
}
