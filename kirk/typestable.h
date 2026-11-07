#pragma once
#include <cstdint>

namespace Types {
	namespace BasePart {
		inline uint32_t Primitive = 0;
		inline uint32_t Shape = 0;

		inline uint32_t start = 0;
		inline uint32_t end = 0;
	}

	namespace Camera {
		inline uint32_t Rotation = 0;
		inline uint32_t Position = 0;
		inline uint32_t FieldOfView = 0;
		inline uint32_t ViewportSize = 0;

		inline uint32_t start = 0;
		inline uint32_t end = 0;
	}

	namespace DataModel {
		inline uint32_t JobId = 0;
		inline uint32_t Workspace = 0;
		inline uint32_t GameId = 0;
		inline uint32_t GameLoaded = 0;

		inline uint32_t start = 0;
		inline uint32_t end = 0;
	}

	namespace FileMeshData {
		inline uint32_t Vertices = 0;
		inline uint32_t VerticesEnd = 0;
		inline uint32_t Faces = 0;
		inline uint32_t FacesEnd = 0;
		inline uint32_t AABBMin = 0;
		inline uint32_t AABBMax = 0;

		inline uint32_t start = 0;
		inline uint32_t end = 0;
	}

	namespace Humanoid {
		inline uint32_t Health = 0;
		inline uint32_t MaxHealth = 0;
		inline uint32_t RigType = 0;

		inline uint32_t start = 0;
		inline uint32_t end = 0;
	}

	namespace Instance {
		inline uint32_t ClassDescriptor = 0;
		inline uint32_t NameContainer = 0;
		inline uint32_t ChildrenContainer = 0;

		inline uint32_t start = 0;
		inline uint32_t end = 0;
	}

	namespace LRUNode {
		inline uint32_t Next = 0;
		inline uint32_t AssetID = 0;
		inline uint32_t CachedItem = 0;

		inline uint32_t start = 0;
		inline uint32_t end = 0;
	}

	namespace Player {
		inline uint32_t LocalPlayer = 0;
		inline uint32_t DisplayName = 0;
		inline uint32_t ModelInstance = 0;
		inline uint32_t AccountAge = 0;
		inline uint32_t TeamColor = 0;

		inline uint32_t start = 0;
		inline uint32_t end = 0;
	}

	namespace Primitive {
		inline uint32_t Validate = 0;
		inline uint32_t Rotation = 0;
		inline uint32_t Position = 0;
		inline uint32_t AssemblyLinearVelocity = 0;
		inline uint32_t Size = 0;
		inline uint32_t Parent = 0;

		inline uint32_t start = 0;
		inline uint32_t end = 0;
	}

	namespace Workspace {
		inline uint32_t World = 0;
		inline uint32_t CurrentCamera = 0;

		inline uint32_t start = 0;
		inline uint32_t end = 0;
	}
}