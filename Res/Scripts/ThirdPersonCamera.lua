camera = {}

cRotSpeed = 0.00125

EulerRotation = {}

function Start()
	camera = GetComponent(this, ComponentType.CAMERA);

	EulerRotation = Vector3D(0,0,0)
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
		
		EulerRotation = EulerRotation + Vector3D(0, deltaX * cRotSpeed, deltaY * cRotSpeed)

		parent:GetParent():GetTransform().Rotation = Quaternion.EulerToQuaternion(EulerRotation.x, EulerRotation.y, EulerRotation.z)
	else
		SetRootActive(false)
	end
end