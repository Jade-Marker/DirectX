camera = {}

cRotSpeed = 0.00125

function Start()
	camera = GetComponent(this, ComponentType.CAMERA);
end

function Update(deltaTime)
	if(GetKeyDown(Input.KEY_4)) then
		SetMainCamera(camera)
	end

	deltaX, deltaY = GetDeltaMousePos()
	SetRootActive = GetEntityComponent(this, parent:GetParent():GetParent(), ComponentType.CUSTOM_COMPONENT):GetFunction("SetRootActive")

	if(GetMainCamera() == camera) then
		SetRootActive(true)

		Position = parent:GetParent():GetTransform().Position
		Rotation = parent:GetParent():GetTransform().Rotation

		Rotation.y = Rotation.y - deltaX * cRotSpeed
		Rotation.z = Rotation.z + deltaY * cRotSpeed
	else
		SetRootActive(false)
	end
end