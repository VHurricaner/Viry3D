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

#include "memory/Ref.h"
#include "container/List.h"

namespace Viry3D
{
    class Material;
    class Camera;
    struct BufferObject;

    class Renderer
    {
    public:
        Renderer();
        virtual ~Renderer();
        virtual Ref<BufferObject> GetVertexBuffer() const = 0;
        virtual Ref<BufferObject> GetIndexBuffer() const = 0;
        virtual void GetIndexRange(int& index_offset, int& index_count) const = 0;
        virtual void Update();
        const Ref<Material>& GetMaterial() const { return m_material; }
        void SetMaterial(const Ref<Material>& material);
        void OnAddToCamera(Camera* camera);
        void OnRemoveFromCamera(Camera* camera);
        void MarkRendererOrderDirty();
        void MarkInstanceCmdDirty();

    private:
        Ref<Material> m_material;
        List<Camera*> m_cameras;
    };
}
