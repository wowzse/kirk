#include "fields.h"

static std::unordered_map<std::string, size_t> typeSizes{
		{ "unsigned __int64", 8 },
		{ "unknown", 8 },
		{ "string", 8 },
		{ "double", 8 },
		{ "int", 4 },
		{ "float", 4 },
		{ "short", 2 },
		{ "bool", 1 },
		{ "BYTE", 1 },
		{ "unsigned char", 1 },
		{ "Vector2", 8 },
		{ "Vector3", 12 },
		{ "Matrix3x3", 36 },
		{ "ViewMatrix_t", 64 },
		{ "Color3", 12 },
		{ "ColorUint_8", 3 },
		{ "UDim2", 16 }
};

static void construct(const std::string& name, const TypeDef& def) {
	TypeMap::types.emplace(name, def);
}

void TypeDef::load(nlohmann::json& o, nlohmann::json& t) {
	for (auto& field : fields) {
		uintptr_t offset = o[field.first];
		*field.second.offset = offset;
		if (offset > *start) *start = offset;

		if (!field.second.type) continue;

		uint32_t typeSize = typeSizes[t[field.first]];
		*field.second.type = typeSize;
		auto fin = offset + typeSize;
		if (fin > *end) *end = fin;
	}
}

void TypeMap::loadTypesMap(nlohmann::json& o, nlohmann::json& t) {
	for (auto& type : TypeMap::types) {
		type.second.load(o[type.first], t[type.first]);
	}
}

