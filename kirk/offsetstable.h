#pragma once

#include <windows.h>

namespace Offsets {
    namespace BasePart {
        inline uintptr_t Primitive = 0;
        inline uintptr_t Shape = 0;
    }

    namespace CachedItem {
        inline uintptr_t FileMeshData = 0;
    }

    namespace Camera {
        inline uintptr_t Rotation = 0;
        inline uintptr_t Position = 0;
        inline uintptr_t FieldOfView = 0;
        inline uintptr_t ViewportSize = 0;
    }

    namespace DataModel {
        inline uintptr_t JobId = 0;
        inline uintptr_t Workspace = 0;
        inline uintptr_t GameId = 0;
        inline uintptr_t GameLoaded = 0;
    }

    namespace FakeDataModel {
        inline uintptr_t RealDataModel = 0;
        inline uintptr_t Pointer = 0;
    }

    namespace FileMeshData {
        inline uintptr_t Vertices = 0;
        inline uintptr_t VerticesEnd = 0;
        inline uintptr_t Faces = 0;
        inline uintptr_t FacesEnd = 0;
        inline uintptr_t AABBMin = 0;
        inline uintptr_t AABBMax = 0;
    }

    namespace Humanoid {
        inline uintptr_t Health = 0;
        inline uintptr_t MaxHealth = 0;
        inline uintptr_t RigType = 0;
    }

    namespace Instance {
        inline uintptr_t ClassDescriptor = 0;
        inline uintptr_t ClassName = 0;

        inline uintptr_t NameContainer = 0;
        inline uintptr_t Name = 0;

        inline uintptr_t ChildrenContainer = 0;
        inline uintptr_t ChildrenEnd = 0;

        inline uintptr_t Parent = 0;
    }

    namespace LRUHolder {
        inline uintptr_t MemEnforcedLRUCache = 0;
    }

    namespace LRUNode {
        inline uintptr_t Next = 0;
        inline uintptr_t AssetID = 0;
        inline uintptr_t CachedItem = 0;
    }

    namespace MemEnforcedLRUCache {
        inline uintptr_t Head = 0;
    }

    namespace MeshContentProvider {
        inline uintptr_t LRUHolder = 0;
    }

    namespace Player {
        inline uintptr_t LocalPlayer = 0;
        inline uintptr_t DisplayName = 0;
        inline uintptr_t ModelInstance = 0;
        inline uintptr_t AccountAge = 0;
        inline uintptr_t TeamColor = 0;
    }

    namespace Primitive {
        inline uintptr_t Validate = 0;
        inline uintptr_t Rotation = 0;
        inline uintptr_t Position = 0;
        inline uintptr_t AssemblyLinearVelocity = 0;
        inline uintptr_t Size = 0;
        inline uintptr_t Owner = 0;
    }

    namespace Workspace {
        inline uintptr_t World = 0;
        inline uintptr_t CurrentCamera = 0;
    }
}