void TypeMap::initTypes() {
	construct("FakeDataModel", TypeDef{
		{
			{ "Pointer", Field { &Offsets::FakeDataModel::Pointer } },
			{ "RealDataModel", Field { &Offsets::FakeDataModel::RealDataModel } }
		}
		});

	construct("DataModel", TypeDef{
		{
			{ "JobId", Field { &Offsets::DataModel::JobId, &Types::DataModel::JobId } },
			{ "GameLoaded", Field { &Offsets::DataModel::GameLoaded, &Types::DataModel::GameLoaded } },
			{ "Workspace", Field { &Offsets::DataModel::Workspace, &Types::DataModel::Workspace } },
			{ "GameId", Field { &Offsets::DataModel::GameId, &Types::DataModel::GameId } }
		},
		&Types::DataModel::start,
		&Types::DataModel::end
		});

	construct("Instance", TypeDef{
		{
			{ "ClassDescriptor", Field { &Offsets::Instance::ClassDescriptor, &Types::Instance::ClassDescriptor } },
			{ "ClassName", Field { &Offsets::Instance::ClassName } },
			{ "NameContainer", Field { &Offsets::Instance::NameContainer, &Types::Instance::NameContainer } },
			{ "Name", Field { &Offsets::Instance::Name } },
			{ "ChildrenStart", Field { &Offsets::Instance::ChildrenContainer, &Types::Instance::ChildrenContainer } },
			{ "ChildrenEnd", Field { &Offsets::Instance::ChildrenEnd } },
			{ "Parent", Field { &Offsets::Instance::Parent } }
		},
		&Types::Instance::start,
		&Types::Instance::end
		});

	construct("Primitive", TypeDef{
		{
			{ "Position", Field { &Offsets::Primitive::Position, &Types::Primitive::Position } },
			{ "Validate", Field { &Offsets::Primitive::Validate, &Types::Primitive::Validate } },
			{ "Size", Field { &Offsets::Primitive::Size, &Types::Primitive::Size } },
			{ "Rotation", Field { &Offsets::Primitive::Rotation, &Types::Primitive::Rotation } },
			{ "AssemblyLinearVelocity", Field { &Offsets::Primitive::AssemblyLinearVelocity, &Types::Primitive::AssemblyLinearVelocity } }
		},
		&Types::Primitive::start,
		&Types::Primitive::end
		});

	construct("BasePart", TypeDef{
		{
			{ "Primitive", Field { &Offsets::BasePart::Primitive, &Types::BasePart::Primitive } },
			{ "Shape", Field { &Offsets::BasePart::Shape, &Types::BasePart::Shape } }
		},
		&Types::BasePart::start,
		&Types::BasePart::end
		});

	construct("Player", TypeDef{
		{
			{ "LocalPlayer", Field { &Offsets::Player::LocalPlayer, &Types::Player::LocalPlayer } },
			{ "DisplayName", Field { &Offsets::Player::DisplayName, &Types::Player::DisplayName } },
			{ "ModelInstance", Field { &Offsets::Player::ModelInstance, &Types::Player::ModelInstance } },
			{ "TeamColor", Field { &Offsets::Player::TeamColor, &Types::Player::TeamColor } },
			{ "AccountAge", Field { &Offsets::Player::AccountAge, &Types::Player::AccountAge } }
		},
		&Types::Player::start,
		&Types::Player::end
		});

	construct("Camera", TypeDef{
		{
			{ "Position", Field { &Offsets::Camera::Position, &Types::Camera::Position } },
			{ "Rotation", Field { &Offsets::Camera::Rotation, &Types::Camera::Rotation } },
			{ "FieldOfView", Field { &Offsets::Camera::FieldOfView, &Types::Camera::FieldOfView } },
			{ "ViewportSize", Field { &Offsets::Camera::ViewportSize, &Types::Camera::ViewportSize } }
		},
		&Types::Camera::start,
		&Types::Camera::end
		});

	construct("Workspace", TypeDef{
		{
			{ "World", Field { &Offsets::Workspace::World, &Types::Workspace::World } },
			{ "CurrentCamera", Field { &Offsets::Workspace::CurrentCamera, &Types::Workspace::CurrentCamera } }
		},
		&Types::Workspace::start,
		&Types::Workspace::end
		});

	construct("Humanoid", TypeDef{
		{
			{ "Health", Field { &Offsets::Humanoid::Health, &Types::Humanoid::Health } },
			{ "MaxHealth", Field { &Offsets::Humanoid::MaxHealth, &Types::Humanoid::MaxHealth } },
			{ "RigType", Field { &Offsets::Humanoid::RigType, &Types::Humanoid::RigType } }
		},
		&Types::Humanoid::start,
		&Types::Humanoid::end
		});

	construct("MeshContentProvider", TypeDef{
		{
			{ "LRUHolder", Field { &Offsets::MeshContentProvider::LRUHolder } }
		}
		});

	construct("LRUHolder", TypeDef{
		{
			{ "MemEnforcedLRUCache", Field { &Offsets::LRUHolder::MemEnforcedLRUCache } }
		}
		});

	construct("MemEnforcedLRUCache", TypeDef{
		{
			{ "Head", Field { &Offsets::MemEnforcedLRUCache::Head } }
		}
		});

	construct("LRUNode", TypeDef{
		{
			{ "Next", Field { &Offsets::LRUNode::Next, &Types::LRUNode::Next } },
			{ "AssetID", Field { &Offsets::LRUNode::AssetID, &Types::LRUNode::AssetID } },
			{ "CachedItem", Field { &Offsets::LRUNode::CachedItem, &Types::LRUNode::CachedItem } }
		},
		&Types::LRUNode::start,
		&Types::LRUNode::end
		});

	construct("CachedItem", TypeDef{
		{
			{ "FileMeshData", Field { &Offsets::CachedItem::FileMeshData } }
		}
		});

	construct("FileMeshData", TypeDef{
		{
			{ "AABBMin", Field { &Offsets::FileMeshData::AABBMin, &Types::FileMeshData::AABBMin } },
			{ "AABBMax", Field { &Offsets::FileMeshData::AABBMax, &Types::FileMeshData::AABBMax } },
			{ "Vertices", Field { &Offsets::FileMeshData::Vertices, &Types::FileMeshData::Vertices } },
			{ "VerticesEnd", Field { &Offsets::FileMeshData::VerticesEnd, &Types::FileMeshData::VerticesEnd } },
			{ "Faces", Field { &Offsets::FileMeshData::Faces, &Types::FileMeshData::Faces } },
			{ "FacesEnd", Field { &Offsets::FileMeshData::FacesEnd, &Types::FileMeshData::FacesEnd } }
		},
		&Types::FileMeshData::start,
		&Types::FileMeshData::end
		});
}